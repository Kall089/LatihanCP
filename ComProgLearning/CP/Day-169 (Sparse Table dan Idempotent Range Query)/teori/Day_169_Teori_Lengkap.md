# 📊 Day 169: Sparse Table & Idempotent Range Query

> **Prasyarat:** Prefix Sum (Day 29), Bitwise (Day 11), Binary Search (Day 48–49)
> **Estimasi belajar:** 3 jam (teori + 6 latihan)
> **Kata kunci soal:** *"minimum pada rentang"*, *"banyak query"*, *"tanpa update"*

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan Day 169, kamu akan mampu:

- [ ] Menjelaskan arti **idempoten** dan kenapa itu syarat sparse table
- [ ] Membangun sparse table dalam **O(n log n)** dan menjawab query **O(1)**
- [ ] Menjelaskan kenapa **dua blok yang tumpang tindih** boleh dipakai
- [ ] Tahu operasi mana yang **bisa** (min, max, gcd, AND, OR) dan mana yang **tidak** (sum)
- [ ] Menghitung `log2` dengan cepat dan benar
- [ ] Memilih antara **prefix sum**, **sparse table**, dan **segment tree**
- [ ] Mengenali bahwa sparse table **tidak mendukung update**

---

## 🔍 1. Konsep & Intuisi

### Masalahnya

```
Diberikan array statis. Jawab q pertanyaan "berapa MINIMUM pada a[l..r]?"
```

Prefix sum tidak berlaku di sini. Untuk `sum` kita bisa mengurangkan,
tetapi untuk `min` **tidak ada operasi pengurangan** — mengetahui minimum
`a[0..r]` dan `a[0..l-1]` tidak memberitahumu minimum `a[l..r]`.

```
a = [5, 1, 9]
min(a[0..2]) = 1,  min(a[0..0]) = 5
minimum a[1..2] = 1, tetapi tidak ada cara "mengurangkan" 5 dari 1
```

### Ide: precompute blok berukuran pangkat dua

```
sp[k][i] = hasil operasi pada a[i .. i + 2^k - 1]
           (blok sepanjang 2^k yang dimulai di i)
```

```
a  :  5   1   9   3   7   2
       └─┘ k=0, panjang 1
       └───┘ k=1, panjang 2
       └───────┘ k=2, panjang 4
```

Membangunnya mudah: blok panjang `2^k` adalah gabungan dua blok panjang `2^(k-1)`.

```
sp[k][i] = op( sp[k-1][i],  sp[k-1][i + 2^(k-1)] )

         [------- 2^k -------]
         [--2^(k-1)--][--2^(k-1)--]
         i            i+2^(k-1)
```

### Menjawab query dalam O(1) — dan kenapa tumpang tindih boleh

Untuk rentang `[l, r]` dengan panjang `len = r - l + 1`, ambil `k` terbesar
dengan `2^k <= len`. Lalu **dua** blok berikut menutupi seluruh rentang:

```
blok kiri  : [l, l + 2^k - 1]
blok kanan : [r - 2^k + 1, r]
```

```
l                                    r
[========== len ==========]
[--- 2^k ---]
        [--- 2^k ---]
        ↑           ↑
      tumpang tindih di tengah
```

Karena `2^k > len/2`, kedua blok itu **pasti tumpang tindih** — dan justru
karena tumpang tindih, seluruh rentang tertutup tanpa celah.

> **Kenapa tumpang tindih boleh?** Karena operasinya **IDEMPOTEN**:
> menghitung elemen yang sama dua kali tidak mengubah hasilnya.
> `min(x, x) = x`, `max(x, x) = x`, `gcd(x, x) = x`.
> Tetapi `x + x ≠ x` — itulah sebabnya sparse table **tidak berlaku untuk sum**.

### Operasi mana yang idempoten?

