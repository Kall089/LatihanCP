"""Build self-contained Indonesian CP lessons from explicitly authored specs.

No generated answer is inferred from a reference solution: authors supply
sample/test outputs and are responsible for independent oracle verification.
"""
from pathlib import Path
import json
import re
from urllib.parse import quote

CP_ROOT = Path(__file__).resolve().parents[1]
STARTER = '''#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <queue>
#include <numeric>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // TODO: Baca input sesuai format soal.
    // TODO: Tentukan invariant/state, lalu implementasikan algoritma.
    // TODO: Cetak jawaban dan jalankan test case.
    return 0;
}
'''

def _nl(text):
    return str(text).strip() + '\n'

def statement(p, number, kind='Exercise'):
    text = f"# {kind} {number} — {p['title']}\n\n"
    text += f"**Tingkat:** {p.get('level', 'Menengah')}  \n"
    text += f"**Batas waktu:** {p.get('time_limit', '2 detik')} · **Memori:** {p.get('memory_limit', '256 MB')}\n\n"
    for name, key in [('Cerita dan tugas','statement'),('Format input','input'),('Format output','output'),('Batasan','constraints')]:
        text += f"## {name}\n\n{p[key].strip()}\n\n"
    for i,(inp,out) in enumerate(p['samples'],1):
        text += f"## Contoh {i}\n\nInput:\n```text\n{_nl(inp)}```\n\nOutput:\n```text\n{_nl(out)}```\n\n"
    if p.get('sample_explanation'):
        text += f"## Penjelasan contoh\n\n{p['sample_explanation'].strip()}\n\n"
    if p.get('hint'):
        text += '<details><summary>Petunjuk bertahap</summary>\n\n' + p['hint'].strip() + '\n\n</details>\n'
    return text

