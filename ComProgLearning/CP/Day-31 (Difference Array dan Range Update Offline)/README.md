# Day 29 — Difference Array & Range Update Offline

> **Ide satu kalimat:** kalau prefix sum mempercepat *bertanya*, difference array mempercepat *mengubah*.

---

## Tujuan Pembelajaran

Setelah menyelesaikan Day 29, kamu akan mampu:

- [ ] Menjelaskan hubungan **difference array ↔ prefix sum** (dua operasi yang saling membalik)
- [ ] Melakukan **range update** `a[L..R] += v` dalam **O(1)** per operasi
- [ ] Merekonstruksi array final dengan satu kali prefix sum **O(N)**
- [ ] Menjelaskan kenapa pengurang ditaruh di indeks **r + 1**, bukan r
- [ ] Mengenali pola **sweep line / event counting** ("paling banyak bersamaan")
- [ ] Menangani koordinat besar (sampai 10⁹) dengan kompresi kejadian
- [ ] Memperluas ke **Difference Array 2D** dengan empat titik penanda
- [ ] Membedakan kasus **offline** (difference array) vs **online** (segment tree + lazy)

---

## Struktur Folder

```
Day-29 (Difference Array)/
├── README.md               ← Panduan ini
├── teori/
│   └── Day_29_Teori_Lengkap.md     ← Teori lengkap 8 bagian
├── latihan/
│   ├── exercise_1.cpp   (Warm-up  : Range Update Sederhana)
│   ├── exercise_2.cpp   (Core     : Nilai Tertinggi Setelah Update)
│   ├── exercise_3.cpp   (Core     : Pengunjung Restoran Terbanyak / sweep line)
│   ├── exercise_4.cpp   (Challenge: Difference Array 2D — Cat Dinding)
│   ├── exercise_5.cpp   (Challenge: Kapasitas Bus Wisata)
│   └── exercise_6.cpp   (Contest  : Menyiram Tanaman — difference array terbalik)
├── solusi/
│   ├── solution_1.cpp   ← Solusi exercise_1
│   ├── solution_2.cpp   ← Solusi exercise_2
│   ├── solution_3.cpp   ← Solusi exercise_3
│   ├── solution_4.cpp   ← Solusi exercise_4
│   ├── solution_5.cpp   ← Solusi exercise_5
│   └── solution_6.cpp   ← Solusi exercise_6
├── tugas/
│   └── tugas_01.cpp     through   tugas_15.cpp
└── template/
    └── template.cpp     ← Starter: diff 1D, struct DiffArray, sweep line, diff 2D
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori Lengkap
Buka `teori/Day_29_Teori_Lengkap.md`. Fokus pada bagian **1 (Konsep & Intuisi)** dan **4 (Trace)** — di situ ada analogi sticky note HRD dan simulasi tabel yang membuat rumusnya "klik".

### Langkah 2 — Pelajari Template
Buka `template/template.cpp`. Ada empat bagian siap pakai:
`rangeUpdate` 1D, `struct DiffArray`, `SweepLine` untuk koordinat besar, dan `rangeUpdate2D`.

### Langkah 3 — Kerjakan Latihan (Berurutan)
```bash
g++ -O2 -std=c++17 latihan/exercise_1.cpp -o latihan/exercise_1
./latihan/exercise_1 < input.txt
```
Urutan `exercise_1 → exercise_6` sengaja disusun menanjak: dari rumus dasar,
sweep line, 2D, sampai membaca difference array secara terbalik.

### Langkah 4 — Cek Solusi (kalau macet > 30 menit)
Semua berkas di `solusi/` **sudah diverifikasi**: dikompilasi, dijalankan pada
seluruh sample di soal, dan diuji-stres melawan brute force dengan data acak.

### Langkah 5 — Kerjakan 15 Tugas Mandiri
`tugas_01.cpp` sampai `tugas_15.cpp`, dari Easy ke Hard.
Target minimal: **10 dari 15** selesai sebelum lanjut ke Day 30.

---

## Quick Reference — Cheatsheet Difference Array

```
DIFFERENCE ARRAY 1D
  • Deklarasi : vector<long long> diff(n + 2, 0);   // n+2, bukan n!
  • Update    : diff[l] += v;  diff[r + 1] -= v;    // O(1)
  • Bangun    : for (i = 1..n) diff[i] += diff[i-1];// O(n)
  • Dari array awal : diff[i] = a[i] - a[i-1];

