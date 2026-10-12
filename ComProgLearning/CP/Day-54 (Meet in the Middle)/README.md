# Day 54 — Meet in the Middle

> **Ide satu kalimat:** `2^40` mustahil, tapi `2^20 + 2^20` seketika — tukar **perkalian** menjadi **penjumlahan**.

---

## Tujuan Pembelajaran

- [ ] Mengenali `n ≤ 40` sebagai isyarat meet in the middle
- [ ] Membangkitkan seluruh subset satu paruh dalam **O(2^k)**, bukan `O(2^k · k)`
- [ ] Menggabungkan dua paruh dengan **sorting + binary search**
- [ ] Menerapkan tiga pola: **tepat X**, **≤ batas**, **terdekat**
- [ ] Menerapkan **prefix maksimum** untuk knapsack (bobot & nilai terpisah)
- [ ] Menerapkan semangat MITM **di luar** konteks bitmask (4-SUM)
- [ ] Tahu kapan **DP knapsack** lebih baik

---

## Struktur Folder

```
Day-54 (Meet in the Middle)/
├── README.md
├── teori/Day_54_Teori_Lengkap.md
├── latihan/exercise_1.cpp .. exercise_6.cpp
├── solusi/solution_1.cpp .. solution_6.cpp
├── tugas/tugas_01.cpp .. tugas_15.cpp
└── template/template.cpp
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (45 menit)

1. **Bagian "bagi dua, gabungkan"** — kenapa `2^40` menjadi `2 × 2^20`, dan
   kenapa kita **tetap** tidak boleh memeriksa setiap gabungan satu per satu.
2. **Trace 4.3** — contoh minimal yang membuktikan **prefix maksimum** wajib.
   Ini bagian terpenting hari ini.
3. **Tabel "kapan JANGAN memakai MITM"** — terutama syarat bobot besar.

### Langkah 2 — Template (15 menit)

Lima langkah yang harus jadi refleks:

```
1. bagi jadi dua paruh (k = n/2)
2. bangkitkan seluruh subset masing-masing
3. urutkan salah satu paruh
4. PREFIX MAKSIMUM   <- kalau ada bobot DAN nilai
5. binary search untuk tiap subset paruh lain
```

### Langkah 3 — Latihan (120 menit)

| # | Judul | Tingkat | Target | Konsep |
|---|-------|---------|--------|--------|
| 1 | Semua Jumlah Subset | Easy | 15 mnt | bitmask inkremental |
| 2 | Jumlah Tepat X | Easy | 25 mnt | pola dasar, hitung kemunculan |
| 3 | Muatan Maksimum | Medium | 25 mnt | terbesar ≤ batas |
| 4 | Knapsack | Medium | 30 mnt | **prefix maksimum** |
| 5 | Terdekat dengan Target | Hard | 25 mnt | dua kandidat |
| 6 | 4-SUM | Hard | 25 mnt | MITM tanpa bitmask |

Exercise 4 memuat bug nomor satu di topik ini. Kerjakan tanpa melihat solusi,
lalu uji dengan brute force `2^n` — kalau salah, kamu akan menemukan sendiri
kenapa prefix maksimum diperlukan.

### Langkah 4 — Tugas

**01–05** dasar dan diagnosis (CSES 1628, plus tugas 4 yang melatih pemilihan alat).
**06–10** varian klasik (LC 1755, UVa 1152, CF 888E, LC 805).
**11–15** level kontes (CF 1006F, SPOJ ABCDEF); tugas 15 memintamu **mengukur
sendiri** kapan DP mengalahkan MITM.

---

## Cheatsheet

```
TANDA PENGENAL: n <= 40 + "pilih subhimpunan"
  2^40 = 1e12 MUSTAHIL  ->  2^20 + 2^20 = 2e6 SEKETIKA

BANGKITKAN SUBSET O(2^k):
  int b = __builtin_ctz(mask);
  hasil[mask] = hasil[mask ^ (1 << b)] + a[b];

POLA 1 -- jumlah TEPAT X:
  total += upper_bound(sk, X-s) - lower_bound(sk, X-s);    KEMUNCULAN

POLA 2 -- terbesar TANPA MELEBIHI batas:
  idx = upper_bound(sk, batas - s) - sk.begin() - 1;
  if (idx >= 0) ...                                        cek batas!

