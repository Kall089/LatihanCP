# Day 46 — Counting Sort, Radix Sort & Bucket Sort

> **Ide satu kalimat:** batas `Ω(n log n)` hanya berlaku kalau kamu **membandingkan** — jadi jangan membandingkan.

---

## Tujuan Pembelajaran

- [ ] Menjelaskan batas bawah **Ω(n log n)** dan kenapa counting sort ada di luar model
- [ ] Menulis counting sort **stabil** dengan prefix sum dan penyapuan mundur
- [ ] Menulis **radix sort LSD** basis 256
- [ ] Menjelaskan kenapa **stabilitas syarat mutlak** untuk radix sort
- [ ] Memilih basis dan menghitung berapa lewat yang dibutuhkan
- [ ] Menangani **bilangan negatif** dan **string**
- [ ] Memutuskan kapan non-komparasi menang — **dengan angka**, bukan refleks

---

## Struktur Folder

```
Day-46 (Counting Sort, Radix Sort dan Bucket Sort)/
├── README.md
├── teori/Day_46_Teori_Lengkap.md
├── latihan/exercise_1.cpp .. exercise_6.cpp
├── solusi/solution_1.cpp .. solution_6.cpp
├── tugas/tugas_01.cpp .. tugas_15.cpp
└── template/template.cpp
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (40 menit)

1. **Bagian batas bawah** — kenapa `log2(n!) ≈ n log n`, dan kenapa counting sort
   tidak melanggarnya. Pelajaran yang lebih umum: kalau sebuah batas bawah
   menghalangimu, periksa apakah **asumsinya** berlaku.
2. **Trace 4.2** — demonstrasi radix sort hancur tanpa stabilitas, pada `[21, 12, 11]`.
   Pendek dan sangat meyakinkan.
3. **Trace 4.4** — kapan counting sort **kalah** telak. Sama pentingnya dengan
   mengetahui kapan ia menang.

### Langkah 2 — Template (10 menit)

Yang perlu diingat bukan kodenya, melainkan tabel keputusan:

```
V <= 1e6 dan V <~ n log n   -> counting sort   O(n + V)
n >= 1e6 dan waktu ketat    -> radix basis 256 (~2-3x std::sort)
selain itu                  -> std::sort
```

### Langkah 3 — Latihan (90 menit)

| # | Judul | Tingkat | Target | Konsep |
|---|-------|---------|--------|--------|
| 1 | Urutkan Umur | Easy | 10 mnt | counting + I/O besar |
| 2 | Counting Sort Stabil | Easy | 15 mnt | prefix sum, sapuan mundur |
| 3 | Nilai Negatif | Medium | 15 mnt | offset, bug indeks negatif |
| 4 | Radix Sort | Medium | 25 mnt | LSD, stabilitas wajib |
| 5 | Selisih Antar Tetangga | Hard | 25 mnt | bucket + pigeonhole |
| 6 | Urutan Relatif Kustom | Hard | 15 mnt | "mengurutkan" tanpa sort |

Exercise 5 punya argumen pigeonhole yang layak dipahami sepenuhnya — ia menunjukkan
bahwa kadang kamu hanya butuh **ringkasan** tiap ember, bukan isinya.

### Langkah 4 — Tugas

**01–05** counting sort dan variannya (UVa 11462, LC 1122).
**06–10** radix sort dan pengukuran empiris (tugas 10 memintamu **mengukur sendiri**
kapan masing-masing menang — kerjakan ini, angkanya lebih meyakinkan daripada teori).
**11–15** level kontes (LC 164, suffix array, optimasi I/O nyata).

Tugas 11 adalah pratinjau **suffix array** (Day 220), yang seluruhnya dibangun di
atas counting sort berulang.

---

## Cheatsheet

```
BATAS BAWAH: pengurutan berbasis PERBANDINGAN >= n log n
Counting sort di LUAR model: nilai dipakai sebagai ALAMAT

COUNTING SORT STABIL (tiga langkah):
  1. for (x : a) cnt[x]++;
  2. for (v = 1..maks) cnt[v] += cnt[v-1];
  3. for (i = n-1 DOWNTO 0) hasil[--cnt[a[i]]] = a[i];
              ^^^^^^^^^^^^^^ MUNDUR = STABIL, dan pre-decrement

