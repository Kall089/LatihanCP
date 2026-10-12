# 📊 Day 52: Ternary Search untuk Fungsi Unimodal

> **Prasyarat:** Binary Search Real (Day 51), Binary Search on Answer (Day 50)
> **Estimasi belajar:** 3 jam (teori + 6 latihan)
> **Kata kunci soal:** *"minimum/maksimum sebuah fungsi"*, *"naik lalu turun"*, *"titik optimal"*

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan Day 52, kamu akan mampu:

- [ ] Mendefinisikan **unimodal** dan membedakannya dari **monoton**
- [ ] Menjelaskan kenapa binary search **tidak berlaku** pada fungsi unimodal
- [ ] Menulis ternary search versi **real** dan versi **integer**
- [ ] Menjelaskan kenapa versi integer butuh **penanganan khusus** di akhir
- [ ] Menghitung berapa iterasi yang dibutuhkan (basis `3/2`, bukan `2`)
- [ ] Mengenali kapan fungsinya **tidak** unimodal dan alat ini gagal diam-diam
- [ ] Memakai alternatif: **binary search pada selisih** dan **convexity**

---

## 🔍 1. Konsep & Intuisi

### Unimodal vs monoton

```
MONOTON (binary search berlaku):
    f: ────────╱╱╱╱╱╱╱        naik terus
       atau    ╲╲╲╲╲╲╲        turun terus

UNIMODAL (ternary search berlaku):
    f:      ╱╲                 naik lalu turun (satu puncak)
          ╱    ╲
        ╱        ╲

    atau    ╲    ╱             turun lalu naik (satu lembah)
              ╲╱
```

Kenapa binary search gagal? Karena tidak ada predikat monoton yang bisa dibentuk.
Kalau kamu bertanya *"apakah `f(mid) > K`?"*, jawabannya bisa `true` di dua daerah
terpisah — dan kamu tidak tahu harus membuang sisi yang mana.

### Analogi: mendaki bukit dalam kabut

Kamu berada di jalan setapak yang menanjak lalu menurun, tetapi kabut tebal
menghalangi pandangan. Kamu ingin menemukan puncaknya.

Kalau kamu hanya mengukur ketinggian di **satu** titik, kamu tidak tahu apa-apa —
apakah puncaknya di kiri atau kanan?

Tetapi kalau kamu mengukur di **dua** titik `m1 < m2`:

```
f(m1) < f(m2)  ->  puncaknya pasti di sebelah KANAN m1
                   (karena kalau puncak ada di kiri m1, maka setelah m1
                    fungsinya menurun, sehingga f(m2) < f(m1) — kontradiksi)
                   -> buang [lo, m1]

f(m1) > f(m2)  ->  puncaknya pasti di sebelah KIRI m2
                   -> buang [m2, hi]
```

Dua pengukuran memberi informasi yang cukup untuk membuang sebagian ruang.
Itulah seluruh ide ternary search.

```
lo          m1        m2          hi
|-----------|---------|-----------|
    1/3         1/3        1/3

f(m1) < f(m2) -> lo = m1     (buang sepertiga kiri)
f(m1) > f(m2) -> hi = m2     (buang sepertiga kanan)
```

### Berapa iterasi?

Setiap langkah menyisakan `2/3` dari rentang:

```
setelah k iterasi: lebar = rentang_awal * (2/3)^k
```

```
rentang 10^9, presisi 10^-6:
    (2/3)^k <= 10^-15
    k * log(2/3) <= -15 * log(10)
    k >= 15 * 2.3026 / 0.4055 ~ 85
```

**200 iterasi** aman untuk hampir semua soal. Perhatikan bahwa ini **lebih banyak**
daripada binary search (100), karena setiap langkah membuang lebih sedikit —
`1/3` alih-alih `1/2`.

⚠️ Ternary search juga **lebih mahal per iterasi**: ia mengevaluasi `f` **dua kali**,
sedangkan binary search hanya sekali. Jadi totalnya bisa 4× lebih lambat dari
binary search. Kalau ada cara mengubahnya menjadi binary search, lakukan itu.

