# Day 169 — Sparse Table & Idempotent Range Query

> **Ide satu kalimat:** dua blok yang **tumpang tindih** menutupi rentang apa pun — dan tumpang tindih tidak apa-apa karena `min(x, x) = x`.

---

## Tujuan Pembelajaran

- [ ] Menjelaskan arti **idempoten** dan kenapa itu syarat sparse table
- [ ] Build **O(n log n)**, query **O(1)**
- [ ] Menjelaskan kenapa dua blok tumpang tindih **selalu** cukup
- [ ] Tahu operasi mana yang bisa (min, max, gcd, AND, OR) dan mana yang tidak (sum, XOR)
- [ ] Menghitung `log2` **tanpa** `std::log2`
- [ ] Memilih antara prefix sum, sparse table, dan segment tree
- [ ] Tahu bahwa sparse table **tidak mendukung update**

---

## Struktur Folder

```
Day-169 (Sparse Table dan Idempotent Range Query)/
├── README.md
├── teori/Day_169_Teori_Lengkap.md
├── latihan/exercise_1.cpp .. exercise_6.cpp
├── solusi/solution_1.cpp .. solution_6.cpp
├── tugas/tugas_01.cpp .. tugas_15.cpp
└── template/template.cpp
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (40 menit)

1. **Bagian "kenapa tumpang tindih boleh"** — ini seluruh idenya dalam satu paragraf.
2. **Trace 4.3** — demonstrasi `sum` gagal dengan angka. Setelah melihat
   selisih 9 = daerah tumpang tindih, kamu tidak akan lupa syarat idempoten.
3. **Trace 4.4** — bahaya `std::log2`. Pendek, tapi bugnya bergantung lingkungan
   sehingga sangat sulit dilacak kalau tidak tahu.

### Langkah 2 — Template (10 menit)

Tiga detail yang paling sering salah — verifikasi ketiganya sebelum submit:

```cpp
for (i = 0; i + (1 << k) <= n; i++)          // 1. batas, bukan i < n
return op(sp[k][l], sp[k][r - (1 << k) + 1]) // 2. +1 pada blok kanan
lg[i] = lg[i/2] + 1                          // 3. tabel, bukan std::log2
```

### Langkah 3 — Latihan (95 menit)

| # | Judul | Tingkat | Target | Konsep |
|---|-------|---------|--------|--------|
| 1 | Minimum Rentang | Easy | 20 mnt | build + query, tiga detail |
| 2 | Kenapa Sum Tidak Bisa | Easy | 15 mnt | idempoten vs invers |
| 3 | GCD pada Rentang | Medium | 10 mnt | operasi diganti, struktur sama |
| 4 | Di Mana Minimumnya | Medium | 20 mnt | simpan indeks, aturan seri |
| 5 | Selisih Terbatas | Hard | 20 mnt | + binary search, lalu two pointers |
| 6 | Nilai Tersering | Hard | 25 mnt | run-length, kasus satu blok |

### Langkah 4 — Tugas

**01–05** dasar (CSES 1647, SPOJ RMQSQ).
**06–10** varian (LC 1438, SPOJ FREQUENT, CF 475D, sparse table 2D).
**11–15** level kontes; tugas 11 adalah pratinjau **Day 202** (LCA via RMQ),
tugas 15 memperkenalkan **disjoint sparse table** untuk operasi non-idempoten.

---

## Cheatsheet

```
sp[k][i] = op pada a[i .. i + 2^k - 1]

BUILD O(n log n):
  for (k = 1; k < K; k++)
      for (i = 0; i + (1 << k) <= n; i++)          <- BATAS
          sp[k][i] = op(sp[k-1][i], sp[k-1][i + (1 << (k-1))]);

QUERY O(1):
  k = lg[r - l + 1];
  return op(sp[k][l], sp[k][r - (1 << k) + 1]);    <- +1

IDEMPOTEN op(x,x) = x  -> boleh TUMPANG TINDIH
  BISA  : min, max, gcd, lcm, AND, OR
  TIDAK : sum (x+x=2x), XOR (x^x=0)  -> prefix sum (punya INVERS)

log2: lg[i] = lg[i/2] + 1   ATAU  31 - __builtin_clz(len)
      JANGAN std::log2 (floating point, log2(8) bisa jadi 2.9999999)
      __builtin_clz(0) TAK TERDEFINISI

TIDAK MENDUKUNG UPDATE. Memori n log n (n=1e6 -> 80 MB, berisiko).

POHON KEPUTUSAN
  ada update?              -> segment tree / Fenwick (Day 170, 172)
  sum/xor tanpa update     -> prefix sum (Day 29)
  min/max/gcd tanpa update -> SPARSE TABLE
  jendela geser ukuran tetap -> monotonic deque (Day 37)

VARIAN: simpan INDEKS -> "di mana minimumnya" -> fondasi LCA O(1) (Day 202)
```

---

## Common Mistakes

1. **Sparse table untuk `sum` atau `XOR`** — tumpang tindih terhitung dua kali.
2. **`std::log2`** — bug yang bergantung lingkungan.
3. **Batas build `i < n`** — membaca di luar array.
4. **`r - (1<<k)` tanpa `+1`** — off-by-one klasik.
5. **Mengira ada update** — satu update memaksa rebuild `O(n log n)`.
6. **Memori** — `n log n` untuk `n = 10^6` adalah 80 MB.
7. **`__builtin_clz(0)`** — perilaku tak terdefinisi.
8. **Aturan seri tidak konsisten** antara build dan query pada varian indeks.

---

## Checklist Sebelum Lanjut ke Day 170

- [ ] Bisa menulis sparse table dari ingatan dalam < 2 menit
- [ ] Bisa menjelaskan kenapa `sum` gagal, dengan contoh angka
- [ ] Hafal tiga detail yang sering salah
- [ ] Tahu kapan memilih prefix sum vs sparse table vs segment tree
- [ ] Sudah menyelesaikan minimal exercise 1–4
- [ ] Sudah AC minimal 1 soal (CSES 1647 paling cepat)

---

## Link Soal Online

| Soal | Platform | Fokus |
| ---- | -------- | ----- |
| [CSES 1647 — Static Range Minimum](https://cses.fi/problemset/task/1647) | CSES | sparse table murni |
| [CSES 1646 — Static Range Sum](https://cses.fi/problemset/task/1646) | CSES | pembanding: prefix sum |
| [SPOJ RMQSQ](https://www.spoj.com/problems/RMQSQ/) | SPOJ | RMQ klasik |
| [SPOJ FREQUENT](https://www.spoj.com/problems/FREQUENT/) | SPOJ | run-length + RMQ |
| [CF 475D — CGCDSSQ](https://codeforces.com/problemset/problem/475/D) | Codeforces | gcd pada rentang |
| [LC 1438 — Longest Subarray with Limit](https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/) | LeetCode | maks-min terbatas |

---

## Preview Day 170 — Fenwick Tree

Sparse table memberi query `O(1)` tetapi **array harus statis**. Besok kamu
akan belajar struktur yang menyelesaikan kelemahan itu: Fenwick Tree memberi
`O(log n)` untuk **query dan update**, dengan kode yang justru lebih pendek
(sepuluh baris) dan memori hanya `O(n)`.

Ia juga yang membuka tugas-tugas di **Day 38, 44, 49, dan 53** yang selama ini
menunggu prasyarat.
