# 📅 Day 79 — Cara Membuktikan (atau Membantah) Greedy

> **Bulan 5–6 · Blok Greedy & Ad-hoc (Day 71–82)**
> Hari ini tidak memperkenalkan algoritma baru. Ia memberi **perkakas** untuk
> memutuskan apakah sebuah ide greedy benar — dan itu lebih berharga daripada
> algoritma mana pun di blok ini.

---

## 🎯 Tujuan Hari Ini

- [ ] Membalik urutan kerja: **brute force dulu, greedy kemudian**
- [ ] Menulis tiga bentuk brute force yang jelas benar
- [ ] **Merancang** generator untuk memecahkan kodemu, bukan "acak saja"
- [ ] Mengecilkan contoh tandingan secara otomatis
- [ ] Memilih di antara **empat alat bukti**
- [ ] Mengenali tanda-tanda greedy akan gagal dari batasan soal

---

## 🔑 Urutan Kerja yang Benar

```
❌ SALAH                          ✅ BENAR
1. punya ide greedy               1. tulis BRUTE FORCE      (5 menit)
2. yakin ia benar                 2. tulis GENERATOR yang dirancang
3. tulis kodenya    (20 menit)    3. baru tulis greedy
4. submit                         4. adu ribuan kali        (30 detik)
5. WA                             5. kalau lolos, BARU cari buktinya
6. tidak tahu kenapa
```

**Menulis bukti untuk ide yang salah** adalah pemborosan waktu terbesar di kontes.
Uji dulu, buktikan kemudian.

---

## 📊 Angka yang Layak Diingat

Persentase kegagalan **diukur langsung** oleh kode di folder ini, bukan ditebak:

| Klaim greedy | Gagal |
|---|---|
| Knapsack 0/1 pakai rasio tertinggi | **~11–12%** |
| Tukar uang pakai koin terbesar | **~9–10%** |
| Interval terpendek dulu | ~2% |
| Antrean bermodal pakai `m` menurun (Day 76) | ~2% |

### Kenapa ini penting

Kalau kamu menguji ide greedy pada **5 sampel** dan semuanya lolos, sementara ide
itu gagal 12% dari waktu, peluang lolos lima kali adalah `0,88^5 ≈ 53%`.

> **Lima sampel tidak membuktikan apa pun.**

Pada tingkat kegagalan 2%, kamu butuh ~150 kasus untuk peluang 95% menemukannya.
Karena itu stress test harus **ribuan** kasus — dan itu murah.

---

## 🎲 Generator Menentukan Kesimpulan

Eksperimen di Exercise 3 menghitung ini **secara eksak** (bukan disimulasikan):

Bug: soal "dua elemen **bernilai berbeda** dengan jumlah terbesar", kode salah
mengambil dua terbesar tanpa memeriksa keunikan.

| Rentang generator | Peluang bug terlihat |
|---|---|
| `1..3` | **33,333333%** |
| `1..1.000.000` | **0,000100%** |

**Bug yang sama. Generator berbeda. Kesimpulan berlawanan.**

### Tabel rentang menurut yang ingin dipecahkan

| Yang diuji | Rentang | Ukuran |
|---|---|---|
| Tie-break, nilai berulang | **sangat kecil** `0..3` | kecil |
| Interval tumpang tindih | kecil `0..15` | kecil |
| Overflow | **maksimum** `10^18` | maksimum |
| Presisi pecahan | dua nilai hampir sama | kecil |
| Kasus tepi | — | `n = 1, 2`, semua sama |

---

## 🧠 Empat Alat Bukti

| Alat | Bentuk | Cocok untuk |
|---|---|---|
| **Exchange argument** | tukar dua elemen berdampingan, tunjukkan tidak memburuk | Day 71, 72, 74, 76, 78 |
| **Greedy stays ahead** | setelah langkah ke-`k`, greedy tidak lebih buruk | activity selection |
| **Dominasi keadaan** | keadaan greedy mendominasi semua keadaan lain | regret (Day 77) |
| **Batas bawah = batas atas** | temukan batas bawah, tunjukkan greedy mencapainya | ruangan minimum |

**Penyaring cepat dari alat ketiga:** kalau keadaan tidak bisa diringkas menjadi
**satu angka** yang bisa dibandingkan, dominasi tidak bisa dirumuskan — dan greedy
kemungkinan besar salah.

---

## ⚠️ Tanda Greedy Akan Gagal

| Tanda | Kemungkinan besar |
|---|---|
| `n ≤ 20` | bitmask / brute force |
| `n ≤ 100` + kapasitas | DP knapsack |
| Ada **bobot** per elemen | curigai DP |
| **Dua besaran bersaing** | hampir pasti DP |
| Jawaban monoton | binary search on answer |

**Batasan kecil hampir selalu disengaja.** Kalau soal memberi `n ≤ 18` padahal
algoritmamu `O(n log n)`, kamu hampir pasti salah membaca soal.

---

## 💣 Contoh Tandingan Wajib Hafal