def write_day(*, day, title, ppt, objectives, theory, problems, tasks,
              prerequisites='', template=None):
    """See README_AUTHORING.md for the small, stable spec schema."""
    assert len(problems) >= 3 and len(tasks) >= 3
    folder = CP_ROOT / f'Day-{day} ({title})'
    existing = list(CP_ROOT.glob(f'Day-{day} (*)'))
    if existing and (existing != [folder] or not (folder/'training.json').exists()):
        raise FileExistsError(f'Refusing to replace an existing user lesson: {existing}')
    for sub in ['teori','latihan','solusi','tugas','template','testcases']:
        (folder/sub).mkdir(parents=True,exist_ok=True)
    sources = [ppt] if isinstance(ppt,str) else list(ppt)
    source_links = []
    for src in sources:
        p = Path(src)
        if str(p).startswith('CP/'):
            p = Path(*p.parts[1:])
        if not (CP_ROOT/p).exists():
            raise FileNotFoundError(CP_ROOT/p)
        source_links.append(f'- [{p.name}](../{quote(str(p))})')
    (folder/'teori'/f'Day_{day}_Teori_Lengkap.md').write_text(
        f'# Day {day} — {title}\n\n**Prasyarat:** {prerequisites or "Lihat urutan ROADMAP_CP.md."}\n\n'
        + theory.strip()+'\n',encoding='utf-8')
    (folder/'template'/'template.cpp').write_text(template or STARTER,encoding='utf-8')
    meta={'version':1,'day':day,'title':title,'sources':sources,'exercises':[],'tasks':len(tasks)}
    exercise_links=[]
    editorial=f'# Pembahasan Day {day}\n\nBaca setelah mencoba soal selama 30–45 menit.\n\n'
    test_notes='# Peta test case\n\nSetiap exercise memiliki direktori sendiri. Nama kasus menjelaskan tujuan pengujiannya.\n\n'
    for i,p in enumerate(problems,1):
        assert len(p['samples']) >= 3, (day,i,'need 3 samples')
        assert 'TODO' not in p['solution'], (day,i,'unfinished solution')
        body=statement(p,i)
        (folder/'latihan'/f'exercise_{i}.md').write_text(body,encoding='utf-8')
        (folder/'latihan'/f'exercise_{i}.cpp').write_text('/*\n'+body.replace('*/','* /')+'\n*/\n\n'+STARTER,encoding='utf-8')
        explanation=p['explanation'].strip()
        complexity=p['complexity'].strip()
        (folder/'solusi'/f'solution_{i}.cpp').write_text(
            f"/*\n{p['title']}\n\n{explanation}\n\nKompleksitas: {complexity}\n*/\n\n"+_nl(p['solution']),encoding='utf-8')
        editorial += f"## {i}. {p['title']}\n\n{explanation}\n\n**Kompleksitas:** {complexity}\n\n"
        exercise_links.append(f"{i}. [{p['title']}](latihan/exercise_{i}.md) — {p.get('level','Menengah')}")
        dest=folder/'testcases'/f'exercise_{i}';dest.mkdir(exist_ok=True)
        cases=[(f'sample_{j}',a,b) for j,(a,b) in enumerate(p['samples'],1)]+list(p.get('tests',[]))
        assert len(cases)>=8,(day,i,'need at least 8 total tests including samples')
        seen=set()
        for name,inp,out in cases:
            assert re.fullmatch(r'[A-Za-z0-9_-]+',name) and name not in seen, name
            assert str(inp).strip() and str(out).strip(), (day,i,name,'empty input/output')
            seen.add(name)
            (dest/f'{name}.in').write_text(_nl(inp),encoding='utf-8')
            (dest/f'{name}.out').write_text(_nl(out),encoding='utf-8')
        compare=p.get('compare','tokens')
        assert compare in ('tokens','float')
        meta['exercises'].append({'id':i,'title':p['title'],'solution':f'solusi/solution_{i}.cpp',
            'source':f'latihan/exercise_{i}.cpp','tests':f'testcases/exercise_{i}',
            'compare':compare,'abs_tol':p.get('abs_tol',1e-6),'rel_tol':p.get('rel_tol',1e-6),
            'timeout':p.get('timeout',4),'case_count':len(cases)})
        test_notes+=f"## Exercise {i}: {p['title']}\n\n"+'\n'.join(f'- `{name}`' for name,_,_ in cases)+'\n\n'
    for i,p in enumerate(tasks,1):
        assert len(p['samples'])>=2,(day,i,'task needs 2 samples')
        body=statement(p,f'{i:02d}','Tugas')
        (folder/'tugas'/f'tugas_{i:02d}.cpp').write_text('/*\n'+body.replace('*/','* /')+'\n*/\n\n'+STARTER,encoding='utf-8')
    (folder/'solusi'/'PEMBAHASAN.md').write_text(editorial,encoding='utf-8')
    (folder/'testcases'/'README.md').write_text(test_notes,encoding='utf-8')
    (folder/'training.json').write_text(json.dumps(meta,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    readme=f'''# Day {day} — {title}

**Prasyarat:** {prerequisites or 'Ikuti urutan ROADMAP_CP.md.'}

## Target belajar

'''+ '\n'.join('- [ ] '+x for x in objectives)+f'''

## Alur pelatihan (2–3 jam)

1. Pelajari [teori](teori/Day_{day}_Teori_Lengkap.md) dan PPT sumber selama 35–45 menit. Tulis state atau invariant tanpa melihat catatan.
2. Kerjakan tiga latihan di bawah selama 75–100 menit. Gunakan file `.cpp` dengan nomor yang sama sebagai tempat jawaban.
3. Jalankan test case, baca [pembahasan](solusi/PEMBAHASAN.md) setelah mencoba, lalu implementasikan kembali bagian yang belum dikuasai.
4. Kerjakan tiga tugas mandiri di `tugas/` sebagai lanjutan atau sesi berikutnya. Catat kesalahan dan buat counterexample sendiri.

## Latihan bertingkat

'''+ '\n'.join(exercise_links)+f'''

## Menjalankan test case

Dari direktori `ComProgLearning`, periksa semua solusi rujukan hari ini:

```sh
python3 CP/_training_tools/judge.py --day {day}
```

Untuk memeriksa jawaban sendiri pada exercise 1:

```sh
python3 CP/_training_tools/judge.py --day {day} --exercise 1 --submission "CP/{folder.name}/latihan/exercise_1.cpp"
```

Runner memakai C++17 dan compiler yang tersedia (`CXX` dapat diatur). Semua file input/output tersedia di `testcases/`; [peta kasus](testcases/README.md) menjelaskan kasus yang dilatih. Tugas mandiri tidak memiliki solusi agar dapat dipakai untuk evaluasi.

## Materi PPT sumber

'''+ '\n'.join(source_links)+'''

Nomor folder mengikuti [ROADMAP](../../ROADMAP_CP.md). Nomor pada beberapa PPT lama berbeda; cocokkan judul materinya.

## Kriteria sebelum melanjutkan

- [ ] Ketiga latihan lolos test case.
- [ ] Dapat menjelaskan mengapa transisi/invariant benar dan menghitung kompleksitas.
- [ ] Dapat membuat satu kasus yang menggagalkan pendekatan keliru.
- [ ] Minimal satu tugas mandiri selesai tanpa membuka solusi latihan.
'''
    (folder/'README.md').write_text(readme,encoding='utf-8')
    return folder
