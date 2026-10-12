# 📊 Day 170: Fenwick Tree (BIT) — Point Update, Prefix Query

> **Prasyarat:** Prefix Sum (Day 29), Bitwise (Day 11), Coordinate Compression (Day 38)
> **Estimasi belajar:** 3–4 jam (teori + 6 latihan)
> **Kata kunci soal:** *"update dan query bergantian"*, *"hitung inversi"*, *"berapa yang lebih kecil"*

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan Day 170, kamu akan mampu:

- [ ] Menulis Fenwick Tree dari nol dalam **kurang dari satu menit**
- [ ] Menjelaskan arti `i & -i` dan kenapa ia memberi **bit terendah yang menyala**
- [ ] Menjelaskan mengapa `i += i & -i` untuk update dan `i -= i & -i` untuk query
- [ ] Menghitung **inversi** dan **"berapa yang lebih kecil di kanan"** dengan BIT
- [ ] Membalik peran untuk **range update, point query**
- [ ] Menggabungkan BIT dengan **kompresi koordinat** (Day 38)
- [ ] Memilih antara **prefix sum**, **sparse table**, **BIT**, dan **segment tree**

---

## 🔍 1. Konsep & Intuisi

### Masalah yang diselesaikan

```
Array yang BERUBAH. Dua operasi, saling berselang:
  update(i, delta) : a[i] += delta
  query(r)         : jumlah a[1..r]
```

Prefix sum memberi query `O(1)` tetapi update `O(n)` (harus membangun ulang).
Array biasa memberi update `O(1)` tetapi query `O(n)`.
Fenwick Tree memberi **`O(log n)` untuk keduanya** — dengan sepuluh baris kode.

```
                 update    query    ruang
array biasa      O(1)      O(n)     O(n)
prefix sum       O(n)      O(1)     O(n)
sparse table     ✗         O(1)     O(n log n)
Fenwick (BIT)    O(log n)  O(log n) O(n)
segment tree     O(log n)  O(log n) O(n)
```

### Analogi: uang kertas dengan pecahan pangkat dua

Bayangkan kamu harus membayar jumlah berapa pun memakai uang pecahan
1, 2, 4, 8, 16, ... Setiap jumlah bisa dibayar dengan **sedikit** lembar —
paling banyak `log n` lembar, sesuai representasi binernya.

```
13 = 8 + 4 + 1     -> tiga lembar
```

Fenwick Tree menyimpan "jumlah parsial" yang panjangnya pangkat dua, sehingga
`query(13)` cukup menjumlahkan tiga blok alih-alih 13 elemen.

### Struktur: setiap simpul menanggung blok berukuran `i & -i`

```
tree[i] menyimpan jumlah a[i - (i & -i) + 1 .. i]
        yaitu blok sepanjang (i & -i) yang BERAKHIR di i
```

```
i      biner    i & -i   blok yang ditanggung
1      0001       1      a[1..1]
2      0010       2      a[1..2]
3      0011       1      a[3..3]
4      0100       4      a[1..4]
5      0101       1      a[5..5]
6      0110       2      a[5..6]
7      0111       1      a[7..7]
8      1000       8      a[1..8]
```

```
Visualisasi (panjang batang = ukuran blok):

 1  [=]
 2  [===]
 3      [=]
 4  [=======]
 5          [=]
 6          [===]
 7              [=]
 8  [===============]
    1  2  3  4  5  6  7  8
```

Perhatikan bahwa blok-blok ini **bersarang rapi** — dan itulah yang membuat
`query(r)` cukup memilih beberapa blok yang menutupi `[1, r]` tanpa tumpang tindih.

### `i & -i` — bit terendah yang menyala

```
i = 12  = 00001100
-i      = 11110100     (two's complement: balik seluruh bit, tambah 1)
i & -i  = 00000100 = 4
```

Dalam representasi two's complement, `-i` adalah `~i + 1`. Operasi `AND`
antara `i` dan `-i` menyisakan **tepat satu bit** — yang terendah menyala.

Nama lainnya `lowbit(i)`. Ia menjawab: *"blok yang berakhir di `i` panjangnya
berapa?"*

### Dua arah pergerakan

