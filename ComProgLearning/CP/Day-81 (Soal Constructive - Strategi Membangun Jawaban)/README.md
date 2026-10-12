# 📅 Day 81 — Soal Constructive: Strategi Membangun Jawaban

> **Bulan 5–6 · Blok Greedy & Ad-hoc (Day 71–82)**
> Soal yang meminta kamu **membangun objek**, bukan menghitung nilai — dan karena
> jawabannya biasanya banyak, cara mengujinya juga berbeda.

---

## 🎯 Tujuan Hari Ini

- [ ] **Menulis pemeriksa sebelum menulis konstruksi**
- [ ] Menguasai lima strategi konstruksi
- [ ] Memeriksa **kemustahilan** lebih dulu (paritas / pencacahan / batas)
- [ ] Mengawasi **titik sambung** antar blok konstruksi
- [ ] Menguji **seluruh** `n` kecil, bukan beberapa pilihan
- [ ] **Memverifikasi klaim "mustahil"** dengan brute force

---

## 🔑 Aturan Emas

> **Selalu tulis pemeriksa (checker) sebelum menulis konstruksi.**

Soal constructive punya **banyak jawaban benar**. Untuk `n = 4`, jawaban
`2 3 4 1`, `4 3 2 1`, dan `2 1 4 3` semuanya benar. Karena itu membandingkan
keluaranmu dengan contoh di soal **tidak bisa** dipakai untuk menguji.

Pemeriksa wajib memvalidasi **tiga** hal:

1. **Ukuran** keluaran benar
2. **Rentang** sah dan tidak ada duplikat
3. **Syarat khusus** soal terpenuhi

Nomor 1 dan 2 paling sering rusak akibat salah indeks — dan paling sering
dilupakan.

---

## 🧠 Lima Strategi

| # | Strategi | Contoh |
|---|---|---|
| 1 | Pola dari kasus kecil | derangement: geser satu langkah |
| 2 | Bangun rekursif (`n` dari `n−1` atau `n/2`) | barisan pangkat dua |
| 3 | Konstruksi baku lalu perbaiki | mulai dari identitas, balik blok |
| 4 | **Buktikan mustahil dulu** | paritas total, pencacahan |
| 5 | Greedy lalu tambal | pilih serakah, perbaiki pelanggaran |

Strategi 4 adalah yang paling **murah** — sering menyelesaikan separuh kasus uji
tanpa kerja sama sekali.

### Kasus mustahil yang layak dihafal

| Soal | Mustahil ketika |
|---|---|
| Derangement `1..n` | `n = 1` |
| Selisih tetangga ≠ 1 | `n = 2` atau `n = 3` |
| Tepat `k` posisi bergeser | `k = 1` |
| Bagi `1..n` jadi dua bagian sama | `n(n+1)/2` ganjil |
| Selisih berbeda tepat `k` | `k > n − 1` |
| Matriks baris-kolom seimbang | `n = 2` |

`k = 1` mustahil karena memindahkan **tepat satu** elemen tidak mungkin —
himpunan posisi yang bergeser membentuk gabungan siklus, dan siklus terpendek
berukuran 2.

---

## ⚠️ Titik Sambung: Contoh Nyata

Soal: susun `1..n` tanpa dua tetangga berselisih 1.

**Ganjil dulu, lalu genap:**

```
n = 5 : 1 3 5 2 4      ✓
n = 6 : 1 3 5 2 4 6    ✓
n = 7 : 1 3 5 7 2 4 6  ✓
n = 4 : 1 3 2 4        ✗   |3 − 2| = 1
```

**Gagal hanya di `n = 4`.** Kalau kamu menguji `n = 5, 6, 7` saja, kamu akan
submit lalu WA.

**Genap dulu, lalu ganjil:** sambungnya adalah genap terbesar dan angka 1 —
selisih minimal 3 untuk `n ≥ 4`. Aman.

> Bug ini benar-benar muncul saat saya menulis template hari ini. Versi pertama
> memakai ganjil-dulu, dan pemeriksa melaporkan **tepat satu** kegagalan dari
> `n = 4..300`.

**Pelajarannya:** pada konstruksi yang menggabungkan blok, titik sambung hampir
selalu menjadi tempat kesalahan. Periksa secara eksplisit, dan uji **seluruh**
`n` kecil.

---

## 🧪 Cara Menguji yang Benar

```
untuk n = 1 sampai 200:
    hasil = bangun(n)
    kalau kodeku bilang mustahil:
        VERIFIKASI dengan brute force bahwa memang tidak ada
    kalau tidak:
        periksa(hasil, n) harus true
```

