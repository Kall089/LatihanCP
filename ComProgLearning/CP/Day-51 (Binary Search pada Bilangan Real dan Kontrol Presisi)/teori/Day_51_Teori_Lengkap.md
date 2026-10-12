# 📊 Day 51: Binary Search pada Bilangan Real & Kontrol Presisi

> **Prasyarat:** Binary Search on Answer (Day 50), Bound Manual (Day 49), Floating Point (Day 10)
> **Estimasi belajar:** 3 jam (teori + 6 latihan)
> **Kata kunci soal:** *"cetak dengan 6 desimal"*, *"kesalahan tidak melebihi 1e-6"*, *"rata-rata maksimum"*

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan Day 51, kamu akan mampu:

- [ ] Menjelaskan kenapa `while (lo < hi)` **tidak bisa** dipakai pada bilangan real
- [ ] Memilih antara **iterasi tetap** dan **epsilon**, dan tahu kenapa yang pertama lebih aman
- [ ] Menghitung berapa iterasi yang dibutuhkan untuk presisi tertentu
- [ ] Membedakan **kesalahan absolut** dan **kesalahan relatif**
- [ ] Mencetak dengan `fixed` dan `setprecision` secara benar
- [ ] Menghindari perbandingan `==` pada `double` dan memahami kenapa
- [ ] Mengubah soal real menjadi soal **bilangan bulat** kalau memungkinkan

---

## 🔍 1. Konsep & Intuisi

### Kenapa kerangka integer tidak bisa dipakai

Pada bilangan bulat, `lo` dan `hi` akhirnya bertemu karena rentangnya **diskrit**.
Pada bilangan real, di antara dua bilangan mana pun selalu ada bilangan lain.

```
lo = 1.0, hi = 2.0
mid = 1.5 -> lo = 1.5
mid = 1.75 -> ...
```

`lo` dan `hi` bisa saling mendekat selamanya tanpa pernah **sama**. Bahkan lebih buruk:
karena `double` punya presisi terbatas, pada suatu titik `mid` menjadi sama persis
dengan `lo` atau `hi`, dan loopnya **berputar selamanya** tanpa kemajuan.

### Dua kriteria berhenti

**Cara 1 — iterasi tetap (disarankan):**

```cpp
for (int iter = 0; iter < 100; iter++) {
    double mid = (lo + hi) / 2;
    if (bisa(mid)) hi = mid;
    else           lo = mid;
}
// jawabannya lo (atau hi, atau (lo+hi)/2 — sudah sangat dekat)
```

**Cara 2 — epsilon:**

```cpp
while (hi - lo > 1e-9) {
    double mid = (lo + hi) / 2;
    ...
}
```

> **Kenapa cara 1 lebih aman?** Karena ia **selalu berhenti**. Cara 2 bisa berputar
> selamanya kalau `hi − lo` sudah lebih kecil daripada presisi `double` yang bisa
> direpresentasikan pada besaran itu — misalnya saat `lo` dan `hi` bernilai sekitar
> `10^18`, selisih `1e-9` tidak mungkin tercapai karena jarak antar `double`
> yang berdekatan di sana sudah lebih besar dari itu.

Cara 1 juga lebih mudah dianalisis: kamu tahu persis berapa lama ia berjalan.

### Berapa iterasi yang dibutuhkan?

Setiap iterasi membagi rentang menjadi dua:

```
setelah k iterasi, lebar rentang = (hi_awal − lo_awal) / 2^k
```

```
rentang awal 10^9, target presisi 10^-6:
    perlu 10^9 / 2^k <= 10^-6
    2^k >= 10^15
    k >= 50

rentang awal 10^18, target presisi 10^-9:
    2^k >= 10^27
    k >= 90
```

**100 iterasi** cukup untuk hampir semua soal: ia mengecilkan rentang dengan faktor
`2^100 ≈ 10^30`. Biayanya sepele — 100 kali evaluasi predikat.

