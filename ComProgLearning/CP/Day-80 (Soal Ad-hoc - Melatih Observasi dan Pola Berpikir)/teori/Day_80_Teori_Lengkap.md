# 📘 Day 80 — Soal Ad-hoc: Melatih Observasi & Pola Berpikir

> **Prasyarat:** seluruh Day 71–79. Hari ini tentang soal yang **tidak** memakai
> algoritma standar — di mana yang dibutuhkan hanya satu pengamatan.

---

## Daftar Isi

1. [Apa Itu Soal Ad-hoc](#1)
2. [Tujuh Pertanyaan Pembuka](#2)
3. [Alat Utama: Program Pencari Pola](#3)
4. [Pola A — Batas Bawah Bertemu Konstruksi](#4)
5. [Pola B — Pikirkan dari Belakang](#5)
6. [Pola C — Hitung Sumbangan, Bukan Objek](#6)
7. [Pola D — Median, Rata-rata, dan Titik Optimal](#7)
8. [Ringkasan, Jebakan, dan Latihan Mandiri](#8)

---

<a name="1"></a>
## 1. Apa Itu Soal Ad-hoc

> Soal ad-hoc adalah soal yang **tidak** diselesaikan dengan algoritma standar.
> Kuncinya satu **pengamatan**, dan setelah pengamatan itu ditemukan, kodenya
> biasanya kurang dari 20 baris.

Ini membuat soal ad-hoc terasa berbeda dari semua yang sudah kamu pelajari.
Pada Day 71–78, kamu mengenali pola lalu menerapkan teknik. Di sini tidak ada
pola untuk dikenali — yang ada hanya struktur khusus soal itu sendiri.

### Ciri-ciri yang membedakan

| Ciri | Artinya |
|---|---|
| Pernyataan soal **pendek** | biasanya ad-hoc |
| Tidak ada struktur data yang jelas | ad-hoc atau matematis |
| Batasan sangat besar (`n ≤ 10^18`) | pasti ada rumus tertutup |
| Banyak kasus uji (`t ≤ 10^5`) | jawaban per kasus harus `O(1)` atau `O(log n)` |
| Contoh masukan kecil dan aneh | penulis soal memberi petunjuk pola |

### Tanda kamu belum menemukan pengamatannya

**Kodemu panjang.** Kalau solusi ad-hoc-mu 80 baris dengan banyak percabangan,
hampir pasti kamu memaksa jalan yang salah. Berhenti mengetik, kembali ke kertas.

---

<a name="2"></a>
## 2. Tujuh Pertanyaan Pembuka

Ketika kamu buntu pada soal ad-hoc, jalankan daftar ini secara berurutan. Salah
satunya hampir selalu membuka jalan.

**1. Apa yang TIDAK berubah?**
Cari besaran yang nilainya tetap setelah setiap operasi — itu **invarian**, dan
biasanya langsung memberi batas bawah atau membuktikan kemustahilan.
(Dibahas penuh di Day 82.)

**2. Apa jawabannya untuk `n = 1, 2, 3`?**
Hitung dengan tangan atau brute force. Lihat barisannya. Sering polanya langsung
terlihat.

**3. Apa batas bawah dan batas atas jawabannya?**
Kalau keduanya bertemu, kamu selesai. Ini strategi paling sering berhasil untuk
soal "berapa langkah minimum".

**4. Bisakah soal dibalik?**
Operasi maju yang rumit sering menjadi sederhana kalau dibaca dari belakang.

**5. Apakah ada besaran yang MONOTON?**
Besaran yang selalu naik (atau selalu turun) memberi batas atas jumlah langkah —
disebut **monovarian**.

**6. Apa kasus ekstremnya?**
Semua elemen sama, semua berbeda, semua nol, `n = 1`. Kasus ekstrem sering
memperlihatkan struktur yang tersembunyi di kasus umum.

**7. Bisakah aku hitung untuk `n` kecil lalu cari polanya?**
Brute force `n ≤ 10`, cetak barisannya, tebak rumusnya, verifikasi untuk `n`
yang lebih besar.

---

<a name="3"></a>
## 3. Alat Utama: Program Pencari Pola

Ini perkakas yang layak kamu simpan permanen.

```cpp
template <typename F>
void cetakBarisan(F brute, int sampai) {
    vector<ll> v;
    for (int n = 1; n <= sampai; n++) v.push_back(brute(n));
    // cetak: barisannya, selisih pertama, selisih kedua, rasio
}
```

### Cara membaca hasilnya

| Yang tetap | Bentuk rumus |
|---|---|
| **Selisih pertama** tetap | linear: `an + b` |
| **Selisih kedua** tetap | kuadrat: `an² + bn + c` |
| **Rasio** tetap | eksponensial: `a·rⁿ` |
| Rasio mendekati `n` | melibatkan **faktorial** |
| Tidak ada yang tetap | coba OEIS, atau cari rekurensi |

### Contoh nyata dari template

```
derangement : 0 1 2 9 44 265 1854 14833
selisih 1   : 1 1 7 35 221 1589 12979
rasio       : 2.000 4.500 4.889 6.023 6.996 8.001
```

Rasio mendekati `n` → curigai faktorial. Dugaan `D(n) = n·D(n−1) + (−1)ⁿ`
diverifikasi cocok untuk `n = 1..8`.

### Aturan penting

- **Hitung minimal 8–10 suku** sebelum menebak. Tiga suku bisa cocok dengan
  ratusan rumus berbeda.
- **Verifikasi tebakanmu** untuk `n` yang **lebih besar** dari yang dipakai
  menebak. Kalau kamu menebak dari 5 suku, verifikasi sampai 12.
- **Periksa `n = 1` dan `n = 2` secara terpisah.** Rumus yang benar untuk `n`
  besar sering gagal di situ.

---

<a name="4"></a>
## 4. Pola A — Batas Bawah Bertemu Konstruksi

Untuk soal berbentuk "berapa langkah **minimum**", jawabannya **selalu** dua
bagian:

```
(a) BATAS BAWAH : buktikan tidak mungkin kurang dari B
(b) KONSTRUKSI  : tunjukkan cara mencapai tepat B
```

Menjawab hanya satu bagian **bukan solusi**. Ini kesalahan paling umum di soal
ad-hoc: orang menemukan konstruksi yang bagus, mengasumsikan itu optimal, lalu WA.

### Cara mencari batas bawah

**Lewat invarian.** Kalau setiap operasi mengubah besaran `X` paling banyak `c`,
dan kamu butuh mengubah `X` sebesar `D`, maka butuh minimal `⌈D/c⌉` operasi.

**Lewat pencacahan.** Kalau ada `k` "hal" yang masing-masing butuh diperbaiki dan
satu operasi memperbaiki paling banyak satu, butuh minimal `k` operasi.

**Lewat paritas.** Kalau paritas suatu besaran tetap tetapi target berparitas
berbeda, jawabannya "tidak mungkin".

### Cara memeriksa konstruksi

Tulis program yang **memverifikasi** konstruksimu: jalankan langkah-langkahmu dan
periksa hasilnya benar-benar mencapai target. Program pemeriksa yang ditulis
independen sering menemukan kesalahan yang tidak kamu duga.

---

<a name="5"></a>
## 5. Pola B — Pikirkan dari Belakang

Kalau operasi maju sulit dianalisis, coba balik arahnya.

### Contoh klasik

> Mulai dari `(1, 1)`. Operasi: `(x,y) → (x+y, y)` atau `(x,y) → (x, y+x)`.
> Berapa langkah minimum untuk mencapai `(a, b)`?

**Maju** sulit: dari `(1,1)` percabangannya eksponensial.

**Mundur** mudah: dari `(a,b)`, langkah sebelumnya pasti `(a−b, b)` kalau `a > b`,
atau `(a, b−a)` kalau `b > a`. **Hanya satu kemungkinan** — tidak ada percabangan
sama sekali.

Dan pengurangan berulang itu persis **algoritma Euclid**, sehingga bisa
dipercepat dengan pembagian:

```cpp
while (a > 1 || b > 1) {
    if (a == b) return -1;                 // macet
    if (a > b) { langkah += (a-1)/b; a -= b * ((a-1)/b); }
    else       { langkah += (b-1)/a; b -= a * ((b-1)/a); }
}
```

`O(log max(a,b))` — bekerja bahkan untuk `a, b ≤ 10^18`.

### Kapan mencoba pembalikan

- Percabangan maju besar, percabangan mundur kecil
- Keadaan akhir diberikan, keadaan awal sederhana
- Operasinya punya invers yang jelas

---

<a name="6"></a>
## 6. Pola C — Hitung Sumbangan, Bukan Objek

Untuk soal "jumlahkan `f(...)` atas **semua** subarray / pasangan / himpunan
bagian", membalik urutan penjumlahan hampir selalu menang.

Alih-alih: *untuk tiap subarray, hitung sumbangannya*
Lakukan: *untuk tiap **elemen**, hitung berapa subarray yang memuatnya*

### Rumus yang wajib dihafal

Elemen ke-`i` (0-indexed) dari array berukuran `n` muncul di

```
(i + 1) × (n − i)
```

subarray. (Ada `i+1` pilihan ujung kiri dan `n−i` pilihan ujung kanan.)

```cpp
ll total = 0;
for (ll i = 0; i < n; i++) total += a[i] * (i + 1) * (n - i);
```

`O(n)` alih-alih `O(n²)`.

### Perluasannya

| Soal | Sumbangan tiap elemen |
|---|---|
| Jumlah seluruh subarray | `(i+1)(n−i)` |
| Jumlah maksimum tiap subarray | butuh monotonic stack (Day 36) |
| Jumlah seluruh pasangan `\|a_i − a_j\|` | urutkan, lalu `a_i·i − prefix(i)` |
| Jumlah seluruh himpunan bagian | tiap elemen muncul di `2^(n−1)` |

Pola pikirnya sama: **jangan iterasi objeknya, iterasi elemennya.**

---

<a name="7"></a>
## 7. Pola D — Median, Rata-rata, dan Titik Optimal

Soal "buat semua sama dengan biaya minimum" muncul terus-menerus. Jawabannya
bergantung pada **fungsi biaya**.

| Fungsi biaya | Titik optimal | Alasan |
|---|---|---|
| `Σ \|a_i − x\|` | **median** | turunan berubah tanda di median |
| `Σ (a_i − x)²` | **rata-rata** | turunannya `2Σ(x − a_i) = 0` |
| `max \|a_i − x\|` | **titik tengah** `(min+max)/2` | menyeimbangkan dua ujung |

### Kenapa median untuk jarak absolut

Bayangkan `x` bergerak ke kanan sejauh `δ`. Biaya bertambah `δ` untuk setiap
`a_i < x`, dan berkurang `δ` untuk setiap `a_i > x`. Jadi bergerak ke kanan
menguntungkan selama **lebih banyak** titik di kanan daripada di kiri.

Titik seimbangnya adalah median. Kalau `n` genap, **seluruh** rentang antara dua
median tengah memberikan biaya sama.

### Varian yang sering muncul

> "Buat semua sama, tetapi operasinya adalah memindahkan 1 unit dari satu elemen
> ke elemen tetangganya."

Di sini jumlahnya **tetap**, jadi targetnya pasti rata-rata (harus bilangan bulat,
kalau tidak → mustahil). Jawabannya adalah `Σ |prefix_i − i·rata|`.

---

<a name="8"></a>
## 8. Ringkasan, Jebakan, dan Latihan Mandiri

### Alur kerja soal ad-hoc

```
1. baca soal, tulis ulang dengan kata-katamu sendiri
2. jalankan tujuh pertanyaan pembuka
3. hitung n = 1..10 dengan brute force
4. cetak barisannya + selisih + rasio
5. tebak polanya
6. VERIFIKASI tebakan untuk n lebih besar
7. kalau soal "minimum": cari batas bawah DAN konstruksi
8. tulis kode (harusnya pendek)
```

### Jebakan

1. **Langsung menulis kode** sebelum menemukan pengamatannya.
2. **Kode panjang** — tanda kamu memaksa jalan yang salah.
3. **Hanya batas bawah atau hanya konstruksi** untuk soal "minimum".
4. **Menebak pola dari 3 suku.** Hitung minimal 8–10.
5. **Tidak memverifikasi** tebakan untuk `n` yang lebih besar.
6. **Lupa `n = 1` dan `n = 2`.**
7. **Mengabaikan batasan besar** (`n ≤ 10^18`) yang jelas menuntut rumus tertutup.
8. **Tidak memeriksa paritas** sebelum mencari konstruksi.

### Kompleksitas

Soal ad-hoc biasanya `O(1)`, `O(log n)`, atau `O(n)` setelah pengamatannya
ditemukan. Kalau solusimu `O(n²)` pada soal yang terasa ad-hoc, kemungkinan besar
kamu belum menemukan pengamatannya.

### Latihan mandiri

- Simpan `cetakBarisan` dari template ke berkas templatemu. Setiap kali kamu buntu
  pada soal yang terasa punya pola, jalankan alat itu sebelum berpikir lebih jauh.
- Ambil 10 soal ad-hoc dari Codeforces Div. 2 A/B, dan untuk setiap soal catat:
  pertanyaan pembuka mana (dari tujuh) yang membuka jalannya. Setelah 10 soal,
  kamu akan melihat bahwa dua atau tiga pertanyaan mendominasi — dan itu menjadi
  refleks pertamamu.
- Latih menebak rumus: ambil barisan `1, 2, 5, 14, 42, 132`, cetak selisih dan
  rasionya, dan lihat apa yang bisa kamu simpulkan sebelum mencarinya.
