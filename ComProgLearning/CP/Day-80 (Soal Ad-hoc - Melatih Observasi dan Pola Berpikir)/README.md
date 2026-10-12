# 📅 Day 80 — Soal Ad-hoc: Melatih Observasi & Pola Berpikir

> **Bulan 5–6 · Blok Greedy & Ad-hoc (Day 71–82)**
> Soal yang tidak memakai algoritma standar. Kuncinya satu **pengamatan** — dan
> setelah pengamatan itu ditemukan, kodenya biasanya kurang dari 20 baris.

---

## 🎯 Tujuan Hari Ini

- [ ] Menjalankan **tujuh pertanyaan pembuka** saat buntu
- [ ] Memakai **program pencari pola** (selisih & rasio) untuk menebak rumus
- [ ] Menyelesaikan soal "minimum" dengan **batas bawah + konstruksi** (keduanya)
- [ ] Membalik arah operasi ketika percabangan maju terlalu besar
- [ ] **Menghitung sumbangan**, bukan mengiterasi objek
- [ ] Membedakan kapan **median**, kapan **rata-rata**, kapan **titik tengah**

---

## 🔑 Tujuh Pertanyaan Pembuka

1. Apa yang **tidak berubah**? (invarian → Day 82)
2. Apa jawabannya untuk `n = 1, 2, 3`?
3. Apa **batas bawah** dan **batas atas**-nya?
4. Bisakah soal **dibalik**?
5. Apakah ada besaran yang **monoton**?
6. Apa kasus **ekstrem**-nya?
7. Bisakah aku hitung `n` kecil lalu cari **polanya**?

> **Tanda kamu belum menemukan pengamatannya: kodemu panjang.** Solusi ad-hoc yang
> benar hampir selalu pendek.

---

## 🧠 Empat Pola Utama

### A — Batas bawah bertemu konstruksi

Soal "berapa langkah minimum" **selalu** butuh dua bagian:

```
(a) BATAS BAWAH : buktikan tidak mungkin kurang dari B
(b) KONSTRUKSI  : tunjukkan cara mencapai tepat B
```

Menjawab hanya satu **bukan solusi**. Ini kesalahan paling umum di soal ad-hoc.

**Argumen sekat** (Exercise 4): untuk soal memindahkan batu ke tetangga, jumlah
batu yang **harus** melintasi sekat ke-`i` adalah `|prefix(i) − (i+1)·rata|`, apa
pun cara kamu mengatur operasinya. Jumlahkan seluruh sekat → batas bawah, dan
konstruksinya mencapainya persis.

⚠️ Jawabannya **bukan** `Σ|a_i − rata|` — batu yang berpindah jauh dihitung sekali
per sekat yang dilintasi.

### B — Pikirkan dari belakang

> `(1,1)` → `(x+y,y)` atau `(x,y+x)`. Berapa langkah ke `(a,b)`?

**Maju:** percabangan `2^langkah`, mustahil untuk `a,b ≤ 10^18`.
**Mundur:** hanya **satu** kemungkinan per langkah — tidak ada percabangan sama
sekali. Dan pengurangan berulang itu persis **algoritma Euclid**.

```cpp
while (a > 1 || b > 1) {
    if (a == b) return -1;                       // macet
    if (a > b) { ll k = (a-1)/b; langkah += k; a -= b*k; }
    else       { ll k = (b-1)/a; langkah += k; b -= a*k; }
}
```

⚠️ `(a-1)/b`, **bukan** `a/b` — yang kedua bisa membuat `a` menjadi 0.

### C — Hitung sumbangan, bukan objek

Elemen ke-`i` (0-indexed) muncul di **`(i+1) × (n−i)`** subarray.

```cpp
for (ll i = 0; i < n; i++) total += a[i] * (i+1) * (n-i);
```

`O(n)` alih-alih `O(n²)`. Pola pikirnya: **jangan iterasi objeknya, iterasi
elemennya.**

| Soal | Sumbangan tiap elemen |
|---|---|
| Seluruh subarray | `(i+1)(n−i)` |
| Seluruh himpunan bagian | `2^(n−1)` |
| Seluruh pasangan `\|a_i − a_j\|` | urutkan, lalu `a_i·i − prefix(i)` |

### D — Median, rata-rata, atau titik tengah

| Fungsi biaya | Titik optimal |
|---|---|
| `Σ \|a_i − x\|` | **median** |
| `Σ (a_i − x)²` | **rata-rata** |
| `max \|a_i − x\|` | **titik tengah** `(min+max)/2` |

**Kenapa median:** geser `x` ke kanan sejauh `δ` → biaya naik `δ` untuk tiap
`a_i < x`, turun `δ` untuk tiap `a_i > x`. Titik seimbangnya adalah median.

Kalau `n` genap, **seluruh** rentang antara dua nilai tengah memberi biaya sama.

---

## 🔍 Alat Pencari Pola