⚠️ Tetapi ada batas yang tidak bisa dilewati: `double` hanya punya sekitar
**15–17 digit desimal signifikan**. Kalau jawabannya bernilai sekitar `10^9`,
kamu tidak bisa berharap presisi lebih baik dari sekitar `10^-7` secara absolut.
Menambah iterasi tidak membantu — informasinya memang tidak ada di dalam `double`.

### Kesalahan absolut vs relatif

Soal biasanya menuliskan salah satu dari dua kalimat ini:

```
"kesalahan absolut tidak melebihi 1e-6"
    |jawabanmu − benar| <= 1e-6

"kesalahan absolut ATAU relatif tidak melebihi 1e-6"
    |jawabanmu − benar| / max(1, |benar|) <= 1e-6
```

Bentuk kedua jauh lebih longgar untuk jawaban besar. Kalau jawabannya `10^9`,
kesalahan absolut `100` masih diterima. Ini penting: soal yang tampak menuntut
presisi mustahil sebenarnya memberi kelonggaran.

⚠️ Kalau soal hanya menyebut **absolut** dan jawabannya bisa besar, itu petunjuk
bahwa jawabannya mungkin sebenarnya **bilangan bulat** atau **pecahan sederhana** —
dan kamu sebaiknya mencari solusi eksak, bukan binary search real.

---

## 🧮 2. Analisis Kompleksitas

| Pendekatan | Iterasi | Catatan |
| ---------- | ------- | ------- |
| Iterasi tetap 100× | 100 | selalu berhenti, mudah dianalisis |
| Epsilon `1e-9` pada rentang `10^9` | ~60 | bisa tak berujung kalau nilainya besar |
| Epsilon relatif | bervariasi | lebih aman tetapi lebih rumit |
| Binary search integer | `log2(rentang)` | **selalu lebih disukai kalau mungkin** |

Total waktu = `iterasi × biaya_predikat`. Kalau predikatnya `O(n)` dan `n = 10^5`,
100 iterasi memberi `10^7` operasi — aman. Kalau predikatnya `O(n log n)`,
hitung ulang: `100 × 10^5 × 17 = 1.7·10^8`, mulai berisiko.

**Pertimbangan penting:** kalau kamu bisa mengubah soalnya menjadi bilangan bulat
(misalnya dengan mengalikan semua nilai dengan `1000`), lakukan itu. Binary search
integer bebas dari seluruh kelas masalah presisi.

---

## 💻 3. Implementasi C++

### 3.1 Kerangka baku

```cpp
double lo = 0, hi = 1e9;                  // batas bawah dan atas jawaban

for (int iter = 0; iter < 100; iter++) {
    double mid = (lo + hi) / 2;           // untuk double, ini AMAN
    if (bisa(mid)) hi = mid;              // mid layak, coba lebih kecil
    else           lo = mid;              // TIDAK mid + 1 -- ini bilangan real
}

printf("%.9f\n", lo);
```

⚠️ **Perhatikan `lo = mid`, bukan `lo = mid + 1`.** Pada bilangan real tidak ada
"bilangan berikutnya". Menambahkan 1 akan melompati seluruh rentang jawaban.

⚠️ **`(lo + hi) / 2` aman untuk `double`** karena `double` tidak meluap seperti
`long long` — ia hanya kehilangan presisi. Untuk `long long` tetap pakai
`lo + (hi − lo) / 2`.

### 3.2 Mencetak dengan presisi

```cpp
// Cara 1 — printf (paling ringkas dan jelas)
printf("%.9f\n", jawab);

// Cara 2 — cout
cout << fixed << setprecision(9) << jawab << '\n';
```

⚠️ `fixed` **wajib** bersama `setprecision`. Tanpa `fixed`, `setprecision(9)`
berarti "9 digit signifikan", bukan "9 digit di belakang koma":

```
tanpa fixed : setprecision(9) pada 1234567.891234  ->  1234567.89   (9 digit total)
dengan fixed: setprecision(9) pada 1234567.891234  ->  1234567.891234000
```

⚠️ Cetak **lebih banyak** desimal daripada yang diminta. Kalau soal minta `1e-6`,
cetak 9 desimal. Biayanya nol, dan ia melindungi dari pembulatan di batas.

