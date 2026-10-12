# 📊 Day 54: Meet in the Middle

> **Prasyarat:** Enumerasi Subset/Bitmask (Day 60 — atau bitwise Day 11), Sorting (Day 20), Bound Manual (Day 49)
> **Estimasi belajar:** 3–4 jam (teori + 6 latihan)
> **Kata kunci soal:** *"n ≤ 40"*, *"pilih subhimpunan"*, *"2^n terlalu besar"*

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan Day 54, kamu akan mampu:

- [ ] Mengenali tanda `n ≤ 40` sebagai isyarat meet in the middle
- [ ] Menjelaskan kenapa `2^40` mustahil tetapi `2^20 + 2^20` seketika
- [ ] Membangkitkan **seluruh subset** satu paruh dengan bitmask
- [ ] Menggabungkan dua paruh dengan **sorting + binary search**
- [ ] Menerapkan pola **"cari pasangan berjumlah tepat X"**
- [ ] Menerapkan pola **"maksimalkan tanpa melebihi batas"** dengan prefix maksimum
- [ ] Mengenali kapan pembagian **tidak** harus tepat separuh

---

## 🔍 1. Konsep & Intuisi

### Masalahnya

Banyak soal meminta kita memeriksa **seluruh subhimpunan** dari `n` benda:

```
n = 20  ->  2^20 ~ 10^6         seketika
n = 30  ->  2^30 ~ 10^9         terlalu lambat
n = 40  ->  2^40 ~ 10^12        MUSTAHIL
n = 50  ->  2^50 ~ 10^15        jauh lebih mustahil
```

`n ≤ 40` adalah batas yang **sangat khas**: terlalu besar untuk brute force,
terlalu kecil untuk DP polinomial, dan biasanya tidak punya struktur greedy.
Ketika kamu melihatnya, meet in the middle hampir selalu jawabannya.

### Ide: bagi dua, gabungkan

```
40 benda
   |
   +-- paruh KIRI  (20 benda)  ->  2^20 = 1.048.576 subset
   +-- paruh KANAN (20 benda)  ->  2^20 = 1.048.576 subset

Setiap subset dari 40 benda adalah GABUNGAN dari
satu subset kiri dan satu subset kanan -- tepat satu cara.
```

```
2^40  =  10^12   membangkitkan seluruhnya: mustahil
2^20 + 2^20 = 2 × 10^6   membangkitkan dua paruh: seketika
```

Kita menukar **perkalian** menjadi **penjumlahan**. Itulah seluruh idenya.

⚠️ Tetapi ada harga: kita tidak bisa lagi memeriksa setiap gabungan satu per satu
(itu tetap `2^20 × 2^20 = 2^40`). Kita harus **menggabungkan dengan cerdas** —
biasanya dengan mengurutkan salah satu paruh lalu mencari dengan binary search.

### Analogi: mencari dua orang yang tinggi totalnya 300 cm

Ada 40 orang. Mencari **semua pasangan** yang totalnya 300 cm dengan memeriksa
setiap pasangan butuh `40 × 40` pemeriksaan — masih kecil, tetapi bayangkan kalau
yang dicari adalah **kelompok** orang, bukan pasangan.

Bagi menjadi dua ruangan berisi 20 orang. Catat total tinggi setiap kemungkinan
kelompok di ruangan A (`2^20` catatan), lalu **urutkan** catatan itu.

Sekarang untuk setiap kelompok di ruangan B dengan total `s`, kamu cukup mencari
`300 − s` di dalam catatan yang sudah terurut — satu binary search, bukan
`2^20` pemeriksaan.

### Kompleksitasnya

```
membangkitkan dua paruh : O(2^(n/2))
mengurutkan satu paruh  : O(2^(n/2) · n/2)
mencari untuk tiap subset paruh lain : O(2^(n/2) · log(2^(n/2))) = O(2^(n/2) · n/2)

total: O(2^(n/2) · n)
```

```
n = 40:  2^20 × 40 ~ 4 × 10^7    aman
n = 50:  2^25 × 50 ~ 1.7 × 10^9  terlalu lambat
```

Jadi meet in the middle mengangkat batas dari `n ≈ 25` menjadi `n ≈ 40`.
Itu bukan perbaikan tak terbatas — hanya **menggandakan** eksponen yang bisa
kamu tangani.

---

## 🧮 2. Analisis Kompleksitas

