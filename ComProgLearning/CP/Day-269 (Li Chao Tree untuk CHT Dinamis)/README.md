# Day 269 — Li Chao Tree untuk CHT Dinamis

> **Ide satu kalimat:** Struktur data variasi Segment Tree yang menyimpan garis-garis linear pada setiap simpulnya, memungkinkan penambahan garis berurutan acak dan kueri nilai minimum/maksimum pada titik kueri acak dalam waktu $\mathcal{O}(\log N)$ tanpa memerlukan pengurutan kemiringan.

---

## 🎯 Tujuan Pembelajaran

- [ ] Memahami keterbatasan CHT Deque saat kemiringan $m$ atau titik kueri $x$ tidak terurut.
- [ ] Memahami invarian simpul Li Chao Tree: simpul interval $[l, r]$ menyimpan garis terbaik pada titik tengah $mid$.
- [ ] Menguasai algoritma `add_line`: menukar garis di $mid$ dan menurunkan garis yang kalah ke anak kiri atau kanan dalam $\mathcal{O}(\log N)$.
- [ ] Menguasai algoritma `query`: mencari nilai ekstrem di sepanjang lintasan akar hingga daun (*root-to-leaf path*) dalam $\mathcal{O}(\log N)$.
- [ ] Menguasai penambahan segmen garis $[L, R]$ dengan dekomposisi kanonik Segment Tree dalam $\mathcal{O}(\log^2 N)$.
- [ ] Menguasai variasi Li Chao Tree untuk kasus maksimasi (*Upper Li Chao Tree*) dan DP kuadratik acak.

---

## 📁 Struktur Folder

```
Day-269 (Li Chao Tree untuk CHT Dinamis)/
├── README.md
├── teori/
│   └── Day_269_Teori_Lengkap.md    (Struktur Li Chao Tree, Invariant Midpoint, Swap & Pushdown, Range Segments [L, R], Analisis Kompleksitas)
├── latihan/
│   ├── exercise_1.cpp              (Papan Tarif yang Terus Berubah - Dynamic Li Chao Tree)
│   ├── exercise_2.cpp              (Katak di Pegunungan Acak - Non-Monotone Frog Jump)
│   ├── exercise_3.cpp              (Promo Hanya untuk Zona Tertentu - Line Segments Li Chao)
│   ├── exercise_4.cpp              (Relai Komunikasi Acak - Arbitrary Kalila & Dimna)
│   ├── exercise_5.cpp              (Penjadwalan Server dengan Penalti Acak - Task Scheduling)
│   └── exercise_6.cpp              (Memaksimalkan Nilai Portofolio Dinamis - Max Li Chao Tree)
├── solusi/
│   ├── solution_1.cpp s.d. solution_6.cpp (Solusi optimal C++17 teruji AC dan terverifikasi)
├── tugas/
│   ├── tugas_01.cpp s.d. tugas_15.cpp     (15 tugas Li Chao Tree terstandar lengkap dengan petunjuk)
└── template/
    └── template.cpp                (Boilerplate Master Li Chao Tree: MinLiChaoTree, DynamicLiChaoTree)
```

---

## 🧭 Panduan Belajar

### Langkah 1 — Pelajari Teori Li Chao Tree (20 menit)
Buka [Day_269_Teori_Lengkap.md](teori/Day_269_Teori_Lengkap.md):
1. **Bagian 1**: Pahami mengapa CHT Deque gagal pada data acak.
2. **Bagian 2**: Pelajari pembuktian mengapa dua garis berpotongan maksimal sekali sehingga penurunan garis hanya masuk ke satu anak.
3. **Bagian 3**: Pahami evaluasi kueri jalur akar ke daun.
4. **Bagian 4**: Pelajari dekomposisi segmen garis terbatas $[L, R]$.

### Langkah 2 — Amati Master Template (10 menit)
Buka [template.cpp](template/template.cpp):
- `MinLiChaoTree`: Li Chao Tree berbasis kompresi koordinat untuk minimasi.
- `DynamicLiChaoTree`: Li Chao Tree dinamis dengan pointer untuk domain luas tanpa kompresi.

### Langkah 3 — Kerjakan 6 Latihan Terpandu (120 menit)

| # | Judul Latihan | Konsep Kunci & Arketipe | Tingkat | Target Waktu |
|---|---|---|---|---|
| 1 | **Papan Tarif yang Terus Berubah** | Offline Coordinate Compression + Dynamic Lines & Queries | Sedang | 15 menit |
| 2 | **Katak di Pegunungan Acak** | Non-Monotone Frog Jump + Quadratic Transition | Sulit | 20 menit |
| 3 | **Promo Hanya untuk Zona Tertentu** | Line Segments $[L, R]$ Li Chao Tree | Sulit | 25 menit |
| 4 | **Relai Komunikasi Acak** | Arbitrary Slopes & Queries DP (Kalila & Dimna Generalized) | Sulit | 20 menit |
| 5 | **Penjadwalan Server dengan Penalti Acak** | Task Scheduling Dynamic Linear DP | Sulit | 20 menit |
| 6 | **Memaksimalkan Nilai Portofolio Dinamis** | Max Li Chao Tree (Upper Hull Maximization) | Menantang | 20 menit |

### Langkah 4 — Uji Pemahaman Mandiri (15 Tugas Praktik)
- `tugas_01.cpp` s.d. `tugas_05.cpp`: Harga maksimum dinamis, katak berpajak acak, promo titik akhir, pemilihan mesin produksi bebas, jaringan transmisi nirkabel acak.
- `tugas_06.cpp` s.d. `tugas_10.cpp`: Pengadaan material promo terbatas, penataan kontainer dermaga gravitasi acak, pipa gas elevasi gunung, penjadwalan server bobot fleksibel, penyewaan kendaraan lintas provinsi.
- `tugas_11.cpp` s.d. `tugas_15.cpp`: Partisi sinyal digital reduksi noise kuadratik, sensor cuaca selisih ekstrem, pembagian beban GPU latensi kuadrat, rute drone variasi angin, penilaian hak tambang dinamis.
