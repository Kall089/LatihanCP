# 📊 Day 49: Lower/Upper Bound Manual & Off-by-One Trap

> **Prasyarat:** Binary Search pada Array Terurut (Day 48), STL algoritma (Day 25)
> **Estimasi belajar:** 3 jam (teori + 6 latihan)
> **Kata kunci soal:** *"pertama yang ≥ x"*, *"terakhir yang ≤ x"*, *"berapa elemen di rentang"*

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan Day 49, kamu akan mampu:

- [ ] Menulis `lower_bound` dan `upper_bound` dari nol **tanpa ragu**
- [ ] Menyatakan **invariant** binary search dan memakainya untuk membuktikan kebenaran
- [ ] Memakai kerangka **"first true / last false"** yang menghapus seluruh kelas bug
- [ ] Menjelaskan kenapa `mid = lo + (hi − lo) / 2` bukan sekadar gaya
- [ ] Menjelaskan kenapa loop **selalu berhenti** dan kapan ia berputar selamanya
- [ ] Menurunkan **hitungan rentang** dari kedua bound
- [ ] Memakai `lower_bound` pada `set`/`map` dan tahu jebakannya

---

## 🔍 1. Konsep & Intuisi

### Dua pertanyaan, satu kerangka

```
lower_bound(x) = posisi PERTAMA yang nilainya >= x
upper_bound(x) = posisi PERTAMA yang nilainya >  x
```

```
a    :  1  3  3  3  5  7
index:  0  1  2  3  4  5

lower_bound(3) = 1      upper_bound(3) = 4
lower_bound(4) = 4      upper_bound(4) = 4
lower_bound(0) = 0      upper_bound(9) = 6 (di luar array)
```

Dua turunan langsung yang menyelesaikan sebagian besar soal:

```
banyaknya elemen == x     :  upper_bound(x) - lower_bound(x)
banyaknya elemen dalam [L, R] :  upper_bound(R) - lower_bound(L)
x ada di array?           :  lower_bound(x) != n && a[lb] == x
elemen terakhir yang <= x :  upper_bound(x) - 1   (cek dulu != 0)
elemen terakhir yang <  x :  lower_bound(x) - 1   (cek dulu != 0)
```

⚠️ Kedua bound bisa mengembalikan `n` (di luar array). **Selalu periksa** sebelum
mengaksesnya. Ini penyebab runtime error nomor satu di topik ini.

### Kerangka yang menghapus seluruh kelas bug

Alih-alih menghafal empat varian binary search, pakai **satu** kerangka:

```
Bayangkan predikat boolean p(i) yang MONOTON:
    false false false TRUE TRUE TRUE
                       ↑
                cari batasnya
```

```cpp
// Mencari INDEKS PERTAMA yang p(i) bernilai true.
// Kalau tidak ada, mengembalikan n.
int cariPertamaTrue(int n, function<bool(int)> p) {
    int lo = 0, hi = n;              // [lo, hi) -- hi = n, bukan n-1
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (p(mid)) hi = mid;        // mid mungkin jawabannya, JANGAN dibuang
        else        lo = mid + 1;    // mid pasti bukan, boleh dibuang
    }
    return lo;                       // lo == hi
}
```

Dengan kerangka ini:

```
lower_bound(x)  ->  p(i) = (a[i] >= x)
upper_bound(x)  ->  p(i) = (a[i] >  x)
```

Satu kerangka, satu perubahan tanda. Tidak ada `+1`/`−1` yang perlu dihafal.

> **Kenapa kerangka ini bekerja:** kita tidak pernah bertanya *"apakah `a[mid] == x`?"*
> Kita hanya bertanya *"apakah `mid` berada di sisi TRUE?"* Karena predikatnya monoton,
> jawabannya selalu memberi tahu kita sisi mana yang bisa dibuang — tanpa kasus khusus.

### Invariant: alasan kerangka ini benar

