# Day 152 — Rekonstruksi Jalur dan Penelusuran Jawaban DP

> **Ide satu kalimat:** Rekonstruksi jalur DP menelusuri mundur (*backtracking*) tabel dari state akhir optimal menuju base case (atau maju dengan Suffix DP) untuk menyusun rangkaian keputusan konkret yang menghasilkan nilai optimum.

---

## 🎯 Tujuan Pembelajaran

- [ ] Memahami perbedaan esensial antara DP Nilai Optimum (*Scalar DP*) dan DP Rekonstruksi (*Path/Solution DP*).
- [ ] Memahami mengapa **Rolling Array 1D tidak dapat digunakan** secara naif untuk rekonstruksi jalur (karena menimpa riwayat dependensi state).
- [ ] Menguasai **Pola 1 (Parent / Choice Array)** untuk merekonstruksi keputusan pada DP 1D, LIS, dan graf DAG.
- [ ] Menguasai **Pola 2 (Table Backtracking)** pada DP 2D (Knapsack 0/1, LCS, Grid Path) tanpa alokasi memori array jejak tambahan.
- [ ] Menguasai teknik **Suffix DP** untuk menyelesaikan masalah yang menuntut urutan keputusan leksikografis terkecil dari depan ke belakang.
- [ ] Menerapkan penanganan pemecah seri (*tie-breaker*) secara deterministik.
- [ ] Menyelesaikan 6 latihan bertingkat dan 15 tugas mandiri dengan C++17 optimal.

---

## 📁 Struktur Folder

```
Day-152 (Rekonstruksi Jalur dan Penelusuran Jawaban DP)/
├── README.md
├── teori/
│   └── Day_152_Teori_Lengkap.md   (Konsep 4 langkah, Pola Parent vs Backtracking, Suffix DP, Tie-Breaker)
├── latihan/
│   ├── exercise_1.cpp             (Rute Foto Pematang - Frog Jump Suffix Path Reconstruction)
│   ├── exercise_2.cpp             (Daftar Keping Terkecil - Coin Change Lexicographical)
│   ├── exercise_3.cpp             (Kurasi Paket Tepat Berat - Exact Knapsack 0/1 Decision String)
│   ├── exercise_4.cpp             (Rekonstruksi Subsekuens Bersama Terpanjang - LCS Reconstruction)
│   ├── exercise_5.cpp             (Penjelajah Labirin Grid Berbobot - Grid Min Path 'D'/'R')
│   └── exercise_6.cpp             (Rekonstruksi Subsekuens Naik Terpanjang - LIS Reconstruction)
├── solusi/
│   ├── solution_1.cpp s.d. solution_6.cpp (Solusi optimal C++17, verified AC)
├── tugas/
│   ├── tugas_01.cpp s.d. tugas_15.cpp     (15 tugas terstandar lengkap dengan petunjuk)
└── template/
    └── template.cpp               (Boilerplate Knapsack, LCS, Grid Path, LIS, Coin Change, Frog Jump)
```

---

## 🧭 Panduan Belajar

### Langkah 1 — Pelajari Teori (40 menit)
Buka [Day_152_Teori_Lengkap.md](teori/Day_152_Teori_Lengkap.md):
1. **Bagian 1 & 2**: Pelajari mengapa kita butuh rekonstruksi dan 4 langkah universal penelusuran mundur.
2. **Bagian 3**: Pahami perbedaan `Parent Array` vs `Table Backtracking`.
3. **Bagian 4**: Pelajari simulasi penelusuran mundur Knapsack 0/1 pada matriks $N \times W$.
4. **Bagian 5 & 6**: Kuasai rekonstruksi LCS dan teknik Suffix DP untuk leksikografis maju.
5. **Bagian 7**: Pahami 5 jebakan klasik rekonstruksi (rolling array, lupa reverse, off-by-one).

### Langkah 2 — Amati Template (10 menit)
Buka [template.cpp](template/template.cpp):
- Fungsi `reconstructKnapsack01(w, v, W)`
- Fungsi `reconstructLCS(s, t)`
- Fungsi `reconstructGridMinPath(grid)`
- Fungsi `reconstructLIS(a)`
- Fungsi `reconstructCoinChange(c, x)`

### Langkah 3 — Kerjakan 6 Latihan Bertingkat (120 menit)

| # | Judul Latihan | Konsep Kunci | Tingkat | Target Waktu |
|---|---|---|---|---|
| 1 | **Rute Foto Pematang** | Suffix DP 1D, Leksikografis Indeks Pos Maju | Mudah-Sedang | 15 menit |
| 2 | **Daftar Keping Terkecil** | Unbounded DP, Greedy-Forward Reconstruction | Sedang | 20 menit |
| 3 | **Kurasi Paket Tepat Berat** | Suffix 2D DP, Bitstring Keputusan 0/1 Leksikografis | Sedang-Menantang | 25 menit |
| 4 | **Rekonstruksi LCS Terpanjang** | 2D DP Table Backtracking, `reverse()` Hasil | Sedang | 20 menit |
| 5 | **Penjelajah Labirin Grid** | Grid Suffix DP, Langkah 'D' < 'R' | Sedang | 20 menit |
| 6 | **Rekonstruksi LIS Terpanjang** | Pola Parent Array, Rantai Pointer LIS | Sedang | 20 menit |

### Langkah 4 — Uji Mandiri (15 Tugas)
- `tugas_01.cpp` s.d. `tugas_05.cpp`: Rute grid D < R, potongan palindrom terawal, LIS indeks terkecil, knapsack barang terpilih, dan LCS leksikografis terkecil.
- `tugas_06.cpp` s.d. `tugas_10.cpp`: Operasi edit distance, jalur piramida angka, koin kasir bounded, rute lompatan katak K-langkah, dan substring palindrom terpanjang.
- `tugas_11.cpp` s.d. `tugas_15.cpp`: Subsekuens berulang terpanjang, partisi subset sama bobot, pembagian kata kamus (word break), penumpukan balok tertinggi, dan kurung MCM lengkap.

---

## 🔗 Tautan Latihan Online Judge

- [AtCoder Educational DP Contest F — LCS](https://atcoder.jp/contests/dp/tasks/dp_f)
- [LeetCode 300 — Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/)
- [LeetCode 64 — Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/)
- [LeetCode 72 — Edit Distance](https://leetcode.com/problems/edit-distance/)
- [LeetCode 140 — Word Break II](https://leetcode.com/problems/word-break-ii/)
- [LeetCode 416 — Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/)