```
QUERY(r)  -- menjumlahkan a[1..r]:
    i -= i & -i     (buang bit terendah)  ->  melompat ke blok sebelumnya

    query(13): 13 = 1101
        i=13 (1101) ambil tree[13] (a[13..13]), i -> 12
        i=12 (1100) ambil tree[12] (a[9..12]),  i -> 8
        i=8  (1000) ambil tree[8]  (a[1..8]),   i -> 0
        Total: a[1..8] + a[9..12] + a[13..13] = a[1..13]   ✓
        Tiga langkah, bukan 13.

UPDATE(i) -- a[i] += delta:
    i += i & -i     (naikkan bit terendah)  ->  ke blok yang MEMUAT i

    update(5): 5 = 0101
        i=5  (0101) tree[5]  memuat a[5]  ->  i -> 6
        i=6  (0110) tree[6]  memuat a[5]  ->  i -> 8
        i=8  (1000) tree[8]  memuat a[5]  ->  i -> 16 (di luar, berhenti)
        Tiga simpul diperbarui, bukan semua.
```

> **Kenapa dua arah berlawanan?** Query bergerak **turun** menyusuri blok-blok
> yang menutupi prefiks; update bergerak **naik** ke seluruh blok yang memuat
> posisi itu. Keduanya `O(log n)` karena setiap langkah mengubah satu bit.

---

## 🧮 2. Analisis Kompleksitas

| Operasi | Waktu | Catatan |
| ------- | ----- | ------- |
| `update(i, delta)` | O(log n) | paling banyak `log n` simpul |
| `query(r)` — prefiks | O(log n) | paling banyak `log n` blok |
| `range(l, r)` | O(log n) | `query(r) − query(l−1)` |
| Build dari array | O(n) | ada trik linear, lihat 3.4 |
| Build naif | O(n log n) | `n` kali update |
| Ruang | **O(n)** | satu array, tidak ada rekursi |

**Konstanta BIT sangat kecil** — sekitar 3–5× lebih cepat daripada segment tree
untuk operasi yang sama, karena tidak ada rekursi, tidak ada pointer, dan
aksesnya ramah cache.

**Perbandingan dengan segment tree:**

| | Fenwick | Segment tree |
| --- | --- | --- |
| Panjang kode | ~10 baris | ~40 baris |
| Konstanta | sangat kecil | sedang |
| Ruang | `n` | `2n` sampai `4n` |
| Operasi | sum, XOR (punya invers) | apa pun (min, max, gcd, ...) |
| Range update | butuh trik | lazy propagation |
| Descent (cari ke-k) | bisa, `O(log n)` | bisa |

⚠️ **Fenwick hanya untuk operasi yang punya INVERS** (sum, XOR), karena
`range(l, r)` dihitung sebagai `query(r) − query(l−1)`. Untuk `min` atau `max`,
pengurangan tidak ada artinya — pakai sparse table (statis) atau segment tree
(dinamis).

Perhatikan bahwa ini **kebalikan** dari sparse table, yang butuh idempoten
tetapi tidak butuh invers. Tiga struktur, tiga syarat berbeda:

```
prefix sum    : butuh INVERS, array STATIS
sparse table  : butuh IDEMPOTEN, array STATIS
Fenwick       : butuh INVERS, array DINAMIS
segment tree  : butuh ASOSIATIF saja, array DINAMIS
```

---

## 💻 3. Implementasi C++

### 3.1 Bentuk baku (hafalkan)

```cpp
struct BIT {
    int n;
    vector<long long> t;

    BIT(int n_) : n(n_), t(n_ + 1, 0) {}          // 1-INDEXED

    void update(int i, long long delta) {
        for (; i <= n; i += i & -i) t[i] += delta;
    }

    long long query(int i) const {                 // jumlah a[1..i]
        long long s = 0;
        for (; i > 0; i -= i & -i) s += t[i];
        return s;
    }

    long long range(int l, int r) const {          // jumlah a[l..r]
        return query(r) - query(l - 1);
    }
};
```

⚠️ **BIT WAJIB 1-indexed.** Kalau `i = 0`, maka `i & -i = 0` dan loop
`i += 0` **berputar selamanya**. Kalau datamu 0-indexed, geser satu saat
memanggil: `update(i + 1, x)`.

Ini adalah kesalahan nomor satu di topik ini, dan gejalanya (program hang)
membingungkan karena tidak ada pesan error.

### 3.2 Build O(n) — lebih cepat dari n kali update