---

## 🧮 2. Analisis Kompleksitas

| Pendekatan | Iterasi | Evaluasi `f` | Catatan |
| ---------- | ------- | ------------ | ------- |
| Ternary search real | ~200 | 2 per iterasi | 400 evaluasi |
| Ternary search integer | `log_{1.5}(n)` | 2 per iterasi | butuh penanganan akhir |
| Binary search pada selisih | ~60 | 2 per iterasi | **lebih disukai kalau bisa** |
| Golden section search | ~140 | **1** per iterasi | lebih cepat, lebih rumit |
| Brute force | `n` | 1 | untuk `n` kecil |

**Total waktu** = `iterasi × 2 × biaya_f`. Kalau `f` berbiaya `O(n)` dengan
`n = 10^5`, maka `200 × 2 × 10^5 = 4·10^7` — aman. Kalau `f` berbiaya `O(n log n)`,
hitung ulang dengan teliti.

### Alternatif yang sering lebih baik: binary search pada selisih

Kalau `f` unimodal (naik lalu turun), maka **selisihnya** `g(i) = f(i+1) − f(i)`
bersifat **monoton menurun** — positif di daerah naik, negatif di daerah turun.

```
f:   1  4  7  9  8  5  2        unimodal (puncak di indeks 3)
g:    3  3  2 -1 -3 -3          MONOTON menurun
                ↑
        cari peralihan positif -> negatif dengan BINARY SEARCH
```

Ini mengubah masalah unimodal menjadi masalah monoton — dan binary search
lebih cepat, lebih sedikit iterasi, serta bebas dari masalah "dua titik sama nilai"
yang mengganggu ternary search integer.

> **Saran praktis:** untuk fungsi **integer**, hampir selalu lebih baik memakai
> binary search pada selisih. Ternary search integer punya kasus tepi yang
> merepotkan; binary search pada selisih tidak.

---

## 💻 3. Implementasi C++

### 3.1 Ternary search real — mencari MINIMUM

```cpp
double cariMinimum(double lo, double hi, function<double(double)> f) {
    for (int iter = 0; iter < 200; iter++) {
        double m1 = lo + (hi - lo) / 3;
        double m2 = hi - (hi - lo) / 3;
        if (f(m1) < f(m2)) hi = m2;      // minimum ada di kiri m2
        else               lo = m1;      // minimum ada di kanan m1
    }
    return (lo + hi) / 2;
}
```

Untuk **maksimum**, cukup balik tanda perbandingannya:

```cpp
if (f(m1) > f(m2)) hi = m2;   // maksimum ada di kiri m2
else               lo = m1;
```

⚠️ Atau lebih aman: cari minimum dari `−f(x)`. Satu fungsi, tidak ada tanda yang
bisa tertukar.

### 3.2 Ternary search integer

```cpp
// Mencari indeks yang MEMINIMUMKAN f pada [lo, hi] inklusif.
int cariMinimumInt(int lo, int hi, function<long long(int)> f) {
    while (hi - lo > 2) {                       // sisakan <= 3 kandidat
        int m1 = lo + (hi - lo) / 3;
        int m2 = hi - (hi - lo) / 3;
        if (f(m1) < f(m2)) hi = m2 - 1;
        else               lo = m1 + 1;
    }
    // periksa sisa kandidat satu per satu
    int best = lo;
    for (int i = lo + 1; i <= hi; i++)
        if (f(i) < f(best)) best = i;
    return best;
}
```

⚠️ **Kenapa harus menyisakan beberapa kandidat dan memeriksanya manual?**
Karena pada domain diskrit, `m1` dan `m2` bisa **bertepatan** atau berdekatan
sehingga `f(m1) == f(m2)` tanpa memberi informasi apa pun tentang arah. Loopnya
bisa macet. Menghentikan loop saat rentangnya kecil, lalu memeriksa manual,
menghilangkan seluruh kelas masalah itu.

