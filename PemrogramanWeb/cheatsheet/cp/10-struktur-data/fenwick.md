# Fenwick Tree (BIT)

[← Sparse Table](sparse-table.md) · [Struktur data](README.md) · [Segment Tree →](segment-tree.md)

Day 170. Prefix sum yang bisa diubah. Di dalam struktur, indeks **wajib 1-based**. Array soal boleh 0-based: geser `+1` saat masuk, `-1` saat keluar.

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
```

## Daftar isi

- [Lowbit dan tanggung jawab](#lowbit-dan-tanggung-jawab)
- [Struct 1-based](#struct-1-based)
- [Query prefix dan rentang](#query-prefix-dan-rentang)
- [Build O(n)](#build-on)
- [Update rentang, baca titik](#update-rentang-baca-titik)
- [Update rentang, jumlah rentang](#update-rentang-jumlah-rentang)
- [Inversi](#inversi)
- [Urutan ke-k](#urutan-ke-k)
- [Dua dimensi singkat](#dua-dimensi-singkat)
- [Fenwick vs Segment Tree](#fenwick-vs-segment-tree)
- [Uji naif](#uji-naif)
- [Ringkasan](#ringkasan)

## Lowbit dan tanggung jawab

**Teori:** `lowbit(i) = i & -i` = bit 1 paling kanan dari i. Simpul `t[i]` menanggung `lowbit(i)` elemen terakhir yang berakhir di i (1-based):

```
t[i] = a[i-lowbit(i)+1] + ... + a[i]
```

Contoh:

| i | biner | lowbit | t[i] menanggung |
|---|---|---|---|
| 1 | 0001 | 1 | a[1] |
| 2 | 0010 | 2 | a[1]+a[2] |
| 3 | 0011 | 1 | a[3] |
| 4 | 0100 | 4 | a[1]+..+a[4] |
| 5 | 0101 | 1 | a[5] |
| 6 | 0110 | 2 | a[5]+a[6] |
| 8 | 1000 | 8 | a[1]+..+a[8] |

Update `a[i] += d`: naik ke semua blok yang memuat i, `i += lowbit(i)`.

Query prefix `a[1]+...+a[i]`: turun, jumlah blok yang menutupi `1..i` tanpa tumpang tindih, `i -= lowbit(i)`.

Kenapa benar: setiap i muncul di O(log n) blok. Setiap prefix terpecah jadi O(log n) blok disjoint. Itu sifat bit, bukan heuristik.

Analogi: tangga. Anak tangga ke-6 menanggung 2 pijakan. Anak tangga ke-4 menanggung 4 pijakan. Naik update = beri tahu semua tangga yang “mengangkat” kamu. Turun query = jumlah tangga yang menutupi dari sini ke tanah.

**Mengapa 1-based di dalam:** `lowbit(0) = 0`. Loop `i += 0` tidak pernah maju. Indeks 0 **dilarang** masuk `update`/`query`.

**Kapan:**

- Pakai: point update + prefix/range sum atau XOR, hitung inversi, frekuensi dinamis.
- Jangan: min/max/gcd pada rentang. Tidak ada invers bersih: `query(r) - query(l-1)` bukan min.
- Jangan: indeks 0.

**Proses:** n = 4, a 1-based `[_, 2, 1, 4, 3]`.

```
i      1    2    3    4
a      2    1    4    3
lowbit 1    2    1    4
t[i]   2    3    4   10
```

Prefix(3): i=3 ambil t[3]=4, i=3-1=2 ambil t[2]=3, i=0. Jumlah 7. Cek 2+1+4=7.

**Kode:**

```cpp
int lowbit(int i) { return i & -i; }
```

**Jebakan:** `i & -i` pada `int` 32-bit untuk i negatif tidak kamu butuhkan. Jaga i > 0. `unsigned` mengubah arti `-i`.

**Kompleksitas:** lowbit O(1). Update/query akan O(log n).

## Struct 1-based

**Teori:** vektor `t` berukuran `n+2` (cadangan `update(r+1)` pada difference). API publik memakai indeks 1..n. Jika soal 0-based, `update(i+1, d)`.

**Kapan:** setiap Fenwick jumlah/XOR.

**Proses:** mulai nol, `update(1, 2)`, `update(2, 1)`, `update(3, 4)`, `update(4, 3)` menghasilkan tabel di atas (build naif O(n log n)).

**Kode:**

```cpp
struct BIT {
    int n;
    vector<ll> t;