```cpp
BIT(const vector<long long>& a) : n(a.size()), t(n + 1, 0) {
    for (int i = 1; i <= n; i++) {
        t[i] += a[i - 1];
        int j = i + (i & -i);
        if (j <= n) t[j] += t[i];                  // wariskan ke induk
    }
}
```

Setiap simpul menambahkan nilainya ke induknya sekali. Total `O(n)` alih-alih
`O(n log n)`. Perbedaannya kecil tetapi gratis.

### 3.3 Menghitung inversi (penerapan paling klasik)

```cpp
// Banyaknya pasangan (i, j) dengan i < j dan a[i] > a[j]
long long hitungInversi(vector<int> a) {
    // 1. kompresi koordinat -- nilai bisa 10^9, BIT butuh indeks kecil
    vector<int> v = a;
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for (int& x : a) x = lower_bound(v.begin(), v.end(), x) - v.begin() + 1;

    BIT bit(v.size());
    long long inv = 0;
    for (int i = (int)a.size() - 1; i >= 0; i--) {  // sapu dari KANAN
        inv += bit.query(a[i] - 1);                 // yang lebih KECIL, sudah lewat
        bit.update(a[i], 1);
    }
    return inv;
}
```

Idenya: sapu dari kanan. Saat memproses `a[i]`, seluruh elemen di kanannya
sudah masuk BIT. `query(a[i] - 1)` menghitung berapa di antaranya yang
**lebih kecil** — dan itulah inversi yang melibatkan `a[i]` sebagai anggota kiri.

⚠️ **Kompresi koordinat wajib** kalau nilai bisa besar. BIT diindeks oleh
**nilai**, jadi domainnya harus kecil (Day 38).

### 3.4 Range update, point query — membalik peran

Trik: simpan **selisih** (difference array, Day 31) di dalam BIT.

```cpp
struct BITRange {
    BIT bit;
    BITRange(int n) : bit(n) {}

    void rangeAdd(int l, int r, long long v) {
        bit.update(l, v);
        bit.update(r + 1, -v);                     // r+1 boleh melebihi n
    }
    long long pointQuery(int i) { return bit.query(i); }
};
```

Karena `query(i)` menjumlahkan seluruh selisih sampai `i`, hasilnya adalah
nilai sesungguhnya di posisi `i`. Ini yang dipakai di Day 53 (parallel binary
search) untuk hujan meteor.

⚠️ `update(r + 1, ...)` bisa melebihi `n`. Alokasikan `n + 2` slot, atau
periksa `if (r + 1 <= n)`.

### 3.5 Range update, range query — dua BIT

```cpp
struct BIT2 {
    BIT b1, b2;
    int n;
    BIT2(int n_) : b1(n_ + 1), b2(n_ + 1), n(n_) {}

    void rangeAdd(int l, int r, long long v) {
        b1.update(l, v);          b1.update(r + 1, -v);
        b2.update(l, v * (l - 1)); b2.update(r + 1, -v * r);
    }
    long long prefix(int i) { return b1.query(i) * i - b2.query(i); }
    long long range(int l, int r) { return prefix(r) - prefix(l - 1); }
};
```

Menyimpan dua komponen agar jumlah prefiks bisa direkonstruksi. Rumusnya tidak
intuitif; simpan di template dan pakai apa adanya. Segment tree dengan lazy
propagation (Day 176) melakukan hal yang sama dengan cara yang lebih jelas.

### 3.6 Descent: mencari elemen ke-k dalam O(log n)

```cpp
// Indeks terkecil i dengan query(i) >= k. Mengembalikan n+1 kalau tidak ada.
int cariKeK(const BIT& bit, long long k) {
    int pos = 0;
    long long sisa = k;
    for (int pw = 1 << (31 - __builtin_clz(bit.n)); pw > 0; pw >>= 1)
        if (pos + pw <= bit.n && bit.t[pos + pw] < sisa) {
            pos += pw;
            sisa -= bit.t[pos];
        }
    return pos + 1;
}
```

Menuruni struktur BIT secara langsung, `O(log n)` alih-alih
`O(log² n)` kalau memakai binary search di luar. Berguna untuk
"nilai terkecil ke-k dalam multiset dinamis".

### 3.7 BIT dua dimensi

```cpp
long long t2[MAXN][MAXM];

void update2(int x, int y, long long v) {
    for (int i = x; i <= n; i += i & -i)
        for (int j = y; j <= m; j += j & -j) t2[i][j] += v;
}
long long query2(int x, int y) {
    long long s = 0;
    for (int i = x; i > 0; i -= i & -i)
        for (int j = y; j > 0; j -= j & -j) s += t2[i][j];
    return s;
}
```

