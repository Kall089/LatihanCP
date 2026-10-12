# Day 151 — Range DP (Matrix Chain dan Palindrome Partition)

> **Ide satu kalimat:** Range DP mendefinisikan state sebagai interval $[l, r]$ dan mencoba seluruh titik pecah $m \in [l, r-1]$ untuk menggabungkan sub-solusi, dengan urutan evaluasi tabel yang **wajib berdasar panjang interval (`len`)** menaik.

---

## 🎯 Tujuan Pembelajaran

- [ ] Memahami konsep dasar Range DP di mana sub-masalah berupa interval kontigu $[l, r]$.
- [ ] Memahami dan mengimplementasikan rekurens titik pecah (split point) $m$:
  $$dp[l][r] = \min_{l \le m < r} (dp[l][m] + dp[m+1][r] + \text{cost}(l, m, r))$$
- [ ] Menguasai hukum urutan evaluasi: tabel **wajib diisi berdasarkan panjang interval** agar semua anak berpanjang lebih kecil sudah valid.
- [ ] Menguasai studi kasus klasik **Matrix Chain Multiplication (MCM)** dan penanganan dimensi array $p[0 \dots N]$.
- [ ] Menggabungkan Range DP dengan **Prefix Sum 1D** pada masalah penggabungan elemen bersebelahan (**Stone Merging / AtCoder Slimes**).
- [ ] Menguasai **Palindrome Partitioning II** melalui pendekatan dua tahap (Range DP Boolean $O(N^2)$ + DP 1D $O(N^2)$).
- [ ] Memahami paradigma **Reverse Range DP** (*Burst Balloons*) dengan menentukan elemen terakhir yang diproses.
- [ ] Menyelesaikan 6 latihan bertingkat dan 15 tugas mandiri dengan C++17 optimal.

---

## 📁 Struktur Folder

```
Day-151 (Range DP - Matrix Chain dan Palindrome Partition)/
├── README.md
├── teori/
│   └── Day_151_Teori_Lengkap.md   (Materi lengkap, rekurens titik pecah, trace tabel, dua tahap DP)
├── latihan/
│   ├── exercise_1.cpp             (Rantai Filter Citra Batik - Matrix Chain Multiplication)
│   ├── exercise_2.cpp             (Menggabungkan Gudang Kopi - Stone Merging / Slimes)
│   ├── exercise_3.cpp             (Potongan Sandi Palindrom - Palindrome Partitioning II)
│   ├── exercise_4.cpp             (Rekonstruksi Kurung Perkalian Matriks - Parenthesization)
│   ├── exercise_5.cpp             (Letusan Balon Karnaval - Burst Balloons / Reverse Range DP)
│   └── exercise_6.cpp             (Memotong Batang Bambu - Minimum Cost to Cut a Stick)
├── solusi/
│   ├── solution_1.cpp s.d. solution_6.cpp (Solusi optimal C++17, verified AC)
├── tugas/
│   ├── tugas_01.cpp s.d. tugas_15.cpp     (15 latihan mandiri lengkap standar CP)
└── template/
    └── template.cpp               (Boilerplate MCM, Parentheses, Stone Merging, Palindrome, Burst Balloons, Cuts)
```

---

## 🧭 Panduan Belajar

### Langkah 1 — Pelajari Teori (45 menit)
Buka [Day_151_Teori_Lengkap.md](teori/Day_151_Teori_Lengkap.md):
1. **Bagian 1 & 2**: Pahami perbedaan DP linear dengan Range DP, dan bukti optimal substructure dari langkah terakhir.
2. **Bagian 3**: Pahami mengapa loop terluar **wajib berdasar panjang interval** (`len = 2 ... N`).
3. **Bagian 4**: Pelajari formulasi MCM dan simulasi trace dimensi $[10, 30, 5, 60]$.
4. **Bagian 5 & 6**: Kuasai optimasi prefix sum pada Stone Merging dan pemisahan dua tahap pada Palindrome Partitioning II.
5. **Bagian 7**: Pelajari reverse Range DP pada Burst Balloons.

### Langkah 2 — Amati Template (10 menit)
Buka [template.cpp](template/template.cpp):
- Fungsi `matrixChainMultiplication(p)`
- Fungsi `matrixChainWithParens(p)`
- Fungsi `stoneMerging(a)`
- Fungsi `minPalindromePartitionCuts(s)`
- Fungsi `burstBalloons(a)`
- Fungsi `minCostToCutStick(L, cuts)`

### Langkah 3 — Kerjakan 6 Latihan Bertingkat (120 menit)

| # | Judul Latihan | Konsep Kunci | Tingkat | Target Waktu |
|---|---|---|---|---|
| 1 | **Rantai Filter Citra Batik** | MCM Standar, 64-bit cost overflow guard | Mudah-Sedang | 15 menit |
| 2 | **Menggabungkan Gudang Kopi** | Stone Merging, AtCoder Slimes, Prefix Sum | Sedang | 20 menit |
| 3 | **Potongan Sandi Palindrom** | Palindrome Partitioning II, Dua Tahap DP | Sedang-Menantang | 25 menit |
| 4 | **Rekonstruksi Kurung Matriks** | Decision Split Tracking, Rekursi Struktur String | Sedang-Menantang | 20 menit |
| 5 | **Letusan Balon Karnaval** | Reverse Range DP, Balon Terakhir, Batas Virtual | Menantang | 20 menit |
| 6 | **Memotong Batang Bambu** | Pemetaan Koordinat Diskret, Sub-interval Cuts | Menantang | 20 menit |

### Langkah 4 — Uji Mandiri (15 Tugas)
- `tugas_01.cpp` s.d. `tugas_05.cpp`: Papan kayu, sisipan cermin, partisi tepat K bagian, penggabungan batu maksimum, dan perkalian matriks beranggaran.
- `tugas_06.cpp` s.d. `tugas_10.cpp`: Substring palindrom terpanjang, LPS subsekuens, permainan deque dua pemain, percampuran ramuan sihir, dan penghapusan karakter identik.
- `tugas_11.cpp` s.d. `tugas_15.cpp`: Pengurungan boolean logika, cetak palindrom supersequence, optimal BST, pewarnaan strip printer, dan penggabungan batu melingkar.

---

## 🔗 Tautan Latihan Online Judge

- [AtCoder Educational DP Contest N — Slimes](https://atcoder.jp/contests/dp/tasks/dp_n)
- [LeetCode 312 — Burst Balloons](https://leetcode.com/problems/burst-balloons/)
- [LeetCode 132 — Palindrome Partitioning II](https://leetcode.com/problems/palindrome-partitioning-ii/)
- [LeetCode 1547 — Minimum Cost to Cut a Stick](https://leetcode.com/problems/minimum-cost-to-cut-a-stick/)
- [LeetCode 664 — Strange Printer](https://leetcode.com/problems/strange-printer/)
- [SPOJ MIXTURES — Mixtures](https://www.spoj.com/problems/MIXTURES/)
