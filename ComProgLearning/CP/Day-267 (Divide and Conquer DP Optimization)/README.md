# Day 267 — Divide and Conquer DP Optimization

> **Ide satu kalimat:** Memangkas pencarian titik transisi partisi kuadratik dari $\mathcal{O}(K \cdot N^2)$ menjadi $\mathcal{O}(K \cdot N \log N)$ dengan memanfaatkan sifat monotonisitas titik potong optimal ($opt[g][i] \le opt[g][i+1]$) melalui rekursi pembagian rentang.

---

## 🎯 Tujuan Pembelajaran

- [ ] Memahami bentuk standar rekurensi DP yang dapat dioptimasi dengan D&C:
  $$dp[g][i] = \min_{0 \le j < i} \{ dp[g-1][j] + \text{Cost}(j + 1, i) \}$$
- [ ] Memahami dan membuktikan **Quadrangle Inequality (Sifat Monge)**:
  $$\text{Cost}(a, c) + \text{Cost}(b, d) \le \text{Cost}(a, d) + \text{Cost}(b, c) \quad \text{untuk } a \le b \le c \le d$$
- [ ] Menguasai implementasi fungsi rekursif `compute(l, r, opt_l, opt_r)` dan pembuktian kompleksitas waktu $\mathcal{O}(K \cdot N \log N)$.
- [ ] Menerapkan D&C DP pada fungsi biaya $\mathcal{O}(1)$ (Prefix Sums 1D dan 2D).
- [ ] Menguasai teknik tingkat lanjut: **D&C DP dengan Stateful Sliding Window (Two Pointers / Mo-Style)** untuk fungsi biaya yang tidak dapat dihitung dalam $\mathcal{O}(1)$ (misal: pasangan kembar atau inversi).

---

## 📁 Struktur Folder

```
Day-267 (Divide and Conquer DP Optimization)/
├── README.md
├── teori/
│   └── Day_267_Teori_Lengkap.md    (Formulasi Matematis, Sifat Monge, Algoritma D&C, Analisis Kompleksitas, Gotchas)
├── latihan/
│   ├── exercise_1.cpp              (Konvoi Logistik Festival - Kuadrat Total Bobot)
│   ├── exercise_2.cpp              (Posko di Jalan Panjang - Jarak Absolut ke Median)
│   ├── exercise_3.cpp              (Bus Tambahan, Anggaran Tambahan - D&C DP Biaya Tetap per Bus)
│   ├── exercise_4.cpp              (Partisi Varians Minimum - Dual Prefix Sums)
│   ├── exercise_5.cpp              (Partisi Pasangan Kembar Minimum - Two-Pointer D&C DP)
│   └── exercise_6.cpp              (Gondola dan Indeks Ketidaksukaan - 2D Prefix Sums Ciel & Gondolas)
├── solusi/
│   ├── solution_1.cpp s.d. solution_6.cpp (Solusi optimal C++17 teruji AC dan terverifikasi)
├── tugas/
│   ├── tugas_01.cpp s.d. tugas_15.cpp     (15 tugas D&C DP terstandar lengkap dengan petunjuk)
└── template/
    └── template.cpp                (Boilerplate Master D&C DP: Standar O(1) dan Stateful Two Pointers)
```

---

## 🧭 Panduan Belajar

### Langkah 1 — Pelajari Teori D&C DP (20 menit)
Buka [Day_267_Teori_Lengkap.md](teori/Day_267_Teori_Lengkap.md):
1. **Bagian 1**: Pahami bentuk rekurensi partisi $dp[g][i]$ dan bottleneck $\mathcal{O}(K \cdot N^2)$.
2. **Bagian 2**: Kuasai syarat monotonisitas dan Quadrangle Inequality.
3. **Bagian 3**: Pahami alur pemanggilan rekursif `compute(l, mid-1, opt_l, best_k)` dan `compute(mid+1, r, best_k, opt_r)`.
4. **Bagian 4**: Pelajari checklist implementasi dan jebakan tie-breaking.

### Langkah 2 — Amati Master Template (10 menit)
Buka [template.cpp](template/template.cpp):
- `dnc_dp_standard(n, k, cost)`: Untuk evaluasi biaya $\mathcal{O}(1)$.
- `TwoPointerCost`: Untuk integrasi jendela geser ketika biaya dievaluasi secara dinamis.

### Langkah 3 — Kerjakan 6 Latihan Terpandu (120 menit)

| # | Judul Latihan | Konsep Kunci & Arketipe | Tingkat | Target Waktu |
|---|---|---|---|---|
| 1 | **Konvoi Logistik Festival** | Kuadrat Jumlah Subarray + 1D Prefix Sum | Sedang | 15 menit |
| 2 | **Posko di Jalan Panjang** | Penempatan Fasilitas Optimal ke Median | Sulit | 20 menit |
| 3 | **Bus Tambahan, Anggaran Tambahan** | D&C DP Multi-Layer dengan Penalti Linier Grup | Sulit | 20 menit |
| 4 | **Partisi Varians Minimum** | Varians Pairwise Difference + Dual Prefix Sums | Sulit | 25 menit |
| 5 | **Partisi Pasangan Kembar Minimum** | Stateful Two-Pointer Sliding Window D&C DP | Menantang | 25 menit |
| 6 | **Gondola & Indeks Ketidaksukaan** | Interaksi Pasangan Matriks + 2D Prefix Sums | Menantang | 25 menit |

### Langkah 4 — Uji Pemahaman Mandiri (15 Tugas Praktik)
- `tugas_01.cpp` s.d. `tugas_05.cpp`: Bobot biner 0/1, cetak seluruh biaya layer 1..K, partisi wajib pada gerbang B, kuadrat panjang dan bobot, biaya varians mandiri.
- `tugas_06.cpp` s.d. `tugas_10.cpp`: Panjang minimum segmen L, penempatan pemancar kuadrat jarak, gerbong kereta selisih absolut, kapasitas maksimum segmen R, penalti konveks kubik.
- `tugas_11.cpp` s.d. `tugas_15.cpp`: Pasangan inversi dengan Sliding Fenwick, konflik pleton submatriks 2D, rentang nilai selisih ekstrem, penjadwalan waktu kuadratik, partisi string frekuensi karakter.
