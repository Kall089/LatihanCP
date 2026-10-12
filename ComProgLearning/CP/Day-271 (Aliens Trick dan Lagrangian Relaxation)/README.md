# Day 271 — Aliens Trick dan Lagrangian Relaxation

> **Ide satu kalimat:** Mengeliminasi dimensi batas kapasitas atau jumlah operasi $K$ pada DP dengan memperkenalkan biaya penalti Lagrangian $\lambda$ per operasi, lalu menggunakan Binary Search (WQS Binary Search) untuk menemukan $\lambda^*$ yang memaksa DP memilih tepat $K$ operasi dalam waktu $\mathcal{O}(N \log(\text{Range}))$.

---

## 🎯 Tujuan Pembelajaran

- [ ] Memahami keterbatasan DP 2D berdimensi $(i, k)$ berbiaya $\mathcal{O}(N \cdot K)$ yang menyebabkan TLE untuk $N, K \ge 10^5$.
- [ ] Memahami syarat utama berlakunya Aliens Trick: fungsi biaya/keuntungan $f(k)$ terhadap jumlah operasi $k$ harus bersifat **konveks** (untuk minimasi) atau **konkaf** (untuk maksimasi).
- [ ] Memahami konsep **Lagrangian Relaxation**: mengenakan biaya penalti $\lambda$ setiap kali 1 operasi digunakan, mereduksi DP menjadi 1 dimensi $\mathcal{O}(N)$.
- [ ] Memahami interpretasi geometris garis singgung (*tangent line*) $y = -\lambda k + g(\lambda)$ pada kurva konveks $f(k)$.
- [ ] Menguasai **WQS Binary Search** untuk menemukan kemiringan penalti optimal $\lambda^*$.
- [ ] Menangani kasus titik segaris lurus (*collinear points*) dengan aturan tie-breaking yang konsisten.
- [ ] Mengombinasikan Aliens Trick dengan **Convex Hull Trick (CHT)** untuk mencapai $\mathcal{O}(N \log(\text{Range}))$.
- [ ] Menerapkan Aliens Trick pada berbagai variasi: *Stock IV*, *Activity Selection*, *K-Subarray Partitioning*, dan *IOI 2016 Aliens*.

---

## 📁 Struktur Folder

```
Day-271 (Aliens Trick dan Lagrangian Relaxation)/
├── README.md
├── teori/
│   └── Day_271_Teori_Lengkap.md    (Motivasi, Konveksitas f(k), Lagrangian Relaxation, WQS Binary Search, Collinear Points & Tie-Breaking, Analisis Kompleksitas)
├── latihan/
│   ├── exercise_1.cpp              (Beli dan Jual Saham dengan Maksimal K Transaksi - Stock IV)
│   ├── exercise_2.cpp              (Partisi Barisan dengan Kuadrat Jumlah Minimum - Aliens + CHT)
│   ├── exercise_3.cpp              (Memilih K Interval Berbobot Maksimum yang Saling Lepas - Weighted Disjoint Intervals)
│   ├── exercise_4.cpp              (Menutupi Titik dengan K Foto Kuadrat - IOI 2016 Aliens 1D)
│   ├── exercise_5.cpp              (Penempatan K Stasiun Relai Sinyal - Discrete Hop Optimization)
│   └── exercise_6.cpp              (Partisi Barisan dengan Biaya Kuadratik dan Biaya Tetap Segmen - Offset Invariance)
├── solusi/
│   ├── solution_1.cpp s.d. solution_6.cpp (Solusi optimal C++17 teruji AC dan terverifikasi)
├── tugas/
│   ├── tugas_01.cpp s.d. tugas_15.cpp     (15 tugas terstandar lengkap dengan batasan dan petunjuk)
└── template/
    └── template.cpp                (Boilerplate Master: AliensCHT, AliensStock, Binary Search Template)
```

---

## 🧭 Panduan Belajar

### Langkah 1 — Pelajari Teori Lengkap (20 menit)
Buka [Day_271_Teori_Lengkap.md](teori/Day_271_Teori_Lengkap.md):
1. **Bagian 1 & 2**: Pahami mengapa DP $\mathcal{O}(N \cdot K)$ lambat dan bagaimana konveksitas fungsi $f(k)$ memungkinkan optimasi.
2. **Bagian 3 & 4**: Pelajari formulasi penalti $\lambda$ dan mekanisme WQS Binary Search.
3. **Bagian 5**: Pelajari bahaya *collinear points* dan teknik tie-breaking yang benar.

### Langkah 2 — Amati Master Template (10 menit)
Buka [template.cpp](template/template.cpp):
- Modul 1: `AliensCHT::solve` — Minimasi kuadratik partisi $K$ segmen dengan CHT Deque $\mathcal{O}(1)$.
- Modul 2: `AliensStock::solve` — Maksimasi keuntungan transaksi saham dengan state machine 1D.

### Langkah 3 — Kerjakan 6 Latihan Terpandu (120 menit)

| # | Judul Latihan | Konsep Kunci & Arketipe | Tingkat | Target Waktu |
|---|---|---|---|---|
| 1 | **Beli dan Jual Saham K Transaksi** | Foundational Aliens Trick + 1D State Machine | Sedang | 15 menit |
| 2 | **Partisi Barisan Kuadrat Minimum** | Aliens Trick + Monotonic Convex Hull Trick (CHT) | Sulit | 25 menit |
| 3 | **Memilih K Interval Berbobot Maksimum** | Weighted Activity Selection + Binary Search Point | Sulit | 20 menit |
| 4 | **Menutupi Titik dengan K Foto Kuadrat** | IOI 2016 Aliens 1D Projection + CHT | Sulit | 25 menit |
| 5 | **Penempatan K Relai Sinyal** | Relay Hop Optimization + Quadratic Loss | Sulit | 20 menit |
| 6 | **Partisi Kuadratik + Biaya Tetap** | Fixed Overhead Invariance under Exact $K$ | Menantang | 15 menit |

### Langkah 4 — Uji Pemahaman Mandiri (15 Tugas Praktik)
- `tugas_01.cpp` s.d. `tugas_05.cpp`: Saham dengan komisi broker, partisi berbobot pengali, interval ber-cooldown, foto berbiaya bingkai, relai nirkabel.
- `tugas_06.cpp` s.d. `tugas_10.cpp`: Kargo kontainer kapal, komoditas emas ber-cooldown, batch server cloud, kamera pengawas tol, terminasi fiber optik.
- `tugas_11.cpp` s.d. `tugas_15.cpp`: Promosi belanja bebas bentrok, kluster sensor suhu, patroli drone, lintasan perakitan pabrik, rantai pasok multi-gudang.
