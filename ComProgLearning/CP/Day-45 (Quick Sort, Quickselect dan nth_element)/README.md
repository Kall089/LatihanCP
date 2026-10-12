# Day 45 — Quick Sort, Quickselect & nth_element

> **Ide satu kalimat:** jangan tulis quicksort — tapi ketahui `nth_element`, karena mencari elemen ke-k tidak butuh pengurutan.

---

## Tujuan Pembelajaran

- [ ] Menulis partisi **Lomuto** dan menjelaskan invariantnya
- [ ] Menjelaskan kenapa quicksort punya kasus terburuk **O(n²)** dan merge sort tidak
- [ ] Menjelaskan kenapa **pivot acak** menyelesaikan masalah itu
- [ ] Menulis **quickselect** dan menjelaskan kenapa rata-ratanya **O(n)**
- [ ] Memakai `nth_element`, `partial_sort`, `partition` dengan tepat
- [ ] Menangani banyak kembaran dengan **partisi tiga arah**
- [ ] Tahu kapan **heap ukuran k** mengalahkan quickselect

---

## Struktur Folder

```
Day-45 (Quick Sort, Quickselect dan nth_element)/
├── README.md
├── teori/Day_45_Teori_Lengkap.md
├── latihan/exercise_1.cpp .. exercise_6.cpp
├── solusi/solution_1.cpp .. solution_6.cpp
├── tugas/tugas_01.cpp .. tugas_15.cpp
└── template/template.cpp
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (40 menit)

1. **Bagian "kebalikan dari merge sort"** — merge bekerja saat menggabung,
   quick bekerja saat membagi. Satu kalimat ini menjelaskan seluruh perbedaan
   sifat keduanya.
2. **Trace 4.3 (kasus terburuk)** — array yang sudah terurut memicu O(n²)
   dengan pivot deterministik. Justru masukan yang paling sering muncul.
3. **Trace 4.4 (tiga arah)** — kenapa array penuh kembaran selesai dalam O(n).

### Langkah 2 — Template (10 menit)

Yang benar-benar perlu kamu ingat bukan kodenya, melainkan tabel ini:

```
butuh seluruh array terurut      -> sort
butuh k terkecil TERURUT         -> partial_sort   O(n log k)
butuh elemen ke-k saja           -> nth_element    O(n)
butuh k terbesar dari STREAM     -> heap ukuran k  O(n log k), ruang O(k)
butuh memisahkan berdasarkan syarat -> partition   O(n)
```

### Langkah 3 — Latihan (90 menit)

| # | Judul | Tingkat | Target | Konsep |
|---|-------|---------|--------|--------|
| 1 | Elemen Terbesar ke-K | Easy | 10 mnt | `nth_element`, konversi indeks |
| 2 | Partisi Genap-Ganjil | Easy | 15 mnt | partisi sebagai pola umum |
| 3 | Quickselect Manual | Medium | 25 mnt | pivot acak, tanpa rekursi |
| 4 | Tiga Warna | Medium | 20 mnt | `i` tidak maju saat tukar kanan |
| 5 | K Titik Terdekat | Hard | 15 mnt | komparator, kuadrat jarak |
| 6 | K Terbesar dari Stream | Hard | 25 mnt | batas memori memaksa heap |

Exercise 6 punya batas memori **16 MB** yang sengaja dibuat ketat: `nth_element`
mustahil di sana. Ini melatih kebiasaan menghitung memori sebelum memilih algoritma.

### Langkah 4 — Tugas

**01–05** terapan STL dan implementasi dasar (LC 215, LC 75).
**06–10** varian (LC 973, LC 347, CSES 1091).
**11–15** level kontes (LC 324, CF 977C, SPOJ MKTHNUM).

Tugas 11 dan 12 sengaja **tidak bisa** diselesaikan dengan quickselect —
keduanya melatih pemilihan alat, bukan penerapan.

---

## Cheatsheet

```
LOMUTO (pivot = a[hi]):
  i = lo;
  for (j = lo; j < hi; j++) if (a[j] <= pivot) swap(a[i++], a[j]);
  swap(a[i], a[hi]); return i;

