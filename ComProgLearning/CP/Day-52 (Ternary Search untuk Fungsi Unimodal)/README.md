# Day 52 — Ternary Search untuk Fungsi Unimodal

> **Ide satu kalimat:** satu titik tidak memberi informasi arah, tapi **dua** titik memberi cukup untuk membuang sepertiga ruang.

---

## Tujuan Pembelajaran

- [ ] Membedakan **unimodal** dari **monoton**
- [ ] Menjelaskan kenapa binary search **tidak berlaku** pada fungsi unimodal
- [ ] Menulis ternary search versi **real** dan **integer**
- [ ] Tahu kenapa versi integer butuh **penanganan akhir**
- [ ] Memakai **binary search pada selisih** — yang hampir selalu lebih baik untuk integer
- [ ] Mengenali kapan fungsinya **tidak** unimodal (gagal diam-diam)
- [ ] Memakai teorema **"max fungsi linear itu cembung"**

---

## Struktur Folder

```
Day-52 (Ternary Search untuk Fungsi Unimodal)/
├── README.md
├── teori/Day_52_Teori_Lengkap.md
├── latihan/exercise_1.cpp .. exercise_6.cpp
├── solusi/solution_1.cpp .. solution_6.cpp
├── tugas/tugas_01.cpp .. tugas_15.cpp
└── template/template.cpp
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (40 menit)

1. **Analogi mendaki dalam kabut** — kenapa **dua** titik cukup dan satu titik tidak.
2. **Bagian "binary search pada selisih"** (2). Ini yang akan kamu pakai paling sering,
   dan ia mengubah masalah unimodal menjadi masalah monoton dari Day 49.
3. **Trace 4.3** — kenapa ternary search integer punya kasus tepi, dan kenapa
   **dataran datar** membuatnya gagal.

### Langkah 2 — Template (10 menit)

Urutan pertimbangan yang harus jadi refleks:

```
1. Adakah solusi EKSAK?              median / rata-rata / -b/(2a)
2. Bisakah jadi binary search?       binary search pada selisih (integer)
3. Baru ternary search.              (domain real)
```

### Langkah 3 — Latihan (100 menit)

| # | Judul | Tingkat | Target | Konsep |
|---|-------|---------|--------|--------|
| 1 | Minimum Parabola | Easy | 15 mnt | kerangka, tanda perbandingan |
| 2 | Puncak Gunung | Easy | 15 mnt | binary search pada selisih |
| 3 | Dua Pelari | Medium | 20 mnt | kuadrat jarak, fungsi konstan |
| 4 | Biaya Perjalanan | Medium | 20 mnt | dataran, linear per bagian |
| 5 | Kelemahan (CF 578C) | Hard | 25 mnt | max fungsi linear, + Kadane |
| 6 | Padang Pasir | Hard | 20 mnt | rentang aman, titik patah |

Exercise 4 sengaja punya **dataran** ketika `A == C` — kasus di mana ternary search
tidak dijamin benar dan pendekatan kandidat menang.

### Langkah 4 — Tugas

**01–05** dasar dan diagnosis (LC 852, LC 162).
**06–10** terapan (CF 578C, CF 439D, ABC 279 D).
**11–15** level kontes; tugas 15 memintamu **mengukur sendiri** perbandingan
ternary vs binary — angkanya lebih meyakinkan daripada teori.

---

## Cheatsheet

```
MONOTON  -> binary search
UNIMODAL -> ternary search   (naik lalu turun, SATU puncak)

REAL (MINIMUM):
  for (int it = 0; it < 200; it++) {
      double m1 = lo + (hi - lo) / 3;
      double m2 = hi - (hi - lo) / 3;
      if (f(m1) < f(m2)) hi = m2;
      else               lo = m1;
  }
  MAKSIMUM: cari minimum dari -f(x)   <- lebih aman dari membalik tanda