| Operasi | `op(x, x) = x`? | Sparse table? |
| ------- | --------------- | ------------- |
| `min` | ✅ | ✅ |
| `max` | ✅ | ✅ |
| `gcd` | ✅ | ✅ |
| `lcm` | ✅ | ✅ (hati-hati overflow) |
| bitwise `AND` | ✅ | ✅ |
| bitwise `OR` | ✅ | ✅ |
| `sum` | ❌ (`x + x = 2x`) | ❌ → prefix sum |
| `XOR` | ❌ (`x ^ x = 0`) | ❌ → prefix XOR |
| perkalian | ❌ | ❌ |

⚠️ Perhatikan bahwa `sum` dan `XOR` punya **invers**, sehingga prefix sum
menyelesaikannya. `min` dan `max` tidak punya invers tetapi **idempoten**,
sehingga sparse table menyelesaikannya. Kedua teknik saling melengkapi,
bukan bersaing.

---

## 🧮 2. Analisis Kompleksitas

| Struktur | Build | Query | Update | Ruang |
| -------- | ----- | ----- | ------ | ----- |
| Prefix sum | O(n) | O(1) | ❌ | O(n) |
| **Sparse table** | O(n log n) | **O(1)** | ❌ | O(n log n) |
| Segment tree | O(n) | O(log n) | O(log n) | O(n) |
| Fenwick (BIT) | O(n log n) | O(log n) | O(log n) | O(n) |
| Naif | O(1) | O(n) | O(1) | O(1) |

### Kapan sparse table menang

```
n = 2*10^5, q = 10^6, query MIN, TANPA update

sparse table : 2*10^5 * 18 (build) + 10^6 * 1 = 4.6*10^6    ✅
segment tree : 2*10^5 (build) + 10^6 * 18     = 1.8*10^7    juga lolos, 4x lebih lambat
naif         : 10^6 * 2*10^5                  = 2*10^11     ❌
```

Sparse table menang ketika `q` besar dan **tidak ada update**. Kalau ada
update sekali saja, sparse table langsung gugur — ia harus dibangun ulang
seluruhnya.

**Memori:** `n log n` sel. Untuk `n = 2·10^5` dan `int`, itu
`2·10^5 × 18 × 4` = 14 MB. Untuk `n = 10^6` menjadi 80 MB — mulai berisiko.
Segment tree hanya `O(n)`.

---

## 💻 3. Implementasi C++

### 3.1 Bentuk baku

```cpp
struct SparseTable {
    vector<vector<int>> sp;
    vector<int> lg;

    void build(const vector<int>& a) {
        int n = a.size();
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;   // log2 tabel

        int K = lg[n] + 1;
        sp.assign(K, vector<int>(n));
        sp[0] = a;

        for (int k = 1; k < K; k++)
            for (int i = 0; i + (1 << k) <= n; i++)
                sp[k][i] = min(sp[k-1][i], sp[k-1][i + (1 << (k-1))]);
    }

    int query(int l, int r) const {        // inklusif
        int k = lg[r - l + 1];
        return min(sp[k][l], sp[k][r - (1 << k) + 1]);
    }
};
```

⚠️ **Batas loop build:** `i + (1 << k) <= n`, bukan `i < n`. Blok panjang `2^k`
yang dimulai di `i` berakhir di `i + 2^k - 1`, yang harus `< n`.

⚠️ **Query memakai `r - (1<<k) + 1`** sebagai awal blok kanan — bukan
`r - (1<<k)`. Karena rentangnya inklusif, blok yang berakhir di `r` dan
panjangnya `2^k` dimulai di `r - 2^k + 1`.

### 3.2 Menghitung `log2` dengan benar

Tiga cara, dengan sifat berbeda:

```cpp
// 1. Tabel precompute -- TERCEPAT dan paling aman
lg[1] = 0;
for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;

// 2. Builtin -- satu instruksi CPU
int k = 31 - __builtin_clz(len);        // untuk int, len > 0
int k = 63 - __builtin_clzll(len);      // untuk long long

// 3. std::log2 -- HINDARI
int k = (int)log2(len);                 // floating point, bisa MELESET
```

