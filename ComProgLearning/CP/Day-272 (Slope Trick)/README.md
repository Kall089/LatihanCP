# Day 272 — Slope Trick

> **Ide satu kalimat:** Memelihara fungsi konveks linier sepotong-sepotong (*piecewise linear convex function*) $f(x)$ secara dinamis menggunakan dua Priority Queue (Max-Heap dan Min-Heap) untuk titik-titik belok (*breakpoints*), mereduksi transisi DP bernilai mutlak atau batas monoton dari $\mathcal{O}(N^2)$ menjadi $\mathcal{O}(N \log N)$.

---

## 🎯 Tujuan Pembelajaran

- [ ] Memahami batasan DP koordinat $\mathcal{O}(N^2)$ pada masalah perataan barisan dan penyelarasan kendala monoton.
- [ ] Memahami karakteristik fungsi konveks linier sepotong-sepotong: kemiringan diskret (*slope* integer) dan titik-titik belok (*breakpoints*).
- [ ] Menguasai representasi fungsi dengan dua Priority Queue: Max-Heap `L` untuk lereng kiri (slope $< 0$) dan Min-Heap `R` untuk lereng kanan (slope $> 0$).
- [ ] Memahami operasi penambahan fungsi nilai mutlak $|x - a|$ serta penambahan lereng satu sisi $\max(0, x - a)$ dan $\max(0, a - x)$.
- [ ] Memahami operasi pemotongan kemiringan: Prefiks Minimum (kosongkan `R`) dan Sufiks Minimum (kosongkan `L`).
- [ ] Menguasai konvolusi infimal (*Minkowski sum*) menggunakan lazy tags untuk batas selisih tetangga $[D_{\min}, D_{\max}]$.
- [ ] Menguasai teknik reduksi indeks $(a_i - i)$ untuk mengubah kendala *strictly increasing* menjadi *non-decreasing* (Codeforces 713C).
- [ ] Menghubungkan Slope Trick dengan strategi *Regret Greedy* pada masalah perdagangan saham berulang (Codeforces 865D).

---

## 📁 Struktur Folder

```
Day-272 (Slope Trick)/
├── README.md
├── teori/
│   └── Day_272_Teori_Lengkap.md    (Motivasi, Piecewise Linear Convex, 2-Heap Representation, Primitif Operasi, Studi Kasus CF 713C & CF 865D)
├── latihan/
│   ├── exercise_1.cpp              (Mengubah Barisan Menjadi Terurut Tidak Menurun - Single Max-Heap)
│   ├── exercise_2.cpp              (Mengubah Barisan Menjadi Terurut Tegas Menaik - CF 713C Sonya and Problem Wi-Fi)
│   ├── exercise_3.cpp              (Mengubah Barisan Menjadi Terurut Tidak Menaik - Single Min-Heap / Suffix Min)
│   ├── exercise_4.cpp              (Mengatur Posisi Titik dengan Batas Jarak Maksimum - 2-Heap + Lazy Tags)
│   ├── exercise_5.cpp              (Penataan Barisan dengan Batas Selisih Umum [D_min, D_max] - General Slope Trick)
│   └── exercise_6.cpp              (Optimal Stock Trading - CF 865D Buy Low Sell High / Regret Greedy)
├── solusi/
│   ├── solution_1.cpp s.d. solution_6.cpp (Solusi optimal C++17 teruji AC dan terverifikasi)
├── tugas/
│   ├── tugas_01.cpp s.d. tugas_15.cpp     (15 tugas terstandar lengkap dengan batasan dan petunjuk)
└── template/
    └── template.cpp                (Boilerplate Master: Kelas SlopeTrick Lengkap + Lazy Tags + Minkowski Sum)
```

---

## 🧭 Panduan Belajar

### Langkah 1 — Pelajari Teori Lengkap (20 menit)
Buka [Day_272_Teori_Lengkap.md](teori/Day_272_Teori_Lengkap.md):
1. **Bagian 1 & 2**: Pahami bagaimana grafik fungsi konveks sepotong-sepotong berubah saat fungsi $|x - a|$ ditambahkan.
2. **Bagian 3 & 4**: Pelajari peran Max-Heap `L` dan Min-Heap `R`, serta bagaimana prefiks/sufiks minimum dieksekusi dalam $\mathcal{O}(1)$.
3. **Bagian 5**: Pahami trik reduksi indeks $a_i - i$ pada Codeforces 713C.

### Langkah 2 — Amati Master Template (10 menit)
Buka [template.cpp](template/template.cpp):
- Struktur kelas `SlopeTrick` dengan `min_val`, `tag_L`, `tag_R`, `L`, dan `R`.
- Fungsi `add_abs`, `add_right`, `add_left`, `prefix_min`, `suffix_min`, dan `shift`.

### Langkah 3 — Kerjakan 6 Latihan Terpandu (120 menit)

| # | Judul Latihan | Konsep Kunci & Arketipe | Tingkat | Target Waktu |
|---|---|---|---|---|
| 1 | **Barisan Tidak Menurun** | Foundational Slope Trick + Single Max-Heap | Sedang | 15 menit |
| 2 | **Barisan Tegas Menaik** | Index Reduction $(a_i - i)$ + CF 713C | Sulit | 20 menit |
| 3 | **Barisan Tidak Menaik** | Suffix Minimum + Single Min-Heap | Sedang | 15 menit |
| 4 | **Batas Jarak Maksimum Antar Titik** | Infimal Convolution + Lazy Tags 2-Heap | Sulit | 25 menit |
| 5 | **Batas Selisih Umum $[D_{\min}, D_{\max}]$** | Generalized Minkowski Sum Framework | Sulit | 25 menit |
| 6 | **Optimal Stock Trading** | Concave Profit Maximization + CF 865D | Menantang | 20 menit |

### Langkah 4 — Uji Pemahaman Mandiri (15 Tugas Praktik)
- `tugas_01.cpp` s.d. `tugas_05.cpp`: Ketinggian menara sinyal, spektrum frekuensi berpita pengaman, aliran irigasi menurun, konvoi drone terdeviasi, perataan termal server.
- `tugas_06.cpp` s.d. `tugas_10.cpp`: Emas batangan terbuka, jadwal kereta cepat, sensor topografi tegas, tiang kabel fiber berjarak, portofolio saham multi-aset.
- `tugas_11.cpp` s.d. `tugas_15.cpp`: Volume audio master, sudut robot manufaktur, jadwal batch pabrik, elevasi terasering sawah, arbitrase kripto dinamis.