### 3.3 Binary search pada selisih (disarankan untuk integer)

```cpp
// f unimodal (naik lalu turun). Cari indeks puncaknya.
int cariPuncak(int lo, int hi, function<long long(int)> f) {
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (f(mid) < f(mid + 1)) lo = mid + 1;   // masih menanjak
        else                     hi = mid;        // sudah menurun
    }
    return lo;
}
```

Kerangka yang **sama persis** dengan Day 49. Predikatnya: *"apakah `f` masih
menanjak di `mid`?"* — dan itu monoton karena fungsinya unimodal.

⚠️ Syaratnya lebih ketat: `f` harus **strictly** unimodal (tidak ada dataran datar).
Kalau ada `f(mid) == f(mid+1)` di daerah datar, kamu bisa terjebak. Tetapi ini
juga masalah yang sama untuk ternary search — jadi bukan kelemahan tambahan.

### 3.4 Ternary search bersarang (dua dimensi)

Kalau `f(x, y)` unimodal terhadap `x` untuk setiap `y` **dan** unimodal terhadap
`y` untuk setiap `x`:

```cpp
double f2d(double x) {
    // untuk x tetap, cari y terbaik dengan ternary search
    double lo = -1e6, hi = 1e6;
    for (int i = 0; i < 100; i++) {
        double m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
        if (g(x, m1) < g(x, m2)) hi = m2; else lo = m1;
    }
    return g(x, (lo + hi) / 2);
}
// lalu ternary search pada x memakai f2d
```

Biayanya `200 × 2 × 200 × 2 = 160000` evaluasi. Boros, tetapi kadang inilah
satu-satunya cara. Kurangi jumlah iterasi lapisan dalam kalau perlu.

### 3.5 Contoh fungsi unimodal yang sering muncul

```cpp
// 1. Parabola: f(x) = a*x^2 + b*x + c dengan a > 0  -> minimum di -b/(2a)
//    (ini punya rumus eksak, tidak perlu ternary search -- tetapi berguna
//     sebagai uji kebenaran implementasimu)

// 2. Jumlah jarak: f(x) = sum |a[i] - x|
//    -> unimodal (cembung), minimumnya di MEDIAN. Juga punya solusi eksak.

// 3. Jumlah kuadrat jarak: f(x) = sum (a[i] - x)^2
//    -> minimumnya di RATA-RATA. Solusi eksak.

// 4. f(x) = max atas beberapa fungsi linear
//    -> cembung, unimodal. Ternary search berlaku dan sering tidak ada
//       solusi eksak yang mudah.

// 5. Waktu tempuh dengan pergantian moda di titik x
//    -> biasanya cembung. Contoh khas soal ternary search.
```

⚠️ Perhatikan bahwa contoh 1–3 punya **solusi eksak**. Kalau kamu mengenali
bentuknya, jangan pakai ternary search — pakai rumusnya. Ternary search adalah
alat untuk fungsi yang **tidak** punya rumus tertutup.

---

## 🔄 4. Trace & Simulasi

### 4.1 Ternary search pada `f(x) = (x − 3)²`, mencari minimum di `[0, 10]`

| iter | lo | hi | m1 | m2 | f(m1) | f(m2) | f(m1) < f(m2)? | aksi |
| ---- | -- | -- | -- | -- | ----- | ----- | -------------- | ---- |
| 1 | 0.00 | 10.00 | 3.33 | 6.67 | 0.11 | 13.44 | ya | `hi = 6.67` |
| 2 | 0.00 | 6.67 | 2.22 | 4.44 | 0.60 | 2.08 | ya | `hi = 4.44` |
| 3 | 0.00 | 4.44 | 1.48 | 2.96 | 2.30 | 0.00 | tidak | `lo = 1.48` |
| 4 | 1.48 | 4.44 | 2.47 | 3.46 | 0.28 | 0.21 | tidak | `lo = 2.47` |
| 5 | 2.47 | 4.44 | 3.13 | 3.79 | 0.02 | 0.62 | ya | `hi = 3.79` |