⚠️ `std::log2` memakai floating point dan bisa memberi `log2(8) = 2.9999999`
yang dibulatkan menjadi 2 alih-alih 3. Bug ini jarang muncul (bergantung
kompilator dan arsitektur) sehingga sangat sulit dilacak. **Jangan pakai.**

⚠️ `__builtin_clz(0)` adalah perilaku tak terdefinisi. Selalu pastikan
`len >= 1`.

### 3.3 Versi generik dengan operasi apa pun

```cpp
template <typename T, typename F>
struct SparseTable {
    vector<vector<T>> sp;
    vector<int> lg;
    F op;

    SparseTable(const vector<T>& a, F op_) : op(op_) {
        int n = a.size();
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;

        int K = lg[n] + 1;
        sp.assign(K, vector<T>(n));
        sp[0] = a;
        for (int k = 1; k < K; k++)
            for (int i = 0; i + (1 << k) <= n; i++)
                sp[k][i] = op(sp[k-1][i], sp[k-1][i + (1 << (k-1))]);
    }

    T query(int l, int r) const {
        int k = lg[r - l + 1];
        return op(sp[k][l], sp[k][r - (1 << k) + 1]);
    }
};

// pemakaian:
SparseTable<int, function<int(int,int)>> st(a, [](int x, int y){ return min(x,y); });
SparseTable<long long, ...> stGcd(a, [](long long x, long long y){ return __gcd(x,y); });
```

⚠️ **Hanya sah untuk operasi idempoten.** Kalau kamu memasukkan `+` ke sini,
kompilasinya berhasil tetapi jawabannya salah — karena daerah tumpang tindih
terhitung dua kali.

### 3.4 Mengembalikan INDEKS, bukan nilai

Sering kali soal butuh *"di mana minimumnya"*, bukan hanya nilainya:

```cpp
// simpan INDEKS di dalam tabel, bandingkan lewat nilainya
sp[k][i] = (a[sp[k-1][i]] <= a[sp[k-1][i + (1<<(k-1))]])
           ? sp[k-1][i] : sp[k-1][i + (1<<(k-1))];

int queryIdx(int l, int r) const {
    int k = lg[r - l + 1];
    int i1 = sp[k][l], i2 = sp[k][r - (1<<k) + 1];
    return (a[i1] <= a[i2]) ? i1 : i2;
}
```

Berguna untuk **LCA dengan Euler tour** (Day 202) dan divide-and-conquer
berbasis minimum.

### 3.5 Sparse table dua dimensi

Untuk query submatriks minimum pada matriks statis:

```cpp
// sp[kr][kc][i][j] = min pada submatriks 2^kr x 2^kc mulai dari (i, j)
// Build O(R·C·log R·log C), query O(1) dengan EMPAT blok tumpang tindih.
```

Memorinya `O(R·C·log R·log C)` — untuk `500 × 500` itu `500·500·9·9 = 2·10^7`
sel. Berat tetapi kadang satu-satunya cara. Jarang muncul di kontes.

### 3.6 Disjoint sparse table (untuk operasi non-idempoten)

Ada varian yang bekerja untuk `sum` dan operasi asosiatif apa pun, dengan
membagi rentang di titik tengah alih-alih tumpang tindih:

```
Build O(n log n), query O(1), TIDAK butuh idempoten.
```

Berguna untuk operasi yang asosiatif tetapi tidak idempoten **dan** tidak
punya invers — misalnya perkalian matriks pada rentang. Jarang dibutuhkan;
disebutkan agar kamu tahu ia ada.

---

## 🔄 4. Trace & Simulasi

### 4.1 Membangun sparse table untuk minimum

```
a = [5, 1, 9, 3, 7, 2]      n = 6
lg = [_, 0, 1, 1, 2, 2, 2]  (lg[1]=0, lg[2]=1, lg[3]=1, lg[4]=2, lg[5]=2, lg[6]=2)
K = lg[6] + 1 = 3
```

**k = 0** (blok panjang 1) — salinan langsung:

```
sp[0] = [5, 1, 9, 3, 7, 2]
```

**k = 1** (blok panjang 2), batas `i + 2 <= 6` → `i = 0..4`:

