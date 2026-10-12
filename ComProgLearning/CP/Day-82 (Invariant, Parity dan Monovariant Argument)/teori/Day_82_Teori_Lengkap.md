# 📘 Day 82 — Invariant, Parity & Monovariant Argument

> **Prasyarat:** Day 79 (verifikasi), Day 80 (ad-hoc), Day 81 (constructive).
> Hari ini menutup blok greedy dengan alat yang paling sering dipakai untuk
> menjawab **"bisakah?"** dan **"pasti berhenti?"**

---

## Daftar Isi

1. [Tiga Alat](#1)
2. [Invarian: Membuktikan Mustahil](#2)
3. [Cara Menemukan Invarian](#3)
4. [Paritas: Invarian yang Paling Sering Dipakai](#4)
5. [Monovarian: Membuktikan Proses Berhenti](#5)
6. [Invarian Klasik yang Wajib Dikenal](#6)
7. [Batas Kekuatan Invarian](#7)
8. [Ringkasan, Jebakan, dan Latihan Mandiri](#8)

---

<a name="1"></a>
## 1. Tiga Alat

| Alat | Definisi | Untuk membuktikan |
|---|---|---|
| **Invarian** | besaran yang **tidak berubah** setelah tiap operasi | sesuatu **mustahil** |
| **Monovarian** | besaran yang selalu **naik** (atau selalu turun) | proses **pasti berhenti** |
| **Paritas** | kasus khusus invarian modulo 2 | mustahil, dengan cara termurah |

### Kapan memakai yang mana

- Soal bertanya **"bisakah mencapai keadaan X?"** → cari invarian
- Soal bertanya **"berapa langkah minimum?"** → invarian memberi batas bawah
- Soal bertanya **"apakah prosesnya berhenti?"** → cari monovarian
- Soal bertanya **"berapa langkah paling banyak?"** → monovarian memberi batas atas

> **Periksa paritas sebelum apa pun.** Ia murah dan sering menyelesaikan separuh
> kasus uji tanpa kerja sama sekali.

---

<a name="2"></a>
## 2. Invarian: Membuktikan Mustahil

**Ide:** kalau ada besaran `I` yang nilainya sama sebelum dan sesudah setiap
operasi, maka `I(awal) = I(akhir)` untuk **semua** urutan operasi. Kalau
`I(target) ≠ I(awal)`, target itu **tidak mungkin dicapai**.

### Contoh klasik

> Di papan ada bilangan `3, 5, 7, 11`. Berulang kali: hapus dua bilangan `x, y`,
> tulis `|x − y|`. Berapa paritas bilangan terakhir yang tersisa?

`|x − y|` selalu berparitas **sama** dengan `x + y`. Jadi setiap operasi mengubah
jumlah seluruh bilangan dengan **kelipatan 2** — paritas jumlah adalah invarian.

Jumlah awal `3+5+7+11 = 26` (genap), jadi bilangan terakhir pasti **genap**,
apa pun urutan operasinya.

### Bentuk umum yang perlu dicari

| Kalau operasinya | Kandidat invarian |
|---|---|
| menukar dua elemen | paritas permutasi |
| menambah/mengurangi elemen | jumlah, jumlah mod `k` |
| mengganti dua elemen dengan satu | jumlah mod 2, XOR |
| memindahkan objek di grid | warna papan catur, `(i+j) mod 2` |
| membalik tanda | banyaknya elemen negatif mod 2 |
| memutar/membalik | jumlah berbobot posisi |

---

<a name="3"></a>
## 3. Cara Menemukan Invarian

Jangan menatap soal berharap ilham. Lakukan ini:

```
1. tulis daftar besaran yang wajar:
      jumlah, jumlah mod 2, jumlah mod 3, XOR, maksimum,
      banyak elemen ganjil, ukuran, jumlah berbobot posisi
2. jalankan operasi ACAK ribuan kali
3. cetak nilai tiap besaran setelah setiap langkah
4. yang TIDAK PERNAH berubah adalah kandidat invarian
5. buktikan kandidat itu secara aljabar
```

Template hari ini menyediakan alat untuk langkah 2–4. Kamu cukup menuliskan
operasinya sebagai lambda, dan ia melaporkan besaran mana yang bertahan.

### Contoh keluaran nyata

```
Operasi: hapus dua elemen x,y; masukkan |x - y|

    jumlah                      berubah
    jumlah mod 2                INVARIAN     ← ini dia
    jumlah mod 3                berubah
    XOR seluruhnya              berubah
    banyak elemen ganjil mod 2  INVARIAN     ← dan ini
    maksimum                    berubah
    ukuran                      berubah
```

Dua kandidat muncul sekaligus, dan keduanya benar (memang ekuivalen di sini).

### Setelah menemukan kandidat

**Buktikan secara aljabar.** Alat ini hanya memberi kandidat, bukan bukti.
Tuliskan nilai besaran sebelum dan sesudah satu operasi, lalu tunjukkan keduanya
sama.

---

<a name="4"></a>
## 4. Paritas: Invarian yang Paling Sering Dipakai

Paritas adalah invarian modulo 2, dan ia muncul jauh lebih sering daripada
invarian lain. Empat bentuk yang perlu dikenali:

### (a) Paritas jumlah

Kalau setiap operasi mengubah jumlah dengan bilangan **genap**, paritas jumlah
tetap.

### (b) Paritas permutasi

Setiap **penukaran** dua elemen membalik paritas permutasi. Karena itu:

- susunan yang butuh jumlah penukaran **genap** tidak bisa dicapai dengan jumlah
  penukaran **ganjil**
- ini dasar dari teka-teki **15-puzzle**: separuh susunan tidak bisa dicapai

Menghitungnya: pecah permutasi menjadi siklus. Siklus panjang `L` membutuhkan
`L − 1` penukaran.

```cpp
int paritas(vector<int> p) {
    int n = p.size(), tukar = 0;
    vector<bool> lihat(n, false);
    for (int i = 0; i < n; i++) {
        if (lihat[i]) continue;
        int L = 0, j = i;
        while (!lihat[j]) { lihat[j] = true; j = p[j]; L++; }
        tukar += L - 1;
    }
    return tukar % 2;
}
```

### (c) Pewarnaan papan catur

Warnai grid seperti papan catur: sel `(i, j)` berwarna `(i + j) mod 2`.

Bidak yang selalu berpindah ke sel bertetangga **selalu berganti warna**. Jadi
setelah jumlah langkah genap ia kembali ke warna semula.

Dipakai untuk: penutupan domino, gerakan kuda, labirin, dan banyak soal grid.

### (d) Paritas ukuran

Kalau operasi mengubah ukuran dengan bilangan tetap, paritas ukuran menentukan
kapan proses bisa berakhir pada ukuran tertentu.

---

<a name="5"></a>
## 5. Monovarian: Membuktikan Proses Berhenti

**Ide:** kalau ada besaran **bilangan bulat non-negatif** yang selalu **turun**
setiap langkah, proses pasti berhenti — dan nilai awalnya adalah **batas atas**
jumlah langkah.

### Syarat yang wajib

1. besarannya **bilangan bulat** (bukan bilangan real)
2. **terbatas di bawah** (misalnya selalu `≥ 0`)
3. **turun tegas** setiap langkah (minimal 1)

Melewatkan syarat kedua adalah kesalahan umum: besaran yang turun tetapi bisa
bernilai negatif tak terbatas **tidak** membuktikan apa-apa.

### Contoh

> Berulang kali: ambil dua bilangan `a > b`, ganti `a` dengan `a − b`.
> Apakah prosesnya berhenti?

Monovariannya adalah **jumlah seluruh bilangan**: ia selalu turun minimal 1 (karena
`b ≥ 1`), dan selalu positif. Jadi proses pasti berhenti, dalam paling banyak
`jumlah awal` langkah.

(Ini persis algoritma Euclid, dan batas yang lebih ketat bisa diperoleh dengan
analisis yang lebih halus.)

### Monovarian untuk batas bawah

Kebalikannya juga berguna: kalau setiap operasi mengubah besaran `X` paling banyak
`c`, dan kamu butuh mengubah `X` sebesar `D`, maka butuh **minimal** `⌈D/c⌉`
operasi. Ini adalah cara paling umum menurunkan batas bawah pada soal ad-hoc
(Day 80 Pola A).

---

<a name="6"></a>
## 6. Invarian Klasik yang Wajib Dikenal

| Soal | Invarian | Kesimpulan |
|---|---|---|
| Papan catur `8×8` tanpa **dua sudut berlawanan**, tutup dengan domino | jumlah sel putih vs hitam | **mustahil** (kedua sudut sewarna) |
| 15-puzzle | paritas permutasi + paritas posisi kotak kosong | separuh susunan mustahil |
| Lampu menyala/mati, tekan membalik satu baris & satu kolom | paritas jumlah lampu menyala | bergantung ukuran |
| Bilangan di papan, ganti `x, y` dengan `x + y` | ukuran turun 1 tiap langkah | berakhir setelah `n − 1` langkah |
| Segitiga koin, balik tiga koin sekaligus | jumlah mod 3 | membatasi keadaan akhir |
| Kuda catur kembali ke asal | warna sel | butuh langkah **genap** |
| Gelas air, tuang antar wadah | FPB isi awal | hanya kelipatan FPB yang bisa dicapai |

Baris terakhir layak diperhatikan: **FPB juga invarian**. Pada soal menuang air,
setiap operasi mempertahankan FPB dari seluruh isi, sehingga hanya volume yang
merupakan kelipatan FPB awal yang bisa dicapai.

---

<a name="7"></a>
## 7. Batas Kekuatan Invarian

Ini bagian yang paling sering disalahpahami.

> **Invarian membuktikan MUSTAHIL. Ia TIDAK membuktikan MUNGKIN.**

Kalau invariannya cocok antara awal dan target, itu berarti target **belum tentu
mustahil** — bukan berarti pasti bisa dicapai. Kamu masih harus memberikan
**konstruksi** (Day 81).

### Contoh nyata

Papan `8×8` tanpa dua sudut **bersebelahan** (misalnya `(0,0)` dan `(0,7)`) punya
31 sel putih dan 31 sel hitam — syarat pewarnaan **lolos**. Tetapi lolosnya
pewarnaan tidak otomatis berarti bisa ditutup; kamu tetap harus menunjukkan
susunan dominonya.

(Dalam kasus ini memang bisa, tetapi buktinya adalah konstruksi, bukan pewarnaan.)

### Pola lengkap untuk soal "bisakah?"

```
1. cari invarian -> kalau tidak cocok, jawabannya TIDAK
2. kalau cocok  -> berikan KONSTRUKSI (Day 81)
3. kalau tidak bisa membuat konstruksi -> cari invarian yang LEBIH KUAT
```

Langkah 3 penting: kadang invarian pertamamu terlalu lemah dan ada invarian lain
yang menutup kasus tersisa.

---

<a name="8"></a>
## 8. Ringkasan, Jebakan, dan Latihan Mandiri

### Daftar periksa saat bertemu soal "bisakah / berapa langkah"

1. Apa **paritas** dari besaran-besaran yang jelas? (jumlah, ukuran, posisi)
2. Apakah ada **pewarnaan** yang membuat operasinya selalu berganti warna?
3. Apakah ada besaran yang selalu **turun**? (monovarian → pasti berhenti)
4. Apakah setiap operasi mengubah besaran paling banyak `c`? (→ batas bawah)
5. Kalau invariannya cocok, apa **konstruksinya**?

### Jebakan

1. **Menyangka invarian membuktikan "mungkin".** Ia hanya membuktikan "mustahil".
2. **Lupa memeriksa paritas** sebelum mencari konstruksi.
3. **Monovarian tidak terbatas di bawah** — tidak membuktikan apa-apa.
4. **Menyangka pewarnaan adalah syarat cukup.** Ia hanya syarat perlu.
5. **Sisa negatif dari `%`** di C++ — tulis `((x % m) + m) % m`.
6. **Berhenti pada invarian pertama** padahal ada yang lebih kuat.
7. **Menebak invarian** alih-alih mencarinya secara sistematis.

### Latihan mandiri

- Simpan alat pencari invarian dari template ke berkas templatemu. Setiap kali
  bertemu soal "bisakah?", jalankan alat itu sebelum berpikir lebih jauh — ia
  sering langsung menunjukkan jawabannya.
- Ambil 5 soal Codeforces bertag `constructive algorithms` atau `math`, dan untuk
  masing-masing catat: apakah ada invarian, apa bentuknya, dan apakah ia cukup
  untuk menjawab seluruh kasus.
- Buktikan sendiri bahwa pada soal menuang air, FPB seluruh isi adalah invarian.
  Lalu gunakan itu untuk menjawab: dengan wadah 3 liter dan 5 liter, volume apa
  saja yang bisa kamu ukur?