```
Invariant yang dijaga sepanjang loop:
    jawabannya SELALU berada di dalam [lo, hi]

  seluruh indeks < lo  ->  p bernilai FALSE
  seluruh indeks >= hi ->  p bernilai TRUE
```

```
p(mid) TRUE  -> mid ada di sisi true -> jawabannya <= mid -> hi = mid
p(mid) FALSE -> mid ada di sisi false -> jawabannya > mid -> lo = mid + 1
```

Saat `lo == hi`, rentangnya menyempit menjadi satu titik — dan invariant memaksa
titik itu menjadi jawabannya.

### Kenapa loop selalu berhenti

```
mid = lo + (hi - lo) / 2       dengan lo < hi

karena pembagian membulat ke BAWAH:  lo <= mid < hi

cabang TRUE  : hi = mid      -> hi TURUN (karena mid < hi)
cabang FALSE : lo = mid + 1  -> lo NAIK  (karena mid >= lo)
```

Kedua cabang **selalu** memperkecil rentang. Loop tidak mungkin berputar selamanya.

⚠️ **Ini rusak kalau kamu memakai `[lo, hi]` inklusif dengan `hi = mid`.**
Dengan `lo = 0, hi = 1`, `mid` menjadi 0, dan cabang `hi = mid` mengembalikan
`hi = 0`... lalu `lo == hi` sehingga berhenti. Tetapi kalau kondisinya `lo <= hi`,
loopnya tidak pernah berhenti. Pilih **satu** konvensi dan jangan mencampur.

---

## 🧮 2. Analisis Kompleksitas

| Operasi | Waktu | Catatan |
| ------- | ----- | ------- |
| `lower_bound` / `upper_bound` pada array | O(log n) | akses acak |
| Pada `vector` | O(log n) | ✅ |
| Pada `set` / `map` (fungsi anggota) | O(log n) | ✅ pakai `s.lower_bound(x)` |
| Pada `set` / `map` (`std::lower_bound`) | **O(n)** | ❌ iterator bukan akses acak |
| Pada `list` | O(n) | ❌ sama alasannya |
| Membangun array terurut | O(n log n) | dibayar sekali |

⚠️ **Jebakan `set`:** `std::lower_bound(s.begin(), s.end(), x)` **bisa dikompilasi**
tetapi berjalan **O(n)**, karena iterator `set` bukan random-access sehingga ia harus
melangkah satu per satu. Pakai `s.lower_bound(x)` (fungsi anggota) yang O(log n).
Bug kinerja ini tidak menghasilkan jawaban salah — hanya TLE, sehingga sulit dilacak.

**Jumlah iterasi:** `ceil(log2(n))`. Untuk `n = 10^6` itu 20 iterasi; untuk `n = 10^9`
hanya 30. Binary search hampir tidak pernah menjadi bagian yang lambat.

---

## 💻 3. Implementasi C++

### 3.1 Lower bound manual

```cpp
// Indeks pertama dengan a[i] >= x. Mengembalikan n kalau tidak ada.
int lowerBound(const vector<int>& a, int x) {
    int lo = 0, hi = a.size();          // [lo, hi), hi = n
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] >= x) hi = mid;      // mungkin jawabannya
        else             lo = mid + 1;  // pasti bukan
    }
    return lo;
}
```

### 3.2 Upper bound manual

```cpp
// Indeks pertama dengan a[i] > x. Mengembalikan n kalau tidak ada.
int upperBound(const vector<int>& a, int x) {
    int lo = 0, hi = a.size();
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] > x) hi = mid;       // hanya '>=' berubah jadi '>'
        else            lo = mid + 1;
    }
    return lo;
}
```

Perbedaannya **satu karakter**. Kalau kamu menghafal dua fungsi berbeda, kamu
menghafal terlalu banyak.

### 3.3 Turunan yang langsung terpakai