| i | blok | `min(sp[0][i], sp[0][i+1])` | sp[1][i] |
| - | ---- | --------------------------- | -------- |
| 0 | a[0..1] | min(5, 1) | **1** |
| 1 | a[1..2] | min(1, 9) | **1** |
| 2 | a[2..3] | min(9, 3) | **3** |
| 3 | a[3..4] | min(3, 7) | **3** |
| 4 | a[4..5] | min(7, 2) | **2** |

**k = 2** (blok panjang 4), batas `i + 4 <= 6` → `i = 0..2`:

| i | blok | `min(sp[1][i], sp[1][i+2])` | sp[2][i] |
| - | ---- | --------------------------- | -------- |
| 0 | a[0..3] | min(1, 3) | **1** |
| 1 | a[1..4] | min(1, 3) | **1** |
| 2 | a[2..5] | min(3, 2) | **2** |

### 4.2 Menjawab query

**Query `[1, 4]`** (nilai `1, 9, 3, 7`):

```
len = 4, k = lg[4] = 2, 2^k = 4
blok kiri  : sp[2][1]           = a[1..4] -> 1
blok kanan : sp[2][4 - 4 + 1] = sp[2][1] = a[1..4] -> 1
jawab min(1, 1) = 1     ✓

Di sini kedua blok KEBETULAN sama, karena len tepat pangkat dua.
```

**Query `[2, 5]`** (nilai `9, 3, 7, 2`):

```
len = 4, k = 2
blok kiri  : sp[2][2] = a[2..5] -> 2
blok kanan : sp[2][2] = a[2..5] -> 2
jawab 2     ✓
```

**Query `[0, 4]`** (nilai `5, 1, 9, 3, 7`) — di sini tumpang tindih terlihat:

```
len = 5, k = lg[5] = 2, 2^k = 4
blok kiri  : sp[2][0]           = a[0..3] -> 1
blok kanan : sp[2][5 - 4 + 1] = sp[2][1] = a[1..4] -> 1

              0   1   2   3   4
              [--- kiri ---]
                  [--- kanan ---]
                  ↑       ↑
              tumpang tindih a[1..3]

a[1..3] terhitung DUA KALI, tetapi min(x, x) = x sehingga tidak berpengaruh.
jawab min(1, 1) = 1     ✓
```

**Query `[3, 3]`** (satu elemen):

```
len = 1, k = lg[1] = 0, 2^k = 1
blok kiri  : sp[0][3] = 3
blok kanan : sp[0][3 - 1 + 1] = sp[0][3] = 3
jawab 3     ✓
```

### 4.3 Kenapa `sum` gagal — demonstrasi

```
a = [1, 2, 3, 4, 5],  query [0, 4],  len = 5, k = 2

Kalau kita memaksakan sparse table untuk SUM:
   blok kiri  : sum a[0..3] = 1+2+3+4 = 10
   blok kanan : sum a[1..4] = 2+3+4+5 = 14
   "jawab"    : 10 + 14 = 24

   Jawaban BENAR: 1+2+3+4+5 = 15
   Selisihnya 9 = 2+3+4, yaitu daerah tumpang tindih yang terhitung DUA KALI.
```

Untuk `min`, terhitung dua kali tidak berpengaruh. Untuk `sum`, ia merusak
jawabannya. Itulah arti "idempoten" secara konkret.

### 4.4 Bahaya `std::log2`

```
Pada beberapa kompilator dan arsitektur:
   log2(8) menghasilkan 2.9999999999999996
   (int)2.9999999999999996 = 2

   Seharusnya k = 3 (karena 2^3 = 8), tetapi kita mendapat k = 2.
   Query [0, 7] akan memakai blok panjang 4 alih-alih 8:
       sp[2][0] = a[0..3],  sp[2][7-4+1] = sp[2][4] = a[4..7]
   Kebetulan ini MASIH BENAR untuk kasus ini!

   Tetapi untuk len yang bukan pangkat dua, k yang terlalu kecil bisa
   membuat kedua blok TIDAK menutupi seluruh rentang -> jawaban salah.
```