POLA 3 -- knapsack (bobot, nilai):
  sort berdasarkan BOBOT, lalu PREFIX MAKSIMUM atas NILAI
  upper_bound(A, make_pair(sisa, LLONG_MAX)) - 1

POLA 4 -- TERDEKAT dengan target:
  i = lower_bound(sk, T - s);  periksa sk[i] DAN sk[i-1]

KOMPLEKSITAS O(2^(n/2) * n)
  n = 40 -> 4e7 aman  |  n = 50 -> 1.7e9 terlalu lambat

JANGAN PAKAI KALAU
  bobot kecil (W <= 1e6) -> DP knapsack O(n W), Day 145
  n <= 20                -> brute force langsung
  n > 45                 -> cari pendekatan lain

BUG NOMOR SATU: lupa PREFIX MAKSIMUM
  -- hanya muncul saat bobot dan nilai TERPISAH
long long untuk SELURUH jumlah DAN untuk penghitungnya (bisa 2^40)
subset KOSONG ikut terhitung
```

---

## Common Mistakes

1. **Lupa prefix maksimum** pada pola bobot–nilai.
2. **Overflow** — `n = 40 × 10^9 = 4·10^10`, dan hitungan bisa `2^40`.
3. **Subset kosong terhitung** padahal soal melarangnya.
4. **Memori** — `2^20` `pair<ll,ll>` = 16 MB; hitung sebelum menulis.
5. **`unordered_map` di-hack** pada varian 4-SUM.
6. **Membangkitkan subset `O(2^k · k)`** padahal ada cara `O(2^k)`.
7. **Membagi tidak seimbang** tanpa alasan.
8. **Memakai MITM padahal DP lebih baik** — periksa batas bobot dulu.
9. **`binary_search` alih-alih `upper_bound − lower_bound`** saat menghitung.

---

## Checklist Sebelum Lanjut ke Day 55/56

- [ ] Bisa menjelaskan kenapa `n ≤ 40` adalah isyarat MITM
- [ ] Bisa menulis pembangkitan subset `O(2^k)` dari ingatan
- [ ] Bisa memberi **contoh minimal** di mana prefix maksimum diperlukan
- [ ] Selalu memeriksa batas bobot sebelum memilih MITM atau DP
- [ ] Sudah menguji implementasi terhadap brute force `2^n`
- [ ] Sudah menyelesaikan minimal exercise 1–4
- [ ] Sudah AC minimal 1 soal (CSES 1628 paling cepat)

---

## Link Soal Online

| Soal | Platform | Fokus |
| ---- | -------- | ----- |
| [CSES 1628 — Meet in the Middle](https://cses.fi/problemset/task/1628) | CSES | pola paling murni |
| [LC 1755 — Closest Subsequence Sum](https://leetcode.com/problems/closest-subsequence-sum/) | LeetCode | terdekat |
| [LC 805 — Split Array With Same Average](https://leetcode.com/problems/split-array-with-same-average/) | LeetCode | MITM + rata-rata |
| [CF 888E — Maximum Subsequence](https://codeforces.com/problemset/problem/888/E) | Codeforces | MITM + modulo |
| [CF 1006F — Xor-Paths](https://codeforces.com/problemset/problem/1006/F) | Codeforces | MITM pada grid |
| [UVa 1152 — 4 Values Sum 0](https://onlinejudge.org/) | UVa | 4-SUM |
| [SPOJ ABCDEF](https://www.spoj.com/problems/ABCDEF/) | SPOJ | enam variabel |

---

## Preview Day 55–56 dan Blok Berikutnya

Day 55–56 adalah **latihan terpadu** dan **review** untuk seluruh blok sorting
dan searching (Day 43–54): tiga sorting O(n²), merge sort dan inversi, quickselect,
counting/radix, kedua bound, binary search on answer, presisi real, ternary search,
parallel binary search, dan meet in the middle.

Setelah itu Day 57 memulai blok **Complete Search & Greedy**. Enumerasi subset
yang kamu pelajari hari ini akan kembali muncul di sana — kali ini sebagai fondasi
**backtracking** (Day 62) dan **DP bitmask** (Day 156).