| Pola | Waktu | Ruang |
| ---- | ----- | ----- |
| Hitung subset berjumlah tepat X | O(2^(n/2) · n) | O(2^(n/2)) |
| Maksimalkan jumlah ≤ batas | O(2^(n/2) · n) | O(2^(n/2)) |
| Knapsack `n ≤ 40`, bobot besar | O(2^(n/2) · n) | O(2^(n/2)) |
| 4-SUM (`n` sampai 4000) | O(n² log n) | O(n²) |
| Jalur terpendek `2^n` state | O(2^(n/2) · ...) | besar |

**Perbandingan dengan alternatif:**

| Situasi | Alat |
| ------- | ---- |
| `n ≤ 20` | brute force `2^n` langsung |
| `n ≤ 40`, bobot besar | **meet in the middle** |
| `n` besar, bobot **kecil** | DP knapsack `O(n·W)` (Day 145) |
| `n` besar, ada struktur | greedy atau DP lain |

⚠️ **Perhatikan syarat "bobot besar".** Kalau bobotnya kecil (`W ≤ 10^5`),
DP knapsack `O(n·W)` biasanya lebih baik dan jauh lebih sederhana. Meet in the
middle unggul justru ketika bobotnya sampai `10^9` sehingga DP mustahil.

**Batas memori:** `2^20` `long long` = 8 MB per paruh. Untuk `n = 42`,
`2^21 × 8` = 16 MB — mulai terasa. Perhitungan memori sama pentingnya dengan waktu.

---

## 💻 3. Implementasi C++

### 3.1 Membangkitkan seluruh subset satu paruh

```cpp
// Mengembalikan jumlah dari setiap subset a[0..k-1]. Ukurannya 2^k.
vector<long long> semuaSubset(const vector<long long>& a) {
    int k = a.size();
    vector<long long> hasil(1 << k, 0);
    for (int mask = 1; mask < (1 << k); mask++) {
        int b = __builtin_ctz(mask);          // bit terendah yang menyala
        hasil[mask] = hasil[mask ^ (1 << b)] + a[b];
    }
    return hasil;
}
```

⚠️ Perhatikan trik `hasil[mask ^ (1<<b)] + a[b]`: kita membangun jawaban dari
subset yang **satu bit lebih kecil**, yang sudah dihitung. Ini O(1) per subset,
bukan O(k) — total `O(2^k)` alih-alih `O(2^k · k)`.

Versi naif yang juga benar tetapi lebih lambat:

```cpp
for (int mask = 0; mask < (1 << k); mask++)
    for (int b = 0; b < k; b++)
        if (mask >> b & 1) hasil[mask] += a[b];
```

### 3.2 Pola 1 — hitung subset berjumlah tepat X

```cpp
long long hitungSubsetJumlah(const vector<long long>& a, long long X) {
    int n = a.size(), k = n / 2;
    vector<long long> kiri(a.begin(), a.begin() + k);
    vector<long long> kanan(a.begin() + k, a.end());

    vector<long long> sk = semuaSubset(kiri);
    vector<long long> sn = semuaSubset(kanan);

    sort(sk.begin(), sk.end());

    long long total = 0;
    for (long long s : sn) {
        long long butuh = X - s;
        // banyaknya kemunculan `butuh` di dalam sk
        total += upper_bound(sk.begin(), sk.end(), butuh)
               - lower_bound(sk.begin(), sk.end(), butuh);
    }
    return total;
}
```

⚠️ Setiap subset penuh terhitung **tepat sekali**, karena pembagian kiri/kanan
sudah tetap. Tidak ada perhitungan ganda yang perlu dikoreksi.

⚠️ Subset **kosong** ikut terhitung (mask = 0 memberi jumlah 0). Kalau soal
melarang subset kosong dan `X = 0`, kurangi satu di akhir.

### 3.3 Pola 2 — maksimalkan jumlah tanpa melebihi batas

Ini bentuk yang paling sering muncul (knapsack `n ≤ 40`).