Bug ini bergantung lingkungan sehingga bisa lolos di mesinmu dan gagal di
juri. Pakai tabel precompute atau `__builtin_clz`.

---

## 📝 5. Variasi & Pattern

| Kalimat di soal | Yang dipakai |
| --------------- | ------------ |
| "minimum/maksimum pada rentang", tanpa update | **sparse table** |
| "gcd pada rentang", tanpa update | sparse table |
| "jumlah pada rentang", tanpa update | prefix sum (Day 29) |
| "jumlah pada rentang", **ada update** | Fenwick / segment tree (Day 170, 172) |
| "minimum pada rentang", **ada update** | segment tree |
| "di mana minimumnya" | sparse table yang menyimpan **indeks** |
| LCA pada pohon | Euler tour + sparse table (Day 202) |
| minimum pada **jendela geser** | monotonic deque (Day 37), lebih ringan |

### Pattern: sparse table untuk LCA

Euler tour mengubah pohon menjadi array, dan LCA menjadi *"simpul dengan
kedalaman minimum pada rentang"* — persis sparse table. Ini memberi LCA
dalam **O(1) per query** setelah preprocessing `O(n log n)`, mengalahkan
binary lifting yang `O(log n)` per query. Materi lengkapnya Day 202.

### Pattern: divide and conquer atas minimum

Beberapa soal memecah array di posisi minimumnya secara rekursif
(misalnya "jumlah minimum atas seluruh subarray"). Sparse table yang
mengembalikan **indeks** membuat pemecahan itu `O(1)` per langkah.

### Kapan JANGAN pakai sparse table

```
1. Ada UPDATE                -> segment tree / Fenwick
2. Operasinya sum atau XOR   -> prefix sum / prefix XOR (lebih sederhana)
3. n sangat besar (>= 1e6)   -> memori n log n mulai berat; segment tree O(n)
4. q kecil                   -> naif atau segment tree sudah cukup
5. Jendela geser ukuran tetap -> monotonic deque, O(n) total
```

---

## ⚠️ 6. Common Mistakes & Edge Cases

1. **Memakai sparse table untuk `sum` atau `XOR`.** Daerah tumpang tindih
   terhitung dua kali. Kompilasinya berhasil, jawabannya salah.

2. **`std::log2` alih-alih tabel atau builtin.** Bug yang bergantung lingkungan.

3. **Batas loop build `i < n` alih-alih `i + (1<<k) <= n`.** Membaca di luar array.

4. **Query memakai `r - (1<<k)` alih-alih `r - (1<<k) + 1`.** Off-by-one klasik.

5. **Mengira sparse table mendukung update.** Tidak. Satu update memaksa
   rebuild `O(n log n)`.

6. **Memori.** `n log n` untuk `n = 10^6` adalah 80 MB. Hitung dulu.

7. **`__builtin_clz(0)`** — perilaku tak terdefinisi. Pastikan `len >= 1`.

8. **Lupa `sp[0] = a`.** Basis tabelnya adalah array itu sendiri.

### Edge cases wajib diuji

```
n = 1                     -> K = 1, hanya sp[0]
query satu elemen (l == r) -> len = 1, k = 0, kedua blok sama
query seluruh array        -> len = n
len tepat pangkat dua      -> kedua blok identik, tidak ada tumpang tindih
len = 2^k + 1              -> tumpang tindih maksimal
seluruh elemen sama        -> jawabannya konstan
nilai negatif              -> tidak masalah untuk min/max
```

---

## 🏆 7. Tips Contest

**Pohon keputusan (10 detik pertama):**

```
Ada UPDATE?
  ├─ YA  -> segment tree (min/max/sum) atau Fenwick (sum)
  └─ TIDAK
       ├─ operasi SUM/XOR   -> prefix sum, O(n) build, O(1) query
       └─ operasi MIN/MAX/GCD -> sparse table, O(n log n) build, O(1) query
```

