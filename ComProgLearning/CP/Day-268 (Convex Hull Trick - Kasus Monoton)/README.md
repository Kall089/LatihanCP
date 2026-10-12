# Day 268 — Convex Hull Trick (Kasus Monoton)

> **Ide satu kalimat:** Mengubah transisi DP berbentuk $dp[i] = \min_{j < i} \{ dp[j] + b[j] \cdot a[i] \}$ menjadi pencarian nilai ekstrem pada sekumpulan garis linear, memangkas kompleksitas dari $\mathcal{O}(N^2)$ menjadi $\mathcal{O}(N)$ menggunakan struktur data Deque.

---

## 🎯 Tujuan Pembelajaran

- [ ] Memahami bentuk aljabar rekurensi DP yang dapat diselesaikan dengan Convex Hull Trick:
  $$dp[i] = \min_{j < i} \{ dp[j] + b[j] \cdot a[i] + \text{cost}_i \}$$
- [ ] Menguasai pemetaan keadaan $j$ menjadi garis $y = m_j \cdot x + c_j$ dan kueri pada titik $x = a_i$.
- [ ] Memahami kondisi kasus monoton: kemiringan $m$ monoton dan titik kueri $x$ monoton.
- [ ] Menguasai uji eliminasi garis belakang (*cross product test*) menggunakan `__int128` anti-overflow:
  $$(c_2 - c_1)(m_2 - m_3) \ge (c_3 - c_2)(m_1 - m_2)$$
- [ ] Menguasai eliminasi garis depan (`pop_front`) berbiaya amortized $\mathcal{O}(1)$ saat kueri $x$ monoton menaik.
- [ ] Menerapkan CHT untuk transisi kuadratik (misal: $(h_i - h_j)^2 + C$) dan varian maksimasi (*Upper Convex Hull*).

---

## 📁 Struktur Folder

```
Day-268 (Convex Hull Trick - Kasus Monoton)/
├── README.md
├── teori/
│   └── Day_268_Teori_Lengkap.md    (Geometri Garis DP, Kondisi Monoton, Deque O(1), Uji Perkalian Silang, Ekspansi Kuadratik)
├── latihan/
│   ├── exercise_1.cpp              (Tarif Angkot di Hari Festival - Static Lines Monotone CHT)
│   ├── exercise_2.cpp              (Katak dan Batu Berkabut - Frog 3 Quadratic Transitions)
│   ├── exercise_3.cpp              (Relai Pengiriman di Jalur Pantai - Kalila and Dimna CHT)
│   ├── exercise_4.cpp              (Akuisisi Lahan Persegi Panjang - Dominance Pruning USACO Gold)
│   ├── exercise_5.cpp              (Penutup Jalan Berlubang - Covered Walkway Quadratic DP)
│   └── exercise_6.cpp              (Memaksimalkan Keuntungan Investasi - Upper Convex Hull Maximization)
├── solusi/
│   ├── solution_1.cpp s.d. solution_6.cpp (Solusi optimal C++17 teruji AC dan terverifikasi)
├── tugas/
│   ├── tugas_01.cpp s.d. tugas_15.cpp     (15 tugas CHT terstandar lengkap dengan petunjuk)
└── template/
    └── template.cpp                (Boilerplate Master CHT: MinConvexHull, MaxConvexHull, MinConvexHullBS)
```

---

## 🧭 Panduan Belajar

### Langkah 1 — Pelajari Teori CHT (20 menit)
Buka [Day_268_Teori_Lengkap.md](teori/Day_268_Teori_Lengkap.md):
1. **Bagian 1**: Pahami bagaimana perkalian silang $b_j \cdot a_i$ membentuk persamaan garis $y = mx + c$.
2. **Bagian 2**: Kuasai syarat monotonisitas dan mengapa Deque bisa bekerja dalam $\mathcal{O}(1)$ amortized.
3. **Bagian 3**: Pahami turunan perkalian silang uji eliminasi dan perlunya `__int128`.
4. **Bagian 4**: Kuasai teknik ekspansi kuadratik $(h_i - h_j)^2$.

### Langkah 2 — Amati Master Template (10 menit)
Buka [template.cpp](template/template.cpp):
- `MinConvexHull`: Untuk minimasi dengan kemiringan menurun dan kueri menaik.
- `MaxConvexHull`: Untuk maksimasi dengan kemiringan menaik dan kueri menaik.
- `MinConvexHullBS`: Jika kemiringan monoton tetapi kueri $x$ acak/tidak terurut ($\mathcal{O}(\log N)$).

### Langkah 3 — Kerjakan 6 Latihan Terpandu (120 menit)

| # | Judul Latihan | Konsep Kunci & Arketipe | Tingkat | Target Waktu |
|---|---|---|---|---|
| 1 | **Tarif Angkot di Hari Festival** | Static Lines Monotone CHT + Deque | Sedang | 15 menit |
| 2 | **Katak dan Batu Berkabut** | Frog 3 + Ekspansi Kuadratik $(h_i - h_j)^2$ | Sedang | 20 menit |
| 3 | **Relai Pengiriman di Jalur Pantai** | Kalila and Dimna Style DP Transisi Murni | Sulit | 20 menit |
| 4 | **Akuisisi Lahan Persegi Panjang** | Dominance Stack Pruning + USACO Gold CHT | Sulit | 25 menit |
| 5 | **Penutup Jalan Berlubang** | Covered Walkway Dynamic Interval CHT | Sulit | 20 menit |
| 6 | **Memaksimalkan Keuntungan Investasi** | Upper Convex Hull (Maksimasi) | Menantang | 20 menit |

### Langkah 4 — Uji Pemahaman Mandiri (15 Tugas Praktik)
- `tugas_01.cpp` s.d. `tugas_05.cpp`: Taksi paling mahal (Upper Hull), katak pajak pendaratan, biaya seluruh pos relai, potong pohon tercepat, penjadwalan mesin setup kuadratik.
- `tugas_06.cpp` s.d. `tugas_10.cpp`: Pengadaan kontainer penyimpanan, pembelian batch diskon linier, pipa air sambungan kuadratik, overhead mesin pabrik, balap sepeda efek slipstream.
- `tugas_11.cpp` s.d. `tugas_15.cpp`: Daya pancar radar (Upper Hull), pengelompokan pelanggan jarak kuadrat, relai sinyal satelit, rak buku ruang kosong, penumpukan kontainer crane.