RADIX LSD basis 256 (4 lewat untuk 32 bit):
  for (shift = 0; shift < 32; shift += 8)
      counting sort STABIL pada (x >> shift) & 255
  a.swap(tmp)   <- O(1), JANGAN menyalin

STABILITAS SYARAT MUTLAK radix. Tanpa itu, info lewat sebelumnya HILANG.

MEMILIH BASIS: 256 -> 4 lewat, cnt 1 KB (cache L1), digit = geser + AND

NEGATIF: offset, atau XOR 0x80000000 pada radix
cnt BESAR: GLOBAL, jangan di stack
maks+1, bukan maks

POLA PALING BERGUNA (berlaku untuk sorting apa pun):
  urutkan kunci KURANG PENTING dulu, lalu kunci PENTING secara STABIL
```

---

## Kapan Menang — Hitung, Jangan Tebak

```
n = 1e6, V = 1e6  ->  counting 2e6   vs sort 3e7    counting menang 15x
n = 1e3, V = 1e6  ->  counting 1e6   vs sort 1.5e4  SORT menang 60x
n = 1e6, V = 1e9  ->  counting MUSTAHIL (4 GB)      pakai radix atau sort
n = 1e7, int      ->  radix ~2-3x lebih cepat dari std::sort
```

---

## Common Mistakes

1. **Menyapu maju di langkah penempatan.** Tidak stabil → radix hancur.
2. **Counting sort saat `V >> n`.** MLE atau sangat lambat.
3. **Lupa bilangan negatif.** Indeks negatif sering **tidak crash** — bug senyap.
4. **Menyalin `tmp` alih-alih `swap`.** `swap` vector adalah O(1).
5. **Radix pada `int` bertanda tanpa penyesuaian.** Negatif terurut di belakang.
6. **`cnt` besar di stack.** Segmentation fault.
7. **Ukuran array `maks` alih-alih `maks+1`.**
8. **Mengira bucket sort selalu O(n).** Hanya kalau seragam.
9. **Post-decrement `cnt[...]--`** alih-alih pre-decrement `--cnt[...]`.

---

## Checklist Sebelum Lanjut ke Day 47

- [ ] Bisa menjelaskan kenapa counting sort tidak melanggar `Ω(n log n)`
- [ ] Bisa mendemonstrasikan radix sort gagal tanpa stabilitas (pakai `[21,12,11]`)
- [ ] Bisa menghitung kapan counting sort menang atas `std::sort`
- [ ] Hafal pola "kunci kurang penting dulu, lalu kunci penting secara stabil"
- [ ] Sudah menyelesaikan minimal exercise 1–4
- [ ] Sudah AC minimal 1 soal (UVa 11462 atau LC 1122)

---

## Link Soal Online

| Soal | Platform | Fokus |
| ---- | -------- | ----- |
| [UVa 11462 — Age Sort](https://onlinejudge.org/) | UVa | counting sort murni |
| [LC 1122 — Relative Sort Array](https://leetcode.com/problems/relative-sort-array/) | LeetCode | urutan kustom |
| [LC 164 — Maximum Gap](https://leetcode.com/problems/maximum-gap/) | LeetCode | bucket + pigeonhole |
| [LC 912 — Sort an Array](https://leetcode.com/problems/sort-an-array/) | LeetCode | implementasi bebas |
| [ABC 209 C](https://atcoder.jp/contests/abc209/tasks/abc209_c) | AtCoder | counting |
| [SPOJ CODESPTB](https://www.spoj.com/problems/CODESPTB/) | SPOJ | inversi |

---

## Preview Day 47 — Sorting Multi-Kriteria & Stabilitas

Pola *"urutkan kunci kurang penting dulu, lalu kunci penting secara stabil"* yang
kamu temukan di radix sort hari ini adalah **inti** dari Day 47. Di sana kamu akan
melihatnya dipakai untuk pengurutan multi-kriteria secara umum — dan mengapa
`std::sort` yang tidak stabil bisa menghasilkan WA pada soal yang terlihat sepele.

Setelah itu Day 48 memulai blok **binary search**, dan Day 49 akan menuntutmu menulis
`lower_bound` dan `upper_bound` dari nol dengan invariant yang benar.
