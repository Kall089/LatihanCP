# Day 44 — Merge Sort & Inversion Count

> **Ide satu kalimat:** kamu menulis merge sort bukan untuk mengurutkan, tapi untuk satu baris `inv += mid − i`.

---

## Tujuan Pembelajaran

- [ ] Menulis merge sort dengan konvensi `[l, r)` dan langkah merge yang benar
- [ ] Menjelaskan kenapa merge sort **stabil** dan `std::sort` tidak
- [ ] Menghitung **inversi** dalam O(n log n)
- [ ] Menjelaskan **kenapa** `mid − i` dan bukan `1`
- [ ] Membuktikan bahwa inversi = **pertukaran berdampingan minimum**
- [ ] Menyesuaikan pola untuk varian `a[i] > 2·a[j]` dengan **dua fase**
- [ ] Menggabungkan **k array** dengan heap dalam O(N log k)

---

## Struktur Folder

```
Day-44 (Merge Sort dan Inversion Count)/
├── README.md
├── teori/Day_44_Teori_Lengkap.md
├── latihan/exercise_1.cpp .. exercise_6.cpp
├── solusi/solution_1.cpp .. solution_6.cpp
├── tugas/tugas_01.cpp .. tugas_15.cpp
└── template/template.cpp
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (40 menit)

1. **Bagian "inversi: ide inti"** — fokus pada satu pertanyaan: *kenapa `mid − i`?*
   Kalau kamu bisa menjelaskannya ke orang lain, hari ini sudah selesai.
2. **Trace 4.2** — tabel penghitungan inversi langkah demi langkah, dengan verifikasi
   manual terhadap 9 pasangan.
3. **Bagian stabilitas** (4.3) — satu karakter `<=` vs `<`.

### Langkah 2 — Template (10 menit)

Simpan **satu** fungsi saja: `invCount`. Ia sudah mengurutkan **dan** menghitung
inversi. Tidak ada alasan menyimpan dua versi terpisah karena bedanya hanya satu baris.

Template juga berisi `inversiNaif` untuk **stress test**. Pakai itu.

### Langkah 3 — Latihan (90 menit)

| # | Judul | Tingkat | Target | Konsep |
|---|-------|---------|--------|--------|
| 1 | Gabung Dua Array | Easy | 10 mnt | langkah merge, salin sisa |
| 2 | Merge Sort dari Nol | Easy | 15 mnt | `[l, r)`, `tmp` di luar |
| 3 | Hitung Inversi | Medium | 20 mnt | `inv += mid − i` |
| 4 | Swap Berdampingan Minimum | Medium | 15 mnt | mengenali inversi menyamar |
| 5 | `a[i] > 2·a[j]` | Hard | 25 mnt | dua fase, overflow |
| 6 | Merge K Barisan | Hard | 25 mnt | heap, `greater<>` |

**Stress test wajib untuk exercise 3 dan 5.** Bug `+= 1` alih-alih `+= mid − i`
tidak terlihat pada sampel kecil.

### Langkah 4 — Tugas

**01–05** implementasi dan inversi dasar (LC 88, UVa 10810, SPOJ INVCNT).
**06–10** varian (LC 493, LC 23, CSES 1090).
**11–15** level kontes (LC 315, LC 4).

Tugas 14 (median dua array) sengaja **bukan** soal merge — ia adalah pengantar ke
binary search pada partisi, yang akan kamu pelajari di Day 48–50.

---

## Cheatsheet

```
mergeSort(l, r)   konvensi SETENGAH TERBUKA [l, r)
  if (r - l <= 1) return;
  mid = l + (r - l) / 2;              hindari overflow