```cpp
long long maksTanpaMelebihi(const vector<long long>& a, long long batas) {
    int n = a.size(), k = n / 2;
    vector<long long> sk = semuaSubset(vector<long long>(a.begin(), a.begin() + k));
    vector<long long> sn = semuaSubset(vector<long long>(a.begin() + k, a.end()));

    sort(sk.begin(), sk.end());

    // PREFIX MAKSIMUM: best[i] = nilai terbesar di antara sk[0..i]
    // Setelah ini, sk menjadi TIDAK MENURUN, sehingga binary search sah
    // dan hasilnya langsung yang terbaik.
    for (size_t i = 1; i < sk.size(); i++)
        sk[i] = max(sk[i], sk[i - 1]);

    long long best = 0;
    for (long long s : sn) {
        if (s > batas) continue;
        long long sisa = batas - s;
        // subset kiri terbesar yang <= sisa
        int idx = int(upper_bound(sk.begin(), sk.end(), sisa) - sk.begin()) - 1;
        if (idx >= 0) best = max(best, s + sk[idx]);
    }
    return best;
}
```

⚠️ **Langkah prefix maksimum sangat penting dan sering dilupakan.**
Setelah diurutkan, `sk` terurut menaik, tetapi kita ingin *"nilai terbesar yang
tidak melebihi sisa"* — dan itu tidak sama dengan *"nilai pada posisi terakhir
yang ≤ sisa"* kalau ada nilai lebih besar di posisi sebelumnya. Untuk **jumlah**
sederhana keduanya kebetulan sama, tetapi pola prefix maksimum menjadi **wajib**
begitu kamu punya dua besaran (bobot dan nilai) — lihat 3.4.

### 3.4 Pola 3 — knapsack 0/1 dengan bobot dan nilai terpisah

```cpp
struct Barang { long long bobot, nilai; };

long long knapsackMitm(const vector<Barang>& b, long long kapasitas) {
    int n = b.size(), k = n / 2;

    // bangkitkan pasangan {bobot, nilai} untuk setiap subset
    auto bangkit = [&](int mulai, int akhir) {
        int m = akhir - mulai;
        vector<pair<long long, long long>> v(1 << m);
        for (int mask = 0; mask < (1 << m); mask++) {
            long long w = 0, p = 0;
            for (int i = 0; i < m; i++)
                if (mask >> i & 1) { w += b[mulai + i].bobot; p += b[mulai + i].nilai; }
            v[mask] = {w, p};
        }
        return v;
    };

    auto A = bangkit(0, k), B = bangkit(k, n);

    sort(A.begin(), A.end());
    // prefix maksimum atas NILAI -- di sinilah langkah ini WAJIB
    for (size_t i = 1; i < A.size(); i++)
        A[i].second = max(A[i].second, A[i - 1].second);

    long long best = 0;
    for (auto& [w, p] : B) {
        if (w > kapasitas) continue;
        long long sisa = kapasitas - w;
        // cari bobot terbesar yang <= sisa
        int idx = int(upper_bound(A.begin(), A.end(),
                      make_pair(sisa, LLONG_MAX)) - A.begin()) - 1;
        if (idx >= 0) best = max(best, p + A[idx].second);
    }
    return best;
}
```

⚠️ Di sini prefix maksimum **benar-benar wajib**: subset dengan bobot lebih kecil
bisa punya nilai lebih besar, sehingga "posisi terakhir yang muat" belum tentu
yang terbaik. Tanpa langkah ini, jawabannya salah pada banyak kasus.

⚠️ `make_pair(sisa, LLONG_MAX)` memastikan `upper_bound` melewati **semua**
pasangan dengan bobot tepat `sisa`, sehingga `idx` menunjuk ke yang terakhir.

### 3.5 Pembagian tidak harus tepat separuh

```cpp
int k = n / 2;
```

Ini pilihan yang **hampir selalu** optimal, karena `2^a + 2^b` dengan `a + b = n`
diminimumkan saat `a = b`. Tetapi kalau salah satu paruh butuh pemrosesan yang
lebih mahal, menggeser pembagiannya bisa membantu:

```cpp
int k = n / 2 + 1;    // paruh kiri sedikit lebih besar
```

Jarang diperlukan, tetapi berguna kalau kamu mendekati batas memori.

### 3.6 Varian tanpa bitmask: 4-SUM

Meet in the middle tidak selalu tentang subset. Pola *"pecah menjadi dua paruh,
lalu gabungkan dengan pencarian"* juga berlaku di sini:

```cpp
// Adakah a[i] + b[j] + c[k] + d[l] == 0?
// Naif O(n^4). Meet in the middle: O(n^2 log n).
unordered_map<long long, int> peta;
for (long long x : A) for (long long y : B) peta[x + y]++;

long long total = 0;
for (long long z : C) for (long long w : D) {
    auto it = peta.find(-(z + w));
    if (it != peta.end()) total += it->second;
}
```

