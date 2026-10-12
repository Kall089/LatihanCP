# 📅 Day 74 — Fractional Knapsack & Greedy Berbasis Rasio

> **Bulan 5–6 · Blok Greedy & Ad-hoc (Day 71–82)**
> Hari ini adalah garis pemisah paling tajam di seluruh blok greedy: **satu kata
> dalam soal** menentukan apakah jawabannya `O(n log n)` atau `O(n·W)`.

---

## 🎯 Tujuan Hari Ini

- [ ] Membaca soal knapsack mencari satu pertanyaan: **"boleh dipotong?"**
- [ ] Membuktikan fractional knapsack, dan menunjukkan **di langkah mana** bukti itu rusak pada 0/1
- [ ] Membandingkan rasio dengan **perkalian silang**, tidak pernah dengan `double`
- [ ] Menguasai keluarga knapsack lengkap dan **arah loop** masing-masing
- [ ] Mengenali **fractional programming** (rasio total → binary search)
- [ ] Memilih **dimensi DP** berdasarkan batasan yang mencolok

---

## 🔑 Satu Kata yang Menentukan Segalanya

| "Boleh dipotong?" | Teknik | Kompleksitas |
|---|---|---|
| **Ya** (fractional) | greedy rasio | `O(n log n)` |
| Tidak, sekali (0/1) | DP, loop **mundur** | `O(n·W)` |
| Tidak, berkali-kali (unbounded) | DP, loop **maju** | `O(n·W)` |
| Tidak, ≤ `c_i` kali (bounded) | DP + dekomposisi biner | `O(n·W·log c)` |

**Petunjuk dari batasan:** `W ≤ 10^18` → DP mustahil → soalnya fractional atau
punya struktur khusus.

---

## 💣 Contoh Tandingan Wajib Hafal

```
W = 10
(berat 6, nilai 7)   rasio 1.167
(berat 5, nilai 5)   rasio 1.000
(berat 5, nilai 5)   rasio 1.000

fractional : 7 + 4/5 · 5 = 11
0/1 greedy : 7          ← salah
0/1 optimal: 5 + 5 = 10
```

### Seberapa sering greedy rasio gagal pada 0/1?

Diukur langsung, bukan ditebak — **3.000 kasus acak** (`n ≤ 7`, `w ≤ 12`,
`v ≤ 20`, `W ≤ 25`):

> **11,2% gagal.**

Angka itu penting secara metodologis. Kalau kamu menguji ide greedy pada 5 sampel
dan semuanya lolos, peluangnya sekitar **53%** meski greedy-nya salah. **Lima
sampel tidak membuktikan apa pun.** Template hari ini menjalankan eksperimen ini
sendiri agar kamu melihat angkanya.

---

## 🧠 Inti Materi

### Kenapa fractional benar, 0/1 tidak

Bukti fractional memakai langkah:

> kurangi barang `y` sebanyak **berat δ**, tambahkan barang `x` sebanyak **berat δ**
> → `Δnilai = δ·(v_x/w_x − v_y/w_y) ≥ 0`

Langkah itu **hanya ada** kalau barang boleh dipotong. Pada 0/1 penukarannya harus
seluruh barang sekaligus, dan beratnya jarang cocok. Greedy choice property hilang.

### Membandingkan rasio dengan benar

```cpp
// ❌ rawan: double punya 53 bit mantissa, v & w sampai 10^9
return (double)v[a] / w[a] > (double)v[b] / w[b];

// ✅ eksak
return (__int128)v[a] * w[b] > (__int128)v[b] * w[a];
```

Komparator yang tidak konsisten melanggar strict weak ordering → `std::sort` bisa
**crash**, bukan sekadar salah.

### Arah loop — satu-satunya perbedaan 0/1 vs unbounded

```cpp
for (ll c = W; c >= w[i]; c--)   // MUNDUR → tiap barang sekali (0/1)
for (ll c = w[i]; c <= W; c++)   // MAJU   → boleh berkali-kali (unbounded)
```

### Dekomposisi biner (bounded)

Pecah `c_i` menjadi `1, 2, 4, ...` + sisa. Dengan potongan itu setiap jumlah
`0..c_i` bisa dibentuk. `O(log c)` potongan per jenis. **Potongan terakhir bukan
pangkat dua** — pakai `min(k, cnt)`.

### Fractional programming (rasio total)

`sum(a)/sum(b)` **tidak bisa** di-greedy. Ubah menjadi kelayakan:

```
sum(a)/sum(b) ≥ x  ⟺  sum(a_i − x·b_i) ≥ 0
```

Ambil `K` terbesar dari `d_i = a_i − x·b_i`, lalu binary search dengan **100
iterasi tetap** (Day 51). Ini generalisasi trik `a_i − x` dari soal "maksimalkan
rata-rata".

### Memilih dimensi DP