    void init(int n_) {
        n = n_;
        t.assign(n + 2, 0);
    }

    void update(int i, ll delta) {          // a[i] += delta, i 1-based
        for (; i <= n; i += i & -i) t[i] += delta;
    }

    ll query(int i) const {                 // jumlah a[1..i]
        ll s = 0;
        for (; i > 0; i -= i & -i) s += t[i];
        return s;
    }

    ll range(int l, int r) const {          // a[l]+...+a[r], 1-based
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};
```

Dokumentasi indeks:

```
soal 0-based a[0..n-1]
BIT  1-based t, update(i+1), range(l+1, r+1)
query(0) = 0  selalu, aman untuk range(1, r)
```

**Jebakan:** `update(0, x)` hang. `t.assign(n, 0)` lalu `update(n, x)` menulis `t[n]` keluar jika ukuran n (indeks 0..n-1). Pakai `n+2`.

**Kompleksitas:** update dan query O(log n), memori O(n). Konstanta kecil, sering 3–5× lebih cepat dari Segment Tree untuk jumlah.

## Query prefix dan rentang

**Teori:** jumlah punya invers. `[l, r] = prefix(r) − prefix(l−1)`. XOR sama: `query(r) ^ query(l-1)`. Min tidak.

**Kapan:** semua range sum. `l = 1` → `query(0) = 0`.

**Proses:** lanjut tabel t = `[_, 2, 3, 4, 10]`.

```
range(2,4) = query(4)-query(1) = 10-2 = 8
cek: 1+4+3 = 8

range(1,1) = query(1)-query(0) = 2
range(4,4) = 10-query(3) = 10-7 = 3
```

Update `a[1] += 5`:

```
i=1 t[1]+=5 → 7
i=2 t[2]+=5 → 8
i=4 t[4]+=5 → 15
prefix(3) = t[3]+t[2] = 4+8 = 12 = (2+5)+1+4
```

**Kode:**

```cpp
ll jumlahNaif(const vector<ll>& a, int l, int r) { // a 0-based, inklusif
    ll s = 0;
    for (int i = l; i <= r; i++) s += a[i];
    return s;
}

void contohRange() {
    vector<ll> a = {2, 1, 4, 3};
    BIT bit;
    bit.init((int)a.size());
    for (int i = 0; i < (int)a.size(); i++) bit.update(i + 1, a[i]);
    cout << bit.range(1, 3) << '\n';        // 7
}
```

**Jebakan:** `range(l, r)` dengan l,r 0-based tanpa geser. Mencampur `query` 1-based dengan loop 0-based di brute.

**Kompleksitas:** O(log n) per range.

## Build O(n)

**Teori:** `update` berulang O(n log n) benar. Build linear: isi `t[i] += a[i-1]`, teruskan ke ayah `i + lowbit(i)` sekali.

**Kapan:** inisialisasi dari array. Tetap benar jika kamu malas dan loop `update`.

**Proses:** a 0-based `{2,1,4,3}`.

```
i=1 t[1]+=2, ayah 2 ← +2    t=[0,2,2,0,0]
i=2 t[2]+=1, ayah 4 ← +3    t=[0,2,3,0,3]
i=3 t[3]+=4, ayah 4 ← +4    t=[0,2,3,4,7]
i=4 t[4]+=3, ayah 8 di luar t=[0,2,3,4,10]
```

Sama seperti sebelumnya.

**Kode:**

```cpp
void build(BIT& bit, const vector<ll>& a) { // a 0-based
    bit.init((int)a.size());
    for (int i = 1; i <= bit.n; i++) {
        bit.t[i] += a[i - 1];
        int j = i + (i & -i);
        if (j <= bit.n) bit.t[j] += bit.t[i];
    }
}
```

Atau method di dalam `struct BIT`:

```cpp
    void build(const vector<ll>& a) {
        init((int)a.size());
        for (int i = 1; i <= n; i++) {
            t[i] += a[i - 1];
            int j = i + (i & -i);
            if (j <= n) t[j] += t[i];
        }
    }
```

**Jebakan:** `t[j] += a[i-1]` bukan `t[i]` — ayah harus menerima jumlah blok anak yang sudah lengkap, yaitu `t[i]` setelah ditambah.

**Kompleksitas:** O(n).

## Update rentang, baca titik

**Teori:** difference array: `a[l..r] += v` menjadi `d[l]+=v`, `d[r+1]-=v`. Nilai `a[i] = prefix(d, i)`. Taruh `d` di Fenwick.

**Kapan:** banyak range-add, baca satu titik atau dump semua di akhir. Jangan jika kamu juga butuh jumlah rentang — lihat bagian berikutnya atau [lazy](lazy.md).

**Proses:** n = 5, semua nol. `rangeAdd(2,4,+3)` lalu `rangeAdd(1,3,+1)`.

```
setelah +3 pada [2,4]:
d:  0  +3  0  0  -3     (1-based posisi 1..5, d[5]=-3 karena r+1=5)
a:  0   3  3  3   0

setelah +1 pada [1,3]:
d: +1  +3  0 -1  -3
a:  1   4  4  3   0

pointQuery(3) = prefix d(3) = 1+3+0 = 4
```

**Kode:**

```cpp
struct BITRangePoint {
    BIT bit;
    explicit BITRangePoint(int n) { bit.init(n); }