Semangatnya identik: `n^4` menjadi `n^2 + n^2`.

---

## 🔄 4. Trace & Simulasi

### 4.1 Hitung subset berjumlah 6 pada `a = [1, 2, 3, 4]`

```
Bagi: kiri = [1, 2], kanan = [3, 4]
```

**Subset paruh kiri (2^2 = 4):**

| mask | isi | jumlah |
| ---- | --- | ------ |
| 00 | {} | 0 |
| 01 | {1} | 1 |
| 10 | {2} | 2 |
| 11 | {1,2} | 3 |

```
sk terurut = [0, 1, 2, 3]
```

**Subset paruh kanan (2^2 = 4):**

| mask | isi | jumlah |
| ---- | --- | ------ |
| 00 | {} | 0 |
| 01 | {3} | 3 |
| 10 | {4} | 4 |
| 11 | {3,4} | 7 |

**Menggabungkan (target X = 6):**

| s (kanan) | butuh = 6 − s | ada di sk? | tambahan |
| --------- | ------------- | ---------- | -------- |
| 0 | 6 | tidak | 0 |
| 3 | 3 | **ya (1×)** | 1 |
| 4 | 2 | **ya (1×)** | 1 |
| 7 | −1 | tidak | 0 |

```
total = 2
Verifikasi manual: {2, 4} dan {1, 2, 3}  ->  2 subset   ✓
```

Perhatikan bahwa kita memeriksa `4 + 4 = 16` kombinasi secara implisit, tetapi
hanya melakukan `4` binary search.

### 4.2 Maksimalkan tanpa melebihi 5 pada `a = [1, 2, 3, 4]`

```
sk = [0, 1, 2, 3]    (sudah terurut, prefix maksimum tidak mengubahnya)
sn = [0, 3, 4, 7]
```

| s (kanan) | sisa = 5 − s | terbesar di sk yang ≤ sisa | total |
| --------- | ------------ | -------------------------- | ----- |
| 0 | 5 | 3 | 3 |
| 3 | 2 | 2 | **5** |
| 4 | 1 | 1 | **5** |
| 7 | — | (7 > 5, lewati) | — |

```
best = 5
Verifikasi: {2, 3} = 5, atau {1, 4} = 5   ✓
```

### 4.3 Kenapa prefix maksimum wajib (dengan bobot dan nilai)

```
Barang paruh kiri: {bobot 1, nilai 10}, {bobot 3, nilai 2}

Subsetnya (bobot, nilai):
   (0, 0), (1, 10), (3, 2), (4, 12)

Terurut berdasarkan bobot: (0,0), (1,10), (3,2), (4,12)

Misalkan sisa kapasitas = 3.
   TANPA prefix maksimum: upper_bound menunjuk ke posisi setelah (3,2),
       mundur satu -> (3, 2), nilainya 2.
       Tetapi (1, 10) juga muat dan nilainya 10!   JAWABAN SALAH.

   DENGAN prefix maksimum, nilainya menjadi:
       (0,0), (1,10), (3,10), (4,12)
       upper_bound mundur satu -> (3, 10), nilainya 10.   BENAR  ✓
```

Ini bug paling umum di topik ini, dan ia **hanya muncul** ketika bobot dan nilai
terpisah. Pada soal yang hanya menjumlahkan satu besaran, keduanya kebetulan sama
sehingga bugnya tidak terlihat sampai kamu mengerjakan soal knapsack.

### 4.4 Perbandingan jumlah operasi

```
n = 40, brute force  : 2^40 = 1.1 × 10^12    MUSTAHIL
n = 40, meet middle  : 2 × 2^20 = 2 × 10^6 untuk membangkitkan
                       + 2^20 × 20 ~ 2 × 10^7 untuk sort dan cari
                       total ~ 4 × 10^7      AMAN

Peningkatannya sekitar 30.000 kali.
```

---

## 📝 5. Variasi & Pattern