Cetak barisan + selisih pertama + selisih kedua + rasio:

| Yang tetap | Bentuk rumus |
|---|---|
| Selisih pertama | linear `an + b` |
| Selisih kedua | kuadrat `an² + bn + c` |
| Rasio | eksponensial `a·rⁿ` |
| Rasio mendekati `n` | melibatkan **faktorial** |

**Contoh nyata** (derangement, dari template):

```
barisan : 0 1 2 9 44 265 1854 14833
rasio   : 2.000 4.500 4.889 6.023 6.996 8.001   ← mendekati n
dugaan  : D(n) = n·D(n−1) + (−1)ⁿ    → diverifikasi cocok n = 1..8
```

**Aturan:** hitung minimal 8–10 suku sebelum menebak, lalu **verifikasi untuk `n`
yang lebih besar** dari yang dipakai menebak.

---

## 📁 Struktur Berkas

```
Day-80 (Soal Ad-hoc - Melatih Observasi dan Pola Berpikir)/
├── README.md
├── teori/
│   └── Day_80_Teori_Lengkap.md
├── latihan/
│   ├── exercise_1.cpp   Menyamakan dengan Biaya Terkecil (Easy)   median
│   ├── exercise_2.cpp   Jumlah Seluruh Subarray          (Easy)   sumbangan
│   ├── exercise_3.cpp   Mundur dari Tujuan               (Medium) balik arah
│   ├── exercise_4.cpp   Memindahkan Batu ke Tetangga     (Medium) argumen sekat
│   ├── exercise_5.cpp   Menemukan Rumus dari Barisan     (Hard)   cari pola
│   └── exercise_6.cpp   Membalik Tanda                   (Hard)   paritas
├── solusi/
│   └── solution_1..6.cpp
├── tugas/
│   └── tugas_01..15.cpp
└── template/
    └── template.cpp    ← alat pencari pola, salin ke template pribadimu
```

---

## ✅ Semua Kode Sudah Diverifikasi

| Yang diuji | Cara | Hasil |
|---|---|---|
| Seluruh 29 berkas | `g++ -std=c++17 -O2 -Wall` | lolos |
| Solusi 1–6 | semua contoh masukan di soal | cocok |
| Solusi 1 (median) | 5.000 kasus vs pencarian menyeluruh atas semua target | cocok |
| Solusi 2 (sumbangan) | 3.000 kasus vs penjumlahan `O(n²)` langsung | cocok |
| Solusi 3 (mundur) | 3.000 kasus vs **BFS maju** | cocok |
| Solusi 4 (sekat) | 5.000 kasus vs rumus referensi independen | cocok |
| Solusi 5 (derangement) | `n = 1..8` vs pencacahan seluruh permutasi | cocok |
| Solusi 6 (paritas) | 5.000 kasus vs pencarian rekursif seluruh `K` operasi | cocok |
| Template | rumus derangement diverifikasi otomatis saat dijalankan | cocok |

Verifikasi Solusi 3 patut dicatat: solusi `O(log n)` yang bekerja mundur diadu
dengan **BFS maju** — dua pendekatan yang sama sekali berbeda, sehingga
kesalahannya tidak mungkin berkorelasi.

Dua sample output yang saya tulis sendiri terbukti salah dan sudah diperbaiki:
Exercise 4 (datanya tidak habis dibagi `n`, jadi jawabannya `-1`) dan Tugas 03
(`29` → `30`).

---

## ⚠️ Jebakan

1. **Langsung menulis kode** sebelum menemukan pengamatannya.
2. **Kode panjang** — tanda memaksa jalan yang salah.
3. **Hanya batas bawah atau hanya konstruksi** untuk soal "minimum".
4. **Menebak pola dari 3 suku.**
5. **Tidak memverifikasi** tebakan untuk `n` lebih besar.
6. **Lupa `n = 1` dan `n = 2`.**
7. **Memakai rata-rata** untuk soal jarak absolut.
8. **`a/b` alih-alih `(a-1)/b`** pada Euclid mundur.
9. **Overflow** karena mengalikan tiga faktor sekaligus sebelum modulo.

---

## 🔗 Prasyarat & Kelanjutan

**Dipakai hari ini:** seluruh Day 71–79, prefix sum (Day 29), aritmetika modular
(Day 90), `nth_element` (Day 45).

**Berikutnya:**

- Day 81 — Soal Constructive: Strategi Membangun Jawaban
- Day 82 — Invariant, Parity & Monovariant

---

## 📝 Alur Kerja Soal Ad-hoc

```
1. tulis ulang soal dengan kata-katamu sendiri
2. jalankan tujuh pertanyaan pembuka
3. hitung n = 1..10 dengan brute force
4. cetak barisan + selisih + rasio
5. tebak polanya
6. VERIFIKASI untuk n lebih besar
7. kalau soal "minimum": batas bawah DAN konstruksi
8. tulis kode (harusnya pendek)
```