MERGE (stabil karena '<='):
  tmp[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
  lalu SALIN SISA kedua-duanya, lalu SALIN tmp KEMBALI ke a

INVERSI -- satu baris:
  else { tmp[k++] = a[j++]; inv += mid - i; }
  KENAPA mid - i: kiri sudah terurut -> a[j] lebih kecil dari SELURUH sisa kiri

inv WAJIB long long          n = 1e5 -> 5e9
tmp dialokasikan SEKALI di luar rekursi

inversi = pertukaran BERDAMPINGAN minimum       (bukti: tiap tukar -1 inversi)
swap minimum kalau boleh tukar BEBAS = n - siklus     <- BERBEDA

VARIAN a[i] > 2*a[j] : DUA FASE
  fase 1 two pointers (j hanya maju), fase 2 merge biasa
  pakai 2LL * a[j] -- overflow nyata di sini

MERGE K ARRAY: min-heap butuh greater<>, lewati barisan kosong. O(N log k)

STRESS TEST WAJIB
```

---

## Kapan Pakai Apa

| Kebutuhan | Alat |
| --------- | ---- |
| Sekadar mengurutkan | `std::sort` (lebih cepat, lebih pendek) |
| Mengurutkan dan harus stabil | `std::stable_sort` |
| **Inversi** | merge sort ← satu-satunya alasan nyata |
| Inversi **per posisi** | BIT + kompresi (Day 38 + 170) |
| Merge k array | heap O(N log k), atau divide-and-conquer berpasangan |

---

## Common Mistakes

1. **`int` untuk inversi.** Bisa `5·10^9`.
2. **`inv += 1` alih-alih `inv += mid − i`.** Bug paling umum, sulit dilihat.
3. **`inv += mid − i` setelah `i` sudah maju.** Meleset satu.
4. **`<` alih-alih `<=`.** Merusak stabilitas dan menghitung pasangan kembar.
5. **Alokasi `tmp` di dalam rekursi.** Bisa 5× lebih lambat.
6. **`(l + r) / 2` pada indeks besar.** Biasakan `l + (r − l) / 2`.
7. **Lupa menyalin `tmp` kembali ke `a`.**
8. **Menggabungkan dua fase** pada varian `2·a[j]`.
9. **Lupa `greater<>`** pada `priority_queue` → hasil menurun.

---

## Checklist Sebelum Lanjut ke Day 45

- [ ] Bisa menulis merge sort dari ingatan dalam < 3 menit
- [ ] Bisa menjelaskan `mid − i` tanpa melihat catatan
- [ ] Bisa membuktikan inversi = swap berdampingan minimum
- [ ] Tahu bedanya dengan "swap bebas minimum" (`n − siklus`)
- [ ] Sudah melakukan stress test minimal sekali
- [ ] Sudah menyelesaikan minimal exercise 1–4
- [ ] Sudah AC minimal 2 soal (SPOJ INVCNT dan UVa 10810)

---

## Link Soal Online

| Soal | Platform | Fokus |
| ---- | -------- | ----- |
| [SPOJ INVCNT](https://www.spoj.com/problems/INVCNT/) | SPOJ | inversi klasik |
| [UVa 10810 — Ultra QuickSort](https://onlinejudge.org/) | UVa | inversi |
| [HR — Counting Inversions](https://www.hackerrank.com/challenges/ctci-merge-sort/) | HackerRank | inversi |
| [LC 88 — Merge Sorted Array](https://leetcode.com/problems/merge-sorted-array/) | LeetCode | merge in-place |
| [LC 493 — Reverse Pairs](https://leetcode.com/problems/reverse-pairs/) | LeetCode | dua fase |
| [LC 315 — Count of Smaller After Self](https://leetcode.com/problems/count-of-smaller-numbers-after-self/) | LeetCode | per posisi |
| [LC 23 — Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/) | LeetCode | heap |
| [CSES 1090 — Ferris Wheel](https://cses.fi/problemset/task/1090) | CSES | sort + two pointers |

---

## Preview Day 45 — Quick Sort, Quickselect & nth_element

Sisi lain dari divide and conquer. Merge sort membagi **secara buta** lalu bekerja
saat menggabungkan; quicksort bekerja saat **membagi** lalu menggabungkan secara gratis.

Konsekuensinya: pembagian quicksort **tidak dijamin seimbang**, sehingga ada kasus
terburuk O(n²). Sebagai gantinya ia bekerja **di tempat** (tanpa memori tambahan),
dan memberi `nth_element` yang menemukan elemen ke-k dalam **O(n)** — lebih cepat
daripada mengurutkan.
