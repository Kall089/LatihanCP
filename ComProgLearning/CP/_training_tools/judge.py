#!/usr/bin/env python3
"""Portable C++17 judge for authored training packages (Python standard library)."""
from pathlib import Path
import argparse
import concurrent.futures
import json
import math
import os
import shlex
import shutil
import subprocess
import sys
import tempfile
import time

ROOT = Path(__file__).resolve().parents[1]

def equal_output(actual, expected, exercise):
    a,b=actual.split(),expected.split()
    if len(a)!=len(b): return False
    if exercise.get('compare','tokens')=='tokens': return a==b
    for x,y in zip(a,b):
        try: xf,yf=float(x),float(y)
        except ValueError:
            if x!=y: return False
            continue
        if not math.isfinite(xf) or not math.isfinite(yf): return False
        if not math.isclose(xf,yf,rel_tol=exercise.get('rel_tol',1e-6),abs_tol=exercise.get('abs_tol',1e-6)):
            return False
    return True

def check_one(job, compiler, submission=None, sanitize=False):
    folder,meta,e=job
    result={'day':meta['day'],'exercise':e['id'],'title':e['title'],'passed':0,'total':0,'failures':[]}
    source=Path(submission).resolve() if submission else folder/e['solution']
    tests=folder/e['tests']; inputs=sorted(tests.glob('*.in'))
    outputs={p.stem for p in tests.glob('*.out')}
    input_names={p.stem for p in inputs}
    if not inputs or outputs!=input_names or len(inputs)!=e['case_count']:
        result['failures'].append('Test suite invalid: missing/extra files or inconsistent case_count.')
        return result
    with tempfile.TemporaryDirectory(prefix='cp-judge-') as tmp:
        binary=Path(tmp)/'solution'
        flags=['-std=c++17','-O2','-Wall','-Wextra']
        if sanitize: flags+=['-fsanitize=address,undefined','-fno-omit-frame-pointer','-g']
        try:
            cp=subprocess.run(compiler+flags+[str(source),'-o',str(binary)],capture_output=True,text=True,timeout=90)
        except (OSError,subprocess.TimeoutExpired) as err:
            result['failures'].append(f'Compile error: {err}'); return result
        if cp.returncode:
            result['failures'].append('Compile error: '+cp.stderr[-6000:]); return result
        if cp.stderr.strip(): result['warnings']=cp.stderr[-6000:]
        result['total']=len(inputs)
        start=time.monotonic()
        for inp in inputs:
            expected=inp.with_suffix('.out').read_text()
            try:
                proc=subprocess.run([str(binary)],input=inp.read_text(),capture_output=True,text=True,
                    timeout=e.get('timeout',4)*(3 if sanitize else 1))
            except subprocess.TimeoutExpired:
                result['failures'].append(f'{inp.name}: TIME LIMIT'); continue
            if proc.returncode:
                result['failures'].append(f'{inp.name}: exit {proc.returncode}: {proc.stderr[:500]}')
            elif equal_output(proc.stdout,expected,e): result['passed']+=1
            else:
                result['failures'].append(f'{inp.name}: WRONG ANSWER expected={expected[:160]!r} actual={proc.stdout[:160]!r}')
        result['seconds']=round(time.monotonic()-start,3)
    return result

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--day',type=int,action='append',help='Select a day; can be repeated.')
    parser.add_argument('--all',action='store_true',help='Check all new lessons with training.json.')
    parser.add_argument('--exercise',type=int)
    parser.add_argument('--submission',help='Your C++ source; requires one --day and --exercise.')
    parser.add_argument('--jobs',type=int,default=4)
    parser.add_argument('--sanitize',action='store_true')
    parser.add_argument('--report',help='Write the full JSON report to this path.')
    args=parser.parse_args()
    if not args.all and not args.day: parser.error('Select --day NUMBER or --all.')
    if args.all and args.day: parser.error('Use --all or --day, not both.')
    if args.submission and (not args.day or len(args.day)!=1 or args.exercise is None or args.all):
        parser.error('--submission requires exactly one --day and --exercise.')
    if args.jobs<1: parser.error('--jobs must be positive.')
    compiler=shlex.split(os.environ.get('CXX',''))
    if not compiler:
        found=shutil.which('g++') or shutil.which('clang++')
        if not found: parser.error('Install a C++17 compiler or set CXX.')
        compiler=[found]
    jobs=[]; found_days=set()
    for manifest in sorted(ROOT.glob('Day-*/training.json')):
        meta=json.loads(manifest.read_text())
        if args.day and meta['day'] not in args.day: continue
        found_days.add(meta['day'])
        for ex in meta['exercises']:
            if args.exercise is None or args.exercise==ex['id']:
                jobs.append((manifest.parent,meta,ex))
    if args.day and set(args.day)-found_days:
        parser.error(f'No authored training package for days: {sorted(set(args.day)-found_days)}')
    if not jobs: parser.error('No matching exercise.')
    results=[]
    with concurrent.futures.ThreadPoolExecutor(max_workers=args.jobs) as pool:
        futures=[pool.submit(check_one,j,compiler,args.submission,args.sanitize) for j in jobs]
        for future in concurrent.futures.as_completed(futures):
            result=future.result(); results.append(result)
            status='PASS' if not result['failures'] else 'FAIL'
            print(f"{status} Day {result['day']} exercise {result['exercise']}: {result['passed']}/{result['total']}",flush=True)
            for failure in result['failures']: print('  '+failure,flush=True)
    results.sort(key=lambda r:(r['day'],r['exercise']))
    report={'compiler':compiler,'sanitizers':args.sanitize,'days':len(found_days),'exercises':len(results),
        'passed_cases':sum(r['passed'] for r in results),'total_cases':sum(r['total'] for r in results),
        'failed_exercises':sum(bool(r['failures']) for r in results),'results':results}
    if args.report:
        dest=Path(args.report);dest.parent.mkdir(parents=True,exist_ok=True)
        dest.write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n')
    print(f"{report['days']} days, {report['exercises']} exercises, {report['passed_cases']}/{report['total_cases']} cases; {report['failed_exercises']} failed exercises.")
    return 1 if report['failed_exercises'] else 0

if __name__=='__main__': sys.exit(main())
