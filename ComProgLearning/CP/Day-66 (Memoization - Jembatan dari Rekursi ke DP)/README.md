# Day 66 — Memoisasi: Jembatan Langsung dari Rekursi ke Dynamic Programming

> **Ide satu kalimat:** Memoisasi adalah teknik mengingat hasil setiap pemanggilan fungsi rekursif menggunakan tabel cache (*look-up table*), memangkas percabangan eksponensial $\mathcal{O}(2^N)$ menjadi polinomial atau linear $\mathcal{O}(N)$ hanya dengan menambahkan 3 baris logika.

---

## 🎯 Tujuan Pembelajaran

- [ ] Memahami fenomena "lupa ingatan" pada fungsi rekursif murni yang memicu kompleksitas waktu eksponensial $\mathcal{O}(2^N)$.
- [ ] Menguasai **Tiga Baris Sakti Memoisasi**:
  1. Pengecekan Cache (`if (seen[state]) return memo[state];`).
  2. Eksekusi Submasalah / Transisi.
  3. Pencatatan ke Cache dan Pengembalian Nilai (`return memo[state] = result;`).
- [ ] Mampu memilih struktur data cache yang tepat:
  - Vektor 1D / 2D dengan nilai sentinel `-1` (bila nilai sah $\ge 0$).
  - Vektor penanda terpisah `seen` (bila nilai sah bisa bernilai $0$ atau negatif).
  - Struktur `std::map` atau `std::unordered_map` (untuk state jarang / *sparse* atau koordinat besar).
- [ ] Memahami perbedaan filosofis antara **Top-Down (Memoisasi)** dan **Bottom-Up (Tabulasi)**, serta kelebihan dan kekurangannya.
- [ ] Menguasai analisis kompleksitas waktu Top-Down: $\mathcal{O}(\text{Banyak State Unik} \times \text{Waktu Transisi per State})$.

---

## 📁 Struktur Folder

```
Day-66 (Memoization - Jembatan dari Rekursi ke DP)/
├── README.md
├── teori/
│   └── Day_66_Teori_Lengkap.md    (Pohon Rekursi, 3 Baris Sakti, Sentinel, Top-Down vs Bottom-Up, Debug Checklist)
├── latihan/
│   ├── exercise_1.cpp              (Lampion di Tangga Kampung - 1D Memoization with Broken Steps)
│   ├── exercise_2.cpp              (Kurir di Pematang Sawah - Frog Jump Min Energy Top-Down)
│   ├── exercise_3.cpp              (Denah Festival Batik - 2D Grid Unique Paths with Obstacles Top-Down)
│   ├── exercise_4.cpp              (Pembagian Harta Warisan - 0/1 Knapsack Top-Down Memoization)
│   ├── exercise_5.cpp              (Subsekuens Bersama Terpanjang - LCS Top-Down Memoization)
│   └── exercise_6.cpp              (Perkalian Potongan Angka Maksimum - Integer Break Top-Down)
├── solusi/
│   ├── solution_1.cpp s.d. solution_6.cpp (Solusi optimal C++17 teruji AC dan terverifikasi)
├── tugas/
│   ├── tugas_01.cpp s.d. tugas_15.cpp     (15 tugas memoisasi terstandar lengkap dengan petunjuk)
└── template/
    └── template.cpp                (Boilerplate Master Memoisasi: 1D Sentinel, 1D Seen, 2D Knapsack, 2D String, Map Sparse)
```

---

## 🧭 Panduan Belajar

### Langkah 1 — Pelajari Teori Memoisasi (20 menit)
Buka [Day_66_Teori_Lengkap.md](teori/Day_66_Teori_Lengkap.md):
1. **Bagian 1**: Pahami visualisasi pohon rekursi Fibonacci yang berulang.
2. **Bagian 2**: Kuasai 3 baris sakti memoisasi.
3. **Bagian 3**: Ketahui kapan menggunakan sentinel `-1`, array `seen`, atau `map`.
4. **Bagian 4**: Pelajari tabel perbandingan Top-Down vs Bottom-Up.
5. **Bagian 5**: Simpan checklist debug untuk menghindari TLE, RTE, atau WA.

### Langkah 2 — Amati Master Template (10 menit)
Buka [template.cpp](template/template.cpp):
- `fib_memo(n, memo)`
- `frog_jump_memo(i, h, memo, seen)`
- `knapsack_top_down(i, s, w, v, memo)`
- `lcs_top_down(i, j, s, t, memo)`
- `grid_large_sparse(r, c)`

### Langkah 3 — Kerjakan 6 Latihan Terpandu (120 menit)

| # | Judul Latihan | Konsep Kunci & Arketipe | Tingkat | Target Waktu |
|---|---|---|---|---|
| 1 | **Lampion di Tangga Kampung** | Top-Down 1D dengan Tangga Rusak | Mudah | 15 menit |
| 2 | **Kurir di Pematang Sawah** | Frog Jump Min Energy Top-Down | Mudah-Sedang | 15 menit |
| 3 | **Denah Festival Batik** | Grid 2D Paths with Obstacles Top-Down | Sedang | 20 menit |
| 4 | **Pembagian Harta Warisan** | 0/1 Knapsack Top-Down 2D Memoization | Sedang | 25 menit |
| 5 | **Subsekuens Bersama Terpanjang** | LCS Two Strings Top-Down 2D Memoization | Sedang | 20 menit |
| 6 | **Perkalian Potongan Angka Maksimum** | Integer Break 1D Top-Down Memoization | Sedang | 25 menit |

### Langkah 4 — Uji Pemahaman Mandiri (15 Tugas Praktik)
- `tugas_01.cpp` s.d. `tugas_05.cpp`: Antrean buku (partisi 2 atau 3), robot pengurang bilangan (reduce to 1), pita tanpa tetangga ("11"), pemotong kayu palindromik min cuts, perjalanan benteng grid 2D.
- `tugas_06.cpp` s.d. `tugas_10.cpp`: House robber top-down, jarak edit Levenshtein top-down, penukaran koin keping minimum top-down, penggabungan tumpukan permen (merge stones interval DP), min cost climbing stairs.
- `tugas_11.cpp` s.d. `tugas_15.cpp`: Predict the winner kartu minimax, coin change II cara kombinasi, derangements (!N), min path sum grid 2D, word break segmentasi kata kamus.
