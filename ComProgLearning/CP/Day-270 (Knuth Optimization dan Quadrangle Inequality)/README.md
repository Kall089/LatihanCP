# Day 270 — Knuth Optimization dan Quadrangle Inequality

> **Ide satu kalimat:** Memanfaatkan sifat *Quadrangle Inequality* dan monotonisitas biaya interval untuk mempersempit ruang pencarian pemisah optimal $opt[i][j-1] \le opt[i][j] \le opt[i+1][j]$, mereduksi kompleksitas Range DP dari $\mathcal{O}(N^3)$ menjadi $\mathcal{O}(N^2)$ via pembuktian teleskopik.

---

## 🎯 Tujuan Pembelajaran

- [ ] Memahami formulasi Range DP klasik: $dp[i][j] = \min_{i \le k < j} \{ dp[i][k] + dp[k+1][j] \} + C(i, j)$.
- [ ] Memahami definisi formal *Quadrangle Inequality* (QI): $C(a, c) + C(b, d) \le C(a, d) + C(b, c)$ untuk $a \le b \le c \le d$.
- [ ] Memahami syarat monotonisitas interval: $C(b, c) \le C(a, d)$ untuk $[b, c] \subseteq [a, d]$.
- [ ] Menguasai Teorema Knuth-Yao: pembatasan $opt[i][j-1] \le opt[i][j] \le opt[i+1][j]$.
- [ ] Memahami pembuktian deret teleskopik yang menjamin total iterasi loop terdalam bernilai $\mathcal{O}(N^2)$.
- [ ] Menguasai teknik penggandaan array (*array doubling*) berukuran $2N$ untuk memecahkan variasi melingkar dalam $\mathcal{O}(N^2)$.
- [ ] Menguasai aplikasi Knuth Optimization pada masalah *Cutting Sticks* dan *Optimal Binary Search Tree* (OBST).

---

## 📁 Struktur Folder

```
Day-270 (Knuth Optimization dan Quadrangle Inequality)/
├── README.md
├── teori/
│   └── Day_270_Teori_Lengkap.md    (Formulasi Range DP, Syarat Quadrangle Inequality, Teorema Knuth-Yao, Bukti Teleskopik O(N^2), Perbandingan Optimasi DP)
├── latihan/
│   ├── exercise_1.cpp              (Peti yang Hanya Bisa Digabung dari Samping - Sequential Merge DP)
│   ├── exercise_2.cpp              (Memotong Pita Panggung - Cutting Sticks Reduction)
│   ├── exercise_3.cpp              (Lampion dalam Lingkaran - Circular Array Doubling)
│   ├── exercise_4.cpp              (Pohon Pencarian Biner Optimal - Classic OBST)
│   ├── exercise_5.cpp              (Pembangunan Rantai Menara Telekomunikasi - Range DP + Fixed Overhead)
│   └── exercise_6.cpp              (Penggabungan File Arsip dengan Faktor Kompresi - Scaled Costs)
├── solusi/
│   ├── solution_1.cpp s.d. solution_6.cpp (Solusi optimal C++17 teruji AC dan terverifikasi)
├── tugas/
│   ├── tugas_01.cpp s.d. tugas_15.cpp     (15 tugas Knuth DP terstandar lengkap dengan batasan dan petunjuk)
└── template/
    └── template.cpp                (Boilerplate Master Knuth: knuth_merge_dp, knuth_circular_dp, knuth_obst)
```

---

## 🧭 Panduan Belajar

### Langkah 1 — Pelajari Teori Knuth Optimization (20 menit)
Buka [Day_270_Teori_Lengkap.md](teori/Day_270_Teori_Lengkap.md):
1. **Bagian 1 & 2**: Pahami formulasi Range DP dan dua syarat wajib: Quadrangle Inequality dan Monotonisitas.
2. **Bagian 3 & 4**: Pelajari batas titik optimal $opt[i][j-1] \le opt[i][j] \le opt[i+1][j]$ dan pembuktian teleskopik $\mathcal{O}(N^2)$.
3. **Bagian 5**: Pahami matriks perbandingan antara Knuth Optimization, Divide and Conquer DP, CHT, dan Li Chao Tree.

### Langkah 2 — Amati Master Template (10 menit)
Buka [template.cpp](template/template.cpp):
- `knuth_merge_dp`: Penggabungan linier berurutan.
- `knuth_circular_dp`: Penggabungan melingkar dengan array doubling $2N$ dan batas `len <= N`.
- `knuth_obst`: Optimal Binary Search Tree dengan batas $l \le k \le r$.

### Langkah 3 — Kerjakan 6 Latihan Terpandu (120 menit)

| # | Judul Latihan | Konsep Kunci & Arketipe | Tingkat | Target Waktu |
|---|---|---|---|---|
| 1 | **Peti yang Hanya Bisa Digabung dari Samping** | Classic Sequential Merging Range DP $\mathcal{O}(N^2)$ | Sedang | 15 menit |
| 2 | **Memotong Pita Panggung** | Reduction of Cutting Sticks to Sequential Merging | Sedang | 20 menit |
| 3 | **Lampion dalam Lingkaran** | Circular Knuth DP via Array Doubling ($2N$) | Sulit | 20 menit |
| 4 | **Pohon Pencarian Biner Optimal** | Classic Donald Knuth OBST Formulation | Sulit | 25 menit |
| 5 | **Pembangunan Rantai Menara Telekomunikasi** | Range DP with Additive Base Cost $K$ | Sulit | 20 menit |
| 6 | **Penggabungan File Arsip dengan Faktor Kompresi** | Scaled Costs with Multiplicative Factor | Menantang | 20 menit |

### Langkah 4 — Uji Pemahaman Mandiri (15 Tugas Praktik)
- `tugas_01.cpp` s.d. `tugas_05.cpp`: Biaya alat tetap, memulihkan potongan awal, biaya seluruh subrentang, logistik gudang regional, pemotongan balok kayu.
- `tugas_06.cpp` s.d. `tugas_10.cpp`: OBST berbobot khusus, rantai kompresi citra satelit, konveyor tambang batubara, gelang energi melingkar, pemotongan pipa lepas pantai.
- `tugas_11.cpp` s.d. `tugas_15.cpp`: Dokumen cetak prioritas, spektrum radio, OBST akses gagal, ligasi DNA sintetis, pipa air melingkar.