DUA PERTAHANAN WAJIB kalau menulis sendiri:
  1. pivot ACAK (mt19937, JANGAN rand())
  2. rekursi ke sisi KECIL, iterasi ke sisi besar -> stack O(log n)

QUICKSELECT: telusuri SATU sisi -> n + n/2 + n/4 + ... = 2n = O(n)
  tanpa rekursi, ruang O(1)

TIGA ARAH (Dutch flag):
  a[i] < p  -> swap(a[lt++], a[i++])
  a[i] > p  -> swap(a[i], a[gt--])     i TIDAK maju
  a[i] == p -> i++
  syarat loop: i <= gt

STL:
  nth_element(b, b+k, e)   elemen ke-k (0-based), O(n), MENGUBAH array
  partial_sort(b, b+k, e)  k terkecil TERURUT, O(n log k)
  partition(b, e, pred)    O(n)   |  stable_partition  versi stabil

terbesar ke-K -> indeks n-K   |  terkecil ke-K -> indeks K-1
k TERBESAR pakai MIN-heap (perlu greater<int>)
bandingkan KUADRAT jarak, jangan sqrt
```

---

## Common Mistakes

1. **Pivot deterministik.** Array terurut → O(n²).
2. **`rand()` alih-alih `mt19937`.** `RAND_MAX` bisa hanya 32767.
3. **Rekursi ke kedua sisi.** Stack bisa O(n).
4. **Lupa `nth_element` mengubah array** dan **tidak** mengurutkan.
5. **`i` maju setelah tukar dengan `gt`** pada partisi tiga arah.
6. **Off-by-one `k`.** `nth_element(b, b+k, e)` memberi terkecil ke-`(k+1)`.
7. **Lupa `greater<int>`** pada min-heap.
8. **Memakai `sqrt`** untuk membandingkan jarak.
9. **Menulis quicksort sendiri** padahal `std::sort` cukup.

---

## Checklist Sebelum Lanjut ke Day 46

- [ ] Bisa menjelaskan kenapa quickselect O(n) dan merge sort O(n log n)
- [ ] Bisa menjelaskan kenapa pivot acak wajib, dengan contoh masukan
- [ ] Hafal tabel `sort` / `partial_sort` / `nth_element` / heap
- [ ] Bisa menjelaskan kenapa `i` tidak boleh maju pada partisi tiga arah
- [ ] Sudah menyelesaikan minimal exercise 1–4
- [ ] Sudah AC minimal 2 soal (LC 215 dan LC 75 paling cepat)

---

## Link Soal Online

| Soal | Platform | Fokus |
| ---- | -------- | ----- |
| [LC 215 — Kth Largest Element](https://leetcode.com/problems/kth-largest-element-in-an-array/) | LeetCode | quickselect |
| [LC 75 — Sort Colors](https://leetcode.com/problems/sort-colors/) | LeetCode | Dutch flag |
| [LC 973 — K Closest Points](https://leetcode.com/problems/k-closest-points-to-origin/) | LeetCode | `nth_element` |
| [LC 347 — Top K Frequent](https://leetcode.com/problems/top-k-frequent-elements/) | LeetCode | counting + seleksi |
| [LC 324 — Wiggle Sort II](https://leetcode.com/problems/wiggle-sort-ii/) | LeetCode | median + penempatan |
| [CSES 1091 — Concert Tickets](https://cses.fi/problemset/task/1091) | CSES | multiset |
| [CF 977C — Less or Equal](https://codeforces.com/problemset/problem/977/C) | Codeforces | kasus tepi |
| [SPOJ MKTHNUM](https://www.spoj.com/problems/MKTHNUM/) | SPOJ | k-th pada rentang |

---

## Preview Day 46 — Counting, Radix & Bucket Sort

Semua yang kita lihat sejauh ini adalah pengurutan berbasis **perbandingan**,
dan kelas itu punya batas bawah teoretis `Ω(n log n)` yang tidak bisa dilanggar.

Besok kita melanggarnya — bukan dengan trik, melainkan dengan **tidak membandingkan
sama sekali**. Counting sort yang sekilas kamu lihat di Day 40 akan kembali sebagai
algoritma penuh, bersama radix sort yang mengurutkan `10^7` bilangan lebih cepat
daripada `std::sort`.
