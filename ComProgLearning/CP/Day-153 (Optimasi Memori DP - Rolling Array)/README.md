# Day 153 — Optimasi Memori DP (Rolling Array, Penekanan Dimensi, dan Bitset)

> **Ide satu kalimat:** Optimasi memori DP memangkas tabel multidimensi yang besar menjadi 2 baris, 1 baris, atau beberapa variabel independen dengan memanfaatkan batas ketergantungan transisi lokal, menghemat memori hingga 99% tanpa mengubah hasil akhir.

---

## 🎯 Tujuan Pembelajaran

- [ ] Memahami mengapa dan kapan memori bisa meledak (*Memory Limit Exceeded*) pada DP $N \times M$ atau $N \times W$.
- [ ] Menguasai **Tingkat 1: Rolling Array 2 Baris** (`prev.swap(cur)` atau `i & 1`) untuk LCS dan Edit Distance dengan memori $O(\min(N, M))$.
- [ ] Menguasai **Tingkat 2: Rolling Array 1 Baris**:
  - **Loop Mundur** untuk 0/1 Knapsack & Subset Sum.
  - **Loop Maju** untuk Unbounded Knapsack & Coin Change.
- [ ] Menguasai **Tingkat 3: Variabel Lepas $O(1)$ Memory** untuk masalah jenis Fibonacci, House Robber, dan Kadane.
- [ ] Menguasai **Optimasi `std::bitset`** untuk percepatan 64x bitwise dan kompresi bit pada DP boolean.
- [ ] Mengetahui aturan pasti **Kapan DILARANG** menggunakan Rolling Array (misalnya saat butuh rekonstruksi jalur lengkap).
- [ ] Menyelesaikan 6 latihan bertingkat dan 15 tugas terstruktur dengan C++17 optimal.

---

## 📁 Struktur Folder

```
Day-153 (Optimasi Memori DP - Rolling Array)/
├── README.md
├── teori/
│   └── Day_153_Teori_Lengkap.md   (Konsep memori, 3 Tingkat Penekanan, Loop Mundur vs Maju, Bitset, Larangan)
├── latihan/
│   ├── exercise_1.cpp             (Arus Logistik Berkas Besar - Grid Min Path O(M) Space)
│   ├── exercise_2.cpp             (Menyunting Nama Arsip - Edit Distance 2-Row O(min(N, M)))
│   ├── exercise_3.cpp             (Manifest Kapasitas Penuh - Exact Knapsack 1D Backward)
│   ├── exercise_4.cpp             (Panjang LCS Dua Baris Bergantian - LCS Length O(min(N, M)))
│   ├── exercise_5.cpp             (Subsekuens Jumlah Target dengan Bitset - Subset Sum Bitset)
│   └── exercise_6.cpp             (Penjaga Museum Berjarak - House Robber O(1) Space)
├── solusi/
│   ├── solution_1.cpp s.d. solution_6.cpp (Solusi optimal C++17 teruji AC)
├── tugas/
│   ├── tugas_01.cpp s.d. tugas_15.cpp     (15 tugas terstandar lengkap dengan petunjuk)
└── template/
    └── template.cpp               (Boilerplate 1D Knapsack, LCS 2-Row, Edit Distance, Grid, House Robber, Bitset)
```

---

## 🧭 Panduan Belajar

### Langkah 1 — Pelajari Teori (30 menit)
Buka [Day_153_Teori_Lengkap.md](teori/Day_153_Teori_Lengkap.md):
1. **Bagian 1**: Pahami rumus menghitung alokasi memori (5 detik sebelum ngetik).
2. **Bagian 2 & 3**: Pelajari teknik 2 Baris Bergantian (`prev.swap(cur)`) dan optimasi dimensi kolom $\min(N, M)$.
3. **Bagian 4**: Pahami mengapa Knapsack 0/1 **wajib loop mundur** sedangkan Unbounded **wajib loop maju**.
4. **Bagian 5 & 6**: Kuasai penekanan $O(1)$ variabel lepas dan akselerasi `std::bitset`.
5. **Bagian 7**: Pahami kapan rolling array dilarang (soal rekonstruksi jalur).

### Langkah 2 — Amati Template (10 menit)
Buka [template.cpp](template/template.cpp):
- `knapsack01_1D(w, v, W)`
- `knapsackUnbounded_1D(w, v, W)`
- `lcsLength_2Row(s, t)`
- `editDistance_2Row(a, b)`
- `gridMinPath_1D(grid)`
- `houseRobber_O1(nums)`
- `subsetSum_Bitset<MAX_T>(w, target)`

### Langkah 3 — Kerjakan 6 Latihan Bertingkat (120 menit)

| # | Judul Latihan | Konsep Kunci | Tingkat | Target Waktu |
|---|---|---|---|---|
| 1 | **Arus Logistik Berkas Besar** | Grid Min Path 1D In-Place, Input Streaming | Mudah | 15 menit |
| 2 | **Menyunting Nama Arsip** | Edit Distance 2-Row Swap, $O(\min(N, M))$ | Sedang | 20 menit |
| 3 | **Manifest Kapasitas Penuh** | Exact Knapsack 1D Backward Loop, Inisialisasi -1 | Menantang | 25 menit |
| 4 | **Panjang LCS Dua Baris** | LCS 2-Row Swap, Mereduksi 100 MB $\to$ 40 KB | Sedang | 20 menit |
| 5 | **Subsekuens Target Bitset** | Subset Sum Boolean, `bs \|= (bs << x)` 64x Speedup | Sedang | 20 menit |
| 6 | **Penjaga Museum Berjarak** | House Robber Sliding Window 2 Variabel, $O(1)$ Space | Mudah-Sedang | 15 menit |

### Langkah 4 — Uji Mandiri (15 Tugas)
- `tugas_01.cpp` s.d. `tugas_05.cpp`: Festival non-adjacent $O(1)$, LCS dua baris, jalur grid rintangan 1D, 0/1 knapsack 1D, koin kombinasi loop maju.
- `tugas_06.cpp` s.d. `tugas_10.cpp`: Jarak edit 2 baris, subset sum bitset, tangga K-langkah sliding window, saham cooldown $O(1)$, segitiga penjumlahan 1D.
- `tugas_11.cpp` s.d. `tugas_15.cpp`: Partisi selisih minimum bitset, grid max path 2 baris, distinct subsequences 1D mundur, CSES book shop 1D, Kadane $O(1)$.

---

## 🔗 Tautan Latihan Online Judge

- [CSES Dynamic Programming — Book Shop](https://cses.fi/problemset/task/1158)
- [CSES Dynamic Programming — Coin Combinations II](https://cses.fi/problemset/task/1636)
- [LeetCode 72 — Edit Distance](https://leetcode.com/problems/edit-distance/)
- [LeetCode 198 — House Robber](https://leetcode.com/problems/house-robber/)
- [LeetCode 309 — Best Time to Buy and Sell Stock with Cooldown](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/)
- [LeetCode 115 — Distinct Subsequences](https://leetcode.com/problems/distinct-subsequences/)