DIFFERENCE ARRAY 2D  (submatriks (r1,c1)..(r2,c2))
  • d[r1][c1] += v;        d[r1][c2+1] -= v;
    d[r2+1][c1] -= v;      d[r2+1][c2+1] += v;
  • Rekonstruksi = prefix sum 2D

SWEEP LINE (koordinat sampai 1e9)
  • ev[s] += 1;  ev[e] -= 1;   lalu jalan menaik sambil menjumlah

Kompleksitas:
  • Update : O(1) per operasi
  • Bangun : O(N) sekali di akhir
  • Total  : O(N + Q)
  • Space  : O(N)

Tiga jebakan utama:
  ✗ vector<ll> diff(n)      → out of bounds saat r = n     (pakai n + 2)
  ✗ diff[r] -= v            → rentang kurang satu elemen   (pakai r + 1)
  ✗ vector<int>             → overflow saat Q x v besar     (pakai long long)

Kapan JANGAN dipakai:
  ✗ Ada query DI ANTARA update (online) → Segment Tree + Lazy / BIT
  ✗ Operasi tanpa kebalikan, misalnya max → tidak bisa dibatalkan
```

---

## Cara Cepat Mengenali Soal Difference Array

```
Ada update rentang "tambah v ke a[l..r]"?
├── Tidak → bukan difference array
└── Ya
    ├── Ada pertanyaan DI ANTARA update? (online)
    │   └── Ya → Segment Tree + Lazy Propagation
    └── Tidak — semua update dulu, baru dibaca (offline)
        └── DIFFERENCE ARRAY ✅
```

Kata kunci lain yang hampir selalu berarti teknik ini:
*"paling banyak bersamaan"*, *"ruangan minimal"*, *"berapa interval menutupi titik ini"*,
*"apakah kapasitas pernah terlampaui"*.

---

## Soal Online Judge Rekomendasi

### CSES Problem Set
- [Restaurant Customers](https://cses.fi/problemset/task/1619) — sweep line paling murni
- [Room Allocation](https://cses.fi/problemset/task/1164) — jumlah ruangan minimal

### LeetCode
- [1109. Corporate Flight Bookings](https://leetcode.com/problems/corporate-flight-bookings/) — difference array dasar
- [1094. Car Pooling](https://leetcode.com/problems/car-pooling/) — pengecekan kapasitas
- [1526. Minimum Number of Increments on Subarrays](https://leetcode.com/problems/minimum-number-of-increments-on-subarrays-to-form-a-target-array/) — sama dengan exercise 6
- [2536. Increment Submatrices by One](https://leetcode.com/problems/increment-submatrices-by-one/) — versi 2D

### Codeforces
- [CF 276C - Little Girl and Maximum Sum](https://codeforces.com/problemset/problem/276/C) — difference array + greedy
- [CF 1355C - Count Triangles](https://codeforces.com/problemset/problem/1355/C)

### AtCoder
- [ABC183D - Water Heater](https://atcoder.jp/contests/abc183/tasks/abc183_d) — kapasitas dengan difference array
- [ABC188D - Snuke Prime](https://atcoder.jp/contests/abc188/tasks/abc188_d) — koordinat besar

---

## Checklist Penyelesaian

- [ ] Membaca teori di `teori/Day_29_Teori_Lengkap.md` (terutama bagian Trace)
- [ ] Bisa menjelaskan sendiri **kenapa `r + 1`**, bukan `r`
- [ ] Menyelesaikan `exercise_1.cpp` (range update dasar)
- [ ] Menyelesaikan `exercise_2.cpp` (nilai maksimum + tie-breaking)
- [ ] Menyelesaikan `exercise_3.cpp` (sweep line koordinat besar)
- [ ] Menyelesaikan `exercise_4.cpp` (difference array 2D)
- [ ] Menyelesaikan `exercise_5.cpp` (pengecekan kapasitas)
- [ ] Menyelesaikan `exercise_6.cpp` (difference array terbalik)
- [ ] Mengerjakan minimal 10 dari 15 tugas mandiri
- [ ] Submit & AC **CSES Restaurant Customers** di online judge
- [ ] Bisa menjawab: kapan harus pindah ke Segment Tree + Lazy?

---

## Catatan Penomoran Hari

Pada `ROADMAP_CP.md`, Difference Array tercatat di **Day 31** (Day 29 = Prefix Sum 1D,
Day 30 = Prefix Sum 2D). Folder ini dibuat sebagai **Day 29** sesuai permintaan.
Kalau ingin selaras dengan roadmap, cukup ganti nama folder menjadi
`Day-31 (Difference Array)` dan ubah tulisan "Day: 29" di header tiap berkas.
