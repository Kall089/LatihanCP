# Day 142 — Top-Down vs Bottom-Up & Cara Mendesain State

> **Ide satu kalimat:** Dua gaya penulisan yang mengevaluasi rekurens matematika yang sama; kuncinya bukan menghafal kode, melainkan menguasai **Empat Uji Desain State** untuk menentukan kapan sebuah dimensi baru harus ditambahkan.

---

## 🎯 Tujuan Pembelajaran

- [ ] Memahami perbedaan cara kerja internal, kelebihan, dan kelemahan **Top-Down (Memoization)** vs **Bottom-Up (Tabulation)**.
- [ ] Menguasai metodologi **Empat Uji Desain State**: Bisa dikalimatkan, Cukup informasinya (Markov property), Setara, dan Muat.
- [ ] Mampu mengenali kapan harus menambah dimensi state (misal: riwayat pilihan terakhir, sisa sumber daya/kupon, status FSM).
- [ ] Mengetahui batasan memori stack C++ dan cara menghindari Runtime Error karena **Stack Overflow**.
- [ ] Memahami dasar optimasi memori menggunakan **Rolling Array** ($O(N) \to O(1)$).
- [ ] Menyelesaikan 6 latihan bertingkat dan 15 tugas mandiri.

---

## 📁 Struktur Folder

```
Day-142 (Top-Down vs Bottom-Up dan Cara Mendesain State)/
├── README.md
├── teori/
│   └── Day_142_Teori_Lengkap.md   (Materi komprehensif, diagram ASCII, trace, pitfall)
├── latihan/
│   ├── exercise_1.cpp             (Frog 1 - Top-Down vs Bottom-Up)
│   ├── exercise_2.cpp             (Frog 2 - Dynamic Transitions K)
│   ├── exercise_3.cpp             (Vacation - State Pilihan Terakhir)
│   ├── exercise_4.cpp             (Satu Kupon di Jalur Dieng - State Sumber Daya)
│   ├── exercise_5.cpp             (Saham dengan Cooldown - State Machine DP)
│   └── exercise_6.cpp             (Lampu Taman Sejumlah K - Counting DP Multi-Dimensi)
├── solusi/
│   ├── solution_1.cpp s.d. solution_6.cpp (Solusi optimal, C++17, verified AC)
├── tugas/
│   ├── tugas_01.cpp s.d. tugas_15.cpp     (15 latihan mandiri dengan format standar)
└── template/
    └── template.cpp               (Boilerplate Top-Down, Bottom-Up, Rolling, Multi-D)
```

---

## 🧭 Panduan Belajar

### Langkah 1 — Pelajari Teori (45 menit)
Buka [Day_142_Teori_Lengkap.md](teori/Day_142_Teori_Lengkap.md):
1. **Bagian 1 & 2**: Pahami perbedaan pohon pemanggilan rekursi vs graf dependensi DAG, serta bahaya nyata stack overflow pada $N > 10^5$.
2. **Bagian 3**: Kuasai **Empat Uji Desain State** (Bisa dikalimatkan, Cukup informasinya, Setara, Muat).
3. **Bagian 4**: Pelajari studi kasus mengapa Vacation, Saham, dan Kupon membutuhkan dimensi tambahan.
4. **Bagian 7**: Pahami prinsip dan batasan Rolling Array.

### Langkah 2 — Amati Template (10 menit)
Buka [template.cpp](template/template.cpp):
- Pola Top-Down dengan reset cache dan penanda `visited` (mencegah bug sentinel collision).
- Pola Bottom-Up terurut secara topologis.
- Pola Rolling Array.

### Langkah 3 — Kerjakan 6 Latihan Bertingkat (120 menit)

| # | Judul Latihan | Konsep Kunci | Tingkat | Target Waktu |
|---|---|---|---|---|
| 1 | **Lompat Katak Dasar (Frog 1)** | Perbandingan Top-Down vs Bottom-Up 1D | Mudah | 15 menit |
| 2 | **Lompat Katak K Langkah (Frog 2)** | Transisi dinamis $K$ langkah | Mudah-Sedang | 20 menit |
| 3 | **Pekan Komunitas Kreatif (Vacation)** | State dimensi tambahan: aktivitas kemarin | Sedang | 25 menit |
| 4 | **Satu Kupon di Jalur Dieng** | State dimensi tambahan: kupon terpakai/belum | Sedang | 25 menit |
| 5 | **Saham dengan Cooldown** | Finite State Machine DP (Hold, Sold, Rest) | Sedang-Menantang | 25 menit |
| 6 | **Lampu Taman Sejumlah K** | Counting DP dengan batasan $K$ dan larangan bertetangga | Menantang | 30 menit |

### Langkah 4 — Uji & Evaluasi Mandiri (15 Tugas)
Kerjakan soal-soal di folder `tugas/` untuk memantapkan pemahaman desain state:
- `tugas_01.cpp` s.d. `tugas_04.cpp`: Transisi 1D & pengujian terminal state.
- `tugas_05.cpp` s.d. `tugas_08.cpp`: Penambahan dimensi pilihan & sumber daya terbatas.
- `tugas_09.cpp` s.d. `tugas_12.cpp`: State run-length & dekomposisi struktur melingkar.
- `tugas_13.cpp` s.d. `tugas_15.cpp`: State non-monoton, kapasitas baterai, dan alokasi tugas bergantian.

---

## 🔗 Tautan Latihan Online Judge

- [AtCoder Educational DP Contest — A: Frog 1](https://atcoder.jp/contests/dp/tasks/dp_a)
- [AtCoder Educational DP Contest — B: Frog 2](https://atcoder.jp/contests/dp/tasks/dp_b)
- [AtCoder Educational DP Contest — C: Vacation](https://atcoder.jp/contests/dp/tasks/dp_c)
- [LeetCode 309 — Best Time to Buy and Sell Stock with Cooldown](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/)
- [CSES Problem Set — Dice Combinations / Coin Combinations](https://cses.fi/problemset/)