    void rangeAdd(int l, int r, ll v) {     // 1-based inklusif
        bit.update(l, v);
        bit.update(r + 1, -v);
    }

    ll pointQuery(int i) const { return bit.query(i); }
};
```

**Jebakan:** `update(r+1)` butuh `t` berukuran ≥ n+2. `r = n` → indeks n+1. Lupa cadangan = out of bound sunyi atau crash.

**Kompleksitas:** O(log n) per operasi.

## Update rentang, jumlah rentang

**Teori:** setelah `+v` pada `[l, r]`, prefix sampai i bertambah `v * (banyak elemen terpengaruh)`. Itu fungsi linear terhadap i. Dua BIT: satu koefisien, satu konstanta.

Rumus yang dihafal:

```
rangeAdd(l, r, v):
  B1.update(l, v);   B1.update(r+1, -v)
  B2.update(l, v*(l-1)); B2.update(r+1, -v*r)

prefix(i) = B1.query(i)*i - B2.query(i)
range(l,r) = prefix(r)-prefix(l-1)
```

Kenapa: jika i di dalam `[l,r]`, tambahan prefix = `v * (i-l+1) = v*i - v*(l-1)`. B1 menyimpan v, B2 menyimpan v*(l-1).

**Kapan:** range add + range sum tanpa lazy. Lazy Segment Tree lebih umum (min + add). Dua BIT lebih pendek untuk **hanya jumlah**.

**Proses:** n = 4, nol. `rangeAdd(2, 4, +2)`.

```
i=1 prefix=0
i=2 prefix=2
i=3 prefix=4
i=4 prefix=6
range(2,3) = 4-0 = 4   (dua elemen bernilai 2)
```

**Kode:**

```cpp
struct BITRangeRange {
    BIT b1, b2;
    int n;
    explicit BITRangeRange(int n_) : n(n_) {
        b1.init(n_);
        b2.init(n_);
    }

    void rangeAdd(int l, int r, ll v) {
        b1.update(l, v);
        b1.update(r + 1, -v);
        b2.update(l, v * (l - 1));
        b2.update(r + 1, -v * r);
    }

    ll prefix(int i) const {
        if (i <= 0) return 0;
        return b1.query(i) * i - b2.query(i);
    }

