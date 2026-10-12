# 📊 Day 35: Kadane's Algorithm & Maximum Subarray

> **Prasyarat:** Prefix Sum (Day 29), Sliding Window (Day 33–34)
> **Estimasi belajar:** 3 jam (teori + 6 latihan)
> **Kata kunci soal:** *"subarray dengan jumlah maksimum"*, *"keuntungan terbesar"*, *"segmen terbaik"*

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan Day 35, kamu akan mampu:

- [ ] Menjelaskan kenapa sliding window **gagal** untuk masalah ini
- [ ] Menurunkan Kadane sebagai **DP satu dimensi**, bukan menghafal tiga barisnya
- [ ] Menangani kasus **semua elemen negatif** dengan benar
- [ ] Mengembalikan **indeks** subarray terbaik, bukan hanya nilainya
- [ ] Menyelesaikan varian **melingkar** dengan trik total − minimum
- [ ] Menyelesaikan **maximum product subarray** dan tahu kenapa Kadane biasa gagal di sana
- [ ] Memakai Kadane sebagai inti solusi **submatriks maksimum O(n³)**

---

## 🔍 1. Konsep & Intuisi

### Kenapa sliding window gagal di sini

Kemarin kita belajar bahwa sliding window butuh **monotonisitas**. Di sini:

```
a = [4, -10, 3]

window [4]        jumlah 4    layak?
window [4, -10]   jumlah -6   memburuk
window [4,-10,3]  jumlah -3   membaik lagi
```

Memperlebar window bisa membuat jumlahnya **turun lalu naik lagi**. Tidak monoton.
Dua pointer tidak punya aturan yang benar untuk memutuskan kapan menyusut.

### Sudut pandang prefix sum

```
jumlah a[l..r] = pre[r+1] − pre[l]
```

Untuk memaksimalkannya dengan `r` tetap, kita ingin `pre[l]` **sekecil mungkin**
di antara semua `l ≤ r`. Jadi:

```cpp
long long best = LLONG_MIN, minPre = 0, cur = 0;
for (int i = 0; i < n; i++) {
    cur += a[i];                     // cur = pre[i+1]
    best = max(best, cur - minPre);  // pakai prefix terkecil sejauh ini
    minPre = min(minPre, cur);       // baru perbarui
}
```

Ini **sudah** solusi lengkap O(n), dan bagi banyak orang lebih mudah dipahami
daripada Kadane. Urutan dua baris terakhir penting: `best` dihitung **sebelum**
`minPre` diperbarui, supaya subarray tidak kosong.

### Sudut pandang Kadane: DP satu dimensi

Definisikan:

```
dp[i] = jumlah maksimum subarray yang BERAKHIR TEPAT di indeks i
```

Ada tepat dua pilihan:

```
1. Perpanjang subarray sebelumnya  ->  dp[i-1] + a[i]
2. Mulai baru dari sini            ->  a[i]

dp[i] = max(dp[i-1] + a[i], a[i])
      = a[i] + max(dp[i-1], 0)
```

Jawabannya `max(dp[i])` untuk semua `i`.

> **Intuisi satu kalimat:** kalau apa yang kamu bawa dari belakang bernilai **negatif**,
> buang saja — beban itu tidak akan pernah membantu.

```
a   :   -2    1   -3    4   -1    2    1   -5    4
dp  :   -2    1   -2    4    3    5    6    1    5
                            ↑              ↑
                     bawa 4 (positif)  maksimum = 6
```

Karena `dp[i]` hanya butuh `dp[i-1]`, arraynya bisa diganti satu variabel — dan
di situlah Kadane terlihat seperti "trik" padahal ia hanya DP dengan rolling variable.

---

## 🧮 2. Analisis Kompleksitas

| Varian | Waktu | Ruang |
| ------ | ----- | ----- |
| Kadane dasar | O(n) | O(1) |
| Kadane + indeks | O(n) | O(1) |
| Melingkar | O(n) | O(1) |
| Maximum product | O(n) | O(1) |
| Maksimum dengan ≤ 1 penghapusan | O(n) | O(1) |
| Submatriks maksimum (R × C) | O(R² · C) | O(C) |
| Naif semua subarray | O(n²) | O(1) |

