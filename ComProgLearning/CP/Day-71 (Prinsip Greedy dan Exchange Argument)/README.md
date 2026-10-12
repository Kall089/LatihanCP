# 📅 Day 71 — Prinsip Greedy dan Exchange Argument

> **Bulan 5–6 · Blok Greedy & Ad-hoc (Day 71–82)**
> Hari pertama dari blok greedy. Fokusnya bukan menghafal algoritma, melainkan
> menguasai **cara memutuskan apakah sebuah ide greedy benar** — dan cara
> membantahnya dengan cepat kalau salah.

---

## 🎯 Tujuan Hari Ini

Setelah hari ini kamu harus bisa:

- [ ] Menjelaskan dua syarat yang membuat greedy sah: **greedy choice property** dan **optimal substructure**
- [ ] Menjalankan **exchange argument** empat langkah untuk membuktikan sebuah kriteria greedy
- [ ] **Menurunkan komparator** dari perbandingan dua elemen, bukan menebaknya
- [ ] Mengenali sinyal bahwa sebuah soal **bukan** soal greedy
- [ ] Membantah dugaan greedy dengan **stress test** dalam waktu di bawah 5 menit
- [ ] Menghindari jebakan komparator: pembagian, overflow, dan strict weak ordering

---

## 📚 Alur Belajar

| Urutan | Berkas | Perkiraan Waktu |
|---|---|---|
| 1 | `teori/Day_71_Teori_Lengkap.md` | 60–75 menit |
| 2 | `template/template.cpp` — baca dan jalankan | 15 menit |
| 3 | `latihan/exercise_1..6.cpp` | 2,5–3,5 jam |
| 4 | `solusi/solution_*.cpp` — hanya SETELAH mencoba sendiri | 45 menit |
| 5 | `tugas/tugas_01..15.cpp` | dikerjakan bertahap |

---

## 🧠 Inti Materi

### Exchange argument dalam empat langkah

1. Andaikan ada solusi **optimal** yang **melanggar** kriteria greedy-mu.
2. Cari dua elemen **berdampingan** yang melanggar kriteria itu.
3. **Tukar** keduanya, lalu hitung perubahan biayanya.
4. Tunjukkan biayanya **tidak memburuk** → kontradiksi, atau ada solusi optimal
   yang mengikuti kriteria greedy. Ulangi sampai seluruh solusi terurut.

Kenapa harus **berdampingan**? Karena penukaran dua elemen berdampingan tidak
mengubah apa pun untuk elemen di luar keduanya — waktu mulai elemen setelahnya
identik karena jumlah kedua durasi tidak berubah. Ini yang membuat
perhitungannya bisa disederhanakan sampai tersisa perbandingan dua elemen saja.

### Menemukan komparator (bukan menebaknya)

Pertanyaan ajaibnya selalu sama:

> **Kalau hanya ada DUA elemen, mana yang lebih dulu?**

Tuliskan biaya untuk kedua urutan, kurangkan, sederhanakan. Yang tersisa adalah
komparatormu.

| Soal | Pertidaksamaan | Komparator |
|---|---|---|
| Minimalkan jumlah waktu selesai | `t[i] < t[j]` | terpendek dulu (SPT) |
| Minimalkan jumlah `w[i]·C[i]` | `t[i]·w[j] < t[j]·w[i]` | rasio `t/w` menaik |
| Susun bilangan terbesar | `x+y > y+x` (string) | gabungan leksikografis |
| Pasangan hasil kali minimum | rearrangement inequality | satu naik, satu turun |

### Cheatsheet komparator

```cpp
// SPT — jumlah waktu selesai minimum
sort(t.begin(), t.end());

// Rasio — hindari pembagian, WAJIB long long (10^6 * 10^6 = 10^12 > int)
sort(a.begin(), a.end(), [](const P& x, const P& y) {
    return (ll)x.t * y.w < (ll)y.t * x.w;
});

// Gabungan string — perhatikan '>' STRICT, bukan '>='
sort(s.begin(), s.end(), [](const string& x, const string& y) {
    return x + y > y + x;
});
```

---

## ⚠️ Sinyal Bahwa Soal Ini BUKAN Greedy

| Sinyal | Kemungkinan besar |
|---|---|
| `n <= 20` | bitmask / brute force |
| `n <= 100` dan ada kapasitas | DP knapsack |
| Ada "pilih paling banyak K" dengan trade-off | DP |
| Jawabannya monoton terhadap sebuah nilai | binary search on answer |
| Idemu benar untuk 10 kasus lalu gagal | greedy-nya memang salah |

