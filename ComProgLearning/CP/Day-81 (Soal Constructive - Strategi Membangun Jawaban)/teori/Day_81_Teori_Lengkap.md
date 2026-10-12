# 📘 Day 81 — Soal Constructive: Strategi Membangun Jawaban

> **Prasyarat:** Day 79 (verifikasi), Day 80 (ad-hoc). Hari ini tentang soal yang
> meminta kamu **membangun objek**, bukan menghitung nilai.

---

## Daftar Isi

1. [Apa yang Membedakan Soal Constructive](#1)
2. [Aturan Emas: Tulis Pemeriksa Dulu](#2)
3. [Lima Strategi Konstruksi](#3)
4. [Membuktikan Mustahil](#4)
5. [Kasus Tepi yang Selalu Membunuh](#5)
6. [Menguji Konstruksi dengan Benar](#6)
7. [Contoh Lengkap: Titik Sambung](#7)
8. [Ringkasan, Jebakan, dan Latihan Mandiri](#8)

---

<a name="1"></a>
## 1. Apa yang Membedakan Soal Constructive

| | Ad-hoc (Day 80) | Constructive (Day 81) |
|---|---|---|
| Yang diminta | sebuah **angka** | sebuah **objek** |
| Jawaban benar | tunggal | biasanya **banyak** |
| Cara menguji | bandingkan angka | **pemeriksa terpisah** |
| Sering ada | — | kasus **"tidak mungkin"** |

Perbedaan ketiga itulah yang paling sering menjebak. Karena jawabannya banyak,
kamu **tidak bisa** membandingkan keluaranmu dengan jawaban contoh. Kalau kamu
mencoba, kamu akan mengira kodemu salah padahal benar — atau sebaliknya.

### Kalimat pemicu di soal

- "cetak **sebuah** susunan yang memenuhi ..."
- "kalau ada beberapa jawaban, cetak **mana saja**"
- "kalau tidak ada, cetak `-1` / `IMPOSSIBLE`"

Begitu kamu melihat "mana saja", kamu tahu ini soal constructive dan kamu tahu
alat pertamamu adalah pemeriksa.

---

<a name="2"></a>
## 2. Aturan Emas: Tulis Pemeriksa Dulu

> **Selalu tulis pemeriksa (checker) sebelum menulis konstruksi.**

Pemeriksa adalah fungsi yang menerima keluaranmu dan memvalidasi **seluruh
syarat soal secara langsung** — bukan membandingkannya dengan apa pun.

```cpp
bool periksa(const vector<int>& p, int n) {
    if ((int)p.size() != n) return false;          // ukuran
    vector<bool> ada(n + 1, false);
    for (int x : p) {
        if (x < 1 || x > n) return false;          // rentang
        if (ada[x]) return false;                  // duplikat
        ada[x] = true;
    }
    // ... lalu syarat khusus soal
    return true;
}
```

### Tiga hal yang wajib diperiksa pemeriksa

1. **Ukuran** keluaran benar
2. **Rentang** setiap nilai sah, dan tidak ada duplikat (kalau permutasi)
3. **Syarat khusus** soal terpenuhi

Nomor 1 dan 2 sering dilupakan padahal itulah yang paling sering rusak — misalnya
konstruksi yang menghasilkan nilai `0` atau `n+1` karena salah indeks.

### Cara memakainya

```
untuk n = 1 sampai 200:
    bangun jawaban untuk n
    kalau soal bilang mustahil -> periksa memang tidak ada jawaban
    kalau tidak -> jalankan pemeriksa, harus lolos
```

Menguji **seluruh** `n` kecil (bukan beberapa) adalah kuncinya. Lihat Bagian 7
untuk contoh nyata mengapa.

---

<a name="3"></a>
## 3. Lima Strategi Konstruksi

### Strategi 1 — pola dari kasus kecil

Bangun jawaban untuk `n = 1, 2, 3, 4, 5` dengan tangan atau brute force, lalu cari
polanya dan perumum.

Contoh: permutasi tanpa titik tetap (derangement). Untuk `n ≥ 2`, cukup **geser
semua satu langkah**: `p[i] = (i + 1) mod n + 1`. Untuk `n = 1` mustahil.

### Strategi 2 — bangun rekursif

Bangun jawaban untuk `n` dari jawaban untuk `n−1` (atau `n/2`).

Cocok ketika menambahkan satu elemen tidak merusak syarat yang sudah dipenuhi.
Sering muncul pada soal pohon, matriks, dan barisan.

### Strategi 3 — konstruksi baku lalu perbaiki

Mulai dari sesuatu yang jelas benar tetapi belum memenuhi seluruh syarat
(misalnya permutasi identitas), lalu ubah sedikit demi sedikit.

Contoh: permutasi dengan **tepat `k`** posisi bergeser — mulai dari identitas,
lalu balik blok sepanjang `k` di depan.

### Strategi 4 — buktikan mustahil dulu

**Periksa kemustahilan sebelum mencari konstruksi.** Ini murah dan sering
menyelesaikan separuh kasus uji.

Alatnya paritas dan invarian (Day 82). Contoh: membagi `1..n` menjadi dua kelompok
berjumlah sama mustahil kalau `n(n+1)/2` ganjil.

### Strategi 5 — greedy lalu tambal

Bangun jawaban seenaknya secara serakah, lalu perbaiki pelanggaran satu per satu.

Cocok kalau setiap perbaikan **tidak merusak** bagian yang sudah benar. Kalau
perbaikan bisa merusak, strategi ini berputar-putar dan kamu butuh pendekatan lain.

---

<a name="4"></a>
## 4. Membuktikan Mustahil

Setengah dari soal constructive punya kasus "tidak mungkin", dan menemukannya
biasanya jauh lebih mudah daripada membuat konstruksi.

### Tiga alat

**(a) Paritas.** Kalau setiap operasi mengubah suatu besaran dengan jumlah genap,
dan target berparitas berbeda dari awal, mustahil.

**(b) Pencacahan.** Kalau kamu butuh `k` "hal" tetapi hanya tersedia `k−1`,
mustahil. Sering berbentuk *pigeonhole*.

**(c) Batas.** Kalau syarat soal menuntut nilai di luar rentang yang mungkin,
mustahil. Contoh: "permutasi `1..n` dengan selisih tetangga minimal `n`" mustahil
untuk `n ≥ 2`.

### Contoh yang layak dihafal

| Soal | Mustahil ketika |
|---|---|
| Derangement `1..n` | `n = 1` |
| Permutasi selisih tetangga ≠ 1 | `n = 2` atau `n = 3` |
| Permutasi dengan tepat `k` bergeser | `k = 1` |
| Bagi `1..n` jadi dua bagian sama | `n(n+1)/2` ganjil |
| Graf dengan derajat ganjil semua | jumlah simpul ganjil |

Perhatikan bahwa `k = 1` mustahil karena kamu tidak bisa memindahkan **tepat satu**
elemen — memindahkan satu memaksa yang lain ikut pindah.

---

<a name="5"></a>
## 5. Kasus Tepi yang Selalu Membunuh

Konstruksi yang bagus untuk `n` besar hampir **selalu** gagal di `n` kecil.

```
n = 1   : hampir selalu kasus khusus
n = 2   : sering mustahil
n = 3   : sering mustahil
n = 4   : batas antara "mustahil" dan "mungkin"
```

Selain itu, waspadai:

- **Titik sambung** antara dua blok konstruksi (lihat Bagian 7)
- **`k = 0`** dan **`k = n`** pada soal berparameter
- **Semua nilai sama** pada masukan yang punya data

### Aturan praktis

> Jalankan pemeriksamu untuk **seluruh** `n` dari 1 sampai 200, bukan untuk
> beberapa `n` yang kamu pilih.

Ini murah (biasanya di bawah satu detik) dan menangkap hampir semua kesalahan
kasus tepi.

---

<a name="6"></a>
## 6. Menguji Konstruksi dengan Benar

### Yang SALAH

```
bandingkan keluaranku dengan keluaran contoh di soal
```

Soal constructive punya banyak jawaban benar. Keluaranmu bisa berbeda dari contoh
dan tetap benar — atau kebetulan sama dan tetap salah untuk `n` lain.

### Yang BENAR

```
untuk setiap n:
    hasil = bangun(n)
    kalau mustahil menurut kodeku:
        verifikasi dengan brute force bahwa memang tidak ada
    kalau tidak:
        periksa(hasil, n) harus true
```

### Memverifikasi klaim "mustahil"

Ini bagian yang paling sering dilewatkan. Kalau kodemu bilang mustahil untuk suatu
`n`, buktikan dengan brute force (`n ≤ 8`) bahwa memang tidak ada jawaban. Kalau
ternyata ada, kodemu salah — dan itu jenis bug yang tidak akan pernah tertangkap
oleh pemeriksa biasa.

---

<a name="7"></a>
## 7. Contoh Lengkap: Titik Sambung

Soal: susun `1..n` sehingga **tidak ada** dua tetangga yang berselisih tepat 1.

### Percobaan pertama: ganjil dulu, lalu genap

```
n = 5 : 1 3 5 2 4    ✓
n = 6 : 1 3 5 2 4 6  ✓
n = 7 : 1 3 5 7 2 4 6 ✓
n = 4 : 1 3 2 4      ✗   |3 − 2| = 1
```

**Gagal hanya di `n = 4`.** Kalau kamu menguji `n = 5, 6, 7` saja, kamu akan
mengira konstruksimu benar.

### Kenapa gagal

Titik **sambung** antara dua blok: ganjil terakhir dan genap pertama. Untuk `n = 4`
itu adalah 3 dan 2 — berselisih tepat 1.

### Perbaikan: genap dulu, lalu ganjil

```
n = 4 : 2 4 1 3      ✓
n = 5 : 2 4 1 3 5    ✓
n = 6 : 2 4 6 1 3 5  ✓
```

Sekarang sambungnya adalah genap terbesar dan angka 1. Selisihnya minimal 3 untuk
`n ≥ 4`. Aman.

### Pelajarannya

Pada konstruksi yang menggabungkan beberapa blok, **titik sambung** hampir selalu
menjadi tempat kesalahan. Periksa titik sambung secara eksplisit, dan uji seluruh
`n` kecil.

---

<a name="8"></a>
## 8. Ringkasan, Jebakan, dan Latihan Mandiri

### Alur kerja soal constructive

```
1. baca soal, kenali kata "mana saja"
2. TULIS PEMERIKSA dulu
3. periksa kemustahilan (paritas/pencacahan/batas)
4. bangun jawaban untuk n = 1..6 dengan tangan
5. cari polanya, perumum
6. jalankan pemeriksa untuk SELURUH n = 1..200
7. verifikasi klaim "mustahil" dengan brute force
```

### Jebakan

1. **Tidak menulis pemeriksa.**
2. **Membandingkan dengan jawaban contoh.**
3. **Lupa `n = 1, 2, 3`.**
4. **Titik sambung antar blok** tidak diperiksa.
5. **Tidak memverifikasi klaim "mustahil".**
6. **Menguji beberapa `n` pilihan**, bukan seluruh `n` kecil.
7. **Lupa format keluaran** untuk kasus mustahil (`-1` vs `IMPOSSIBLE`).
8. **Konstruksi menghasilkan nilai di luar rentang** karena salah indeks.

### Latihan mandiri

- Ambil kembali soal constructive apa pun yang pernah kamu kerjakan, lalu tulis
  pemeriksanya dan jalankan untuk `n = 1..200`. Kalau ada yang gagal, kamu baru
  saja menemukan bug yang lolos dari submit.
- Untuk setiap konstruksi yang menggabungkan dua blok, tuliskan secara eksplisit
  apa titik sambungnya dan buktikan syaratnya terpenuhi di situ. Kebiasaan ini
  mencegah seluruh kelas kesalahan.