| Batasan | Tabel |
|---|---|
| `W` kecil, nilai besar | `dp[kapasitas] = nilai maks` |
| nilai kecil, `W` besar | `dp[nilai] = berat min` |
| keduanya besar, `n ≤ 40` | meet in the middle (Day 54) |

Batasan mencolok seperti `sum(v) ≤ 10^5` hampir selalu disengaja.

---

## 📁 Struktur Berkas

```
Day-74 (Fractional Knapsack dan Greedy Berbasis Rasio)/
├── README.md
├── teori/
│   └── Day_74_Teori_Lengkap.md
├── latihan/
│   ├── exercise_1.cpp   Perampokan Gudang Emas        (Easy)   fractional
│   ├── exercise_2.cpp   Membuktikan Greedy Gagal      (Easy)   greedy vs DP
│   ├── exercise_3.cpp   Mencampur Bahan Bakar         (Medium) minimasi
│   ├── exercise_4.cpp   Knapsack Bertingkat           (Medium) dekomposisi biner
│   ├── exercise_5.cpp   Rasio Terbaik                 (Hard)   fractional programming
│   └── exercise_6.cpp   Kapasitas Raksasa             (Hard)   DP di atas nilai
├── solusi/
│   └── solution_1..6.cpp
├── tugas/
│   └── tugas_01..15.cpp
└── template/
    └── template.cpp
```

---

## ✅ Semua Kode Sudah Diverifikasi

| Yang diuji | Cara | Hasil |
|---|---|---|
| Seluruh 30 berkas | `g++ -std=c++17 -O2 -Wall` | lolos |
| Solusi 1–6 | semua contoh masukan di soal | cocok |
| Solusi 1 (fractional) | 3.000 kasus acak vs `Fraction` eksak Python | cocok |
| Solusi 2 (greedy vs DP) | 3.000 kasus acak vs brute force `2^n` | cocok |
| Solusi 3 (minimasi) | 3.000 kasus acak vs referensi independen | cocok |
| Solusi 4 (bounded) | 2.000 kasus acak vs DP naif per buah | cocok |
| Solusi 5 (rasio) | 1.500 kasus acak vs seluruh `C(n,K)` | cocok |
| Solusi 6 (DP nilai) | 3.000 kasus acak vs brute force `2^n` | cocok |
| Template | 20.000 kasus: `fractional ≥ 0/1` | selalu benar |

Dua angka yang saya tulis sendiri ternyata salah dan sudah diperbaiki: sample
output Exercise 4 (`14` → `12`) dan komentar template fractional
(`10.833` → `11.000`). Tugas 08 dan 13 juga dikoreksi setelah dihitung ulang.

---

## ⚠️ Jebakan

1. **Greedy rasio pada 0/1** — gagal 11,2% kasus acak.
2. **Rasio dibandingkan sebagai `double`** — pakai perkalian silang.
3. **Lupa `__int128`** — `v·w` mencapai `10^18`, nyaris meluap di `long long`.
4. **`w = 0`** merusak perkalian silang (barang gratis tenggelam). Tangani terpisah.
5. **Arah loop DP terbalik** — mengubah 0/1 menjadi unbounded.
6. **Potongan terakhir dekomposisi biner** dihitung sebagai pangkat dua.
7. **Sentinel `INF` meluap** saat ditambah berat `10^9` pada DP di atas nilai.
8. **Menyangka `sum(a)/sum(b)` bisa di-greedy** — itu binary search.

---

## 🔗 Prasyarat & Kelanjutan

**Dipakai hari ini:** exchange argument (Day 71), 0/1 knapsack (Day 145),
binary search real (Day 51), `nth_element` (Day 45), monotonic deque (Day 37,
sebagai alternatif bounded).

**Tugas yang butuh materi lain:**

- Tugas 08 — meet in the middle (Day 54) → **terbuka**
- Tugas 05 — prefix sum + minimum berjalan (Day 29) → **terbuka**
- Tugas 10 — branch and bound; pemanasan untuk Day 63

**Berikutnya:**

- Day 75 — Huffman Coding & Greedy dengan Heap
- Day 76 — Greedy dengan Sorting Multi-Kriteria
- Day 77 — Greedy + Priority Queue (teknik regret)

---

## 📝 Checklist Penguasaan

- [ ] Refleks bertanya "boleh dipotong?" sebelum menulis kode knapsack
- [ ] Bisa menunjukkan **di langkah mana** bukti fractional rusak pada 0/1
- [ ] Hafal contoh tandingan `W=10`, `(6,7) (5,5) (5,5)`
- [ ] Tidak pernah lagi membandingkan rasio dengan pembagian
- [ ] Hafal arah loop untuk keempat varian knapsack
- [ ] Bisa mengubah `sum(a)/sum(b) ≥ x` menjadi bentuk tanpa pembagian
- [ ] Membaca batasan mencolok sebagai petunjuk dimensi DP