**Sparse table adalah struktur "tulis sekali, pakai sepanjang kontes".**
Simpan di template pribadimu — 15 baris, dan ia menghilangkan seluruh kelas
soal RMQ statis.

**Yang paling sering salah** bukan idenya, melainkan tiga detail:
batas loop `i + (1<<k) <= n`, awal blok kanan `r - (1<<k) + 1`, dan
cara menghitung `log2`. Verifikasi ketiganya dengan array kecil sebelum submit.

**Uji dengan array 4–6 elemen dan seluruh pasangan `(l, r)`** dibandingkan
brute force. Sepuluh detik, dan menangkap semua off-by-one.

---

## 📌 8. Ringkasan & Cheatsheet

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  SPARSE TABLE
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  sp[k][i] = op pada a[i .. i + 2^k - 1]

  BUILD  O(n log n):
    for (k = 1; k < K; k++)
        for (i = 0; i + (1 << k) <= n; i++)      <- BATAS, bukan i < n
            sp[k][i] = op(sp[k-1][i], sp[k-1][i + (1 << (k-1))]);

  QUERY  O(1):
    k = lg[r - l + 1];
    return op(sp[k][l], sp[k][r - (1 << k) + 1]);   <- +1, jangan lupa

  KENAPA BOLEH TUMPANG TINDIH: operasinya IDEMPOTEN, op(x,x) = x
    BISA  : min, max, gcd, lcm, AND, OR
    TIDAK : sum (x+x = 2x), XOR (x^x = 0), perkalian
            -> pakai PREFIX SUM (punya invers)

  log2 -- JANGAN pakai std::log2 (floating point, bisa meleset)
    tabel : lg[i] = lg[i/2] + 1          <- tercepat & teraman
    builtin: 31 - __builtin_clz(len)     <- clz(0) TAK TERDEFINISI

  TIDAK MENDUKUNG UPDATE. Satu update -> rebuild O(n log n).
  Memori n log n: n = 2e5 -> 14 MB ; n = 1e6 -> 80 MB (berisiko)

  POHON KEPUTUSAN
    ada update?          -> segment tree / Fenwick
    sum/xor tanpa update -> prefix sum
    min/max/gcd tanpa update -> SPARSE TABLE
    jendela geser tetap  -> monotonic deque (Day 37)

  VARIAN: simpan INDEKS untuk "di mana minimumnya" (dipakai LCA, Day 202)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### Soal latihan online

| Soal | Platform | Topik |
| ---- | -------- | ----- |
| [CSES 1647 — Static Range Minimum Queries](https://cses.fi/problemset/task/1647) | CSES | sparse table murni |
| [CSES 1646 — Static Range Sum Queries](https://cses.fi/problemset/task/1646) | CSES | (pembanding: prefix sum) |
| [SPOJ RMQSQ — Range Minimum Query](https://www.spoj.com/problems/RMQSQ/) | SPOJ | RMQ klasik |
| [SPOJ FREQUENT — Frequent Values](https://www.spoj.com/problems/FREQUENT/) | SPOJ | sparse table + kompresi |
| [Codeforces 475D — CGCDSSQ](https://codeforces.com/problemset/problem/475/D) | Codeforces | gcd pada rentang |
| [Codeforces 1000E / 689D](https://codeforces.com/problemset) | Codeforces | RMQ + binary search |
| [LeetCode 1521 — Find a Value of a Mysterious Function](https://leetcode.com/problems/find-a-value-of-a-mysterious-function-closest-to-target/) | LeetCode | AND pada rentang |
| [UVa 11235 — Frequent Values](https://onlinejudge.org/) | UVa | RMQ + run-length |

---

**Selanjutnya:** Day 170 — Fenwick Tree, yang menyelesaikan kelemahan terbesar
sparse table: **ia mendukung update**. Sparse table memberi query `O(1)` tetapi
array harus statis; Fenwick memberi `O(log n)` untuk keduanya.

Dan Day 202 — LCA dengan Euler tour + sparse table, yang memberi LCA dalam
`O(1)` per query dengan mengubah pohon menjadi masalah RMQ.