| Klaim | Contoh tandingan | Greedy | Optimal |
|---|---|---|---|
| Knapsack 0/1 rasio | `W=10`, `(6,7) (5,5) (5,5)` | 7 | 10 |
| Koin terbesar | `{1,3,4}`, bayar 6 | 3 | 2 |
| Interval terpendek dulu | `[1,10] [9,12] [11,20]` | 1 | 2 |
| Interval mulai terkecil | `[1,100] [2,3] [4,5]` | 1 | 2 |
| Jembatan senter | `{1,2,5,10}` | 19 | 17 |
| Huffman sekuensial | `{1,1,1,1,1,1}` | 20 | 16 |

---

## 📁 Struktur Berkas

```
Day-79 (Cara Membuktikan atau Membantah Greedy)/
├── README.md
├── teori/
│   └── Day_79_Teori_Lengkap.md
├── latihan/
│   ├── exercise_1.cpp   Menguji Klaim Tukar Uang     (Easy)   pembanding
│   ├── exercise_2.cpp   Contoh Tandingan Terkecil    (Easy)   pengecilan
│   ├── exercise_3.cpp   Pengaruh Rentang Generator   (Medium) hitung eksak
│   ├── exercise_4.cpp   Enam Klaim                   (Medium) enam brute force
│   ├── exercise_5.cpp   Menebak Kriteria dari Data   (Hard)   penemuan empiris
│   └── exercise_6.cpp   Kerangka Stress Test Generik (Hard)   perkakas
├── solusi/
│   └── solution_1..6.cpp
├── tugas/
│   └── tugas_01..15.cpp
└── template/
    └── template.cpp    ← salin ke template pribadimu
```

---

## ✅ Semua Kode Sudah Diverifikasi

| Yang diuji | Cara | Hasil |
|---|---|---|
| Seluruh 29 berkas | `g++ -std=c++17 -O2 -Wall` | lolos |
| Solusi 1–6 | semua contoh masukan di soal | cocok |
| Solusi 1 (tukar uang) | 4.000 kasus vs DP referensi | cocok |
| Solusi 2 (pengecilan) | 2.000 kasus: hasil **tetap** contoh tandingan sah | cocok |
| Solusi 3 (peluang) | dibandingkan dengan aritmetika **pecahan eksak** Python | cocok |
| Solusi 4 (enam klaim) | keenam klaim diperiksa manual + brute force | cocok |
| Solusi 5 (kriteria) | 4.000 kasus vs seluruh permutasi | cocok |
| Solusi 6 (kerangka) | dijalankan pada ketiga soal, hasil reproducible | cocok |

### Temuan yang layak dicatat

Saat menulis Solusi 2, stress test menemukan sesuatu yang tidak saya duga:
**mengurutkan keluaran justru merusak contoh tandingannya.**

```
(6,6) (5,5) (5,2), W=10  →  greedy 6, optimal 7   ✓ contoh tandingan
(5,2) (5,5) (6,6), W=10  →  greedy 7, optimal 7   ✗ bukan lagi
```

Sebabnya: greedy memakai tie-break indeks saat rasio seri, sehingga hasilnya
**sensitif terhadap urutan masukan**. Ketika algoritma yang diuji sensitif urutan,
urutan adalah bagian dari contoh tandingan itu sendiri — dan naluri "urutkan agar
deterministik" dari Day 76 justru salah di sini. Soal dan solusinya sudah
disesuaikan, dan jebakan ini didokumentasikan di dalam komentar.

---

## ⚠️ Jebakan

1. **Menulis greedy dulu, brute force belakangan** (atau tidak sama sekali).
2. **Generator berentang besar** — bug tidak akan pernah muncul.
3. **Menguji hanya puluhan kasus.**
4. **Menganalisis contoh tandingan besar** tanpa mengecilkannya.
5. **Membuktikan ide yang salah.**
6. **Brute force yang "dioptimalkan"** — setiap optimasi adalah kesempatan salah.
7. **Membandingkan greedy dengan greedy lain**, bukan dengan jawaban pasti benar.
8. **Benih acak berbasis waktu** — hasil tidak bisa direproduksi.
9. **Mengurutkan hasil** ketika algoritmanya sensitif urutan.

---

## 🔗 Prasyarat & Kelanjutan

**Dipakai hari ini:** seluruh Day 71–78.

**Berikutnya:**

- Day 80 — Soal Ad-hoc: Melatih Observasi
- Day 81 — Soal Constructive
- Day 82 — Invariant, Parity & Monovariant

---

## 📝 Daftar Periksa Sebelum Submit Solusi Greedy

1. Sudahkah aku menulis brute force?
2. Sudahkah aku menjalankan minimal 10.000 kasus?
3. Apakah generatorku memakai rentang nilai **kecil**?
4. Sudahkah aku mencoba `n = 1`, `n = 2`, dan semua-nilai-sama?
5. Sudahkah aku mencoba struktur khusus (terurut, satu outlier)?
6. **Apakah aku bisa menuliskan buktinya dalam tiga kalimat?**
7. Apakah batasan soal masuk akal untuk `O(n log n)`?

Kalau nomor 6 tidak bisa dijawab, jangan submit.
