# Format generator

Import `write_day` dari `authoring`. Panggil dengan keyword:

```python
write_day(day=142, title="Top-Down vs Bottom-Up dan Desain State",
    ppt="CP/_PPT-09-DP/Day-142 - Top-Down, Bottom-Up & Desain State.pptx",
    prerequisites="Day 66 dan 141", objectives=["..."], theory="Markdown lengkap...",
    problems=[problem1, problem2, problem3], tasks=[task1, task2, task3])
```

`problem` adalah dict: `title`, `level`, `statement`, `input`, `output`, `constraints`,
`samples` (list tuple `(input_string,output_string)`, >=3), `solution` (full C++17),
`explanation` (ide + bukti kebenaran), `complexity`, `tests` (list tuple
`(case_name,input_string,output_string)`; >=5 selain tiga samples).
Optional: `hint`, `sample_explanation`, `compare` (`tokens` default / `float`),
`abs_tol`, `rel_tol`, `timeout` seconds default4, `time_limit` text default2 detik.

Task dict sama dengan problem tetapi tanpa solution/explanation/complexity/tests;
samples minimal2. Buat tugas berbeda, bukan sekadar ganti nama exercise.

Semua output sample dan testcase harus dihitung/ditinjau oleh oracle independen.
Simpan generator spesifikasi agar suite dapat diperluas. Jangan buat soal yang
punya banyak output valid tanpa tie-break atau checker yang sesuai.

Helper menghasilkan README, teori, exercise .md/.cpp, solusi, editorial,
tugas, template, testcases dan `training.json`. `ppt` juga menerima list string.
Folder existing yang tidak punya training.json ditolak untuk melindungi pekerjaan pengguna.
