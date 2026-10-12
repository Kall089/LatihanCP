# 📅 Day 76 — Greedy dengan Sorting Multi-Kriteria

> **Bulan 5–6 · Blok Greedy & Ad-hoc (Day 71–82)**
> Satu pertanyaan menguasai seluruh hari ini: **ketika kriteria pertama seri,
> apa yang menentukan urutan?**

---

## 🎯 Tujuan Hari Ini

- [ ] Menulis komparator berlapis dengan **bentuk yang benar** (periksa ketidaksamaan dulu)
- [ ] Menjelaskan **strict weak ordering** dan kenapa `<=` bisa membuat `std::sort` crash
- [ ] Merancang generator stress test yang **sengaja memunculkan seri**
- [ ] Menguasai pola **dominasi / Pareto front** dengan dua pembanding berbeda
- [ ] **Menurunkan** kriteria pengurutan lewat exchange argument, bukan menebaknya
- [ ] Memakai tie-break untuk **menegakkan batasan soal secara otomatis**

---

## 🔑 Bug yang Tidak Pernah Tertangkap Generator Buruk

Kesalahan tie-break punya sifat berbahaya: kodenya **benar pada hampir semua
masukan acak**. Dengan `rand() % 1000000000`, dua nilai sama hampir tak pernah
muncul — bugnya tidak akan terlihat sampai juri memakai data dengan banyak
pengulangan.

> **Aturan generator:** untuk menguji tie-break, pakai rentang nilai **kecil**
> (`0..3`). Semakin sering seri, semakin cepat bugnya muncul.

| Yang diuji | Rentang generator |
|---|---|
| Tie-break | **kecil** (`0..3`) |
| Interval tumpang tindih | kecil (`0..15`) |
| Overflow | maksimum (`10^18`) |
| Presisi pecahan | dua nilai hampir sama |

Generator yang bagus **dirancang untuk memecahkan kodemu**, bukan "acak saja".

---

## 🧠 Inti Materi

### Bentuk komparator yang benar

```cpp
// ✅ BENAR — periksa ketidaksamaan dulu di tiap lapis
if (x.a != y.a) return x.a < y.a;
if (x.b != y.b) return x.b > y.b;
return x.idx < y.idx;              // tie-break terakhir: urutan asli

// ❌ SALAH — cabang kedua jalan meski x.a > y.a
if (x.a < y.a) return true;
if (x.b < y.b) return true;
return false;
```

**Pemeriksa tercepat:** panggil `cmp(x, x)`. Kalau `true`, komparatormu salah.
**Pemeriksa menyeluruh:** kompilasi dengan `-D_GLIBCXX_DEBUG`.

### Indeks sebagai tie-break terakhir

Karena indeks unik, komparatormu menjadi **urutan total**: hasilnya deterministik,
`sort` dan `stable_sort` memberi hasil identik, dan seluruh kelas bug seri lenyap.
Lebih baik daripada mengandalkan `stable_sort` karena niatnya tertulis eksplisit.

### Pola A — Pareto front (dua pembanding **berbeda**)

```
i Pareto-optimal
⟺ y_i maksimum di dalam kelompok ber-x SAMA        (seri boleh, ==)
   DAN y_i > maksimum y di kelompok ber-x LEBIH BESAR (STRICT, >)
```

Terhadap `x` yang lebih besar, ketidaksamaannya sudah strict — jadi `y` seri pun
cukup untuk mendominasi. Di dalam kelompok `x` sama, dibutuhkan `y` yang benar-benar
lebih besar. **Menyamakan kedua pembanding ini adalah bug klasik.**

Proses **per kelompok**, dan perbarui maksimum **setelah** kelompok selesai.

### Pola B — penjadwalan dua tahap

> `a_i` pada satu mesin bersama, lalu `b_i` paralel tak terbatas. Minimalkan
> waktu selesai terakhir.

**Jawaban: urut `b` MENURUN.** Perhatikan `a` sama sekali tidak muncul.

Bukti: kurangi konstanta `S + a_i + a_j`, tersisa
`max(b_i − a_j, b_j)` vs `max(b_j − a_i, b_i)`. Bila `b_i ≥ b_j`, sisi kiri `≤ b_i`
dan sisi kanan `≥ b_i`. ∎

### Pola C — kelayakan (bukan optimasi)

> Tugas butuh modal `m_i`, menghabiskan `c_i` (`c_i ≤ m_i`). Adakah urutan yang sah?

**Jawaban: urut `(m − c)` MENURUN** — "cadangan" terbesar dulu.

Bukti: `(i,j)` layak ⟺ `M ≥ max(m_i, m_j + c_i)`. Tambahkan `c_i + c_j` ke tiap
suku; suku keduanya identik, tersisa `m_i + c_j` vs `m_j + c_i` ⟺ `m_i − c_i` vs
`m_j − c_j`. ∎

**Dugaan "urut `m` menurun" gagal 602 dari 30.000 kasus acak.** Terlihat sangat
masuk akal, dan salah.

### Pola D — tie-break yang menegakkan batasan

Boneka Rusia: amplop berlebar **sama** tidak boleh bersarang.