```cpp
bool ada(const vector<int>& a, int x) {
    int i = lowerBound(a, x);
    return i < (int)a.size() && a[i] == x;      // cek batas DULU
}

int hitungSamaDengan(const vector<int>& a, int x) {
    return upperBound(a, x) - lowerBound(a, x);
}

int hitungRentang(const vector<int>& a, int L, int R) {   // [L, R] inklusif
    return upperBound(a, R) - lowerBound(a, L);
}

// Nilai terbesar yang <= x. Mengembalikan false kalau tidak ada.
bool terbesarKurangSama(const vector<int>& a, int x, int& hasil) {
    int i = upperBound(a, x);
    if (i == 0) return false;                   // semua elemen > x
    hasil = a[i - 1];
    return true;
}

// Nilai terkecil yang >= x.
bool terkecilLebihSama(const vector<int>& a, int x, int& hasil) {
    int i = lowerBound(a, x);
    if (i == (int)a.size()) return false;       // semua elemen < x
    hasil = a[i];
    return true;
}
```

### 3.4 Varian "last true" (kadang lebih alami)

```cpp
// Indeks TERAKHIR dengan p(i) true, dengan pola: TRUE TRUE FALSE FALSE
// Mengembalikan -1 kalau tidak ada.
int cariTerakhirTrue(int n, function<bool(int)> p) {
    int lo = -1, hi = n - 1;            // lo = -1 mewakili "tidak ada"
    while (lo < hi) {
        int mid = lo + (hi - lo + 1) / 2;   // pembulatan KE ATAS
        if (p(mid)) lo = mid;
        else        hi = mid - 1;
    }
    return lo;
}
```

⚠️ Perhatikan `+1` pada perhitungan `mid`. Tanpa itu, ketika `hi = lo + 1` dan
`p(mid)` bernilai true, `lo` tidak berubah dan loopnya **berputar selamanya**.

> **Saran praktis:** hafalkan **hanya** kerangka "first true". Varian "last true"
> selalu bisa diperoleh sebagai `cariPertamaTrue(...) - 1` dengan predikat yang
> dibalik. Menghafal satu kerangka jauh lebih aman daripada dua.

### 3.5 STL — yang sebenarnya kamu pakai

```cpp
auto it = lower_bound(a.begin(), a.end(), x);
int idx = it - a.begin();

// dengan komparator kustom (array harus terurut menurut komparator yang SAMA)
auto it2 = lower_bound(a.begin(), a.end(), x, greater<int>());   // array MENURUN

// pada struct
auto it3 = lower_bound(v.begin(), v.end(), Item{5, 0},
                       [](const Item& a, const Item& b){ return a.kunci < b.kunci; });

// pada set / map -- WAJIB fungsi anggota
auto it4 = s.lower_bound(x);        // O(log n)   ✅
// auto bad = lower_bound(s.begin(), s.end(), x);   // O(n)   ❌

// equal_range memberi keduanya sekaligus
auto [lb, ub] = equal_range(a.begin(), a.end(), x);
int banyak = ub - lb;
```

### 3.6 Binary search pada jawaban (pratinjau Day 50)

Kerangka yang sama bekerja pada **rentang nilai**, bukan hanya indeks array:

```cpp
long long lo = 1, hi = 1e18;
while (lo < hi) {
    long long mid = lo + (hi - lo) / 2;
    if (bisa(mid)) hi = mid;         // mid layak, coba yang lebih kecil
    else           lo = mid + 1;
}
// lo = nilai terkecil yang layak
```

Di sinilah `lo + (hi − lo) / 2` menjadi **penting sungguhan**: dengan `hi = 10^18`,
`(lo + hi)` meluap di `long long`. Kebiasaan yang kamu bentuk sekarang akan
menyelamatkanmu besok.

---

## 🔄 4. Trace & Simulasi

### 4.1 `lowerBound([1,3,3,3,5,7], 3)`