`O(log n · log m)` per operasi. Untuk submatriks, pakai inklusi-eksklusi
empat sudut (Day 30).

---

## 🔄 4. Trace & Simulasi

### 4.1 Membangun BIT untuk `a = [3, 2, -1, 6, 5, 4, -3, 3]` (n = 8)

```
tree[i] menanggung blok sepanjang (i & -i) yang berakhir di i:

tree[1] = a[1]             = 3
tree[2] = a[1..2]          = 3 + 2 = 5
tree[3] = a[3]             = -1
tree[4] = a[1..4]          = 3 + 2 - 1 + 6 = 10
tree[5] = a[5]             = 5
tree[6] = a[5..6]          = 5 + 4 = 9
tree[7] = a[7]             = -3
tree[8] = a[1..8]          = 10 + 5 + 4 - 3 + 3 = 19
```

### 4.2 `query(7)` — jumlah `a[1..7]`

| i (biner) | `i & -i` | ambil `tree[i]` | blok | i berikutnya |
| --------- | -------- | --------------- | ---- | ------------ |
| 7 (0111) | 1 | −3 | a[7..7] | 7 − 1 = 6 |
| 6 (0110) | 2 | 9 | a[5..6] | 6 − 2 = 4 |
| 4 (0100) | 4 | 10 | a[1..4] | 4 − 4 = 0 |

```
Total = -3 + 9 + 10 = 16
Verifikasi: 3 + 2 - 1 + 6 + 5 + 4 - 3 = 16   ✓

Tiga blok menutupi [1,7] TANPA tumpang tindih:
   [1..4] + [5..6] + [7..7]
Bandingkan dengan sparse table yang justru MEMBUTUHKAN tumpang tindih.
```

### 4.3 `update(5, +10)` — `a[5] += 10`

| i (biner) | `i & -i` | `tree[i]` menanggung | memuat a[5]? | i berikutnya |
| --------- | -------- | -------------------- | ------------ | ------------ |
| 5 (0101) | 1 | a[5..5] | ya | 5 + 1 = 6 |
| 6 (0110) | 2 | a[5..6] | ya | 6 + 2 = 8 |
| 8 (1000) | a[1..8] | ya | 8 + 8 = 16 > n, berhenti |

```
tree[5] : 5  -> 15
tree[6] : 9  -> 19
tree[8] : 19 -> 29

Tiga simpul, bukan delapan. Setiap simpul yang blok-nya MEMUAT posisi 5.
```

Perhatikan bahwa `tree[7]` **tidak** diperbarui — bloknya `a[7..7]` tidak
memuat posisi 5. Struktur BIT memastikan kita hanya menyentuh yang perlu.

### 4.4 `i & -i` pada beberapa nilai

```
i = 6:   0110
-i:      1010    (~0110 = 1001, +1 = 1010)
i & -i:  0010 = 2     -> blok panjang 2

i = 8:   1000
-i:      1000
i & -i:  1000 = 8     -> blok panjang 8

i = 12:  1100
-i:      0100
i & -i:  0100 = 4     -> blok panjang 4
```

⚠️ `i = 0`: `0 & -0 = 0`. Loop `i += 0` **tidak pernah maju** → hang.
Inilah kenapa BIT wajib 1-indexed.

### 4.5 Menghitung inversi pada `a = [3, 1, 2]`

```
Setelah kompresi: [3, 1, 2] (sudah kecil, peringkat 3, 1, 2)
BIT kosong, sapu dari KANAN:

i=2 (nilai 2): query(1) = 0        inv = 0    lalu update(2, 1)
i=1 (nilai 1): query(0) = 0        inv = 0    lalu update(1, 1)
i=0 (nilai 3): query(2) = 2        inv = 2    lalu update(3, 1)

Total inversi = 2
Verifikasi manual: (3,1) dan (3,2)   ✓
```

Saat memproses nilai 3, BIT sudah memuat 1 dan 2 (keduanya di kanannya dan
lebih kecil), sehingga `query(3-1) = query(2) = 2` tepat menghitung keduanya.

---

## 📝 5. Variasi & Pattern