```cpp
sort: w MENAIK, saat w seri h MENURUN
lalu: barisan naik TEGAS pada h (lower_bound, bukan upper_bound)
```

Dengan `h` menurun saat `w` seri, dua amplop berlebar sama muncul sebagai
`(6,7) (6,4)` — dan barisan naik tidak akan pernah mengambil keduanya. Tie-break
menegakkan batasan **secara otomatis**, tanpa pemeriksaan tambahan.

---

## 📁 Struktur Berkas

```
Day-76 (Greedy dengan Sorting Multi-Kriteria)/
├── README.md
├── teori/
│   └── Day_76_Teori_Lengkap.md
├── latihan/
│   ├── exercise_1.cpp   Peringkat Siswa              (Easy)   komparator berlapis
│   ├── exercise_2.cpp   Titik Pareto                 (Easy)   dua pembanding beda
│   ├── exercise_3.cpp   Rentang Bersarang            (Medium) dominasi + duplikat
│   ├── exercise_4.cpp   Pekerjaan Dua Tahap          (Medium) turunkan kriteria
│   ├── exercise_5.cpp   Antrean Bermodal             (Hard)   kriteria kelayakan
│   └── exercise_6.cpp   Boneka Rusia                 (Hard)   tie-break + LIS
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
| Seluruh 29 berkas | `g++ -std=c++17 -O2 -Wall` | lolos |
| Solusi 1–6 | semua contoh masukan di soal | cocok |
| Solusi 1 (komparator) | 3.000 kasus, nilai dibatasi `0..2` | cocok |
| Solusi 2 (Pareto) | **20.000** kasus, koordinat `0..3` | cocok |
| Solusi 3 (bersarang) | **20.000** kasus, koordinat `1..4` | cocok |
| Solusi 4 (dua tahap) | 3.000 kasus vs seluruh permutasi | cocok |
| Solusi 5 (bermodal) | 5.000 kasus vs seluruh permutasi | cocok |
| Solusi 6 (boneka) | 3.000 kasus vs brute force rantai | cocok |
| Template | 20.000 kasus Pareto + 200 kasus uji strict weak ordering | cocok |
| Kriteria dua tahap | 20.000 kasus vs seluruh permutasi | cocok |
| Kriteria bermodal | perbandingan 4 dugaan pada 30.000 kasus | hanya `(m−c)` menurun lolos |

Seluruh generator sengaja memakai **rentang nilai kecil** — itulah yang membuat
bug tie-break muncul. Dengan rentang besar, semua varian yang salah pun akan lolos.

Tiga sample output yang saya tulis sendiri terbukti salah dan sudah diperbaiki:
Exercise 5 (`10` → `20` pada modal awal), Tugas 13 (`23` → `20`), Tugas 14
(`3 2 1 4` → `3 1 2 4`). Solusi 3 juga ditulis ulang setelah stress test menemukan
kasus rentang identik yang tidak tertangani.

---

## ⚠️ Jebakan

1. **Lupa tie-break** — lolos generator besar, gagal di juri.
2. **Memakai `<=`** — melanggar strict weak ordering, bisa crash.
3. **Cabang tie-break tidak memeriksa kesamaan dulu** — komparator asimetris.
4. **Negasi untuk membalik urutan** pada nilai yang bisa `LLONG_MIN`.
5. **Mengandalkan `std::sort` untuk stabilitas** — ia tidak stabil.
6. **Menyamakan pembanding dalam-kelompok dan antar-kelompok** pada dominasi.
7. **Melupakan elemen identik** — kasus tersendiri yang sering butuh tambalan.
8. **Menebak kriteria** alih-alih menurunkannya.

---

## 🔗 Prasyarat & Kelanjutan

**Dipakai hari ini:** exchange argument (Day 71), stabilitas (Day 47), komparator
(Day 43–46), interval (Day 72–73), perbandingan rasio (Day 74), LIS + `lower_bound`
(Day 49).

**Tugas yang butuh materi lain:** Tugas 02 dan 08 memakai Fenwick Tree (Day 170) +
kompresi koordinat (Day 38) — keduanya sudah kamu kerjakan, jadi **terbuka**.

**Berikutnya:**

- Day 77 — Greedy + Priority Queue (teknik regret/pembatalan)
- Day 78 — Scheduling dengan Deadline & Penalti
- Day 79 — Cara Membuktikan (atau Membantah) Greedy

---

## 📝 Checklist Penguasaan

- [ ] Selalu menulis komparator dengan `if (x.a != y.a) return ...`
- [ ] Refleks menambahkan indeks sebagai tie-break terakhir
- [ ] Refleks memakai rentang nilai **kecil** saat menulis generator
- [ ] Bisa menjelaskan kenapa dominasi butuh **dua** pembanding berbeda
- [ ] Bisa menurunkan kriteria "urut `b` menurun" untuk dua tahap dari nol
- [ ] Bisa menurunkan kriteria `(m − c)` menurun untuk soal kelayakan
- [ ] Bisa menjelaskan kenapa tie-break `h` menurun menegakkan batasan Boneka Rusia