**Submatriks maksimum** patut diperhatikan: untuk matriks 300×300, `O(R²C)` = 27 juta —
lolos. Untuk 1000×1000 sudah 10⁹ — tidak lolos. Batas inilah yang menentukan apakah
soal matriks bisa diserang dengan Kadane.

---

## 💻 3. Implementasi C++

### 3.1 Kadane dasar

```cpp
long long kadane(const vector<long long>& a) {
    long long best = LLONG_MIN, cur = 0;
    for (long long x : a) {
        cur = max(x, cur + x);      // mulai baru, atau lanjutkan
        best = max(best, cur);
    }
    return best;
}
```

⚠️ **Inisialisasi `best = LLONG_MIN`, bukan 0.** Kalau `best` dimulai dari 0 dan semua
elemen negatif, jawabannya akan salah menjadi 0 — padahal subarray tidak boleh kosong.
Ini bug nomor satu di Kadane.

```
a = [-5, -2, -9]
best awal 0  -> jawab 0    ✗ SALAH
best awal MIN -> jawab -2  ✓ BENAR
```

Kalau soal **memperbolehkan** subarray kosong, barulah `best = 0` yang benar.
Baca soalnya baik-baik; keduanya sama-sama lazim.

### 3.2 Kadane dengan indeks

```cpp
// mengembalikan {jumlah, l, r} dengan l dan r inklusif
tuple<long long,int,int> kadaneIdx(const vector<long long>& a) {
    long long best = LLONG_MIN, cur = 0;
    int bl = 0, br = 0, curL = 0;

    for (int i = 0; i < (int)a.size(); i++) {
        if (cur + a[i] < a[i]) {    // lebih baik mulai baru
            cur = a[i];
            curL = i;
        } else {
            cur += a[i];
        }
        if (cur > best) { best = cur; bl = curL; br = i; }
    }
    return {best, bl, br};
}
```

Kuncinya: `curL` diperbarui **hanya** saat kita memutuskan mulai baru.

### 3.3 Varian melingkar

Subarray melingkar boleh membungkus dari ujung kanan ke ujung kiri.
Ada tepat dua kemungkinan bentuk jawaban:

```
1. Tidak membungkus  ->  Kadane biasa
2. Membungkus        ->  total − (subarray MINIMUM di tengah)
```

```
a = [5, -3, 5]
tidak membungkus: 5        (atau 7 = seluruh array)
membungkus      : total 7 − min subarray (-3) = 10   <- ini jawabannya
```

```cpp
long long kadaneMelingkar(const vector<long long>& a) {
    long long total = 0, maxSum = LLONG_MIN, minSum = LLONG_MAX;
    long long curMax = 0, curMin = 0;

    for (long long x : a) {
        total += x;
        curMax = max(x, curMax + x);   maxSum = max(maxSum, curMax);
        curMin = min(x, curMin + x);   minSum = min(minSum, curMin);
    }

    // Kalau SEMUA elemen negatif, "total - minSum" = subarray kosong.
    // Kasus itu harus ditolak.
    if (maxSum < 0) return maxSum;
    return max(maxSum, total - minSum);
}
```

⚠️ Penanganan `maxSum < 0` wajib. Tanpa itu, `a = [-3, -2, -5]` akan menghasilkan
`total − minSum = −10 − (−10) = 0`, yaitu subarray kosong.

### 3.4 Maximum product subarray

Kadane biasa **gagal** untuk perkalian, karena bilangan negatif bisa berubah menjadi
keuntungan begitu dikalikan negatif lain. Solusinya: bawa **dua** nilai.

```cpp
long long maxProduct(const vector<long long>& a) {
    long long best = a[0], curMax = a[0], curMin = a[0];

    for (int i = 1; i < (int)a.size(); i++) {
        long long x = a[i];
        if (x < 0) swap(curMax, curMin);   // negatif membalik peran
        curMax = max(x, curMax * x);
        curMin = min(x, curMin * x);
        best = max(best, curMax);
    }
    return best;
}
```

Minimum yang sangat negatif adalah **aset**, bukan beban — sekali bertemu bilangan
negatif, ia berubah menjadi maksimum. Inilah alasan kita melacak keduanya.

⚠️ Waspadai overflow: hasil kali bisa meledak jauh lebih cepat daripada penjumlahan.

### 3.5 Maksimum dengan paling banyak satu penghapusan