INTEGER -> PAKAI BINARY SEARCH PADA SELISIH (lebih baik):
  while (lo < hi) {
      mid = lo + (hi - lo) / 2;
      if (f(mid) < f(mid + 1)) lo = mid + 1;   masih menanjak
      else                     hi = mid;
  }
  4x lebih cepat: buang 1/2 (bukan 1/3), 1 evaluasi (bukan 2), tanpa kasus tepi

BIAYA: f dievaluasi DUA KALI per iterasi, buang hanya 1/3
  rentang * (2/3)^k <= presisi  ->  butuh LEBIH BANYAK iterasi dari binary

SOLUSI EKSAK (jangan ternary kalau mengenalinya):
  sum |a[i] - x|   -> MEDIAN
  sum (a[i]-x)^2   -> RATA-RATA
  a*x^2 + b*x + c  -> -b / (2a)

TEOREMA BERGUNA: max dari fungsi-fungsi LINEAR selalu CEMBUNG -> unimodal
  (membebaskanmu dari membuktikan unimodalitas satu per satu)

BAHAYA: fungsi TIDAK unimodal -> GAGAL DIAM-DIAM
        fungsi punya DATARAN  -> f(m1) == f(m2), tidak ada info arah
UJI DULU dengan f(x) = (x-3)^2 pada [0,10] yang jawabannya 3
```

---

## Common Mistakes

1. **Memakai ternary pada fungsi tidak unimodal** — gagal **diam-diam**.
2. **Fungsi punya dataran** — `f(m1) == f(m2)` tanpa informasi arah.
3. **Tanda perbandingan terbalik** (minimum vs maksimum).
4. **Iterasi terlalu sedikit** — ternary butuh lebih banyak daripada binary.
5. **Versi integer tanpa penanganan akhir** — bisa macet.
6. **Lupa `f` dievaluasi dua kali** saat menghitung total biaya.
7. **Memakai ternary padahal ada solusi eksak.**
8. **Ternary bersarang tanpa menghitung biaya** — bisa 160000 evaluasi.

---

## Checklist Sebelum Lanjut ke Day 53

- [ ] Bisa menjelaskan kenapa dua titik cukup dan satu titik tidak
- [ ] Selalu menguji dengan `(x−3)²` sebelum mempercayai implementasi
- [ ] Untuk domain integer, refleks memakai binary search pada selisih
- [ ] Bisa menyebutkan tiga fungsi yang punya solusi eksak
- [ ] Tahu teorema "max fungsi linear itu cembung"
- [ ] Sudah menyelesaikan minimal exercise 1–4
- [ ] Sudah AC minimal 1 soal (LC 852 atau LC 162)

---

## Link Soal Online

| Soal | Platform | Fokus |
| ---- | -------- | ----- |
| [LC 852 — Peak Index in Mountain Array](https://leetcode.com/problems/peak-index-in-a-mountain-array/) | LeetCode | binary pada selisih |
| [LC 162 — Find Peak Element](https://leetcode.com/problems/find-peak-element/) | LeetCode | puncak lokal |
| [CF 578C — Weakness and Poorness](https://codeforces.com/problemset/problem/578/C) | Codeforces | ternary + Kadane |
| [CF 439D — Devu and his Brother](https://codeforces.com/problemset/problem/439/D) | Codeforces | fungsi cembung |
| [ABC 279 D — Freefall](https://atcoder.jp/contests/abc279/tasks/abc279_d) | AtCoder | ternary integer |
| [ABC 102 C — Linear Approximation](https://atcoder.jp/contests/abc102/tasks/arc100_a) | AtCoder | median |

---

## Preview Day 53 — Parallel Binary Search

Sejauh ini kita menjalankan **satu** binary search untuk **satu** pertanyaan.

Besok kamu akan menjalankan **ribuan binary search sekaligus** — bukan satu per satu
(yang akan terlalu lambat), melainkan berbarengan: kelompokkan seluruh pertanyaan
berdasarkan nilai tengah yang sedang mereka periksa, lalu proses seluruh kelompok
dalam satu sapuan. Teknik ini mengubah `O(q · n log n)` menjadi `O((n + q) log n)`.
