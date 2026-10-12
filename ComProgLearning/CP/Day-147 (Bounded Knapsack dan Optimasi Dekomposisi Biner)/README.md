# Day 147 — Bounded Knapsack dan Optimasi Dekomposisi Biner

> **Ide satu kalimat:** Alih-alih menduplikasi barang identik sebanyak $c_i$ kali yang memicu TLE, pecah persediaan secara biner menjadi $O(\log c_i)$ paket virtual $\{1, 2, 4, \dots, \text{sisa}\}$ lalu selesaikan dengan $0/1$ Knapsack loop kapasitas mundur.

---

## 🎯 Tujuan Pembelajaran

- [ ] Memahami batasan pendekatan naif $O(W \sum c_i)$ dan mengapa solusi tersebut TLE pada $c_i$ besar.
- [ ] Menguasai metodologi **Dekomposisi Biner (Binary Splitting)** untuk memecah stok $c_i$ menjadi $O(\log c_i)$ paket.
- [ ] Membuktikan secara matematis bahwa subset paket pangkat dua mencakup seluruh kuantitas $[0, c_i]$ tanpa pernah melebihi $c_i$.
- [ ] Mengimplementasikan **Pintasan Unbounded (Unbounded Short-Circuit)** saat $c_i \times w_i \ge W$ untuk mengubah kompleksitas menjadi $O(W)$.
- [ ] Mampu melakukan **rekonstruksi solusi** kuantitas barang asli dari paket-paket biner yang terpilih.
- [ ] Menyelesaikan 6 latihan bertingkat dan 15 tugas mandiri dengan C++17 optimal.

---

## 📁 Struktur Folder

```
Day-147 (Bounded Knapsack dan Optimasi Dekomposisi Biner)/
├── README.md
├── teori/
│   └── Day_147_Teori_Lengkap.md   (Materi komprehensif, pembuktian biner, diagram trace, hybrid DP)
├── latihan/
│   ├── exercise_1.cpp             (Paket Logistik Pulau - Bounded Knapsack Klasik)
│   ├── exercise_2.cpp             (Kasir dengan Laci Terbatas - Bounded Coin Change Min)
│   ├── exercise_3.cpp             (Nominal Donasi yang Mungkin - Bounded Reachability)
│   ├── exercise_4.cpp             (Rekonstruksi Solusi Bounded Knapsack - Decision Tracking)
│   ├── exercise_5.cpp             (Hybrid Bounded Knapsack - Pintasan Unbounded)
│   └── exercise_6.cpp             (Bounded Knapsack Kapasitas Tepat - Exact Target)
├── solusi/
│   ├── solution_1.cpp s.d. solution_6.cpp (Solusi optimal C++17, verified AC)
├── tugas/
│   ├── tugas_01.cpp s.d. tugas_15.cpp     (15 latihan mandiri dengan format standar)
└── template/
    └── template.cpp               (Boilerplate Bounded Knapsack, Reachability, Min Coins, Hybrid)
```

---

## 🧭 Panduan Belajar

### Langkah 1 — Pelajari Teori (45 menit)
Buka [Day_147_Teori_Lengkap.md](teori/Day_147_Teori_Lengkap.md):
1. **Bagian 1 & 2**: Pahami posisi Bounded Knapsack di antara 0/1 dan Unbounded Knapsack, serta analisis mengapa pendekatan naif gagal ($10^9$ operasi).
2. **Bagian 3 & 4**: Pelajari pembuktian dekomposisi biner stok 13 menjadi $\{1, 2, 4, 6\}$ dan algoritma pemecahannya.
3. **Bagian 5**: Kuasai pintasan Unbounded saat $c_i \times w_i \ge W$.
4. **Bagian 6 & 7**: Simak simulasi trace tabel langkah demi langkah dan 5 jebakan umum (common mistakes).

### Langkah 2 — Amati Template (10 menit)
Buka [template.cpp](template/template.cpp):
- Fungsi `boundedKnapsackMax(W, items)`
- Fungsi `boundedKnapsackMinCoins(target, coins)`
- Fungsi `boundedReachability(S, items)`
- Fungsi `hybridBoundedKnapsack(W, items)`
- Fungsi `exactTargetBoundedKnapsack(W, items)`

### Langkah 3 — Kerjakan 6 Latihan Bertingkat (120 menit)

| # | Judul Latihan | Konsep Kunci | Tingkat | Target Waktu |
|---|---|---|---|---|
| 1 | **Paket Logistik Pulau** | Bounded Knapsack Klasik, 64-bit value | Mudah | 15 menit |
| 2 | **Kasir dengan Laci Terbatas** | Bounded Coin Change Min, Biaya $q$ keping | Sedang | 20 menit |
| 3 | **Nominal Donasi yang Mungkin** | Bounded Reachability / Subset Sum, Logika OR | Sedang | 20 menit |
| 4 | **Rekonstruksi Solusi Bounded Knapsack** | Decision Tracking, 2D Backtracking Paket Biner | Sedang | 25 menit |
| 5 | **Hybrid Bounded Knapsack** | Optimasi Pintasan Unbounded Loop Maju saat $c_i w_i \ge W$ | Sedang-Menantang | 20 menit |
| 6 | **Bounded Knapsack Kapasitas Tepat** | Exact Target Reachability dengan Sentinel -1 | Menantang | 20 menit |

### Langkah 4 — Uji & Evaluasi Mandiri (15 Tugas)
Kerjakan soal-soal di folder `tugas/` untuk memantapkan pemahaman:
- `tugas_01.cpp` s.d. `tugas_05.cpp`: Paket gempa, tukar uang bank, jangkauan skor ujian, toko roti kapasitas tepat, dan belanja hemat at-least-target.
- `tugas_06.cpp` s.d. `tugas_10.cpp`: Rekonstruksi pembelian barang, penjualan emas batangan nilai besar, mesin capit, pembagian kargo seimbang, dan material bangunan diskon bertingkat.
- `tugas_11.cpp` s.d. `tugas_15.cpp`: Pertukaran koin dua kasir, kapasitas berjarak $[L, R]$, alokasi waktu server, partisi selisih minimum, dan peluru pertahanan strategis.

---

## 🔗 Tautan Latihan Online Judge

- [HDU 2191 — Multiple Pack](https://acm.dingbacode.com/showproblem.php?pid=2191)
- [POJ 1742 — Coins (Bounded Subset Sum)](http://poj.org/problem?id=1742)
- [Codeforces 106C — Buns](https://codeforces.com/problemset/problem/106/C)
- [AtCoder ABC 060 D — Simple Knapsack](https://atcoder.jp/contests/abc060/tasks/arc073_b)