Batasan kecil hampir selalu berarti soal itu **sengaja** dibuat agar greedy gagal.

---

## 💣 Contoh Tandingan yang Wajib Kamu Hafal

| Klaim greedy | Contoh tandingan | Greedy | Optimal |
|---|---|---|---|
| Knapsack 0/1 pakai rasio tertinggi | `W=10`, barang `(6,7) (5,5) (5,5)` | 7 | 10 |
| Tukar uang pakai koin terbesar | koin `{1,3,4}`, bayar 6 | 3 keping | 2 keping |
| Interval: pilih yang terpendek dulu | `[1,10] [9,12] [11,20]` | 1 | 2 |
| Jembatan: tercepat selalu mengantar | `{1,2,5,10}` | 19 | 17 |

Empat contoh ini menutup sebagian besar kesalahan greedy yang akan kamu temui.

---

## 🔧 Jebakan Teknis

1. **Overflow di dalam komparator.** Array bertipe `long long` tidak menyelamatkanmu
   kalau komparatormu menerima `int`. `t*w` sampai `10^12`.
2. **Pembagian dalam komparator.** `(double)a/b < (double)c/d` bisa salah ketika dua
   rasio sangat dekat. Ubah menjadi `a*d < c*b`.
3. **Strict weak ordering.** Komparator harus memakai `<` atau `>` yang STRICT.
   Memakai `<=` membuat `std::sort` membaca di luar batas array → crash atau
   perilaku tak terduga.
4. **Lupa `long long` pada akumulasi.** `2·10^5` elemen bernilai `10^9` → total
   dengan mudah melampaui `int`.

---

## 📁 Struktur Berkas

```
Day-71 (Prinsip Greedy dan Exchange Argument)/
├── README.md
├── teori/
│   └── Day_71_Teori_Lengkap.md
├── latihan/
│   ├── exercise_1.cpp   Antrean Kasir              (Easy)
│   ├── exercise_2.cpp   Susun Bilangan Terbesar    (Easy)
│   ├── exercise_3.cpp   Membagi Apartemen          (Medium)
│   ├── exercise_4.cpp   Mencari Contoh Tandingan   (Medium)
│   ├── exercise_5.cpp   Urutan Tugas dengan Bobot  (Hard)
│   └── exercise_6.cpp   Menyeberangi Jembatan      (Hard)
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
| Solusi 3 (apartemen) | 3.000 kasus acak vs pencocokan brute force | cocok |
| Solusi 5 (rasio) | 3.000 kasus acak vs seluruh permutasi | cocok |
| Solusi 6 (jembatan) | 1.500 kasus acak vs Dijkstra atas ruang keadaan | cocok |
| Template (SPT) | 3.000 kasus acak vs seluruh permutasi | cocok |

Solusi 6 khususnya penting: greedy naif yang paling sering ditulis orang **gagal**
pada `{1,2,5,10}`, dan stress test itulah yang membuktikannya.

---

## 🔗 Prasyarat & Kelanjutan

**Sudah kamu kuasai (dipakai hari ini):** pengurutan dan komparator (Day 43–46),
dua pointer (Day 34), DP dasar (Day 145).

**Tugas yang butuh materi lain:**

- Tugas 03 (Towers) — butuh `multiset` / pencarian biner pada struktur (Day 49)
- Tugas 14 (Nested Ranges Count) — butuh Fenwick Tree (Day 170) + kompresi koordinat (Day 40).
  Keduanya sudah kamu kerjakan, jadi tugas ini **terbuka**.

**Berikutnya:**

- Day 72 — Activity Selection & Interval Scheduling (Tugas 05 adalah pemanasannya)
- Day 73 — Interval Covering & Merging Intervals
- Day 74 — Fractional Knapsack & Greedy Berbasis Rasio

---

## 📝 Checklist Penguasaan

- [ ] Bisa menuliskan exchange argument SPT dari nol tanpa melihat catatan
- [ ] Bisa menurunkan komparator rasio `t·w'` vs `t'·w` sendiri
- [ ] Hafal keempat contoh tandingan di tabel atas
- [ ] Refleks menulis stress test sebelum mengirim solusi greedy
- [ ] Selalu memeriksa overflow di dalam komparator
- [ ] Bisa menyebutkan minimal tiga sinyal "ini bukan soal greedy"