| Kalimat di soal | Yang dipakai |
| --------------- | ------------ |
| "update titik, jumlah prefiks/rentang" | BIT dasar |
| "hitung inversi" | BIT + kompresi, sapu dari kanan |
| "berapa yang lebih kecil di kanan" | BIT + kompresi |
| "update rentang, baca satu titik" | BIT atas difference array |
| "update rentang, jumlah rentang" | dua BIT, atau segment tree lazy |
| "nilai terkecil ke-k, ada penyisipan/penghapusan" | BIT + descent |
| "min/max pada rentang, ada update" | ❌ BIT tidak bisa; segment tree |
| nilai sampai `10^9` | kompresi dulu (Day 38) |
| "berapa titik di dalam persegi" | BIT 2D, atau sweep + BIT 1D |

### Pattern: BIT sebagai multiset dinamis

```cpp
bit.update(nilai, +1);       // sisipkan
bit.update(nilai, -1);       // hapus
bit.query(x);                // berapa elemen <= x
cariKeK(bit, k);             // nilai terkecil ke-k
```

Empat operasi ini menjadikan BIT pengganti `multiset` yang jauh lebih cepat,
selama domain nilainya bisa dikompresi. Ini pola yang sangat sering terpakai.

### Pattern: sweep line + BIT

Untuk soal "berapa pasangan yang memenuhi dua kondisi", sering kali kamu
mengurutkan berdasarkan satu dimensi lalu memakai BIT pada dimensi lain:

```
urutkan titik berdasarkan x
untuk setiap titik: query BIT pada rentang y, lalu update BIT di posisi y
```

Ini mengubah masalah 2D menjadi 1D + sapuan, dan muncul di banyak soal
geometri dan penghitungan.

### Kapan JANGAN memakai BIT

```
1. Operasi min/max/gcd     -> tidak punya invers; segment tree
2. Array statis, hanya query -> prefix sum (O(1)) atau sparse table
3. Butuh operasi kompleks pada rentang -> segment tree dengan lazy
4. Domain nilai besar tanpa kompresi -> kompres dulu (Day 38)
```

---

## ⚠️ 6. Common Mistakes & Edge Cases

1. **0-indexed.** `i & -i = 0` saat `i = 0` → loop tak berujung. **Selalu 1-indexed.**

2. **Lupa kompresi koordinat.** BIT diindeks oleh nilai; `10^9` slot mustahil.

3. **`int` untuk jumlah.** `n = 2·10^5` dengan nilai `10^9` memberi `2·10^14`.
   Inversi bisa `5·10^9`.

4. **`update(r+1, ...)` melebihi `n`** pada range update. Alokasikan `n+2`.

5. **Memakai BIT untuk min/max.** `query(r) − query(l−1)` tidak punya arti.

6. **Salah arah pada penghitungan inversi.** Sapu dari kanan dan hitung yang
   lebih kecil, **atau** sapu dari kiri dan hitung yang lebih besar. Mencampur
   keduanya memberi jawaban yang salah.

7. **Build naif `n` kali update** ketika ada versi `O(n)`. Bukan bug, tetapi
   gratis diperbaiki.

8. **`query(0)`** harus mengembalikan 0, bukan masuk loop. Kondisi `i > 0`
   sudah menanganinya.

### Edge cases wajib diuji

```
n = 1                    -> update(1), query(1)
query(0)                 -> harus 0
range(l, l)              -> satu elemen
seluruh nilai sama       -> inversi = 0
array terurut menaik     -> inversi = 0
array terurut menurun    -> inversi = n(n-1)/2, kasus maksimum
delta negatif            -> BIT tidak peduli tanda
range update sampai n    -> r+1 = n+1, harus aman
```

---

## 🏆 7. Tips Contest

**BIT adalah struktur dengan rasio manfaat-terhadap-panjang-kode terbaik kedua
setelah DSU.** Sepuluh baris, `O(log n)` untuk semuanya, konstanta sangat kecil.
Hafalkan sampai bisa ditulis tanpa berpikir.

**Pohon keputusan (10 detik pertama):**

```
Ada UPDATE?
  ├─ TIDAK
  │    ├─ sum/xor      -> prefix sum, O(1) query
  │    └─ min/max/gcd  -> sparse table, O(1) query
  └─ YA
       ├─ sum/xor      -> FENWICK (lebih pendek & cepat dari segment tree)
       └─ min/max/gcd  -> segment tree
```

**Kalau nilai bisa besar, refleks pertama adalah kompresi koordinat.**
BIT dan kompresi hampir selalu muncul bersama — simpan keduanya berdekatan
di template.