### 3.3 Perbandingan yang aman

```cpp
const double EPS = 1e-9;

bool sama(double a, double b)      { return fabs(a - b) < EPS; }
bool kurangDari(double a, double b) { return a < b - EPS; }
bool kurangSama(double a, double b) { return a < b + EPS; }
```

⚠️ **Jangan pernah menulis `if (a == b)` untuk `double`.**
`0.1 + 0.2 == 0.3` bernilai **false** karena `0.1` dan `0.2` tidak bisa
direpresentasikan tepat dalam biner.

⚠️ Untuk nilai yang sangat besar, epsilon absolut menjadi terlalu ketat.
Pakai epsilon relatif:

```cpp
bool samaRelatif(double a, double b) {
    return fabs(a - b) <= 1e-9 * max(1.0, max(fabs(a), fabs(b)));
}
```

### 3.4 Pola klasik: memaksimalkan rata-rata

*Pilih tepat `k` elemen sehingga rata-ratanya maksimum.*

Kelihatannya tidak bisa di-binary-search karena rata-rata bukan fungsi monoton dari
apa pun. Tetapi:

```
rata-rata >= x
  <=>  (jumlah k elemen terpilih) / k >= x
  <=>  jumlah terpilih − k·x >= 0
  <=>  jumlah dari (a[i] − x) untuk elemen terpilih >= 0
```

Jadi predikatnya: *"apakah ada `k` elemen yang jumlah `(a[i] − x)`-nya ≥ 0?"* —
dan itu cukup mengambil `k` nilai `(a[i] − x)` terbesar.

```cpp
bool bisa(double x, const vector<double>& a, int k) {
    vector<double> b(a.size());
    for (size_t i = 0; i < a.size(); i++) b[i] = a[i] - x;
    sort(b.rbegin(), b.rend());
    double s = 0;
    for (int i = 0; i < k; i++) s += b[i];
    return s >= 0;
}
```

**Trik `a[i] − x` ini adalah pola paling penting dari seluruh topik ini.** Ia
mengubah "rata-rata" (tidak monoton) menjadi "jumlah" (monoton), dan muncul di
puluhan soal: rata-rata maksimum, rasio maksimum, *maximum density subgraph*,
dan seluruh keluarga **fractional programming**.

### 3.5 Pola: rata-rata segmen maksimum dengan panjang minimal L

```cpp
bool bisa(double x, const vector<double>& a, int L) {
    int n = a.size();
    vector<double> pre(n + 1, 0);
    for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + (a[i] - x);

    double minPre = 0;
    for (int i = L; i <= n; i++) {
        minPre = min(minPre, pre[i - L]);
        if (pre[i] - minPre >= 0) return true;   // ada segmen yang memenuhi
    }
    return false;
}
```

Gabungan tiga teknik: transformasi `a[i] − x`, prefix sum (Day 29), dan minimum
berjalan. Ini bentuk soal yang sangat umum.

### 3.6 Kapan JANGAN memakai bilangan real

Kalau jawabannya dijamin bilangan bulat atau kelipatan sesuatu, **jangan** memakai
`double` sama sekali:

```cpp
// SALAH: rawan presisi
double lo = 0, hi = 1e9;
for (int i = 0; i < 100; i++) { ... }

// BENAR: kalau jawabannya pasti bilangan bulat
long long lo = 0, hi = 1e9;
while (lo < hi) {
    long long mid = lo + (hi - lo) / 2;
    if (bisa(mid)) hi = mid;
    else           lo = mid + 1;
}
```

Kalau nilainya punya sampai 3 desimal, kalikan semuanya dengan 1000 dan kerjakan
dalam bilangan bulat. Ini menghilangkan seluruh kelas bug presisi sekaligus.

---

## 🔄 4. Trace & Simulasi

### 4.1 Mencari akar kuadrat 2 dengan 10 iterasi

```
lo = 0, hi = 2, predikat: mid*mid >= 2
```

