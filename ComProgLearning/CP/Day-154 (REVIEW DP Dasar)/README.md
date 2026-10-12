# Day 154 — REVIEW DP Dasar (Sintesis & Kerangka Kerja Universal DP)

> **Ide satu kalimat:** Dynamic Programming bukanlah tentang menghafal rumus, melainkan tentang kerangka berpikir memecah masalah menjadi relasi rekursif berstruktur DAG (*Directed Acyclic Graph*), memetakan 4 komponen inti (State, Transisi, Kasus Dasar, Urutan), dan mengenali salah satu dari 5 arketipe klasik.

---

## 🎯 Tujuan Pembelajaran

- [ ] Merangkum dan mengintegrasikan seluruh materi DP Dasar (**Day 141 — Day 153**) menjadi satu kerangka kerja universal.
- [ ] Menguasai **Kerangka Berpikir Universal 4 Komponen Wajib**:
  1. **State** (Apa yang harus diingat / parameter submasalah).
  2. **Transisi** (Dari state mana ke state ini).
  3. **Kasus Dasar** (Nilai awal yang sudah pasti diketahui).
  4. **Urutan Komputasi** (Arah perulangan loop agar dependensi selalu dihitung lebih dahulu).
- [ ] Menguasai **5 Arketipe Kode Universal**:
  - **Kerangka 1**: DP 1D (Barisan & Jendela Sliding).
  - **Kerangka 2**: Knapsack & Kapasitas (Loop Mundur 0/1 vs Maju Unbounded).
  - **Kerangka 3**: Dua String (Awalan & Karakter Terakhir).
  - **Kerangka 4**: Grid 2D (Sel Masuk Atas & Kiri).
  - **Kerangka 5**: Interval / Range DP (Loop atas Panjang Subarray $L$).
- [ ] Mampu membaca kata kunci pada deskripsi soal kompetisi dan memetakan langsung ke arketipe DP yang sesuai.
- [ ] Menguasai **Checklist Debug 10 Pertanyaan** untuk mengatasi WA, TLE, atau RTE.
- [ ] Memahami persiapan dan prasyarat menuju **DP Tingkat Lanjut** (Day 155+): State Lanjut, Bitmask DP, Digit DP, dan Tree DP.

---

## 📁 Struktur Folder

```
Day-154 (REVIEW DP Dasar)/
├── README.md
├── teori/
│   └── Day_154_Teori_Lengkap.md   (Peta Kurikulum, 4 Komponen, 5 Kerangka Kode, Keyword Mapping, Debug Checklist)
├── latihan/
│   ├── exercise_1.cpp             (Agenda Stan dan Anggaran - House Robber + Knapsack Hybrid)
│   ├── exercise_2.cpp             (Rangkaian Pameran Bertumbuh - Weighted LIS O(N^2))
│   ├── exercise_3.cpp             (Rute Hadiah dan Banyak Pemenang - Grid Max + Way Counting modulo 10^9+7)
│   ├── exercise_4.cpp             (Pembagian Cerita Terpanjang - LCS + Lexicographical Reconstruction)
│   ├── exercise_5.cpp             (Pemotongan Bambu Biaya Minimum - Interval / Range DP Stick Cutting)
│   └── exercise_6.cpp             (Penukaran Mata Uang Minimum & Banyak Cara - Unbounded Optimization + Counting)
├── solusi/
│   ├── solution_1.cpp s.d. solution_6.cpp (Solusi optimal C++17 teruji AC dan terverifikasi)
├── tugas/
│   ├── tugas_01.cpp s.d. tugas_15.cpp     (15 tugas sintesis terstandar lengkap dengan petunjuk)
└── template/
    └── template.cpp               (Boilerplate Master 5 Arketipe: DP 1D, Knapsack, LCS, Grid, MCM, Coin Change)
```

---

## 🧭 Panduan Belajar

### Langkah 1 — Pelajari Rangkuman Teori (30 menit)
Buka [Day_154_Teori_Lengkap.md](teori/Day_154_Teori_Lengkap.md):
1. **Bagian 1 & 2**: Pelajari peta kurikulum Day 141–153 dan 4 baris wajib yang harus ditulis sebelum mengetik kode.
2. **Bagian 3**: Pahami 5 kerangka kode universal (DP 1D, Knapsack, Two Strings, Grid, Range DP).
3. **Bagian 4**: Gunakan tabel kata kunci (*keyword mapping*) untuk mendiagnosis jenis soal dalam hitungan detik.
4. **Bagian 5**: Gunakan checklist debug 10 poin saat menghadapi *Wrong Answer* atau *Time Limit Exceeded*.

### Langkah 2 — Amati Master Template (10 menit)
Buka [template.cpp](template/template.cpp):
- `dp_1D_sequence(nums)`
- `knapsack_01(w, v, W)`
- `two_strings_lcs(s, t)`
- `grid_min_path(grid)`
- `interval_range_dp(arr)`
- `coin_change_synthesis(coins, target)`

### Langkah 3 — Kerjakan 6 Latihan Sintesis Terpadu (150 menit)

| # | Judul Latihan | Konsep Kunci & Arketipe | Tingkat | Target Waktu |
|---|---|---|---|---|
| 1 | **Agenda Stan dan Anggaran** | House Robber + Knapsack Hybrid | Sedang | 20 menit |
| 2 | **Rangkaian Pameran Bertumbuh** | Maximum Sum Increasing Subsequence (Weighted LIS) | Sedang | 20 menit |
| 3 | **Rute Hadiah dan Banyak Pemenang** | Grid Max Path + Way Counting Modulo $10^9+7$ | Menantang | 30 menit |
| 4 | **Pembagian Cerita Terpanjang** | LCS Suffix DP + Lexicographically Smallest Reconstruction | Sedang-Menantang | 25 menit |
| 5 | **Pemotongan Bambu Biaya Minimum** | Interval / Range DP Stick Cutting $O(M^3)$ | Menantang | 30 menit |
| 6 | **Penukaran Mata Uang Sintesis** | Coin Change: Min Coins & Number of Ways Kombinasi | Sedang | 25 menit |

### Langkah 4 — Uji Pemahaman Mandiri (15 Tugas Sintesis)
- `tugas_01.cpp` s.d. `tugas_05.cpp`: Ekspedisi tepat K stan, partisi palindrom min cuts + ways, knapsack max value + count, LIS + counting, weighted edit distance.
- `tugas_06.cpp` s.d. `tugas_10.cpp`: Grid langkah diagonal / raja, bounded coin change, subarray jumlah kelipatan K, MCM rekonstruksi tanda kurung lengkap, penebangan pohon cooldown 2 hari.
- `tugas_11.cpp` s.d. `tugas_15.cpp`: 3-way partition reachability, grid 2-pemain simultan, LCS 3 string 3D, box stacking tower 3D, word break max words.

---

## 🔗 Tautan Latihan Terpadu Online Judge

- [CSES Problem Set — Dynamic Programming (19 Problems)](https://cses.fi/problemset/list/)
- [AtCoder Educational DP Contest (A s.d. H)](https://atcoder.jp/contests/dp)
- [LeetCode 1547 — Minimum Cost to Cut a Stick](https://leetcode.com/problems/minimum-cost-to-cut-a-stick/)
- [LeetCode 673 — Number of Longest Increasing Subsequence](https://leetcode.com/problems/number-of-longest-increasing-subsequence/)
- [LeetCode 139 — Word Break](https://leetcode.com/problems/word-break/)
- [LeetCode 741 — Cherry Pickup](https://leetcode.com/problems/cherry-pickup/)