    ll range(int l, int r) const { return prefix(r) - prefix(l - 1); }
};
```

**Jebakan:** mencampur BIT biasa (menyimpan a) dengan BIT difference tanpa nama. Overflow `v * (l-1)` — pakai `ll`. `r+1` lagi butuh n+2.

**Kompleksitas:** O(log n), memori 2n.

## Inversi

**Teori:** inversi = pasangan `i < j` dan `a[i] > a[j]`. Sapu dari **kanan**. BIT frekuensi nilai yang sudah dilihat. Di `a[i]`, `query(nilai-1)` = banyak yang lebih kecil di kanan = inversi dengan kiri = i. Lalu `update(nilai, 1)`.

Nilai sampai 10^18 wajib dikompresi dulu ke 1..n.

**Kapan:** hitung inversi O(n log n), “berapa lebih kecil di kanan”, versi 2D (lebih rumit).

**Proses:** `a = [3, 1, 2]`. Kompresi identitas 1,2,3.

```
i=2 nilai 2: BIT kosong, query(1)=0, masukkan 2
i=1 nilai 1: query(0)=0, masukkan 1
i=0 nilai 3: query(2)=2  → (3,1) dan (3,2)
inversi = 2
```

`a = [2, 2]`: inversi ketat `>` = 0. Kompresi unique: keduanya indeks 1. `query(0)=0`. Benar.

**Kode:**

```cpp
struct Kompres {
    vector<ll> v;
    void tambah(ll x) { v.push_back(x); }
    void bangun() {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
    }
    int idx(ll x) const {                   // 1-based
        return int(lower_bound(v.begin(), v.end(), x) - v.begin()) + 1;
    }
};

ll hitungInversi(vector<ll> a) {
    Kompres k;
    for (ll x : a) k.tambah(x);
    k.bangun();
    BIT bit;
    bit.init((int)k.v.size());
    ll inv = 0;
    for (int i = (int)a.size() - 1; i >= 0; i--) {
        int p = k.idx(a[i]);
        inv += bit.query(p - 1);
        bit.update(p, 1);
    }
    return inv;
}
```

**Jebakan:** sapu kiri lalu rumus “lebih besar” terbalik. Domain 10^9 tanpa kompresi → vektor mustahil. Inversi `>=` butuh `query(p)` bukan `p-1`.

**Kompleksitas:** O(n log n).

## Urutan ke-k

**Teori:** BIT sebagai multiset. `t[i]` = banyak elemen di blok. Cari indeks terkecil dengan prefix ≥ k: binary lifting di dalam pohon Fenwick, bit besar dulu.

**Kapan:** order statistic dinamis, “hapus median”, k-th setelah kompresi.

**Proses:** masukkan 1, 3, 3, 5 (nilai = indeks).

```
prefix: 1→1, 2→1, 3→3, 4→3, 5→4
k=1 → 1
k=2 → 3
k=3 → 3
k=4 → 5
```

**Kode:**

```cpp
int cariKeK(const BIT& bit, ll k) {         // 1-based, prefix >= k
    int pos = 0, n = bit.n;
    if (n <= 0) return 1;
    int pw = 1 << (31 - __builtin_clz(n));
    for (; pw > 0; pw >>= 1) {
        if (pos + pw <= n && bit.t[pos + pw] < k) {
            pos += pw;
            k -= bit.t[pos];
        }
    }
    return pos + 1;
}
```

**Jebakan:** `k` lebih besar dari jumlah elemen → hasil n+1 atau n, tidak bermakna. Akses `bit.t` mengandalkan layout 1-based. Setelah `update` hapus, jumlah berubah.

**Kompleksitas:** O(log n).

## Dua dimensi singkat

**Teori:** `update(x, y, d)` bersarang: loop x naik, di dalam y naik. Query prefix persegi `(1,1)..(x,y)`. Range persegi 4 prefix (inclusion-exclusion).

**Kapan:** n,m ≤ 1000, atau terkompresi. n = 10^5 murni 2D BIT O(n^2) memori tidak muat — kompres + Fenwick 2D pada titik jarang butuh struktur lain (atau cdq, offline).

**Proses:** matriks 2×2, tambah 5 di (1,1) 1-based. Prefix (2,2) = 5. Range (2,2)-(2,2) = 0.

**Kode:**

```cpp
struct BIT2D {
    int n, m;
    vector<vector<ll>> t;
    BIT2D(int n_, int m_) : n(n_), m(m_), t(n_ + 2, vector<ll>(m_ + 2)) {}