| iter | lo | hi | mid | mid² | ≥ 2? | aksi |
| ---- | -- | -- | --- | ---- | ---- | ---- |
| 1 | 0 | 2 | 1.0 | 1.00 | tidak | `lo = 1.0` |
| 2 | 1.0 | 2 | 1.5 | 2.25 | ya | `hi = 1.5` |
| 3 | 1.0 | 1.5 | 1.25 | 1.5625 | tidak | `lo = 1.25` |
| 4 | 1.25 | 1.5 | 1.375 | 1.8906 | tidak | `lo = 1.375` |
| 5 | 1.375 | 1.5 | 1.4375 | 2.0664 | ya | `hi = 1.4375` |
| 6 | 1.375 | 1.4375 | 1.40625 | 1.9775 | tidak | `lo = 1.40625` |
| 7 | 1.40625 | 1.4375 | 1.421875 | 2.0217 | ya | `hi = 1.421875` |

```
setelah 7 iterasi : rentang [1.40625, 1.421875], lebar ~0.0156
setelah 50 iterasi: lebar ~2 / 2^50 ~ 1.8e-15
setelah 100 iterasi: lebar sudah di bawah presisi double
nilai benar: 1.41421356...
```

Perhatikan lebar rentang mengecil **eksponensial**: setiap iterasi membaginya dua.
Itulah kenapa 100 iterasi lebih dari cukup untuk hampir semua soal.

### 4.2 Rata-rata maksimum dari `k = 2` elemen pada `a = [1, 3, 5, 2]`

```
lo = 1, hi = 5
```

| iter | mid (x) | `a[i] − x` | 2 terbesar | jumlah | ≥ 0? | aksi |
| ---- | ------- | ---------- | ---------- | ------ | ---- | ---- |
| 1 | 3.0 | −2, 0, 2, −1 | 2, 0 | 2.0 | ya | `lo = 3.0` |
| 2 | 4.0 | −3, −1, 1, −2 | 1, −1 | 0.0 | ya | `lo = 4.0` |
| 3 | 4.5 | −3.5, −1.5, 0.5, −2.5 | 0.5, −1.5 | −1.0 | tidak | `hi = 4.5` |
| 4 | 4.25 | ... | 0.75, −1.25 | −0.5 | tidak | `hi = 4.25` |

```
konvergen ke 4.0
Verifikasi: dua elemen terbesar adalah 5 dan 3, rata-ratanya (5+3)/2 = 4.0   ✓
```

Perhatikan iterasi 2: jumlahnya **tepat 0**, artinya `x = 4` masih layak.
Ini kasus batas yang membuat pemilihan `>=` versus `>` pada predikat penting.

### 4.3 Kenapa `while (hi − lo > eps)` bisa tak berujung

```
lo = 1e18, hi = 1e18 + 1

Pada besaran 1e18, jarak antara dua double berdekatan sekitar 128.
Jadi hi - lo = 1 tidak bisa direpresentasikan -- selisihnya membulat.

mid = (lo + hi) / 2  ->  hasilnya SAMA PERSIS dengan lo (atau hi)
     -> lo = mid tidak mengubah apa pun
     -> hi - lo tidak pernah turun di bawah 1e-9
     -> BERPUTAR SELAMANYA
```

Dengan iterasi tetap, program tetap berhenti setelah 100 langkah — mungkin dengan
jawaban yang presisinya terbatas, tetapi setidaknya ia **berhenti**.

### 4.4 Jebakan `setprecision` tanpa `fixed`

```cpp
double x = 1234567.891234;

cout << setprecision(9) << x;           //  1234567.89     <- 9 digit SIGNIFIKAN
cout << fixed << setprecision(9) << x;  //  1234567.891234000
```

Kalau soal minta 6 desimal dan jawabannya besar, versi pertama akan kehilangan
seluruh bagian desimal — dan kamu mendapat WA meski algoritmanya benar sempurna.

---

## 📝 5. Variasi & Pattern