```
rentang menyempit: 10 -> 6.67 -> 4.44 -> 2.96 -> 1.97 -> 1.32 ...
setiap langkah menjadi 2/3 lebarnya
setelah 200 iterasi: (2/3)^200 ~ 10^-35, jauh di bawah presisi double
konvergen ke 3.0   ✓
```

Bandingkan dengan binary search yang menyisakan `1/2` per langkah: ternary search
memang lebih lambat menyempit, itulah kenapa butuh lebih banyak iterasi.

### 4.2 Kenapa binary search gagal di sini

```
f(x) = (x - 3)^2 pada [0, 10]

Coba predikat "f(mid) > 1":
   f(0) = 9  -> true
   f(2) = 1  -> false
   f(3) = 0  -> false
   f(5) = 4  -> true

Pola: TRUE ... FALSE ... TRUE      <- TIDAK MONOTON
```

Binary search tidak punya aturan yang benar untuk memilih sisi. Ia akan memberi
jawaban, tetapi jawaban itu sembarang.

### 4.3 Ternary search integer dan masalahnya

```
f = [1, 4, 7, 9, 8, 5, 2]   indeks 0..6, puncak di indeks 3

lo=0, hi=6:
   m1 = 0 + 6/3 = 2, m2 = 6 - 6/3 = 4
   f(2)=7, f(4)=8 -> f(m1) < f(m2) (mencari maksimum: f(m1) < f(m2) -> buang kiri)
   lo = m1 + 1 = 3

lo=3, hi=6:
   m1 = 3 + 1 = 4, m2 = 6 - 1 = 5
   f(4)=8, f(5)=5 -> f(m1) > f(m2) -> hi = m2 - 1 = 4

lo=3, hi=4:  hi - lo = 1 <= 2  -> keluar loop
periksa manual f(3)=9, f(4)=8  ->  jawabannya indeks 3   ✓
```

**Kasus yang bermasalah** — kalau ada dataran datar:

```
f = [1, 5, 5, 5, 2]

m1 dan m2 keduanya jatuh di daerah datar -> f(m1) == f(m2)
Tidak ada informasi arah. Kalau kamu memilih cabang sembarang, kamu bisa
membuang sisi yang memuat jawabannya.
```

Untuk `f` yang punya dataran, **tidak ada** jaminan ternary search benar.
Ini bukan bug implementasi — memang syaratnya tidak terpenuhi.

### 4.4 Binary search pada selisih untuk kasus yang sama

```
f = [1, 4, 7, 9, 8, 5, 2]
g(i) = f(i+1) - f(i) untuk i = 0..5:
g = [3, 3, 2, -1, -3, -3]

Predikat: g(i) > 0 (masih menanjak)
   TRUE TRUE TRUE FALSE FALSE FALSE     <- MONOTON

Cari indeks pertama yang FALSE -> indeks 3
Puncaknya di indeks 3.   ✓
```

Lebih sederhana, lebih sedikit iterasi, dan memakai kerangka yang sudah kamu
kuasai dari Day 49.

---

## 📝 5. Variasi & Pattern

| Kalimat di soal | Yang dipakai |
| --------------- | ------------ |
| "minimumkan f(x)" dengan `f` cembung | ternary search real |
| "maksimumkan f(x)" dengan `f` cekung | ternary search real |
| fungsi integer unimodal | **binary search pada selisih** |
| `f(x) = Σ|a[i] − x|` | median (solusi eksak, jangan ternary) |
| `f(x) = Σ(a[i] − x)²` | rata-rata (solusi eksak) |
| `f(x) = max` beberapa fungsi linear | ternary search (cembung) |
| "waktu tempuh minimum dengan titik pergantian" | ternary search |
| optimasi dua variabel | ternary bersarang (mahal) |
| fungsi punya **dataran** | ⚠️ ternary search **tidak** dijamin benar |

### Pattern: fungsi cembung dari `max`

