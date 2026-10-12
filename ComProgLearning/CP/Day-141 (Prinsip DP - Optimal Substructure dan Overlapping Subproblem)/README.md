# Day 85 — Konsep DP & Dynamic Programming 1D

> **Ide satu kalimat:** DP adalah **rekursi yang tidak mau menghitung hal yang sama dua kali**.

---

## Tujuan Pembelajaran

Setelah menyelesaikan Day 85, kamu akan mampu:

- [ ] Menjelaskan dua syarat wajib DP: **overlapping subproblem** & **optimal substructure**
- [ ] Membedakan **rekursi polos**, **memoisasi (top-down)**, dan **tabulasi (bottom-up)**
- [ ] Merancang **state → transisi → basis** dari nol untuk soal 1 dimensi
- [ ] Menyelesaikan empat pola klasik: berapa cara, maksimum, minimal langkah, bisa/tidak
- [ ] Menghemat memori dari O(N) ke **O(1)** dengan rolling variable
- [ ] Menjelaskan kapan greedy gagal dan DP wajib dipakai

---

## Struktur Folder

```
Day-85 (Konsep DP dan DP 1D)/
├── README.md               ← Panduan ini
├── teori/
│   └── Day_85_Teori_Lengkap.md     ← Teori lengkap 8 bagian
├── latihan/
│   ├── exercise_1.cpp   (Warm-up  : Naik Tangga)
│   ├── exercise_2.cpp   (Warm-up  : Naik Tangga dengan K Langkah)
│   ├── exercise_3.cpp   (Core     : Perampok Rumah)
│   ├── exercise_4.cpp   (Core     : Koin Minimum)
│   ├── exercise_5.cpp   (Challenge: Banyaknya Cara Menyusun Koin)
│   └── exercise_6.cpp   (Contest  : Lompatan Minimum)
├── solusi/
│   └── solution_1.cpp .. solution_6.cpp
├── tugas/
│   └── tugas_01.cpp     through   tugas_15.cpp
└── template/
    └── template.cpp     ← memoisasi, tabulasi, rolling, 4 pola transisi
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori
`teori/Day_85_Teori_Lengkap.md`. Bagian yang paling penting:
**analogi buku catatan PR** (bagian 1) dan **tabel trace** (bagian 4).
Trace coin change {1,3,4} target 6 membuktikan secara langsung kenapa greedy salah.

### Langkah 2 — Hafalkan Tiga Pertanyaan
Sebelum menulis satu baris kode pun, jawab ini:

```
1. STATE    : dp[i] artinya apa?  (tulis sebagai KALIMAT LENGKAP)
2. TRANSISI : dp[i] dihitung dari state mana?
3. BASIS    : nilai terkecil berapa?
```

Kalau langkah 1 sulit ditulis dalam satu kalimat, **state-nya belum benar** —
jangan buru-buru menulis kode.

### Langkah 3 — Pelajari Template
`template/template.cpp` memuat delapan bagian: memoisasi, tabulasi, rolling variable,
dan empat pola transisi yang paling sering muncul.

### Langkah 4 — Kerjakan Latihan Berurutan
```bash
g++ -O2 -std=c++17 latihan/exercise_1.cpp -o latihan/exercise_1
echo "5" | ./latihan/exercise_1
```

### Langkah 5 — Cek Solusi (kalau macet > 30 menit)
Semua solusi **sudah diverifikasi**: 18 uji sample lolos, dan solusi 3 & 4
diuji-stres melawan brute force (700 kasus acak, cocok semua).

### Langkah 6 — Kerjakan 15 Tugas Mandiri
Target minimal **10 dari 15** sebelum lanjut ke Day 86–88 (LIS).

---

## Quick Reference — Cheatsheet DP 1D

```
TIGA PERTANYAAN WAJIB
  1. STATE    : dp[i] artinya apa?
  2. TRANSISI : dp[i] dari state mana?
  3. BASIS    : nilai terkecil berapa?

EMPAT POLA TRANSISI
  "berapa cara"     -> dp[i] = dp[i-1] + dp[i-2]        (jumlahkan)
  "maksimum"        -> dp[i] = max(dp[i-1], dp[i-2]+a[i])
  "minimal langkah" -> dp[i] = min(dp[i], dp[j] + 1)
  "bisa/tidak"      -> dp[i] = dp[i-1] || dp[i-k]