| Kalimat di soal | Yang dipakai |
| --------------- | ------------ |
| "cetak dengan 6 desimal" | binary search real, cetak 9 desimal |
| "kesalahan tidak melebihi 1e-6" | 100 iterasi cukup |
| "rata-rata maksimum" | trik `a[i] − x` |
| "rasio maksimum P/Q" | fractional programming, `P − x·Q` |
| "jarak minimum maksimum" | biasanya bilangan bulat — cek dulu |
| "waktu minimum" dengan kecepatan pecahan | real, atau kalikan agar bulat |
| jawabannya pasti bilangan bulat | **jangan** pakai `double` |
| nilai punya ≤ 3 desimal | kalikan 1000, kerjakan sebagai bilangan bulat |

### Pattern: fractional programming (rasio maksimum)

*Pilih himpunan bagian sehingga `(Σ p[i]) / (Σ q[i])` maksimum.*

```
rasio >= x
  <=>  Σp / Σq >= x
  <=>  Σp − x·Σq >= 0
  <=>  Σ(p[i] − x·q[i]) >= 0
```

Sekali lagi pola yang sama: bagi menjadi kurang, lalu masalahnya menjadi monoton.
Ini disebut **Dinkelbach / parametric search**, dan berlaku untuk banyak soal
optimasi rasio.

### Pattern: mengubah menjadi bilangan bulat

```
"jarak minimum antar sapi dimaksimalkan"  -> posisi bilangan bulat -> jawaban bulat
"waktu minimum menyelesaikan pekerjaan"   -> sering bulat, periksa
"panjang tali maksimum"                   -> sering ada 2 desimal -> kali 100
```

Selalu tanyakan: *"apakah jawabannya bisa dinyatakan sebagai bilangan bulat setelah
penskalaan?"* Kalau ya, lakukan — kamu menghilangkan seluruh kelas bug.

---

## ⚠️ 6. Common Mistakes & Edge Cases

1. **`lo = mid + 1` pada bilangan real.** Melompati seluruh rentang jawaban.

2. **`while (hi − lo > eps)` pada nilai besar.** Bisa tak berujung. Pakai iterasi tetap.

3. **`setprecision` tanpa `fixed`.** Mencetak digit signifikan, bukan desimal.

4. **Mencetak desimal terlalu sedikit.** Minta 6, cetak 9.

5. **`if (a == b)` pada `double`.** Hampir selalu salah.

6. **Epsilon absolut pada nilai besar.** `1e-9` mustahil dicapai kalau nilainya `10^18`.

7. **Batas atas terlalu kecil.** Sama seperti binary search integer, hitung kasus
   terburuk secara eksplisit.

8. **Memakai `double` padahal jawabannya bilangan bulat.** Menambah risiko tanpa alasan.

9. **`float` alih-alih `double`.** `float` hanya punya ~7 digit signifikan —
   hampir tidak pernah cukup. Selalu `double` (atau `long double` kalau perlu).

### Edge cases wajib diuji

```
jawaban tepat di batas bawah    -> lo tidak pernah bergerak
jawaban tepat di batas atas     -> hi tidak pernah bergerak
seluruh elemen sama             -> predikat berubah tepat di satu titik
nilai sangat besar (1e18)       -> presisi double terbatas
nilai sangat kecil (1e-9)       -> epsilon absolut jadi bermasalah
k = 1 dan k = n pada soal rata-rata
```

---

## 🏆 7. Tips Contest

**Aturan pertama: coba dulu apakah bisa dikerjakan dengan bilangan bulat.**
Kalau ya, kerjakan begitu. Seluruh materi hari ini adalah rencana cadangan.

**Kalau harus real, pakai kerangka ini apa adanya:**

```cpp
double lo = ..., hi = ...;
for (int it = 0; it < 100; it++) {
    double mid = (lo + hi) / 2;
    if (bisa(mid)) hi = mid; else lo = mid;
}
printf("%.9f\n", lo);
```

Tiga hal yang membuatnya aman: iterasi tetap (pasti berhenti), `lo = mid`
(bukan `mid + 1`), dan 9 desimal (lebih dari yang diminta).