| Kalimat di soal | Yang dipakai |
| --------------- | ------------ |
| `n ≤ 40` + "pilih subhimpunan" | meet in the middle |
| "berapa subset yang jumlahnya tepat X" | pola 1, hitung kemunculan |
| "maksimalkan jumlah tanpa melebihi W" | pola 2, prefix maksimum |
| knapsack dengan `n ≤ 40`, bobot `10^9` | pola 3, pasangan (bobot, nilai) |
| "adakah 4 bilangan berjumlah 0" | 4-SUM, `O(n² log n)` |
| `n` besar tetapi bobot **kecil** | ❌ pakai DP knapsack (Day 145) |
| "bagi menjadi dua kelompok seimbang" | meet in the middle atas selisih |

### Pattern: membagi menjadi dua kelompok seimbang

*Bagi `n ≤ 40` benda menjadi dua kelompok sehingga selisih totalnya minimum.*

```
Setiap benda mendapat tanda +1 atau -1. Kita ingin |jumlah bertanda| minimum.
Bangkitkan seluruh jumlah bertanda paruh kiri (3^k? Tidak -- 2^k, karena setiap
benda pasti masuk salah satu kelompok).
Untuk setiap jumlah kanan s, cari jumlah kiri yang paling dekat dengan -s.
```

Perhatikan bahwa "paling dekat" berarti kamu memeriksa **dua** kandidat di sekitar
posisi `lower_bound` — pola yang sama dengan Day 49.

### Pattern: meet in the middle pada jalur

Untuk soal *"berapa jalur sepanjang `L` dari A ke B"* dengan `L` genap, kamu bisa
membangkitkan seluruh jalur sepanjang `L/2` dari A, dan seluruh jalur sepanjang
`L/2` yang **berakhir** di B, lalu mencocokkan titik tengahnya. Semangatnya sama.

### Kapan JANGAN memakai meet in the middle

```
1. Bobot kecil          -> DP knapsack O(n W) lebih sederhana dan cepat
2. n <= 20              -> brute force langsung, tidak perlu repot
3. n > 45               -> 2^22 x 45 mulai terlalu berat; cari pendekatan lain
4. Ada struktur greedy  -> hampir selalu lebih baik
```

---

## ⚠️ 6. Common Mistakes & Edge Cases

1. **Lupa prefix maksimum** pada pola bobot–nilai. Bug paling umum, dan hanya
   muncul saat dua besaran terpisah.

2. **Overflow.** `n = 40` dengan nilai `10^9` memberi jumlah `4·10^10` — melebihi
   `int`. Pakai `long long` untuk seluruh jumlah.

3. **Subset kosong terhitung.** `mask = 0` memberi jumlah 0. Kalau soal melarang
   subset kosong, koreksi di akhir.

4. **Memori.** `2^20` `pair<ll,ll>` = 16 MB. Untuk `n = 44`, `2^22 × 16` = 64 MB —
   hitung sebelum menulis.

5. **`unordered_map` di-hack.** Untuk pola 4-SUM di Codeforces, pakai `map`
   atau tambahkan custom hash.

6. **Membangkitkan subset dengan loop bersarang `O(2^k · k)`.** Untuk `k = 20`
   itu `2·10^7` — masih lolos, tetapi trik `mask ^ (1<<b)` membuatnya `10^6`.

7. **Membagi tidak seimbang tanpa alasan.** `2^15 + 2^25` jauh lebih buruk
   daripada `2^20 + 2^20`.

8. **Memakai MITM padahal DP lebih baik.** Periksa batas bobot dulu.

### Edge cases wajib diuji

```
n = 1                    -> satu paruh kosong; pastikan tidak crash
n ganjil                 -> pembagian n/2 dan n - n/2 berbeda ukuran
seluruh nilai nol        -> banyak subset berjumlah sama
X = 0                    -> subset kosong menjadi jawaban valid
batas lebih kecil dari elemen terkecil -> jawabannya 0 (subset kosong)
seluruh elemen melebihi batas -> jawabannya 0
```

---

## 🏆 7. Tips Contest

**Tanda pengenal:** `n ≤ 40` (kadang `n ≤ 35` atau `n ≤ 45`) yang muncul bersama
kata *"pilih subhimpunan"* atau *"pilih beberapa benda"*. Batas itu tidak muncul
secara kebetulan — penyusun soal memilihnya persis agar `2^(n/2)` lolos dan `2^n`
tidak.

**Sebelum menulis, periksa dua hal:**

1. **Apakah bobotnya kecil?** Kalau `W ≤ 10^6`, DP knapsack `O(n·W)` lebih
   sederhana dan lebih cepat.
2. **Berapa memorinya?** `2^(n/2)` elemen dikali ukuran tipe data.