BASIS YANG SERING DIPAKAI
  berapa cara -> dp[0] = 1     (1 cara untuk tidak berbuat apa-apa)
  minimal     -> dp[0] = 0, sisanya INF
  maksimum    -> dp[0] = 0

MEMOISASI (top-down)          TABULASI (bottom-up)
  tulis rekursi + cache         isi tabel dari kecil ke besar
  penanda -1, JANGAN 0          tidak ada risiko stack overflow
  hati-hati stack overflow      harus tahu urutan pengisian

KOMPLEKSITAS = (jumlah state) x (biaya per state)
HEMAT MEMORI : ganti tabel dengan 2 variabel bergulir

TIGA JEBAKAN UTAMA
  ✗ dp[0] tidak diisi          -> seluruh tabel jadi 0
  ✗ memo diinisialisasi 0      -> jawaban yang memang 0 dihitung ulang terus
  ✗ urutan loop coin change    -> kombinasi berubah jadi permutasi
```

---

## Greedy atau DP?

```
Pilihan sekarang mempengaruhi pilihan berikutnya?
├── Tidak → GREEDY mungkin cukup
└── Ya
    ├── Bisa dibuktikan greedy tetap benar? (exchange argument)
    │   └── Ya → GREEDY
    └── Tidak / ragu → DP ✅
```

**Bukti nyata greedy bisa salah** (ada di exercise 4):
koin {1, 3, 4}, target 6. Greedy ambil 4 dulu → 4+1+1 = **3 koin**.
DP menemukan → 3+3 = **2 koin**. Greedy salah.

---

## Soal Online Judge Rekomendasi

### LeetCode (mulai dari sini)
- [70. Climbing Stairs](https://leetcode.com/problems/climbing-stairs/) — persis exercise 1
- [198. House Robber](https://leetcode.com/problems/house-robber/) — persis exercise 3
- [322. Coin Change](https://leetcode.com/problems/coin-change/) — persis exercise 4
- [518. Coin Change II](https://leetcode.com/problems/coin-change-ii/) — persis exercise 5
- [55. Jump Game](https://leetcode.com/problems/jump-game/) / [45. Jump Game II](https://leetcode.com/problems/jump-game-ii/) — exercise 6
- [746. Min Cost Climbing Stairs](https://leetcode.com/problems/min-cost-climbing-stairs/) — tugas 08

### CSES Problem Set — bagian Dynamic Programming
- [Dice Combinations](https://cses.fi/problemset/task/1633) — tugas 02
- [Minimizing Coins](https://cses.fi/problemset/task/1634) — tugas 04
- [Coin Combinations I](https://cses.fi/problemset/task/1635) — permutasi (tugas 06)
- [Coin Combinations II](https://cses.fi/problemset/task/1636) — kombinasi (tugas 05)
- [Removing Digits](https://cses.fi/problemset/task/1637) — tugas 09

### AtCoder Educational DP Contest (sangat direkomendasikan)
- [A - Frog 1](https://atcoder.jp/contests/dp/tasks/dp_a) — DP 1D paling murni
- [B - Frog 2](https://atcoder.jp/contests/dp/tasks/dp_b) — versi K langkah

---

## Checklist Penyelesaian

- [ ] Membaca teori, terutama trace coin change {1,3,4}
- [ ] Bisa menyebutkan tiga pertanyaan DP tanpa melihat catatan
- [ ] Bisa menjelaskan kenapa `dp[0] = 1` pada soal "berapa cara"
- [ ] `exercise_1.cpp` — naik tangga
- [ ] `exercise_2.cpp` — K langkah
- [ ] `exercise_3.cpp` — house robber
- [ ] `exercise_4.cpp` — koin minimum
- [ ] `exercise_5.cpp` — kombinasi vs permutasi
- [ ] `exercise_6.cpp` — lompatan minimum (forward DP)
- [ ] Minimal 10 dari 15 tugas mandiri
- [ ] Submit & AC **CSES Dice Combinations** dan **Minimizing Coins**
- [ ] Bisa menjelaskan kapan greedy gagal dan DP wajib

---

**Materi visual pendamping:** buka `learn-cp-visual` → menu **Greedy & DP → DP 1D**
untuk melihat tabel DP terisi sel demi sel, lengkap dengan panah asal nilainya.