**Kalau melihat "rata-rata" atau "rasio",** langsung pikirkan trik `a[i] − x`.
Ini pola yang membuka seluruh keluarga soal, dan tanpa mengetahuinya soalnya
terlihat mustahil.

**Kalau jawabanmu meleset di digit keenam,** biasanya bukan iterasinya kurang —
biasanya `fixed` yang lupa, atau kamu memakai `float`, atau presisi `double`
memang sudah habis karena nilainya terlalu besar.

**Menghitung ulang biaya:** 100 iterasi × predikat `O(n log n)` untuk `n = 10^5`
adalah `1.7·10^8`. Kalau ketat, kurangi menjadi 60 iterasi (masih memberi presisi
`10^-18` relatif terhadap rentang) atau optimalkan predikatnya.

---

## 📌 8. Ringkasan & Cheatsheet

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  BINARY SEARCH PADA BILANGAN REAL
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  KERANGKA BAKU (pakai apa adanya):
    double lo = ..., hi = ...;
    for (int it = 0; it < 100; it++) {
        double mid = (lo + hi) / 2;
        if (bisa(mid)) hi = mid;
        else           lo = mid;        <- lo = mid, BUKAN mid + 1
    }
    printf("%.9f\n", lo);

  ITERASI TETAP > EPSILON
    epsilon bisa TAK BERUJUNG kalau nilainya besar
    100 iterasi mengecilkan rentang dengan faktor 2^100 ~ 1e30

  BERAPA ITERASI: rentang / 2^k <= presisi
    rentang 1e9,  presisi 1e-6 -> k >= 50
    rentang 1e18, presisi 1e-9 -> k >= 90
    double hanya punya ~15-17 digit signifikan -- ada batas keras

  MENCETAK
    printf("%.9f\n", x)                        paling ringkas
    cout << fixed << setprecision(9) << x      'fixed' WAJIB
    cetak LEBIH BANYAK desimal dari yang diminta

  JANGAN PERNAH: if (a == b) untuk double
    pakai fabs(a - b) < EPS, atau epsilon RELATIF untuk nilai besar

  TRIK a[i] - x  (paling penting hari ini)
    rata-rata >= x  <=>  jumlah (a[i] - x) >= 0
    rasio P/Q >= x  <=>  jumlah (p[i] - x*q[i]) >= 0
    mengubah masalah TIDAK monoton menjadi monoton

  ATURAN PERTAMA: kalau jawabannya bisa bilangan bulat, JANGAN pakai double
    nilai punya <= 3 desimal -> kalikan 1000, kerjakan sebagai integer
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### Soal latihan online

| Soal | Platform | Topik |
| ---- | -------- | ----- |
| [CF 670C / 1613C](https://codeforces.com/problemset) | Codeforces | binary search real |
| [SPOJ AGGRCOW](https://www.spoj.com/problems/AGGRCOW/) | SPOJ | (integer — bandingkan!) |
| [POJ 2018 — Best Cow Fences](http://poj.org/problem?id=2018) | POJ | rata-rata segmen maksimum |
| [POJ 3111 — K Best](http://poj.org/problem?id=3111) | POJ | fractional programming |
| [LeetCode 644 — Maximum Average Subarray II](https://leetcode.com/problems/maximum-average-subarray-ii/) | LeetCode | trik `a[i] − x` |
| [LeetCode 774 — Minimize Max Distance to Gas Station](https://leetcode.com/problems/minimize-max-distance-to-gas-station/) | LeetCode | real, predikat greedy |
| [UVa 10341 — Solve It](https://onlinejudge.org/) | UVa | akar persamaan monoton |
| [Timus 1494 / e-olymp](https://acm.timus.ru/) | Timus | latihan presisi |

---

**Selanjutnya:** Day 52 — Ternary Search. Binary search membutuhkan predikat
**monoton**; ternary search bekerja pada fungsi **unimodal** (naik lalu turun),
di mana tidak ada predikat monoton yang bisa dibentuk. Kontrol presisi yang kamu
pelajari hari ini berlaku persis sama di sana.
