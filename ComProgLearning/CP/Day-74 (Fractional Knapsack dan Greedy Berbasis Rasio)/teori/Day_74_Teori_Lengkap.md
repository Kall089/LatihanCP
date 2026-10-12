# 📘 Day 74 — Fractional Knapsack & Greedy Berbasis Rasio

> **Prasyarat:** Day 71 (exchange argument), Day 145 (0/1 knapsack),
> Day 50/51 (binary search on answer), Day 43–47 (komparator).

---

## Daftar Isi

1. [Satu Kata yang Menentukan Segalanya](#1)
2. [Fractional Knapsack & Buktinya](#2)
3. [Kenapa Bukti Itu Rusak pada 0/1](#3)
4. [Menulis Perbandingan Rasio dengan Benar](#4)
5. [Keluarga Knapsack Lengkap](#5)
6. [Pola Rasio Lain: Fractional Programming](#6)
7. [Kasus Tepi yang Membunuh](#7)
8. [Ringkasan, Jebakan, dan Latihan Mandiri](#8)

---

<a name="1"></a>
## 1. Satu Kata yang Menentukan Segalanya

Bacalah setiap soal knapsack mencari satu informasi:

> **Apakah barang boleh dipotong?**

| Jawaban | Teknik | Kompleksitas |
|---|---|---|
| Boleh dipotong (*fractional*) | **Greedy** rasio | `O(n log n)` |
| Harus utuh, satu kali (*0/1*) | **DP**, loop mundur | `O(n·W)` |
| Harus utuh, berkali-kali (*unbounded*) | **DP**, loop maju | `O(n·W)` |
| Utuh, paling banyak `c_i` kali (*bounded*) | **DP** + dekomposisi biner | `O(n·W·log c)` |

Satu kata itu memisahkan solusi `O(n log n)` dari solusi `O(n·W)` — dan
memisahkan AC dari WA.

**Petunjuk tambahan dari batasan.** Kalau kapasitas `W` mencapai `10^18`, DP
mustahil. Itu sinyal kuat bahwa soalnya fractional, atau punya struktur khusus
lain.

---

<a name="2"></a>
## 2. Fractional Knapsack & Buktinya

> `n` barang; barang ke-`i` berbobot `w_i` dan bernilai `v_i`. Kapasitas `W`.
> Barang **boleh dipotong**: mengambil fraksi `f` dari barang `i` menambah
> berat `f·w_i` dan nilai `f·v_i`. Maksimalkan total nilai.

**Algoritmanya:**

```
urutkan menurut rasio v_i / w_i MENURUN
untuk tiap barang:
    kalau muat utuh  -> ambil semua
    kalau tidak      -> ambil sebanyak sisa kapasitas, lalu berhenti
```

`O(n log n)`.

### Contoh

`W = 10`, barang `(6,7)`, `(5,5)`, `(5,5)`:

| Barang | Rasio | Aksi | Sisa | Total |
|---|---|---|---|---|
| `(6,7)` | 1.167 | ambil utuh | 4 | 7 |
| `(5,5)` | 1.000 | potong `4/5` | 0 | 7 + 4 = **11** |

Bandingkan dengan versi 0/1 pada data yang sama: jawabannya hanya **10**.
Kemampuan memotong bernilai satu satuan penuh di sini.

### Bukti (exchange argument)

**Klaim.** Ada solusi optimal yang mengambil barang berasio tertinggi
sebanyak-banyaknya.

**Bukti.** Sebut barang berasio tertinggi `x`. Ambil solusi optimal `O`.
Andaikan `O` mengambil `x` sebanyak `f_x < min(1, W/w_x)` — artinya masih ada
ruang untuk lebih banyak `x`, tetapi `O` tidak mengambilnya.

Karena kapasitas terpakai penuh (kalau tidak, tambahkan saja `x` dan nilainya
naik — kontradiksi), pasti ada barang lain `y` dengan `f_y > 0` dan
`v_y/w_y ≤ v_x/w_x`.

Kurangi `y` sebanyak berat `δ > 0`, tambahkan `x` sebanyak berat `δ` yang sama.
Perubahan nilainya:

```
Δ = δ·(v_x/w_x) − δ·(v_y/w_y) = δ·(v_x/w_x − v_y/w_y) ≥ 0
```

Nilainya **tidak turun**. Ulangi sampai `x` terambil maksimal. ∎

**Optimal substructure:** setelah `x` habis atau kapasitas penuh, sisanya adalah
soal fractional knapsack yang identik dengan kapasitas lebih kecil. Induksi.

### Intuisi

Kapasitas adalah sumber daya yang bisa dibelanjakan **secara kontinu**. Setiap
satuan berat harus dibelanjakan pada barang yang memberi nilai per satuan berat
tertinggi. Tidak ada alasan untuk tidak melakukannya, karena tidak ada batasan
"harus utuh" yang memaksa pemborosan.

---

<a name="3"></a>
## 3. Kenapa Bukti Itu Rusak pada 0/1

Ini bagian terpenting hari ini.

Pada 0/1 kamu **tidak bisa** melakukan langkah "kurangi `y` sebanyak `δ`,
tambahkan `x` sebanyak `δ`". Barang tidak bisa dipotong. Penukarannya harus
seluruh barang sekaligus, dan beratnya tidak cocok.

**Contoh tandingan wajib hafal:**

```
W = 10
barang: (berat 6, nilai 7)   rasio 1.167
        (berat 5, nilai 5)   rasio 1.000
        (berat 5, nilai 5)   rasio 1.000

greedy rasio : ambil (6,7), sisa 4, tidak ada yang muat  -> 7
optimal      : (5,5) + (5,5)                             -> 10
```

Greedy kehilangan 30% dari jawaban.

### Seberapa sering greedy gagal?

Template hari ini menjalankan eksperimen ini: **20.000 kasus acak** dengan
`n ≤ 8`, `w ≤ 12`, `v ≤ 20`, `W ≤ 25`.

> **Greedy rasio gagal pada sekitar 12% kasus.**

Dua belas persen adalah angka yang harus kamu ingat. Cukup jarang sehingga
greedy terlihat benar pada sampel-sampel kecil, cukup sering sehingga kamu pasti
WA di kontes.

**Pelajaran metodologisnya:** kalau kamu menguji ide greedy pada 5 sampel dan
semuanya lolos, itu **tidak berarti apa-apa** — peluang lolos 5 kali berturut-turut
pada 12% kegagalan adalah sekitar 53%. Stress test dengan ribuan kasus adalah
satu-satunya cara.

### Batas atas yang berguna

Meski salah sebagai jawaban, fractional knapsack adalah **batas atas** yang ketat
untuk 0/1:

```
jawaban_0/1  ≤  jawaban_fractional
```

Ini dipakai dalam **branch and bound** (Day 63): saat menelusuri pohon
keputusan, hitung batas atas fractional dari sisa barang; kalau batas atas itu
tidak melebihi jawaban terbaik yang sudah ditemukan, pangkas cabangnya. Teknik
ini membuat 0/1 knapsack dengan `n = 40` bisa diselesaikan tanpa DP.

---

<a name="4"></a>
## 4. Menulis Perbandingan Rasio dengan Benar

### ❌ Jangan bandingkan sebagai `double`

```cpp
return (double)v[a] / w[a] > (double)v[b] / w[b];   // rawan
```

`double` punya 53 bit mantissa. Dengan `v, w ≤ 10^9`, dua rasio yang berbeda
sangat tipis bisa terbaca sama atau bahkan tertukar. Hasilnya bukan hanya
jawaban salah, tetapi bisa juga **crash** — komparator yang tidak konsisten
melanggar strict weak ordering dan membuat `std::sort` membaca di luar batas.

### ✅ Pakai perkalian silang

```
v_a / w_a  >  v_b / w_b     (dengan w_a, w_b > 0)
⟺  v_a · w_b  >  v_b · w_a
```

```cpp
return (__int128)v[a] * w[b] > (__int128)v[b] * w[a];
```

**Kenapa `__int128`?** `v · w` dengan keduanya `10^9` menghasilkan `10^18`, yang
masih muat di `long long` (`9.2·10^18`) — tapi nyaris. Kalau batasannya sedikit
lebih besar, kamu meluap. `__int128` menghilangkan kekhawatiran itu tanpa biaya
berarti.

**Syarat penting:** perkalian silang hanya sah kalau `w > 0`. Kalau `w` bisa nol,
lihat Bagian 7.

---

<a name="5"></a>
## 5. Keluarga Knapsack Lengkap

Rangkuman satu halaman. Perhatikan **arah loop** — itu satu-satunya perbedaan
antara 0/1 dan unbounded.

### 0/1 — tiap barang paling banyak sekali

```cpp
for (int i = 0; i < n; i++)
    for (ll c = W; c >= w[i]; c--)          // MUNDUR
        dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
```

Loop mundur memastikan `dp[c - w[i]]` masih berisi keadaan **sebelum** barang
`i` dipertimbangkan.

### Unbounded — tiap barang berkali-kali

```cpp
for (ll c = 1; c <= W; c++)                 // MAJU
    for (int i = 0; i < n; i++)
        if (w[i] <= c) dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
```

Loop maju sengaja membiarkan `dp[c - w[i]]` sudah memuat barang `i`.

### Bounded — tiap barang paling banyak `c_i` kali

Dekomposisi biner: pecah `c_i` menjadi `1, 2, 4, ..., sisa`, lalu perlakukan
setiap potongan sebagai barang 0/1. Dengan potongan-potongan itu, setiap jumlah
dari `0` sampai `c_i` bisa dibentuk.

```cpp
for (ll k = 1; cnt > 0; k <<= 1) {
    ll amb = min(k, cnt);
    barang0_1.push_back({w[i] * amb, v[i] * amb});
    cnt -= amb;
}
```

### Fractional — boleh dipotong

Greedy rasio, seperti Bagian 2.

### Tabel perbandingan

| Varian | Teknik | Waktu | `W` besar? |
|---|---|---|---|
| Fractional | greedy | `O(n log n)` | ✅ tidak masalah |
| 0/1 | DP mundur | `O(n·W)` | ❌ mustahil |
| Unbounded | DP maju | `O(n·W)` | ❌ mustahil |
| Bounded | DP + biner | `O(n·W·log c)` | ❌ mustahil |

---

<a name="6"></a>
## 6. Pola Rasio Lain: Fractional Programming

Rasio muncul di luar knapsack, dan di sana greedy biasanya **tidak** langsung
bekerja.

### Masalah: maksimalkan `sum(a_i) / sum(b_i)` atas himpunan bagian berukuran `k`

Naluri: urutkan menurut `a_i / b_i` dan ambil `k` teratas. **Salah** — contoh
tandingannya mudah dibuat, karena rasio total bukan gabungan sederhana dari rasio
individual.

**Teknik yang benar (Dinkelbach / binary search on answer):**

```
Apakah ada himpunan bagian dengan rasio ≥ x?
⟺  sum(a) / sum(b) ≥ x
⟺  sum(a) − x·sum(b) ≥ 0
⟺  sum(a_i − x·b_i) ≥ 0
```

Sisi kanan bisa dimaksimalkan langsung: hitung `d_i = a_i − x·b_i`, ambil `k`
terbesar, jumlahkan. Kalau hasilnya `≥ 0`, maka `x` bisa dicapai.

Predikat ini **monoton turun** terhadap `x` → binary search.

```cpp
double lo = 0, hi = 1e9;
for (int it = 0; it < 100; it++) {          // 100 iterasi, bukan while
    double x = (lo + hi) / 2;
    for (int i = 0; i < n; i++) d[i] = a[i] - x * b[i];
    sort(d.rbegin(), d.rend());
    double s = 0;
    for (int i = 0; i < k; i++) s += d[i];
    if (s >= 0) lo = x; else hi = x;
}
```

Ini menggabungkan Day 51 (binary search real, 100 iterasi tetap) dengan pola
rasio hari ini. Perhatikan trik `a_i − x·b_i` — bentuknya sama persis dengan
trik `a_i − x` pada soal "maksimalkan rata-rata" di Day 51.

### Kapan rasio boleh langsung di-greedy?

| Soal | Greedy rasio? |
|---|---|
| Fractional knapsack | ✅ |
| 0/1 knapsack | ❌ (DP) |
| Urutan tugas minimalkan `sum(w_i·C_i)` | ✅ (Day 71) |
| Maksimalkan `sum(a)/sum(b)` atas subset | ❌ (binary search) |
| Maksimalkan rata-rata subarray | ❌ (binary search) |

Polanya: greedy rasio bekerja kalau **setiap satuan sumber daya bisa dinilai
secara terpisah**. Begitu ada batasan yang mengikat barang menjadi satu kesatuan
(harus utuh) atau membuat nilai bergantung pada seluruh himpunan (rasio total),
greedy runtuh.

---

<a name="7"></a>
## 7. Kasus Tepi yang Membunuh

### `w_i = 0` (barang tanpa berat)

Perkalian silang `v_a·w_b > v_b·w_a` menjadi `v_a·0 > v_b·w_a`, yang **selalu
false** ketika `w_b = 0`. Akibatnya barang gratis bernilai tinggi justru
tenggelam ke bawah dan tidak terambil.

**Solusi:** tangani terpisah — ambil semua barang dengan `w = 0` dan `v > 0`
lebih dulu, lalu jalankan algoritma pada sisanya.

### `v_i = 0`

Tidak berbahaya untuk kebenaran (barang itu akan berada di urutan terakhir),
tetapi jangan sampai ia mengonsumsi kapasitas. Kode standar aman karena rasionya
nol dan hanya diambil setelah semua yang bernilai habis.

### `W = 0`

Loop harus langsung berhenti. Kode `if (sisa == 0) break;` menanganinya.

### Format keluaran

Jawaban fractional biasanya **bukan bilangan bulat**. Perhatikan berapa desimal
yang diminta. Kalau soal meminta jawaban eksak, pakai representasi pecahan
(lihat `fractionalEksak` di template) alih-alih `double`.

### Presisi `double`

Kalau soal minta 6 desimal dan nilainya sampai `10^14`, `double` sudah di batas
presisi (`~15–16` digit signifikan). Pertimbangkan `long double`, atau susun
ulang perhitungan agar tidak menjumlahkan bilangan besar dengan bilangan kecil.

---

<a name="8"></a>
## 8. Ringkasan, Jebakan, dan Latihan Mandiri

### Pohon keputusan

```
Soal knapsack
├── boleh dipotong?
│   ├── YA  -> greedy rasio, O(n log n)
│   └── TIDAK
│       ├── W kecil (<= 10^5)
│       │   ├── sekali per barang     -> DP mundur
│       │   ├── berkali-kali          -> DP maju
│       │   └── paling banyak c kali  -> DP + dekomposisi biner
│       ├── n <= 40                   -> meet in the middle (Day 54)
│       └── W besar, nilai kecil      -> DP di atas NILAI, bukan berat
└── yang dimaksimalkan berupa RASIO total -> binary search on answer
```

### Jebakan

1. **Greedy rasio pada 0/1.** Gagal ~12% kasus acak. Hafalkan contoh tandingan
   `W=10`, `(6,7) (5,5) (5,5)`.
2. **Membandingkan rasio dengan `double`.** Pakai perkalian silang.
3. **Lupa `__int128`** pada perkalian silang saat `v, w` besar.
4. **`w = 0`** merusak perkalian silang.
5. **Salah arah loop DP.** Mundur = 0/1, maju = unbounded.
6. **Format keluaran pecahan.**
7. **Menyangka `sum(a)/sum(b)` bisa di-greedy.** Itu binary search.

### Kompleksitas

| Operasi | Waktu | Memori |
|---|---|---|
| Fractional knapsack | `O(n log n)` | `O(n)` |
| 0/1 knapsack | `O(n·W)` | `O(W)` |
| Unbounded | `O(n·W)` | `O(W)` |
| Bounded (biner) | `O(n·W·log c)` | `O(W)` |
| Fractional programming | `O(100·n log n)` | `O(n)` |

### Latihan mandiri

- Jalankan sendiri eksperimen di template dengan batasan berbeda: apa yang
  terjadi pada persentase kegagalan greedy kalau `W` jauh lebih besar dari total
  berat? Kalau semua berat sama? Kalau semua nilai sama? Jawaban-jawaban ini
  membangun intuisi tentang **kapan** greedy kebetulan benar.
- Implementasikan branch and bound untuk 0/1 knapsack memakai batas atas
  fractional, lalu bandingkan waktu jalannya dengan DP pada `n = 35`, `W = 10^9`
  (DP tidak akan bisa; itulah intinya).