Jika `f(x) = max(g₁(x), g₂(x), ..., gₖ(x))` dan setiap `gᵢ` adalah fungsi **linear**,
maka `f` pasti **cembung** (dan karenanya unimodal). Ini teorema yang berguna:
kamu bisa memakai ternary search tanpa membuktikan unimodalitas satu per satu.

Contoh: `f(t) = ` jarak maksimum yang ditempuh salah satu dari `k` objek yang
bergerak lurus pada waktu `t`.

### Pattern: memeriksa unimodalitas

Sebelum memakai ternary search, **buktikan** fungsimu unimodal — atau setidaknya
uji secara empiris:

```cpp
// uji cepat: evaluasi f pada 1000 titik, cek apakah polanya naik-lalu-turun
bool ujiUnimodal(function<double(double)> f, double lo, double hi) {
    int n = 1000;
    vector<double> v(n);
    for (int i = 0; i < n; i++) v[i] = f(lo + (hi - lo) * i / (n - 1));
    int naik = 0;
    for (int i = 1; i < n; i++) if (v[i] > v[i-1]) naik++;
    // pada unimodal (naik lalu turun), pergantian arah hanya terjadi SEKALI
    int ganti = 0;
    for (int i = 2; i < n; i++)
        if ((v[i] > v[i-1]) != (v[i-1] > v[i-2])) ganti++;
    return ganti <= 1;
}
```

Lima menit menguji jauh lebih murah daripada satu jam men-debug algoritma yang
memang tidak berlaku.

---

## ⚠️ 6. Common Mistakes & Edge Cases

1. **Memakai ternary search pada fungsi yang tidak unimodal.** Ini **gagal diam-diam**
   — ia memberi jawaban yang terlihat masuk akal tetapi salah. Kesalahan paling
   berbahaya di topik ini.

2. **Fungsi punya dataran datar.** `f(m1) == f(m2)` tidak memberi informasi arah.

3. **Tanda perbandingan terbalik** (minimum vs maksimum). Uji dengan fungsi
   sederhana seperti `(x−3)²` sebelum memakainya pada soal sungguhan.

4. **Iterasi terlalu sedikit.** Ternary search butuh **lebih banyak** iterasi
   daripada binary search karena hanya membuang `1/3`.

5. **Versi integer tanpa penanganan akhir.** Loopnya bisa macet atau melewatkan
   jawaban.

6. **Lupa bahwa `f` dievaluasi dua kali per iterasi.** Kalau `f` mahal, hitung
   ulang total biayanya.

7. **Memakai ternary search padahal ada solusi eksak.** `Σ|a[i]−x|` minimumnya
   di median; tidak perlu pencarian.

8. **Ternary bersarang tanpa menghitung biaya.** `200 × 2 × 200 × 2` evaluasi
   bisa jauh melampaui batas waktu.

### Edge cases wajib diuji

```
minimum di ujung kiri rentang     -> lo tidak pernah bergerak
minimum di ujung kanan rentang    -> hi tidak pernah bergerak
fungsi konstan                    -> tidak unimodal ketat; hasilnya sembarang
                                     (tetapi nilai minimumnya tetap benar)
rentang sangat sempit (lo ~ hi)   -> pastikan tidak membagi nol
fungsi dengan dua puncak          -> ternary search SALAH, uji dulu
n = 1 pada versi integer          -> jangan masuk loop
```

---

## 🏆 7. Tips Contest

**Urutan pertimbangan:**

```
1. Apakah ada solusi eksak?           (median, rata-rata, rumus parabola)
2. Apakah bisa jadi binary search?    (binary search pada selisih)
3. Baru ternary search.
```

**Kalau fungsinya integer,** hampir selalu pakai **binary search pada selisih**.
Kerangkanya sama dengan Day 49, iterasinya lebih sedikit, dan tidak ada kasus
tepi yang merepotkan.

**Kalau fungsinya real,** ternary search dengan 200 iterasi adalah pilihan yang
aman dan mudah ditulis.