Memverifikasi klaim **"mustahil"** adalah bagian yang paling sering dilewatkan.
Kalau kodemu bilang mustahil padahal sebenarnya ada jawaban, pemeriksa biasa
tidak akan pernah menangkapnya.

---

## 📁 Struktur Berkas

```
Day-81 (Soal Constructive - Strategi Membangun Jawaban)/
├── README.md
├── teori/
│   └── Day_81_Teori_Lengkap.md
├── latihan/
│   ├── exercise_1.cpp   Permutasi Tanpa Titik Tetap    (Easy)   pemeriksa
│   ├── exercise_2.cpp   Tetangga Tidak Berurutan       (Easy)   titik sambung
│   ├── exercise_3.cpp   Tepat K Bergeser               (Medium) baku + perbaiki
│   ├── exercise_4.cpp   Membagi Jadi Dua Bagian Sama   (Medium) paritas + greedy
│   ├── exercise_5.cpp   Matriks Baris-Kolom Seimbang   (Hard)   Latin ortogonal
│   └── exercise_6.cpp   Selisih Berbeda Tepat K        (Hard)   gabung dua pola
├── solusi/
│   └── solution_1..6.cpp
├── tugas/
│   └── tugas_01..15.cpp
└── template/
    └── template.cpp
```

---

## ✅ Semua Kode Sudah Diverifikasi

Karena ini soal constructive, seluruh verifikasi memakai **pemeriksa**, bukan
perbandingan keluaran.

| Yang diuji | Cara | Hasil |
|---|---|---|
| Seluruh 29 berkas | `g++ -std=c++17 -O2 -Wall` | lolos |
| Solusi 1 (derangement) | pemeriksa untuk **seluruh** `n = 1..300` | lolos |
| Solusi 2 (tanpa tetangga) | pemeriksa `n = 1..300` + brute force `n ≤ 7` | lolos |
| Solusi 3 (tepat `k`) | **seluruh** pasangan `(n,k)`, `n ≤ 60` (~1.800 kasus) | lolos |
| Solusi 4 (bagi dua) | pemeriksa `n = 1..400`, termasuk klaim `NO` | lolos |
| Solusi 5 (matriks) | pemeriksa 3 syarat, seluruh `n` ganjil `1..59` | lolos |
| Solusi 6 (selisih `k`) | **seluruh** pasangan `(n,k)`, `n ≤ 50` | lolos |
| Template | 4 konstruksi diuji untuk seluruh `n` kecil | 0 kegagalan |

Perhatikan pola verifikasinya: **seluruh** nilai parameter, bukan sampel acak.
Untuk soal constructive itu justru lebih murah dan jauh lebih andal.

Exercise 5 juga diganti seluruhnya di tengah jalan: versi awalnya meminta matriks
untuk `n` sembarang, tetapi ternyata `n = 2` **mustahil** dan `n` genap ≥ 4 butuh
konstruksi yang jauh lebih rumit. Versinya sekarang dibatasi ke `n` ganjil, dengan
konstruksi persegi Latin ortogonal yang buktinya bersih.

---

## ⚠️ Jebakan

1. **Tidak menulis pemeriksa.**
2. **Membandingkan dengan jawaban contoh.**
3. **Lupa `n = 1, 2, 3`.**
4. **Titik sambung antar blok** tidak diperiksa.
5. **Tidak memverifikasi klaim "mustahil".**
6. **Menguji beberapa `n` pilihan**, bukan seluruhnya.
7. **Lupa format keluaran** untuk kasus mustahil (`-1` vs `IMPOSSIBLE` vs `NO`).
8. **Sisa negatif** dari `%` di C++ — tulis `((x % n) + n) % n`.

---

## 🔗 Prasyarat & Kelanjutan

**Dipakai hari ini:** verifikasi (Day 79), ad-hoc (Day 80), paritas (Day 82),
permutasi (Day 61), graf (Day 113).

**Berikutnya:** Day 82 — Invariant, Parity & Monovariant (penutup blok greedy).

---

## 📝 Alur Kerja Soal Constructive

```
1. kenali kata "mana saja" di soal
2. TULIS PEMERIKSA dulu
3. periksa kemustahilan (paritas / pencacahan / batas)
4. bangun jawaban untuk n = 1..6 dengan tangan
5. cari polanya, perumum
6. jalankan pemeriksa untuk SELURUH n = 1..200
7. verifikasi klaim "mustahil" dengan brute force
```
