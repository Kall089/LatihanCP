# Day 144 — Coin Change Minimum dan Unbounded Knapsack

> **Ide satu kalimat:** Ketika barang atau koin tersedia tanpa batas, perbedaan antara $0/1$ Knapsack dan Unbounded Knapsack terletak pada **arah iterasi loop kapasitas** (Maju vs Mundur); buktikan mengapa Greedy gagal dan gunakan DP untuk optimasi global.

---

## 🎯 Tujuan Pembelajaran

- [ ] Memahami karakteristik masalah **Unbounded Knapsack** di mana setiap item dapat diambil berulang kali ($0, 1, 2, \dots$).
- [ ] Menguasai rekurens dan transisi **Coin Change Minimum** beserta penanganan inisialisasi tak terhingga (`INF`).
- [ ] Membuktikan secara formal mengapa pendekatan **Greedy gagal** pada sistem koin umum dan kapan DP wajib digunakan.
- [ ] Menguasai **Hukum Arah Loop (Forward vs Backward Loop)**: perbedaan mendasar loop maju (unbounded) vs loop mundur (0/1 knapsack).
- [ ] Mampu melakukan **rekonstruksi solusi** menggunakan pointer keputusan (`pick` / `parent array`) untuk mencetak koin-koin penyusun.
- [ ] Membedakan dengan tegas antara **Coin Combinations I (Permutasi)** dan **Coin Combinations II (Kombinasi)** melalui pengaturan urutan *nested loop*.
- [ ] Menyelesaikan 6 latihan bertingkat dan 15 tugas mandiri dengan C++17 optimal.

---

## 📁 Struktur Folder

```
Day-144 (Coin Change Minimum dan Unbounded Knapsack)/
├── README.md
├── teori/
│   └── Day_144_Teori_Lengkap.md   (Materi komprehensif, counterexample greedy, hukum arah loop, trace)
├── latihan/
│   ├── exercise_1.cpp             (Coin Change Minimum - CSES 1634 / LeetCode 322)
│   ├── exercise_2.cpp             (Unbounded Knapsack Klasik - Maksimum Nilai)
│   ├── exercise_3.cpp             (Rekonstruksi Koin Minimum - Decision Tracking)
│   ├── exercise_4.cpp             (Coin Combinations I - Banyak Cara Permutasi)
│   ├── exercise_5.cpp             (Coin Combinations II - Banyak Cara Kombinasi)
│   └── exercise_6.cpp             (Weighted Unbounded Knapsack - Biaya Transaksi)
├── solusi/
│   ├── solution_1.cpp s.d. solution_6.cpp (Solusi optimal, C++17, verified AC)
├── tugas/
│   ├── tugas_01.cpp s.d. tugas_15.cpp     (15 latihan mandiri dengan format standar)
└── template/
    └── template.cpp               (Boilerplate Coin Change Min, Unbounded Knapsack, Counting DP)
```

---

## 🧭 Panduan Belajar

### Langkah 1 — Pelajari Teori (45 menit)
Buka [Day_144_Teori_Lengkap.md](teori/Day_144_Teori_Lengkap.md):
1. **Bagian 1 & 2**: Pahami konsep persediaan tak terbatas dan counterexample koin $\{1, 3, 4\}$ nominal 6 yang membuktikan mengapa Greedy gagal.
2. **Bagian 3**: Kuasai **Hukum Arah Loop**: mengapa loop maju mengizinkan pengambilan berulang kali sedangkan loop mundur membatasi maksimal satu kali.
3. **Bagian 4 & 5**: Simak tabel trace step-by-step dan mekanisme array `pick` untuk rekonstruksi solusi.
4. **Bagian 6**: Pahami perbedaan urutan loop pada Coin Combinations I (Permutasi: nominal di luar) vs Coin Combinations II (Kombinasi: koin di luar).

### Langkah 2 — Amati Template (10 menit)
Buka [template.cpp](template/template.cpp):
- Fungsi `coinChangeMin(x, coins)`
- Fungsi `coinChangeWithReconstruct(x, coins)`
- Fungsi `unboundedKnapsackMax(W, wt, val)`
- Fungsi `unboundedKnapsackMinCost(W, wt, cost)`
- Fungsi `coinCombinationsPermutations(x, coins, mod)`
- Fungsi `coinCombinationsCombinations(x, coins, mod)`

### Langkah 3 — Kerjakan 6 Latihan Bertingkat (120 menit)

| # | Judul Latihan | Konsep Kunci | Tingkat | Target Waktu |
|---|---|---|---|---|
| 1 | **Penukaran Koin Minimum** | Bottom-Up 1D, Inisialisasi INF, Guard Overflow | Mudah | 15 menit |
| 2 | **Unbounded Knapsack Maksimum Nilai** | Forward Loop Capacity, 64-bit Accumulation | Sedang | 20 menit |
| 3 | **Rekonstruksi Koin Minimum** | Decision Tracking Array `pick[i]`, Backtracking | Sedang | 25 menit |
| 4 | **Coin Combinations I (Permutasi)** | Counting DP, Loop Nominal di LUAR, Modulo $10^9+7$ | Sedang | 20 menit |
| 5 | **Coin Combinations II (Kombinasi)** | Counting DP, Loop Koin di LUAR, Unbounded Forward | Sedang | 20 menit |
| 6 | **Penukaran Koin dengan Biaya Transaksi** | Weighted Unbounded Min Cost, Exact Target Target | Menantang | 25 menit |

### Langkah 4 — Uji & Evaluasi Mandiri (15 Tugas)
Kerjakan soal-soal di folder `tugas/` untuk memantapkan pemahaman:
- `tugas_01.cpp` s.d. `tugas_05.cpp`: Perfect squares, at-least-K target, permutasi lompatan, jangkauan kapasitas, dan Rod Cutting.
- `tugas_06.cpp` s.d. `tugas_10.cpp`: Word segmentation, batas banyak keping, kembalian minimum, Integer Break, dan Range Capacity.
- `tugas_11.cpp` s.d. `tugas_15.cpp`: Rekonstruksi leksikografis, exact capacity knapsack, optimasi stamina arkade, pembayaran dua arah (kembalian), dan tiket multi-hari.

---

## 🔗 Tautan Latihan Online Judge

- [CSES — Minimizing Coins](https://cses.fi/problemset/task/1634)
- [CSES — Coin Combinations I](https://cses.fi/problemset/task/1635)
- [CSES — Coin Combinations II](https://cses.fi/problemset/task/1636)
- [LeetCode 322 — Coin Change](https://leetcode.com/problems/coin-change/)
- [LeetCode 518 — Coin Change II](https://leetcode.com/problems/coin-change-ii/)
- [LeetCode 279 — Perfect Squares](https://leetcode.com/problems/perfect-squares/)
- [LeetCode 983 — Minimum Cost For Tickets](https://leetcode.com/problems/minimum-cost-for-tickets/)