**Sebelum submit, uji dengan fungsi yang kamu tahu jawabannya.** Misalnya
`f(x) = (x − 3)²` pada `[0, 10]` harus memberi 3. Sepuluh detik, dan ia menangkap
tanda perbandingan yang terbalik — bug paling umum di topik ini.

**Tanda-tanda soal ternary search:** ada satu parameter kontinu yang bisa kamu
pilih (waktu, posisi, sudut, kecepatan), dan hasilnya memburuk kalau kamu terlalu
kecil **maupun** terlalu besar. Kata kunci: *"optimal"*, *"minimum dari maksimum"*
dalam konteks kontinu.

---

## 📌 8. Ringkasan & Cheatsheet

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  TERNARY SEARCH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  MONOTON  -> binary search
  UNIMODAL -> ternary search   (naik lalu turun, SATU puncak)

  REAL (mencari MINIMUM):
    for (int it = 0; it < 200; it++) {
        double m1 = lo + (hi - lo) / 3;
        double m2 = hi - (hi - lo) / 3;
        if (f(m1) < f(m2)) hi = m2;
        else               lo = m1;
    }
    return (lo + hi) / 2;

    MAKSIMUM: balik tandanya, ATAU cari minimum dari -f(x) (lebih aman)

  BERAPA ITERASI: rentang * (2/3)^k <= presisi
    lebih banyak dari binary search (buang 1/3, bukan 1/2)
    200 iterasi aman; ingat f dievaluasi DUA KALI per iterasi

  INTEGER -> LEBIH BAIK BINARY SEARCH PADA SELISIH:
    while (lo < hi) {
        mid = lo + (hi - lo) / 2;
        if (f(mid) < f(mid + 1)) lo = mid + 1;    masih menanjak
        else                     hi = mid;
    }
    kerangka SAMA dengan Day 49, lebih sedikit iterasi, tanpa kasus tepi

  SOLUSI EKSAK (jangan pakai ternary kalau mengenali bentuknya):
    sum |a[i] - x|      -> MEDIAN
    sum (a[i] - x)^2    -> RATA-RATA
    a*x^2 + b*x + c     -> -b / (2a)

  max dari beberapa fungsi LINEAR selalu CEMBUNG -> unimodal

  BAHAYA: fungsi TIDAK unimodal -> GAGAL DIAM-DIAM, jawaban salah
          fungsi punya DATARAN  -> f(m1) == f(m2), tidak ada info arah
  UJI DULU dengan f(x) = (x-3)^2 yang jawabannya kamu tahu
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### Soal latihan online

| Soal | Platform | Topik |
| ---- | -------- | ----- |
| [CF 439D — Devu and his Brother](https://codeforces.com/problemset/problem/439/D) | Codeforces | ternary / median |
| [CF 578C — Weakness and Poorness](https://codeforces.com/problemset/problem/578/C) | Codeforces | ternary + Kadane |
| [CF 1301E / 1355E](https://codeforces.com/problemset) | Codeforces | ternary pada biaya |
| [AtCoder ABC 279 D — Freefall](https://atcoder.jp/contests/abc279/tasks/abc279_d) | AtCoder | ternary integer |
| [AtCoder ABC 130 D / 102 C](https://atcoder.jp/) | AtCoder | fungsi cembung |
| [SPOJ KOPC12A / TRT](https://www.spoj.com/) | SPOJ | optimasi |
| [LeetCode 852 — Peak Index in Mountain Array](https://leetcode.com/problems/peak-index-in-a-mountain-array/) | LeetCode | puncak unimodal |
| [LeetCode 162 — Find Peak Element](https://leetcode.com/problems/find-peak-element/) | LeetCode | binary search pada selisih |

---

**Selanjutnya:** Day 53 — Parallel Binary Search. Sejauh ini kita menjalankan satu
binary search untuk satu pertanyaan. Besok kamu akan menjalankan **ribuan binary
search sekaligus** — bukan satu per satu, melainkan berbarengan, dengan mengelompokkan
pertanyaan yang kebetulan sedang memeriksa nilai tengah yang sama.