```cpp
long long maxSatuHapus(const vector<long long>& a) {
    long long tanpaHapus = a[0], denganHapus = LLONG_MIN, best = a[0];

    for (int i = 1; i < (int)a.size(); i++) {
        denganHapus = max(denganHapus + a[i], tanpaHapus);  // hapus a[i], atau bawa
        tanpaHapus  = max(tanpaHapus + a[i], a[i]);
        best = max(best, max(tanpaHapus, denganHapus));
    }
    return best;
}
```

Ini Kadane dengan **dua state**: sudah pernah menghapus, atau belum.
Pola "Kadane + satu dimensi state" muncul di banyak soal.

### 3.6 Submatriks dengan jumlah maksimum

```cpp
long long maxSubmatriks(const vector<vector<long long>>& g) {
    int R = g.size(), C = g[0].size();
    long long best = LLONG_MIN;

    for (int atas = 0; atas < R; atas++) {
        vector<long long> kolom(C, 0);
        for (int bawah = atas; bawah < R; bawah++) {
            for (int c = 0; c < C; c++) kolom[c] += g[bawah][c];  // tambah satu baris

            // sekarang masalahnya jadi 1D: Kadane pada 'kolom'
            long long cur = 0, lokal = LLONG_MIN;
            for (int c = 0; c < C; c++) {
                cur = max(kolom[c], cur + kolom[c]);
                lokal = max(lokal, cur);
            }
            best = max(best, lokal);
        }
    }
    return best;
}
```

Idenya: **kunci** pasangan baris atas–bawah, jumlahkan tiap kolom di antaranya,
lalu masalah 2D runtuh menjadi masalah 1D. Pola "kunci satu dimensi, Kadane di dimensi
lain" adalah salah satu teknik paling berguna di seluruh CP.

---

## 🔄 4. Trace & Simulasi

### 4.1 Kadane pada `a = [-2, 1, -3, 4, -1, 2, 1, -5, 4]`

| i | a[i] | cur + a[i] | a[i] | cur (max) | keputusan | best |
| - | ---- | ---------- | ---- | --------- | --------- | ---- |
| 0 | −2 | — | −2 | **−2** | mulai | **−2** |
| 1 | 1 | −1 | 1 | **1** | mulai baru | **1** |
| 2 | −3 | −2 | −3 | **−2** | lanjut | 1 |
| 3 | 4 | 2 | 4 | **4** | mulai baru | **4** |
| 4 | −1 | 3 | −1 | **3** | lanjut | 4 |
| 5 | 2 | 5 | 2 | **5** | lanjut | **5** |
| 6 | 1 | 6 | 1 | **6** | lanjut | **6** |
| 7 | −5 | 1 | −5 | **1** | lanjut | 6 |
| 8 | 4 | 5 | 4 | **5** | lanjut | 6 |

```
best = 6   ->  subarray [4, -1, 2, 1]  (indeks 3..6)
```

Perhatikan `i = 3`: `cur` sebelumnya `−2`, dan membawa beban negatif itu membuat
hasilnya `2`, lebih buruk daripada memulai baru dengan `4`. Di situlah keputusan
"buang beban" terjadi.

### 4.2 Semua negatif — `a = [-5, -2, -9]`

| i | a[i] | cur | best |
| - | ---- | --- | ---- |
| 0 | −5 | −5 | **−5** |
| 1 | −2 | max(−2, −7) = **−2** | **−2** |
| 2 | −9 | max(−9, −11) = **−9** | −2 |

```
best = -2   ->  subarray [-2]
```

Kalau `best` diinisialisasi 0, jawabannya akan menjadi 0 — **salah**, karena tidak ada
subarray tidak kosong yang jumlahnya 0.

### 4.3 Melingkar pada `a = [5, -3, 5]`

```
total  = 7
maxSum (Kadane biasa) = 7        -> [5,-3,5]
minSum (Kadane minimum) = -3     -> [-3]

kandidat membungkus = total - minSum = 7 - (-3) = 10   -> [5] + [5] membungkus
jawab = max(7, 10) = 10   ✓
```

Cek kasus semua negatif, `a = [-3, -2, -5]`:

```
maxSum = -2
total = -10, minSum = -10 -> total - minSum = 0    <- subarray KOSONG, tidak sah
karena maxSum < 0, kembalikan maxSum = -2   ✓
```

