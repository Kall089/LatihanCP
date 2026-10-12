# Day 29 — Prefix Sum 1D & Range Sum Query

> **Ide satu kalimat:** pasang patokan kilometer sekali, lalu setiap pertanyaan jarak jadi satu pengurangan.

---

## Tujuan Pembelajaran

- [ ] Membangun prefix sum dan menjawab range sum dalam **O(1)** per query
- [ ] Memakai konvensi `pre[0] = 0` sehingga **tidak ada** percabangan tepi
- [ ] Tahu operasi mana yang **tidak bisa** di-prefix (min, max, gcd)
- [ ] Memakai **prefix XOR** dan **prefix count** dengan pola pikir yang sama
- [ ] Menghitung **subarray dengan jumlah = K** memakai map, termasuk saat ada bilangan negatif
- [ ] Menghitung **subarray kelipatan K** lewat sisa bagi, dengan normalisasi negatif
- [ ] Refleks memakai `long long`

---

## Struktur Folder

```
Day-29 (Prefix Sum 1D dan Range Sum Query)/
├── README.md
├── teori/Day_29_Teori_Lengkap.md
├── latihan/exercise_1.cpp .. exercise_6.cpp
├── solusi/solution_1.cpp .. solution_6.cpp
├── tugas/tugas_01.cpp .. tugas_15.cpp
└── template/template.cpp
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (30 menit)

Tiga bagian penting:

1. **Analogi patokan kilometer** (bagian 1) — kenapa `pre[0] = 0` bukan detail sepele.
2. **Tabel operasi yang bisa/tidak bisa di-prefix** — ini yang membuatmu tidak
   membuang waktu mencoba "prefix min".
3. **Trace subarray jumlah = K** (bagian 4.2) — perhatikan langkah yang pasangannya
   adalah prefix kosong.

### Langkah 2 — Template (10 menit)

Dua baris yang harus jadi refleks:

```cpp
vector<long long> pre(n + 1, 0);
for (int i = 0; i < n; i++) pre[i+1] = pre[i] + a[i];
```

### Langkah 3 — Latihan (60–90 menit)

| # | Judul | Tingkat | Target | Konsep |
|---|-------|---------|--------|--------|
| 1 | Range Sum Query | Easy | 10 mnt | prefix polos, konversi 1-based |
| 2 | Hitung Genap | Easy | 10 mnt | prefix count, `%` pada negatif |
| 3 | Subarray Jumlah = K | Medium | 20 mnt | prefix + map, `freq[0] = 1` |
| 4 | Subarray Kelipatan K | Medium | 20 mnt | sisa bagi, normalisasi negatif |
| 5 | Potongan Seimbang | Hard | 15 mnt | `kanan = total − kiri` |
| 6 | Rentang Seimbang Terpanjang | Hard | 25 mnt | trik +1/−1, posisi **pertama** |

### Langkah 4 — Tugas

15 soal: **01–05** terapan langsung (CSES 1646, 1650, ABC122 C), **06–10** butuh satu
transformasi (CSES 1661, 1662), **11–15** level kontes.

Tugas 11 dan 14 sengaja menyentuh alat yang belum kamu pelajari (BIT, merge sort).
Kerjakan versi O(n²)-nya dulu, lalu kembali ke soal ini setelah Day 44 dan Day 170.

---

## Cheatsheet

```
pre[0] = 0;  pre[i+1] = pre[i] + a[i];        ukuran n+1, long long SELALU
jumlah a[l..r] = pre[r+1] - pre[l]            0-based inklusif
jumlah a[L..R] = pre[R]   - pre[L-1]          1-based inklusif

prefix XOR   : px[i+1] = px[i] ^ a[i]
prefix count : c[i+1] = c[i] + (kondisi(a[i]) ? 1 : 0)

subarray jumlah = K   : freq[0]=1; hasil += freq[cur-K]; freq[cur]++;
subarray kelipatan K  : cur = ((cur+v)%K+K)%K; hasil += cnt[cur]; cnt[cur]++;
"sama banyak A dan B" : bobot +1/-1, lalu cari jumlah nol
terpanjang -> simpan posisi PERTAMA ; berapa banyak -> simpan FREKUENSI

TIDAK BISA: min, max, gcd        -> Sparse Table (Day 169)
ADA UPDATE: Fenwick (Day 170) ; UPDATE RANGE: difference array (Day 31)
```

---

## Common Mistakes

1. **`int` untuk prefix.** `2·10^5 × 10^9 = 2·10^14`.
2. **`pre` berukuran `n`** lalu butuh `if (l == 0)`. Ganti ke `n+1`.
3. **Lupa `freq[0] = 1`** — subarray yang mulai di indeks 0 hilang.
4. **`(-7) % 3 == -1`** di C++ → indeks array negatif → RE atau WA senyap.
5. **Menghitung `freq[cur]++` sebelum `hasil +=`** — saat `K = 0` kamu menghitung
   subarray kosong.
6. **Mencoba prefix min/max/gcd.** Tidak ada inversnya.
7. **`unordered_map` di Codeforces** bisa di-hack jadi O(n²). Pakai `map` atau custom hash.

---

## Checklist Sebelum Lanjut ke Day 30

- [ ] Bisa menulis prefix sum dari ingatan tanpa berpikir tentang off-by-one
- [ ] Bisa menjelaskan kenapa `freq[0] = 1` diperlukan
- [ ] Tahu kapan sliding window **tidak** boleh dipakai (jawaban: ada bilangan negatif)
- [ ] Sudah menyelesaikan minimal exercise 1–4
- [ ] Sudah AC minimal 2 soal CSES (1646 dan 1662 paling cepat)

---

## Link Soal Online

| Soal | Platform | Fokus |
| ---- | -------- | ----- |
| [CSES 1646 — Static Range Sum](https://cses.fi/problemset/task/1646) | CSES | prefix polos |
| [CSES 1650 — Range XOR](https://cses.fi/problemset/task/1650) | CSES | prefix XOR |
| [CSES 1661 — Subarray Sums II](https://cses.fi/problemset/task/1661) | CSES | prefix + map |
| [CSES 1662 — Subarray Divisibility](https://cses.fi/problemset/task/1662) | CSES | sisa bagi |
| [LeetCode 560 — Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/) | LeetCode | prefix + map |
| [LeetCode 724 — Find Pivot Index](https://leetcode.com/problems/find-pivot-index/) | LeetCode | keseimbangan |
| [ABC 122 C — GeT AC](https://atcoder.jp/contests/abc122/tasks/abc122_c) | AtCoder | prefix count |

---

## Preview Day 30 — Prefix Sum 2D

Ide yang sama, tapi pengurangannya melibatkan **empat sudut**, dan satu bagian ikut
terkurang dua kali sehingga harus dikembalikan. Itu inklusi-eksklusi dalam bentuk paling
sederhana. Kalau `pre[0] = 0` sudah refleks, baris nol dan kolom nol di versi 2D akan
terasa wajar.