**Untuk inversi, hafalkan satu arah saja** (sapu kanan, hitung yang lebih kecil)
dan pakai itu terus. Mencampur arah adalah sumber bug yang tidak perlu.

**Uji dengan brute force `O(n²)`** pada 1000 array acak berukuran ≤ 8.
Semua bug indeks BIT tertangkap dalam hitungan detik.

---

## 📌 8. Ringkasan & Cheatsheet

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  FENWICK TREE (BIT)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  struct BIT {
      int n; vector<ll> t;
      BIT(int n_) : n(n_), t(n_ + 1, 0) {}       1-INDEXED WAJIB

      void update(int i, ll d) { for (; i <= n; i += i & -i) t[i] += d; }
      ll query(int i) { ll s=0; for (; i > 0; i -= i & -i) s += t[i]; return s; }
      ll range(int l, int r) { return query(r) - query(l - 1); }
  };

  tree[i] menanggung a[i - (i&-i) + 1 .. i]      blok sepanjang lowbit(i)
  i & -i = bit terendah yang menyala (two's complement)
  UPDATE naik (i += i&-i)  : ke semua blok yang MEMUAT i
  QUERY  turun (i -= i&-i) : blok-blok yang MENUTUPI prefiks

  i = 0 -> i & -i = 0 -> LOOP TAK BERUJUNG. Ini bug nomor satu.

  SYARAT: operasi harus punya INVERS (sum, XOR).
    min/max/gcd -> TIDAK BISA, pakai segment tree

  TIGA STRUKTUR, TIGA SYARAT
    prefix sum   : INVERS  + statis   -> O(1) query
    sparse table : IDEMPOTEN + statis -> O(1) query
    Fenwick      : INVERS  + dinamis  -> O(log n)
    segment tree : ASOSIATIF + dinamis -> O(log n), paling umum

  POLA
    inversi         : kompresi, sapu KANAN, query(a[i]-1), update(a[i],1)
    range update    : BIT atas DIFFERENCE array (update l, -update r+1)
    multiset dinamis: update(v,+1)/(v,-1), query(x), descent untuk ke-k
    2D              : dua loop bersarang, O(log n log m)

  build O(n): t[i] += a[i]; j = i + (i&-i); if (j<=n) t[j] += t[i];
  long long: jumlah 2e14, inversi 5e9
  NILAI BESAR -> KOMPRESI KOORDINAT DULU (Day 38)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### Soal latihan online

| Soal | Platform | Topik |
| ---- | -------- | ----- |
| [CSES 1648 — Dynamic Range Sum Queries](https://cses.fi/problemset/task/1648) | CSES | BIT dasar |
| [CSES 1651 — Range Update Queries](https://cses.fi/problemset/task/1651) | CSES | range update, point query |
| [CSES 1144 — Salary Queries](https://cses.fi/problemset/task/1144) | CSES | BIT + kompresi |
| [CSES 1734 — Distinct Values Queries](https://cses.fi/problemset/task/1734) | CSES | offline + BIT |
| [SPOJ INVCNT](https://www.spoj.com/problems/INVCNT/) | SPOJ | inversi |
| [LeetCode 315 — Count of Smaller After Self](https://leetcode.com/problems/count-of-smaller-numbers-after-self/) | LeetCode | BIT + kompresi |
| [LeetCode 493 — Reverse Pairs](https://leetcode.com/problems/reverse-pairs/) | LeetCode | BIT, `a[i] > 2a[j]` |
| [CF 61E — Enemy is weak](https://codeforces.com/problemset/problem/61/E) | Codeforces | inversi tiga elemen |
| [UVa 11525 — Permutation](https://onlinejudge.org/) | UVa | BIT + descent |

---

**Selanjutnya:** Day 171 — Fenwick 2D dan BIT untuk range update, lalu
Day 172–178 — Segment Tree, yang menyelesaikan kelemahan terbesar BIT:
ia bekerja untuk **operasi apa pun yang asosiatif**, termasuk `min`, `max`,
dan `gcd`.

Dan yang lebih dekat: BIT ini membuka tugas-tugas yang selama ini menunggu
prasyarat — **tugas 6, 11, dan 14 di Day 38**, **tugas 11 di Day 44**,
**tugas 12 di Day 45**, dan **tugas 6 di Day 53**.