### 4.4 Maximum product pada `a = [2, -3, -2, 4]`

| i | x | swap? | curMax | curMin | best |
| - | - | ----- | ------ | ------ | ---- |
| 0 | 2 | — | 2 | 2 | **2** |
| 1 | −3 | ya (tukar 2↔2) | max(−3, −6) = **−3** | min(−3, −6) = **−6** | 2 |
| 2 | −2 | ya (curMax=−6, curMin=−3) | max(−2, 12) = **12** | min(−2, 6) = **−2** | **12** |
| 3 | 4 | tidak | max(4, 48) = **48** | min(4, −8) = **−8** | **48** |

```
best = 48   ->  [2, -3, -2, 4]  seluruhnya
```

Perhatikan langkah `i = 2`: `curMin = −6` yang tadinya terlihat buruk berubah menjadi
`12` begitu dikalikan `−2`. Itulah kenapa minimum harus dilacak.

---

## 📝 5. Variasi & Pattern

| Kalimat di soal | Yang dipakai |
| --------------- | ------------ |
| "subarray dengan jumlah maksimum" | Kadane |
| "subarray tidak boleh kosong" | `best = LLONG_MIN` |
| "subarray boleh kosong" | `best = 0` |
| "array melingkar" | `max(kadane, total − minKadane)`, cek semua-negatif |
| "hasil kali maksimum" | lacak curMax **dan** curMin |
| "boleh hapus paling banyak satu elemen" | Kadane dua state |
| "submatriks dengan jumlah maksimum" | kunci dua baris + Kadane, O(R²C) |
| "keuntungan maksimum jual-beli saham sekali" | Kadane pada array selisih |
| "subarray maksimum dengan panjang ≤ k" | monotonic deque atas prefix (Day 37) |
| "subarray maksimum dengan panjang tepat k" | prefix sum / window tetap (Day 33) |

### Pattern: saham = Kadane pada selisih

*Beli sekali, jual sekali, maksimalkan keuntungan.*

```cpp
// harga[i] -> selisih d[i] = harga[i] - harga[i-1]
// keuntungan maksimum = subarray maksimum dari d
```

Dua masalah yang terlihat sama sekali berbeda ternyata identik setelah satu
transformasi. Kebiasaan bertanya *"apa yang terjadi kalau saya lihat selisihnya?"*
sangat berharga.

### Pattern: Kadane + state tambahan

Begitu soal menambahkan aturan ("boleh hapus satu", "boleh gandakan satu segmen",
"paling banyak dua subarray"), polanya hampir selalu:

```
dp[i][j] = jawaban terbaik yang berakhir di i, dengan j = berapa kali aturan dipakai
```

dan setiap dimensi tambahan hanya menambah beberapa variabel rolling.

---

## ⚠️ 6. Common Mistakes & Edge Cases

1. **`best = 0` padahal subarray tidak boleh kosong.** Jawaban salah saat semua negatif.
   Ini penyebab WA paling sering.

2. **Lupa kasus semua-negatif pada varian melingkar.** `total − minSum` menjadi 0,
   yaitu subarray kosong.

3. **Memakai Kadane biasa untuk perkalian.** Harus melacak minimum juga.

4. **Overflow.** `10^5` elemen bernilai `10^9` → `10^14`. Untuk perkalian, jauh lebih
   cepat meledak — beberapa soal sengaja membatasi hasil agar muat di `long long`.

5. **`curL` diperbarui di tempat yang salah** saat melacak indeks. Ia hanya berubah
   ketika kita memutuskan **mulai baru**.

6. **Mengira Kadane bisa dibatasi panjang.** "Subarray maksimum dengan panjang ≤ k"
   bukan Kadane — itu prefix sum + monotonic deque (Day 37).

7. **Submatriks O(R²C) dianggap selalu cukup.** Untuk 1000×1000 itu 10⁹. Periksa batas.

### Edge cases wajib diuji

```
n = 1                        -> jawabannya elemen itu sendiri
semua elemen negatif         -> jawabannya elemen terbesar (paling mendekati nol)
semua elemen nol             -> jawabannya 0
satu elemen positif besar di tengah lautan negatif
[5, -3, 5] melingkar         -> jawaban 10, bukan 7
[-3, -2, -5] melingkar       -> jawaban -2, bukan 0
[0, 0, -1] produk            -> jawabannya 0
```

