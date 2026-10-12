# Day 43 — Sorting O(n²): Bubble, Selection, Insertion

> **Ide satu kalimat:** kamu tidak mempelajari ini untuk memakainya — kamu mempelajarinya karena soal menanyakan **prosesnya**, dan karena swap bubble = inversi.

---

## Tujuan Pembelajaran

- [ ] Menulis ketiganya dari nol dan menjelaskan **invariant** masing-masing
- [ ] Menjelaskan **stabilitas** dan tahu mana yang stabil
- [ ] Menghubungkan **swap bubble** dengan **banyaknya inversi**
- [ ] Menjelaskan kenapa insertion sort **cepat** pada data hampir terurut
- [ ] Tahu kenapa selection sort punya **jumlah swap paling sedikit**
- [ ] Tahu bahwa `std::sort` **tidak menjamin** stabilitas

---

## Struktur Folder

```
Day-43 (Sorting O(n2) - Bubble, Selection, Insertion)/
├── README.md
├── teori/Day_43_Teori_Lengkap.md
├── latihan/exercise_1.cpp .. exercise_6.cpp
├── solusi/solution_1.cpp .. solution_6.cpp
├── tugas/tugas_01.cpp .. tugas_15.cpp
└── template/template.cpp
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (35 menit)

1. **Tiga invariant** (bagian 1). Perhatikan perbedaan halus: bubble dan selection
   menempatkan elemen di posisi **final**; insertion hanya menjaga bagian kiri
   **terurut relatif**.
2. **Bagian stabilitas** dengan contoh `[2a, 2b, 1]`. Pendek tapi menentukan.
3. **Trace 4.1** — perhatikan bahwa jumlah swap (4) sama persis dengan jumlah
   inversi (4). Itu bukan kebetulan.

### Langkah 2 — Template (10 menit)

Yang penting bukan menghafal kodenya, melainkan tiga fakta:

```
swap bubble = inversi
kerja insertion = O(n + inversi)
selection = n-1 swap, tetapi n(n-1)/2 perbandingan SELALU
```

### Langkah 3 — Latihan (75 menit)

| # | Judul | Tingkat | Target | Konsep |
|---|-------|---------|--------|--------|
| 1 | Swap Bubble | Easy | 10 mnt | batas `j+1 < n-i` |
| 2 | Selection Hemat Swap | Easy | 10 mnt | hindari swap sia-sia |
| 3 | Kartu Bertahap | Medium | 15 mnt | arah pergeseran |
| 4 | Stabilitas | Medium | 15 mnt | pilih algoritma yang benar |
| 5 | Hampir Terurut | Hard | 15 mnt | O(nK), baca constraint sebagai petunjuk |
| 6 | K Sapuan | Hard | 20 mnt | ketelitian membaca definisi |

Exercise 6 sengaja punya sampel yang menjebak (`K = 10` menghasilkan jawaban 1).
Soal simulasi menguji ketelitian membaca, bukan algoritma.

### Langkah 4 — Tugas

**01–05** implementasi dan penghitungan dasar (HackerRank, UVa 10327).
**06–10** stabilitas dan varian (termasuk dekomposisi siklus, yang **berbeda** dari inversi).
**11–15** level kontes; tugas 11 butuh Day 44, tugas 12 butuh greedy siklus.

---

## Cheatsheet

```
             invariant                    stabil  swap    terbaik
BUBBLE       k terbesar sudah di kanan     YA     O(n^2)  O(n) dgn flag
SELECTION    k terkecil sudah di kiri      TIDAK  n-1     O(n^2)
INSERTION    k pertama terurut relatif     YA     O(n^2)  O(n)

swap bubble = banyaknya INVERSI
kerja insertion = O(n + inversi)
selection: perbandingan SELALU n(n-1)/2, buta terhadap keteraturan data

stabilitas dijaga oleh '>' (bukan '>=')
std::sort TIDAK stabil -> pakai stable_sort atau pemecah seri indeks

swap minimum MUTLAK (tukar bebas) = n - banyaknya siklus   <- BUKAN inversi

n <= 5000  -> O(n^2) aman
n > 10^4   -> WAJIB O(n log n)
```

---

## Common Mistakes

1. **Batas loop bubble `j < n-i`** → akses `a[n]` di luar array.
2. **`>=` alih-alih `>`** → merusak stabilitas dan menambah swap.
3. **Insertion memakai `swap`** → tiga kali penulisan memori.
4. **Mengira selection sort stabil.** Tidak.
5. **Mengira `std::sort` stabil.** Tidak.
6. **`int` untuk jumlah swap** — bisa `5·10^9` saat `n = 10^5`.
7. **Mengubah array asli** saat hanya ingin menghitung — terima parameter by value.
8. **Mencampur "inversi" dengan "swap minimum mutlak".** Yang pertama untuk tukar
   berdampingan, yang kedua `n − siklus` untuk tukar bebas.

---

## Checklist Sebelum Lanjut ke Day 44

- [ ] Bisa menjelaskan invariant ketiga algoritma tanpa melihat catatan
- [ ] Bisa membuktikan kenapa swap bubble = inversi
- [ ] Bisa menyebutkan contoh minimal di mana selection sort merusak stabilitas
- [ ] Tahu `std::sort` tidak stabil dan tahu dua cara mengatasinya
- [ ] Sudah menyelesaikan minimal exercise 1–4
- [ ] Sudah AC minimal 1 soal (UVa 10327 atau HackerRank Bubble Sort)

---

## Link Soal Online

| Soal | Platform | Fokus |
| ---- | -------- | ----- |
| [HR — Sorting: Bubble Sort](https://www.hackerrank.com/challenges/ctci-bubble-sort/) | HackerRank | hitung swap |
| [HR — Insertion Sort Advanced](https://www.hackerrank.com/challenges/insertion-sort/) | HackerRank | inversi |
| [UVa 10327 — Flip Sort](https://onlinejudge.org/) | UVa | swap berdampingan |
| [SPOJ CODESPTB](https://www.spoj.com/problems/CODESPTB/) | SPOJ | inversi |
| [CSES 1090 — Ferris Wheel](https://cses.fi/problemset/task/1090) | CSES | sort + two pointers |
| [LC 912 — Sort an Array](https://leetcode.com/problems/sort-an-array/) | LeetCode | implementasi |

---

## Preview Day 44 — Merge Sort & Inversion Count

Identitas "swap bubble = inversi" yang kamu temukan hari ini akan menjadi **soalnya
sendiri**. Kamu akan menghitung inversi dalam **O(n log n)** — dan yang menyenangkan,
penghitungannya nyaris **gratis** di dalam merge sort: satu baris tambahan di dalam
langkah penggabungan.