    void update(int x, int y, ll d) {
        for (int i = x; i <= n; i += i & -i)
            for (int j = y; j <= m; j += j & -j) t[i][j] += d;
    }

    ll query(int x, int y) const {
        ll s = 0;
        for (int i = x; i > 0; i -= i & -i)
            for (int j = y; j > 0; j -= j & -j) s += t[i][j];
        return s;
    }

    ll range(int x1, int y1, int x2, int y2) const {
        if (x1 > x2 || y1 > y2) return 0;
        return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1)
               + query(x1 - 1, y1 - 1);
    }
};
```

**Jebakan:** lupa `+ query(x1-1,y1-1)`. Indeks 0 di salah satu sumbu hang.

**Kompleksitas:** O(log n log m) per operasi, memori O(n m).

## Fenwick vs Segment Tree

**Teori:** keduanya O(log n). Fenwick menang kode dan konstanta untuk operasi berinvers. Segment Tree menang min, simpul kaya, lazy, persisten.

**Kapan:** jumlah/XOR + update titik → Fenwick dulu. Ragu → Segment Tree.

**Proses:** soal min `[l,r]` + set titik. Fenwick `range = query(r)-query(l-1)` salah. Tulis [segment-tree.md](segment-tree.md).

**Kode:** tidak ada pemenang universal.

**Jebakan:** memaksakan min ke Fenwick dengan “trick” yang hanya jalan untuk prefix min, bukan range bebas.

**Kompleksitas:** sama big-O, Fenwick lebih ramping.

## Uji naif

**Teori:** array kecil, acak update dan query, bandingkan loop. Geser +1 ke BIT.

**Kapan:** setiap kali menulis ulang `update`/`query`.

**Proses:** n ≤ 20, 50 operasi, seed 1..200.

**Kode:**

```cpp
bool cekBit(int n, int q, int seed) {
    mt19937 rng(seed);
    vector<ll> a(n);
    for (ll& x : a) x = int(rng() % 11) - 5;
    BIT bit;
    bit.build(a);
    for (int i = 0; i < q; i++) {
        if (rng() & 1) {
            int p = rng() % n;
            ll d = int(rng() % 11) - 5;
            a[p] += d;
            bit.update(p + 1, d);
        } else {
            int l = rng() % n, r = rng() % n;
            if (l > r) swap(l, r);
            if (bit.range(l + 1, r + 1) != jumlahNaif(a, l, r)) return false;
        }
    }
    return true;
}

int main() {
    FASTIO;
    for (int s = 1; s <= 200; s++)
        if (!cekBit(15, 80, s)) {
            cout << "WA seed=" << s << '\n';
            return 0;
        }
    cout << "ok\n";
}
```

**Jebakan:** brute 0-based, BIT 0-based. Selalu dokumentasikan: **di dalam, 1-based**.

**Kompleksitas:** tes kecil O(q n).

## Ringkasan

1. Fenwick = tangga `lowbit`. **Internal 1-based.** `i=0` hang.
2. Update naik `i += lowbit`, query prefix turun `i -= lowbit`.
3. Range sum = prefix r − prefix l−1. Min tidak.
4. Range add titik = difference + satu BIT. Range+range = dua BIT.
5. Inversi: sapu kanan + kompresi + BIT frekuensi.
6. Lebih pendek dari Segment Tree untuk jumlah; kalah untuk min dan lazy.

Latihan: Day 170 di `ComprogLearning/CP`. Jangan salin `exercise_*.cpp` ke folder ini.