```
n = 6, lo = 0, hi = 6
```

| iter | lo | hi | mid | a[mid] | `a[mid] >= 3`? | aksi | lo, hi baru |
| ---- | -- | -- | --- | ------ | -------------- | ---- | ----------- |
| 1 | 0 | 6 | 3 | 3 | ya | `hi = mid` | 0, 3 |
| 2 | 0 | 3 | 1 | 3 | ya | `hi = mid` | 0, 1 |
| 3 | 0 | 1 | 0 | 1 | tidak | `lo = mid+1` | 1, 1 |

```
lo == hi == 1  ->  jawabannya 1     ✓  (a[1] = 3, kemunculan PERTAMA)
```

### 4.2 `upperBound([1,3,3,3,5,7], 3)`

| iter | lo | hi | mid | a[mid] | `a[mid] > 3`? | aksi | lo, hi baru |
| ---- | -- | -- | --- | ------ | ------------- | ---- | ----------- |
| 1 | 0 | 6 | 3 | 3 | tidak | `lo = mid+1` | 4, 6 |
| 2 | 4 | 6 | 5 | 7 | ya | `hi = mid` | 4, 5 |
| 3 | 4 | 5 | 4 | 5 | ya | `hi = mid` | 4, 4 |

```
lo == hi == 4  ->  jawabannya 4     ✓  (a[4] = 5, pertama yang > 3)

banyaknya 3 = upper(3) - lower(3) = 4 - 1 = 3     ✓
```

### 4.3 Kasus tepi

```
lowerBound([1,3,3,3,5,7], 0):
   semua elemen >= 0  ->  hi terus mengecil sampai 0
   jawabannya 0        (sisipkan di depan)

lowerBound([1,3,3,3,5,7], 9):
   tidak ada elemen >= 9  ->  lo terus naik sampai 6
   jawabannya 6 == n      (DI LUAR array!)
   -> a[6] adalah akses di luar batas. SELALU cek i < n dulu.

upperBound([1,3,3,3,5,7], 0):
   jawabannya 0
   -> "elemen terakhir yang <= 0" = a[0-1] = a[-1]. SELALU cek i != 0 dulu.
```

Dua pemeriksaan batas ini — `i < n` dan `i != 0` — adalah hal yang paling sering
dilupakan, dan keduanya menghasilkan runtime error atau jawaban sampah.

### 4.4 Overflow yang nyata

```
lo = 2*10^9, hi = 2*10^9 + 10       (misalnya pada binary search jawaban)

(lo + hi) / 2  ->  4*10^9 + 10  MELUAP di int (batas 2.1*10^9)
                   hasilnya bilangan NEGATIF -> mid negatif -> crash

lo + (hi - lo) / 2  ->  2*10^9 + 5   AMAN
```

Selisih `hi − lo` selalu muat kalau `lo` dan `hi` masing-masing muat.
Itulah seluruh alasan bentuk ini dipakai.

### 4.5 Loop tak berujung pada varian "last true"

```
Salah: mid = lo + (hi - lo) / 2   pada kerangka "last true"

lo = 0, hi = 1
mid = 0 + (1-0)/2 = 0
p(0) true -> lo = mid = 0        <- lo TIDAK BERUBAH
lo = 0, hi = 1   ->  keadaan yang SAMA PERSIS  ->  berputar selamanya
```

```
Benar: mid = lo + (hi - lo + 1) / 2      (pembulatan KE ATAS)

lo = 0, hi = 1
mid = 0 + (1-0+1)/2 = 1
p(1) true -> lo = 1  -> lo == hi -> berhenti    ✓
```

Aturannya: **kalau kamu memakai `lo = mid`, bulatkan `mid` ke atas.**

---

## 📝 5. Variasi & Pattern

