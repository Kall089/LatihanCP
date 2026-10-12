# Day 30 — Prefix Sum 2D & Submatrix Sum

## Tujuan Pembelajaran

Setelah menyelesaikan Day 30, kamu akan mampu:

- [ ] Memahami konsep dan intuisi **Prefix Sum 2D** (Inclusion-Exclusion Principle)
- [ ] Membangun tabel prefix sum 2D dari matriks dengan kompleksitas **O(N × M)**
- [ ] Menjawab **Submatrix Sum Query** dalam waktu **O(1)** per query
- [ ] Menangani koordinat **1-indexed** dengan padding baris/kolom 0
- [ ] Menyelesaikan masalah **Maximum Submatrix Sum** ukuran tetap (K × L)
- [ ] Menerapkan prefix sum 2D pada grid karakter (misal: menghitung frekuensi objek di area)
- [ ] Memahami dasar **Difference Array 2D** untuk range update offline

---

## Struktur Folder

```
Day-30 (Prefix Sum 2D)/
├── README.md               ← Panduan ini
├── teori/
│   └── Day_30_Teori_Lengkap.md     ← Teori lengkap (Markdown)
├── latihan/
│   ├── exercise_1.cpp   (Warm-up : Submatrix Sum Query Dasar)
│   ├── exercise_2.cpp   (Core    : Maximum Submatrix Sum K × L)
│   ├── exercise_3.cpp   (Core    : Counting Trees di Grid / Forest Queries)
│   ├── exercise_4.cpp   (Challenge: Maximum Submatrix Sum Ukuran Bebas)
│   ├── exercise_5.cpp   (Challenge: Difference Array 2D / Range Update)
│   └── exercise_6.cpp   (Contest : Count Submatrices dengan Jumlah = K)
├── solusi/
│   ├── solution_1.cpp   ← Solusi exercise_1
│   ├── solution_2.cpp   ← Solusi exercise_2
│   ├── solution_3.cpp   ← Solusi exercise_3
│   ├── solution_4.cpp   ← Solusi exercise_4
│   ├── solution_5.cpp   ← Solusi exercise_5
│   └── solution_6.cpp   ← Solusi exercise_6
├── tugas/
│   ├── tugas_01.cpp     through   tugas_15.cpp
└── template/
    └── template.cpp     ← Starter template Prefix Sum 2D
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori Lengkap
Buka `teori/Day_30_Teori_Lengkap.md` untuk mempelajari konsep inclusion-exclusion 2D, formula build, dan formula query.

### Langkah 2 — Pelajari Template
Buka `template/template.cpp` untuk melihat implementasi baku prefix sum 2D dan difference array 2D.

### Langkah 3 — Kerjakan Latihan (Progressive)
```bash
g++ -O2 -std=c++17 latihan/exercise_1.cpp -o latihan/exercise_1
./latihan/exercise_1
```

### Langkah 4 — Cek Solusi (jika stuck > 30 menit)
Bandingkan kodinganmu dengan file di folder `solusi/`.

### Langkah 5 — Kerjakan 15 Tugas Mandiri
Kerjakan `tugas_01.cpp` hingga `tugas_15.cpp` untuk menguji pemahaman dari level Easy hingga Hard.

---

## Quick Reference — Cheatsheet Prefix Sum 2D

```
Prefix Sum 2D (Inclusion-Exclusion):
  • psum[i][j] = A[i][j] + psum[i-1][j] + psum[i][j-1] - psum[i-1][j-1]
  • Query(r1, c1, r2, c2) = psum[r2][c2] - psum[r1-1][c2] - psum[r2][c1-1] + psum[r1-1][c1-1]

Kompleksitas:
  • Build : O(N × M)
  • Query : O(1)
  • Space : O(N × M)

Trik Penting:
  ✓ Gunakan 1-indexed (padding baris 0 & kolom 0 bernilai 0)
  ✓ Perhatikan overflow! Gunakan `long long` jika elemen matriks / sum > 2 × 10^9
  ✓ Pastikan r1 <= r2 dan c1 <= c2
```

---

## Soal Online Judge Rekomendasi

### CSES Problem Set
- [Forest Queries](https://cses.fi/problemset/task/1652) — Klasik Prefix Sum 2D pada grid karakter

### LeetCode
- [304. Range Sum Query 2D - Immutable](https://leetcode.com/problems/range-sum-query-2d-immutable/)
- [1314. Matrix Block Sum](https://leetcode.com/problems/matrix-block-sum/)

### Codeforces
- [CF 611C - New Year and Domino](https://codeforces.com/problemset/problem/611/C)
- [CF 1722D - Line](https://codeforces.com/problemset/problem/1722/D)

### AtCoder
- [ABC106D - AtCoder Express 2](https://atcoder.jp/contests/abc106/tasks/abc106_d)

---

## Checklist Penyelesaian

- [ ] Membaca materi teori di `teori/Day_30_Teori_Lengkap.md`
- [ ] Menyelesaikan `exercise_1.cpp` (Query dasar)
- [ ] Menyelesaikan `exercise_2.cpp` (Submatriks K×L)
- [ ] Menyelesaikan `exercise_3.cpp` (Grid karakter / CSES Forest Queries)
- [ ] Menyelesaikan `exercise_4.cpp` (Max submatrix sum ukuran bebas)
- [ ] Menyelesaikan `exercise_5.cpp` (Difference array 2D)
- [ ] Menyelesaikan `exercise_6.cpp` (Submatriks dengan sum = K)
- [ ] Mengerjakan minimal 10 dari 15 tugas mandiri
- [ ] Submit & AC soal CSES Forest Queries di online judge