**Kerangka yang harus kamu hafal:**

```
1. bagi menjadi dua paruh
2. bangkitkan seluruh subset masing-masing
3. urutkan salah satu paruh
4. (kalau ada dua besaran) prefix maksimum
5. untuk setiap subset paruh lain, binary search di paruh terurut
```

**Debugging:** kalau jawabanmu benar untuk `n` kecil tetapi salah untuk `n` besar,
biasanya masalah overflow. Kalau salah pada soal knapsack tetapi benar pada soal
"jumlah tepat X", hampir pasti prefix maksimum yang lupa.

**Uji dengan brute force.** Untuk `n ≤ 20`, brute force `2^n` langsung mudah
ditulis dan membandingkannya pada 1000 kasus acak akan menangkap hampir semua bug.

---

## 📌 8. Ringkasan & Cheatsheet

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  MEET IN THE MIDDLE
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  TANDA PENGENAL: n <= 40 + "pilih subhimpunan"
  2^40 = 1e12 MUSTAHIL  ->  2^20 + 2^20 = 2e6 SEKETIKA
  (perkalian menjadi PENJUMLAHAN)

  KERANGKA
    1. bagi jadi dua paruh (k = n/2)
    2. bangkitkan SELURUH subset masing-masing
    3. urutkan salah satu paruh
    4. PREFIX MAKSIMUM  (wajib kalau ada bobot DAN nilai)
    5. untuk tiap subset paruh lain, binary search

  BANGKITKAN SUBSET O(2^k), bukan O(2^k * k):
    int b = __builtin_ctz(mask);
    hasil[mask] = hasil[mask ^ (1 << b)] + a[b];

  POLA 1 -- jumlah TEPAT X:
    total += upper_bound(sk, X-s) - lower_bound(sk, X-s);

  POLA 2 -- maksimalkan TANPA MELEBIHI batas:
    prefix maksimum dulu, lalu
    idx = upper_bound(sk, batas - s) - sk.begin() - 1;

  POLA 3 -- knapsack (bobot, nilai):
    urutkan berdasarkan BOBOT, prefix maksimum atas NILAI
    upper_bound dengan make_pair(sisa, LLONG_MAX)

  KOMPLEKSITAS O(2^(n/2) * n)
    n = 40 -> 4e7 aman  |  n = 50 -> 1.7e9 terlalu lambat

  JANGAN PAKAI KALAU
    bobot kecil     -> DP knapsack O(n W) (Day 145)
    n <= 20         -> brute force langsung
    n > 45          -> cari pendekatan lain

  BUG NOMOR SATU: lupa PREFIX MAKSIMUM (hanya muncul pada bobot+nilai)
  long long untuk SELURUH jumlah (n=40 x 1e9 = 4e10)
  subset KOSONG ikut terhitung -- koreksi kalau soal melarangnya
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### Soal latihan online

| Soal | Platform | Topik |
| ---- | -------- | ----- |
| [CSES 1628 — Meet in the Middle](https://cses.fi/problemset/task/1628) | CSES | contoh paling murni |
| [CSES 2181 — Elevator Rides](https://cses.fi/problemset/task/2181) | CSES | (pembanding: DP bitmask) |
| [LeetCode 805 — Split Array With Same Average](https://leetcode.com/problems/split-array-with-same-average/) | LeetCode | MITM + rata-rata |
| [LeetCode 1755 — Closest Subsequence Sum](https://leetcode.com/problems/closest-subsequence-sum/) | LeetCode | MITM + terdekat |
| [CF 888E — Maximum Subsequence](https://codeforces.com/problemset/problem/888/E) | Codeforces | MITM + modulo |
| [CF 1006F — Xor-Paths](https://codeforces.com/problemset/problem/1006/F) | Codeforces | MITM pada grid |
| [SPOJ ABCDEF](https://www.spoj.com/problems/ABCDEF/) | SPOJ | varian 6 variabel |
| [UVa 1152 — 4 Values Sum 0](https://onlinejudge.org/) | UVa | 4-SUM |

---

**Selanjutnya:** Day 55–56 adalah **latihan terpadu** dan **review** untuk seluruh
blok sorting dan searching (Day 43–54). Setelah itu Day 57 memulai blok
**Complete Search & Greedy**, di mana enumerasi subset yang kamu pelajari hari ini
akan kembali muncul — kali ini sebagai fondasi backtracking dan DP bitmask.