| Kalimat di soal | Yang dipakai |
| --------------- | ------------ |
| "pertama yang ≥ x" | `lower_bound` |
| "pertama yang > x" | `upper_bound` |
| "terakhir yang ≤ x" | `upper_bound(x) − 1`, cek `!= 0` |
| "terakhir yang < x" | `lower_bound(x) − 1`, cek `!= 0` |
| "berapa yang sama dengan x" | `ub − lb` |
| "berapa yang di rentang [L, R]" | `ub(R) − lb(L)` |
| "apakah x ada" | `lb != n && a[lb] == x` |
| "nilai terdekat dengan x" | bandingkan `a[lb]` dan `a[lb−1]` |
| pada `set`/`map` | **fungsi anggota**, bukan `std::lower_bound` |
| array **menurun** | tambahkan `greater<>()` |

### Pattern: nilai terdekat

```cpp
int terdekat(const vector<int>& a, int x) {
    int i = lowerBound(a, x);
    if (i == 0) return a[0];                    // semua lebih besar
    if (i == (int)a.size()) return a.back();    // semua lebih kecil
    return (x - a[i-1] <= a[i] - x) ? a[i-1] : a[i];
}
```

Dua pemeriksaan batas di awal, lalu perbandingan. Pola ini muncul berkali-kali.

### Pattern: two pointers menggantikan binary search

Kalau kamu melakukan `lower_bound` untuk **setiap** elemen dari array lain yang juga
terurut, seringkali two pointers (Day 32) menggantikannya dengan O(n) alih-alih
O(n log n) — dan lebih pendek. Perhatikan apakah ambang batasnya **monoton**.

### Pattern: binary search pada jawaban

Kerangkanya identik, tetapi ruang pencariannya adalah **nilai jawaban**, bukan indeks.
Ini materi Day 50 dan salah satu teknik paling sering terpakai di CP.

---

## ⚠️ 6. Common Mistakes & Edge Cases

1. **Tidak memeriksa `i < n` sebelum mengakses `a[i]`.** Kedua bound bisa
   mengembalikan `n`.

2. **Tidak memeriksa `i != 0` sebelum mengakses `a[i-1]`.** Menghasilkan `a[-1]`.

3. **`(lo + hi) / 2` pada rentang besar.** Overflow. Selalu `lo + (hi − lo) / 2`.

4. **Mencampur konvensi `[lo, hi)` dan `[lo, hi]`.** Menyalin kode dari dua sumber
   berbeda adalah cara tercepat mendapat bug yang sulit dilihat.

5. **`lo = mid` tanpa pembulatan ke atas.** Loop tak berujung.

6. **`std::lower_bound` pada `set`.** Kompilasi berhasil, berjalan O(n) → TLE.

7. **Array tidak terurut.** Binary search pada data tak terurut memberi jawaban
   sembarang **tanpa error**. Selalu pastikan sudah terurut.

8. **Komparator tidak konsisten dengan urutan array.** Kalau array diurutkan menurun,
   `lower_bound` biasa memberi hasil sampah — butuh `greater<>()`.

9. **Menganggap `lower_bound` mencari nilai `x`.** Ia mencari **posisi**, dan posisi
   itu belum tentu berisi `x`.

### Edge cases wajib diuji

```
array kosong             -> kedua bound mengembalikan 0
x lebih kecil dari semua -> lb = ub = 0
x lebih besar dari semua -> lb = ub = n
x tidak ada di tengah    -> lb == ub (rentang kosong)
seluruh elemen sama      -> lb = 0, ub = n
n = 1                    -> uji ketiga kemungkinan x
```

---

## 🏆 7. Tips Contest

**Hafalkan SATU kerangka, bukan empat varian:**

```cpp
int lo = 0, hi = n;
while (lo < hi) {
    int mid = lo + (hi - lo) / 2;
    if (p(mid)) hi = mid;
    else        lo = mid + 1;
}
// lo = indeks PERTAMA yang p bernilai true (atau n)
```

