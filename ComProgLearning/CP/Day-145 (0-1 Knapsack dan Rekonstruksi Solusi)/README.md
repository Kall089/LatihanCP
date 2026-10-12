# Day 145 — 0/1 Knapsack & Rekonstruksi Solusi

> **Ide satu kalimat:** loop kapasitas **mundur** memberimu 0/1; loop **maju** memberimu unbounded — satu karakter, dua masalah.

---

## Tujuan Pembelajaran

- [ ] Menurunkan rekurens knapsack dari definisi state
- [ ] Menulis versi **1D** sebagai default, dan tahu kapan butuh **2D**
- [ ] Menjelaskan kenapa loop kapasitas versi 1D harus **MUNDUR**
- [ ] **Merekonstruksi** barang mana yang dipilih
- [ ] Membedakan **0/1**, **unbounded**, dan **bounded**
- [ ] Memilih antara DP kapasitas, DP **nilai**, dan **meet in the middle** — dengan angka
- [ ] Mengenali knapsack yang menyamar (subset sum, partisi, hitung cara)

---

## Struktur Folder

```
Day-145 (0-1 Knapsack dan Rekonstruksi Solusi)/
├── README.md
├── teori/Day_145_Teori_Lengkap.md
├── latihan/exercise_1.cpp .. exercise_6.cpp
├── solusi/solution_1.cpp .. solution_6.cpp
├── tugas/tugas_01.cpp .. tugas_15.cpp
└── template/template.cpp
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (45 menit)

1. **Contoh tandingan greedy rasio** (bagian 1). Dua menit, dan ia menutup
   pertanyaan "kenapa tidak greedy saja?" untuk selamanya.
2. **Trace 4.3** — demonstrasi loop maju vs mundur pada satu barang.
   Ini bagian terpenting hari ini.
3. **Tabel "memilih varian"** (bagian 2) — hitung `n × W` **sebelum** menulis.

### Langkah 2 — Template (10 menit)

Tiga baris yang harus jadi refleks:

```cpp
for (int i = 0; i < n; i++)
    for (int c = W; c >= w[i]; c--)          // MUNDUR untuk 0/1
        dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
```

Ganti `c--` menjadi `c++` dan kamu punya unbounded knapsack. Dua soal, satu template.

### Langkah 3 — Latihan (110 menit)

| # | Judul | Tingkat | Target | Konsep |
|---|-------|---------|--------|--------|
| 1 | Toko Buku | Easy | 15 mnt | 0/1 dasar, hitung memori |
| 2 | Arah Loop | Easy | 15 mnt | 0/1 vs unbounded |
| 3 | Barang Mana | Medium | 25 mnt | rekonstruksi, butuh 2D |
| 4 | Semua Jumlah | Medium | 20 mnt | subset sum, bitset |
| 5 | Kapasitas Raksasa | Hard | 25 mnt | DP atas **nilai** |
| 6 | Warisan Adil | Hard | 20 mnt | partisi = subset sum |

### Langkah 4 — Tugas

**01–05** dasar (CSES 1158, 1745, AtCoder DP D).
**06–10** varian klasik (LC 416, LC 1049, AtCoder DP E, LC 494, UVa 10130).
**11–15** level kontes.

**Tugas 14 adalah tugas 15 di Day 51** yang tadinya menunggu prasyarat ini —
kamu sekarang bisa menggabungkan binary search di luar dengan knapsack di dalam.
Tugas 13 mengarahkanmu kembali ke Day 54 (meet in the middle) untuk `n ≤ 40`.

---

## Cheatsheet

```
dp[i][c] = max(dp[i-1][c], dp[i-1][c - w[i]] + v[i])
dp[i-1] di KEDUA sisi -> tiap barang PALING BANYAK SEKALI

VERSI 1D (default):
  for (i = 0..n-1)
      for (c = W; c >= w[i]; c--)          <- MUNDUR!
          dp[c] = max(dp[c], dp[c - w[i]] + v[i]);

  MUNDUR -> dp[c-w] masih dari barang SEBELUMNYA -> 0/1
  MAJU   -> dp[c-w] sudah diperbarui -> UNBOUNDED