---

## 🏆 7. Tips Contest

**Red flag → aksi:**

- Kata *"jumlah maksimum"* + *"berurutan/segmen/subarray"* → Kadane, langsung tulis.
  Lima baris.
- Ada kata *"melingkar"* → tulis Kadane maksimum **dan** minimum sekaligus, plus
  cek semua-negatif. Tiga hal, jangan lupa yang ketiga.
- Ada kata *"hasil kali"* → dua variabel, bukan satu.
- Ada matriks kecil (≤ 300) + *"submatriks maksimum"* → kunci baris + Kadane.

**Pertanyaan yang harus kamu jawab sebelum menulis:** *"Boleh kosong atau tidak?"*
Jawabannya menentukan inisialisasi `best`, dan itu satu-satunya hal yang membedakan
AC dari WA di separuh soal Kadane.

**Kalau ragu antara window dan Kadane:** lihat apakah ada bilangan negatif.
Ada negatif → Kadane atau prefix. Semua non-negatif dan ada batas → window.

**Trik debugging:** tulis versi naif O(n²) yang mencoba semua `(l, r)`. Untuk `n = 200`
itu instan, dan membandingkan keduanya pada 1000 array acak akan menangkap hampir
semua bug Kadane dalam hitungan detik.

---

## 📌 8. Ringkasan & Cheatsheet

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  KADANE
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  dp[i] = jumlah maksimum subarray yang BERAKHIR di i
        = max(dp[i-1] + a[i], a[i])
        = a[i] + max(dp[i-1], 0)          "buang beban negatif"

  cur = max(x, cur + x);
  best = max(best, cur);

  best = LLONG_MIN  -> subarray TIDAK boleh kosong   <- default
  best = 0          -> subarray BOLEH kosong

  SETARA (prefix): best = max(pre[r+1] - min pre[l] untuk l <= r)

  MELINGKAR : max(kadane, total - kadaneMin)
              KECUALI kalau semua negatif -> kembalikan kadane

  PRODUK    : lacak curMax DAN curMin; kalau x < 0 tukar keduanya

  <= 1 HAPUS: dua state (sudah hapus / belum)

  SUBMATRIKS: kunci baris atas & bawah, jumlahkan kolom, Kadane 1D
              O(R^2 * C) -- 300x300 lolos, 1000x1000 tidak

  SAHAM     : Kadane pada array SELISIH harga
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### Soal latihan online

| Soal | Platform | Topik |
| ---- | -------- | ----- |
| [CSES 1643 — Maximum Subarray Sum](https://cses.fi/problemset/task/1643) | CSES | Kadane dasar |
| [CSES 1644 — Maximum Subarray Sum II](https://cses.fi/problemset/task/1644) | CSES | panjang dibatasi (bukan Kadane!) |
| [LeetCode 53 — Maximum Subarray](https://leetcode.com/problems/maximum-subarray/) | LeetCode | Kadane dasar |
| [LeetCode 152 — Maximum Product Subarray](https://leetcode.com/problems/maximum-product-subarray/) | LeetCode | dua variabel |
| [LeetCode 918 — Maximum Sum Circular Subarray](https://leetcode.com/problems/maximum-sum-circular-subarray/) | LeetCode | melingkar |
| [LeetCode 1186 — Maximum Subarray Sum with One Deletion](https://leetcode.com/problems/maximum-subarray-sum-with-one-deletion/) | LeetCode | dua state |
| [SPOJ MAXSUMSQ / KGSS](https://www.spoj.com/) | SPOJ | variasi |
| [UVa 108 — Maximum Sum](https://onlinejudge.org/) | UVa | submatriks O(R²C) |
| [CF 1155D — Beautiful Array](https://codeforces.com/problemset/problem/1155/D) | Codeforces | Kadane + state |

---

**Selanjutnya:** Day 36 (sudah kamu selesaikan) — Monotonic Stack. Perhatikan benang
merahnya: Day 34 memakai dua pointer monoton, hari ini memakai satu state rolling,
dan Day 36–37 memakai struktur yang menjaga urutan monoton. Ketiganya adalah cara
berbeda untuk **membuang informasi yang sudah pasti tidak berguna** — dan itulah inti
dari hampir semua teknik O(n) pada array.