Setiap soal binary search direduksi menjadi *"apa predikat monotonnya?"*
Kalau kamu bisa menuliskan `p`, sisanya mekanis.

**Di kontes, pakai STL.** `lower_bound`/`upper_bound` sudah teruji dan lebih cepat
ditulis. Menulis manual berguna untuk (a) memahami, (b) saat predikatnya bukan
perbandingan sederhana, (c) binary search pada jawaban (Day 50).

**Uji tiga kasus sebelum submit:** `x` lebih kecil dari semua, `x` lebih besar dari
semua, dan `x` yang tidak ada di tengah. Sepuluh detik, dan menangkap hampir semua
off-by-one.

**Peringatan `set`:** kalau kamu menulis `lower_bound(s.begin(), s.end(), x)` dan
soalnya TLE tanpa alasan jelas, ini biasanya penyebabnya.

---

## 📌 8. Ringkasan & Cheatsheet

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  LOWER / UPPER BOUND
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  SATU KERANGKA UNTUK SEMUANYA (first true):
    int lo = 0, hi = n;                 [lo, hi), hi = n
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;   hindari overflow
        if (p(mid)) hi = mid;           mungkin jawabannya
        else        lo = mid + 1;       pasti bukan
    }
    return lo;

    lower_bound -> p(i) = (a[i] >= x)
    upper_bound -> p(i) = (a[i] >  x)      bedanya SATU KARAKTER

  INVARIANT: indeks < lo semuanya FALSE, indeks >= hi semuanya TRUE

  TURUNAN
    jumlah == x        : ub(x) - lb(x)
    jumlah di [L, R]   : ub(R) - lb(L)
    x ada?             : lb != n && a[lb] == x
    terakhir <= x      : ub(x) - 1     cek != 0 DULU
    terakhir <  x      : lb(x) - 1     cek != 0 DULU
    terkecil >= x      : a[lb(x)]      cek != n DULU

  VARIAN "last true": mid = lo + (hi - lo + 1) / 2   <- BULATKAN KE ATAS
    (kalau memakai lo = mid, tanpa +1 loopnya TAK BERUJUNG)

  set/map: WAJIB s.lower_bound(x)  O(log n)
           std::lower_bound(s.begin(), ...)  O(n)   -> TLE senyap

  array MENURUN: tambahkan greater<>()
  array TIDAK TERURUT: hasilnya sampah TANPA error
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### Soal latihan online

| Soal | Platform | Topik |
| ---- | -------- | ----- |
| [CSES 1091 — Concert Tickets](https://cses.fi/problemset/task/1091) | CSES | `upper_bound` pada multiset |
| [CSES 1618 — ... / 1620 Factory Machines](https://cses.fi/problemset/task/1620) | CSES | binary search jawaban |
| [LeetCode 34 — Find First and Last Position](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/) | LeetCode | kedua bound |
| [LeetCode 35 — Search Insert Position](https://leetcode.com/problems/search-insert-position/) | LeetCode | `lower_bound` murni |
| [LeetCode 704 — Binary Search](https://leetcode.com/problems/binary-search/) | LeetCode | dasar |
| [LeetCode 658 — Find K Closest Elements](https://leetcode.com/problems/find-k-closest-elements/) | LeetCode | bound + two pointers |
| [CF 600B — Queries about less or equal](https://codeforces.com/problemset/problem/600/B) | Codeforces | `upper_bound` |
| [UVa 10611 — The Playboy Chimp](https://onlinejudge.org/) | UVa | kedua bound + kasus tepi |

---

**Selanjutnya:** Day 50 (sudah kamu selesaikan) — Binary Search on Answer, dan
Day 51 — Binary Search pada Bilangan Real. Kerangka yang sama akan dipakai pada
ruang pencarian yang bukan indeks array, dan di sana `lo + (hi − lo) / 2` berhenti
menjadi kebiasaan baik dan menjadi **keharusan**.