REKONSTRUKSI: butuh 2D. dp[i][c] != dp[i-1][c] -> barang i diambil, c -= w[i]

VARIAN
  unbounded   : loop MAJU
  bounded k   : dekomposisi biner 1,2,4,... -> O(W log k)
  subset sum  : nilai = berat; bitset `bs |= bs << x` beri 64x
  hitung cara : ganti max jadi +
  W besar, V kecil: dp[val] = berat MINIMUM

PILIH VARIAN -- HITUNG DULU
  n*W  <= 1e8 -> DP kapasitas
  n*SV <= 1e8 -> DP nilai
  n <= 40     -> meet in the middle (Day 54)

GREEDY RASIO SALAH untuk 0/1 (benar hanya untuk FRACTIONAL, Day 74)
long long untuk nilai total | subset sum: bisa[0] = 1
```

---

## Common Mistakes

1. **Loop kapasitas MAJU pada 0/1** — menghasilkan unbounded, dan hasilnya
   terlihat masuk akal (hanya terlalu besar).
2. **Off-by-one `dp[i]` vs `w[i-1]`.**
3. **`int` untuk nilai total** — `100 × 10^9 = 10^11`.
4. **Memori `O(n·W)`** — `1000 × 10^5` = 400 MB. Pakai 1D.
5. **Lupa `c >= w[i]`** — indeks negatif.
6. **Mengira greedy rasio benar.**
7. **Merekonstruksi dari tabel 1D** — tidak bisa, riwayatnya tertimpa.
8. **`bisa[0] = 0`** pada subset sum — harus `1`.
9. **Menambahkan berat ke penanda INF** pada DP atas nilai — bisa overflow.

---

## Checklist Sebelum Lanjut

- [ ] Bisa menulis versi 1D dari ingatan dalam < 1 menit
- [ ] Bisa menjelaskan kenapa loop harus mundur, dengan contoh
- [ ] Selalu menghitung `n × W` sebelum memilih pendekatan
- [ ] Bisa merekonstruksi dan tahu kenapa butuh 2D
- [ ] Tahu tiga varian: unbounded, bounded, DP atas nilai
- [ ] Sudah menyelesaikan minimal exercise 1–4
- [ ] Sudah AC minimal 2 soal (CSES 1158 dan 1745 paling cepat)
- [ ] **Sudah mengerjakan ulang tugas 15 di Day 51** yang tadinya terkunci

---

## Link Soal Online

| Soal | Platform | Fokus |
| ---- | -------- | ----- |
| [CSES 1158 — Book Shop](https://cses.fi/problemset/task/1158) | CSES | 0/1 murni |
| [CSES 1745 — Money Sums](https://cses.fi/problemset/task/1745) | CSES | subset sum |
| [AtCoder DP D — Knapsack 1](https://atcoder.jp/contests/dp/tasks/dp_d) | AtCoder | 0/1 dasar |
| [AtCoder DP E — Knapsack 2](https://atcoder.jp/contests/dp/tasks/dp_e) | AtCoder | DP atas **nilai** |
| [LC 416 — Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/) | LeetCode | partisi |
| [LC 494 — Target Sum](https://leetcode.com/problems/target-sum/) | LeetCode | subset sum bertanda |
| [LC 1049 — Last Stone Weight II](https://leetcode.com/problems/last-stone-weight-ii/) | LeetCode | partisi menyamar |
| [UVa 10130 — SuperSale](https://onlinejudge.org/) | UVa | knapsack + banyak query |

---

## Preview

**Day 146** — Subset Sum & Partition secara mendalam.
**Day 147** — Bounded Knapsack dengan dekomposisi biner (tugas 11 hari ini).
**Day 152** — Rekonstruksi jalur DP secara umum, memperluas teknik hari ini.
