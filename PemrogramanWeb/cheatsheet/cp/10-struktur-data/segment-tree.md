# Segment Tree

[← Fenwick](fenwick.md) · [Struktur data](README.md) · [Lazy →](lazy.md)

Day 172. Pohon biner di atas array. Update titik dan query rentang O(log n) untuk **operasi asosiatif apa pun**, termasuk yang tidak punya invers (`min`, simpul kaya).

Indeks array data **0-based**. Simpul pohon **1-based** (`v=1` akar). `typedef long long ll`.

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
```

Wajib: `struct` dengan fungsi `build`, `update`, `query`. Bukan semua logika di `main`.

## Daftar isi

- [Pohon dan asosiatif](#pohon-dan-asosiatif)
- [Identitas](#identitas)
- [Struct jumlah](#struct-jumlah)
- [Simulasi angka](#simulasi-angka)
- [Struct minimum](#struct-minimum)
- [Simpul kaya Kadane](#simpul-kaya-kadane)
- [Jalan mencari posisi](#jalan-mencari-posisi)
- [Ukuran 4n](#ukuran-4n)
- [Iteratif singkat](#iteratif-singkat)
- [Uji naif](#uji-naif)
- [Ringkasan](#ringkasan)

## Pohon dan asosiatif

**Teori:** daun = satu elemen. Ayah = `gabung(kiri, kanan)`. Operasi `⊕` harus **asosiatif**: `(a⊕b)⊕c = a⊕(b⊕c)`. Jumlah, min, max, gcd, XOR, kali modulo — semua asosiatif.

Query `[ql, qr]` memotong rentang jadi O(log n) simpul yang sudah dihitung. Update titik menaiki satu jalur daun–akar, O(log n).

Kenapa O(log n): tinggi ≈ log₂ n. Di tiap tingkat, query mengambil paling banyak dua simpul (potongan kiri dan kanan).

Analogi: peta. Akar = seluruh kota. Anak kiri = barat, kanan = timur. Mau macet di beberapa kelurahan? Ambil kotak peta yang sudah jadi.

Beda dengan Fenwick: tidak butuh invers. `min(a,b)` tidak bisa “dikurangi”. Segment Tree tetap benar.

**Kapan:**

- Pakai: update + query rentang, operasi asosiatif, “cari posisi paling kiri yang prefix ≥ x”.
- Jangan: data statis + min — [Sparse Table](sparse-table.md) query O(1).
- Jangan: hanya jumlah + update titik dan kamu ingin kode 15 baris — [Fenwick](fenwick.md).
- Jangan: update **rentang** tanpa lazy — O(n) tersembunyi jika kamu loop `update` titik.

**Proses:** n = 4, a = `[2, 1, 4, 3]`, jumlah.

```
            v=1 [0..3] sum=10
           /                \
     v=2 [0..1] = 3      v=3 [2..3] = 7
      /        \          /        \
  v=4 [0]=2  v=5 [1]=1  v=6 [2]=4  v=7 [3]=3
```

**Kode:** kerangka `gabung` dulu.

```cpp
ll gabungSum(ll a, ll b) { return a + b; }
ll gabungMin(ll a, ll b) { return min(a, b); }
```

**Jebakan:** operasi tidak asosiatif (rata-rata mentah, modus) tidak muat di satu `ll` tanpa simpul kaya yang dirancang khusus.

**Kompleksitas:** build O(n), update/query O(log n), memori O(n).

## Identitas

**Teori:** query yang tidak menyentuh simpul mengembalikan **identitas** e dengan `gabung(e, x) = x`. Salah identitas = WA sunyi.

| Operasi | Identitas | Alasan |
|---|---|---|
| jumlah | 0 | 0+x = x |
| XOR | 0 | 0^x = x |
| min | `LLONG_MAX` | min(∞, x) = x |
| max | `LLONG_MIN` | max(−∞, x) = x |
| gcd | 0 | gcd(0, x) = x |
| kali | 1 | 1*x = x |

**Kapan:** setiap `query` cabang “di luar rentang”.

**Proses:** query min pada array `[3, -1]`. Identitas 0 → potongan kosong “menang” atas −1 jika kamu `min(0, jawaban)`. Salah. Identitas +∞.

**Kode:**

```cpp
const ll ID_SUM = 0;
const ll ID_MIN = (ll)4e18;
const ll ID_MAX = (ll)-4e18;
```

**Jebakan:** identitas min = 0. Array negatif hilang. Identitas Kadane `{0,0,0,0}` — lihat simpul kaya.

**Kompleksitas:** O(1) konsep.

## Struct jumlah

**Teori:** satu `struct SegTree` memegang `n` dan `t`. Tiga fungsi rekursif: `build`, `update` (set titik), `query`. Anak kiri `2*v` rentang `[l, m]`, kanan `2*v+1` rentang `[m+1, r]`, `m = (l+r)/2`.

**Kapan:** jumlah, XOR (ganti `+` jadi `^`, identitas 0).

**Proses:** lihat bagian simulasi. Pemanggilan dari luar selalu `v=1, l=0, r=n-1`.

**Kode:**

```cpp
struct SegTree {
    int n;
    vector<ll> t;

    explicit SegTree(int n_) : n(n_), t(4 * n_ + 4, 0) {}

    void build(int v, int l, int r, const vector<ll>& a) {
        if (l == r) {
            t[v] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(2 * v, l, m, a);
        build(2 * v + 1, m + 1, r, a);
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    void update(int v, int l, int r, int i, ll x) { // a[i] = x
        if (l == r) {
            t[v] = x;
            return;
        }
        int m = (l + r) / 2;
        if (i <= m) update(2 * v, l, m, i, x);
        else update(2 * v + 1, m + 1, r, i, x);
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    ll query(int v, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;     // identitas jumlah
        if (ql <= l && r <= qr) return t[v];
        int m = (l + r) / 2;
        return query(2 * v, l, m, ql, qr) + query(2 * v + 1, m + 1, r, ql, qr);
    }
};

struct SegSum {
    SegTree st;
    int n;
    explicit SegSum(const vector<ll>& a) : st((int)a.size()), n((int)a.size()) {
        if (n) st.build(1, 0, n - 1, a);
    }
    void setPos(int i, ll x) { st.update(1, 0, n - 1, i, x); }
    ll range(int l, int r) { return st.query(1, 0, n - 1, l, r); }
};
```

**Jebakan:** `m = (l+r)/2` lalu kiri `[l, m-1]` — bolong atau tak hingga. Recursion `update` lupa menulis ulang ayah `t[v] = ...`. `query` tanpa cabang kosong memakai `t[v]` pada simpul yang hanya sebagian overlap — dobel atau kurang.

**Kompleksitas:** build O(n), update/query O(log n).

## Simulasi angka

**Teori:** jejak rekursi pada contoh kecil. Ini yang kamu gambar saat WA.

**Kapan:** debug. Jika jawaban naif 5 dan pohon 9, gambar simpul.

**Proses:** a = `[2, 1, 4, 3]`. Query jumlah `[1, 2]` (nilai 1 dan 4).

```
1. query v=1 [0..3] vs [1,2]
   tidak di luar, tidak penuh → pecah m=1
2. kiri v=2 [0..1] vs [1,2]
   tidak penuh → pecah m=0
   v=4 [0..0] vs [1,2] → di luar → 0
   v=5 [1..1] vs [1,2] → penuh → 1
   kiri = 0+1 = 1
3. kanan v=3 [2..3] vs [1,2]
   tidak penuh → pecah m=2
   v=6 [2..2] penuh → 4
   v=7 [3..3] di luar → 0
   kanan = 4
4. jawaban 1+4 = 5
```

Update `a[1] = 8`:

```
daun v=5 = 8
ayah v=2 = 2+8 = 10
akar v=1 = 10+7 = 17
query [1,2] sekarang 8+4 = 12
```

**Kode:** `main` mini.

```cpp
int main() {
    FASTIO;
    vector<ll> a = {2, 1, 4, 3};
    SegSum seg(a);
    cout << seg.range(1, 2) << '\n';        // 5
    seg.setPos(1, 8);
    cout << seg.range(1, 2) << '\n';        // 12
}
```

**Jebakan:** mengira `setPos` adalah `+=`. API di atas **assign**. Untuk delta: baca dulu atau simpan array samping.

**Kompleksitas:** dua query contoh O(log n).

## Struct minimum

**Teori:** salin `SegTree`, ganti `+` jadi `min`, identitas `ID_MIN`.

**Kapan:** RMQ dinamis. Statis → Sparse Table.

**Proses:** a = `[5, 1, 9, 3]`. Query `[1, 3]` = 1. Set `a[1]=7`. Query `[1, 3]` = 3.

**Kode:**

```cpp
struct SegMin {
    int n;
    vector<ll> t;

    explicit SegMin(int n_) : n(n_), t(4 * n_ + 4, ID_MIN) {}

    void build(int v, int l, int r, const vector<ll>& a) {
        if (l == r) {
            t[v] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(2 * v, l, m, a);
        build(2 * v + 1, m + 1, r, a);
        t[v] = min(t[2 * v], t[2 * v + 1]);
    }

    void update(int v, int l, int r, int i, ll x) {
        if (l == r) {
            t[v] = x;
            return;
        }
        int m = (l + r) / 2;
        if (i <= m) update(2 * v, l, m, i, x);
        else update(2 * v + 1, m + 1, r, i, x);
        t[v] = min(t[2 * v], t[2 * v + 1]);
    }

    ll query(int v, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return ID_MIN;
        if (ql <= l && r <= qr) return t[v];
        int m = (l + r) / 2;
        return min(query(2 * v, l, m, ql, qr),
                   query(2 * v + 1, m + 1, r, ql, qr));
    }
};
```

Pembungkus:

```cpp
ll rangeMin(SegMin& st, int l, int r) {
    return st.query(1, 0, st.n - 1, l, r);
}
```

**Jebakan:** menyalin `SegTree` jumlah lalu ganti sebagian `+` — identitas masih 0. GCD: identitas 0, `t[v] = gcd(kiri, kanan)`.

**Kompleksitas:** sama O(log n).

## Simpul kaya Kadane

**Teori:** satu `ll` tidak cukup untuk “jumlah subarray maksimum pada `[L,R]`”. Simpul menyimpan `sum`, `pref`, `suf`, `ans`. Gabungan:

```
sum  = kiri.sum + kanan.sum
pref = max(kiri.pref, kiri.sum + kanan.pref)
suf  = max(kanan.suf, kanan.sum + kiri.suf)
ans  = max(kiri.ans, kanan.ans, kiri.suf + kanan.pref)
```

Benar karena subarray terbaik seluruhnya kiri, seluruhnya kanan, atau menyeberang tengah.

Identitas: `sum = 0`, `pref/suf/ans = −∞`. Jangan `{0,0,0,0}` — query kosong mengalahkan subarray negatif.

**Kapan:** CSES *Range Queries* varian subarray max, “longest consecutive ones” (field berbeda).

**Proses:** a = `[2, -5, 3]`.

```
daun 2:    sum=2  pref=2  suf=2  ans=2
daun -5:   sum=-5 pref=-5 suf=-5 ans=-5
daun 3:    sum=3  pref=3  suf=3  ans=3

gabung [-5,3]:
  sum=-2
  pref=max(-5, -5+3)=-2
  suf =max(3, 3-5)=3
  ans =max(-5, 3, -5+3)=3

gabung [2] + [-5,3]:
  sum=1
  pref=max(2, 2-2)=2
  suf =max(3, -2+2)=3
  ans =max(2, 3, 2+(-2))=3     elemen 3
```

Cek naif: `[2]=2`, `[-5]=-5`, `[3]=3`, `[2,-5]=-3`, `[-5,3]=-2`, `[2,-5,3]=0`. Max = 3.

**Kode:**

```cpp
struct Node {
    ll sum, pref, suf, ans;
};

Node buat(ll x) {
    Node p;
    p.sum = x;
    p.pref = p.suf = p.ans = x;             // satu elemen, boleh negatif
    return p;
}

Node gabung(const Node& a, const Node& b) {
    Node c;
    c.sum = a.sum + b.sum;
    c.pref = max(a.pref, a.sum + b.pref);
    c.suf = max(b.suf, b.sum + a.suf);
    c.ans = max({a.ans, b.ans, a.suf + b.pref});
    return c;
}

const Node ID_KAD = {0, (ll)-4e18, (ll)-4e18, (ll)-4e18};

struct SegKadane {
    int n;
    vector<Node> t;

    explicit SegKadane(const vector<ll>& a) : n((int)a.size()), t(4 * n + 4) {
        if (n) build(1, 0, n - 1, a);
    }

    void build(int v, int l, int r, const vector<ll>& a) {
        if (l == r) {
            t[v] = buat(a[l]);
            return;
        }
        int m = (l + r) / 2;
        build(2 * v, l, m, a);
        build(2 * v + 1, m + 1, r, a);
        t[v] = gabung(t[2 * v], t[2 * v + 1]);
    }

    void update(int v, int l, int r, int i, ll x) {
        if (l == r) {
            t[v] = buat(x);
            return;
        }
        int m = (l + r) / 2;
        if (i <= m) update(2 * v, l, m, i, x);
        else update(2 * v + 1, m + 1, r, i, x);
        t[v] = gabung(t[2 * v], t[2 * v + 1]);
    }

    Node query(int v, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return ID_KAD;
        if (ql <= l && r <= qr) return t[v];
        int m = (l + r) / 2;
        return gabung(query(2 * v, l, m, ql, qr),
                      query(2 * v + 1, m + 1, r, ql, qr));
    }
};
```

**Jebakan:** `gabung(ID, x)` harus = x. Jika `pref` identitas 0, array negatif rusak. `ans` satu elemen negatif harus elemen itu, bukan 0 (kecuali soal mengizinkan kosong).

**Kompleksitas:** tetap O(log n), konstanta naik.

## Jalan mencari posisi

**Teori:** “posisi paling kiri yang prefix sum ≥ k” berjalan di pohon. Jika jumlah kiri ≥ sisa, ke kiri; jika tidak, kurangi dan ke kanan.

**Kapan:** order statistic pada array 0/1, “k-th satu”, lower_bound pada prefix.

**Proses:** a = `[1, 0, 1, 1]`, k = 2 (satu ke-2). Prefix: 1,1,2,3. Jawaban indeks 2.

```
akar sum=3 >= 2, kiri sum=1 < 2 → sisa 1, ke kanan
kanan [2,3] sum=2, kiri daun 1 >= 1 → indeks 2
```

**Kode:**

```cpp
int jalanKiri(const SegTree& st, int v, int l, int r, ll& sisa) {
    if (st.t[v] < sisa) {
        sisa -= st.t[v];
        return -1;
    }
    if (l == r) return l;
    int m = (l + r) / 2;
    int kiri = jalanKiri(st, 2 * v, l, m, sisa);
    if (kiri != -1) return kiri;
    return jalanKiri(st, 2 * v + 1, m + 1, r, sisa);
}

int posisiPrefix(SegTree& st, ll k) {
    if (k <= 0 || st.n == 0 || st.t[1] < k) return -1;
    return jalanKiri(st, 1, 0, st.n - 1, k);
}
```

**Jebakan:** `sisa` harus referensi — cabang kanan memakai sisa yang sudah dikurangi. Memanggil jalan pada pohon min tanpa arti prefix.

**Kompleksitas:** O(log n).

## Ukuran 4n

**Teori:** heap-like index `2*v`. Untuk n bukan pangkat dua, indeks simpul bisa mendekati 4n. `vector(2*n)` **bocor** pada banyak n.

Aturan praktis: `t(4*n + 4)`.

**Kapan:** selalu. n = 1: 4+4 aman.

**Proses:** n = 5. Daun tidak rapi di `n..2n`. Simpul `v=13` bisa muncul. `2*n=10` tidak cukup.

**Kode:**

```cpp
int kapasitas(int n) { return 4 * n + 4; }
```

**Jebakan:** `t(2*n)` lulus tes n=8, WA/crash n=7. Jangan hemat 4n di kontes.

**Kompleksitas:** memori O(n).

## Iteratif singkat

**Teori:** pohon iteratif: daun di `t[n+i]`, ayah `i/2`. Query geser `l,r` di ruang daun. Lebih cepat konstanta, mudah salah off-by-one. Untuk belajar, rekursif dulu.

**Kapan:** setelah rekursif AC, jika TLE konstanta (jarang untuk n=2e5).

**Proses:** n dibulatkan ke pangkat dua, atau pakai n asli dengan hati-hati pada batas.

**Kode:** jumlah iteratif (daun di `n..`):

```cpp
struct SegIter {
    int n;
    vector<ll> t;
    explicit SegIter(int n_) : n(n_), t(2 * n_) {}

    void build(const vector<ll>& a) {
        for (int i = 0; i < n; i++) t[n + i] = a[i];
        for (int i = n - 1; i > 0; i--) t[i] = t[2 * i] + t[2 * i + 1];
    }

    void update(int i, ll x) {
        for (t[i += n] = x; i > 1; i >>= 1) t[i >> 1] = t[i] + t[i ^ 1];
    }

    ll query(int l, int r) {                // [l, r) eksklusif kanan
        ll res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += t[l++];
            if (r & 1) res += t[--r];
        }
        return res;
    }
};
```

**Jebakan:** campur `[l,r]` inklusif dengan `[l,r)` iteratif. Template ini **kanan eksklusif**. Rekursif di atas **inklusif**.

**Kompleksitas:** O(log n), konstanta lebih kecil.

## Uji naif

**Teori:** assign acak + query, banding loop. Wajib sebelum soal.

**Kapan:** setiap ganti `gabung`.

**Proses:** n=12, 100 operasi.

**Kode:**

```cpp
ll jumlahNaif(const vector<ll>& a, int l, int r) {
    ll s = 0;
    for (int i = l; i <= r; i++) s += a[i];
    return s;
}

bool cekSeg(int n, int q, int seed) {
    mt19937 rng(seed);
    vector<ll> a(n);
    for (ll& x : a) x = int(rng() % 11) - 5;
    SegSum seg(a);
    for (int i = 0; i < q; i++) {
        if (rng() & 1) {
            int p = rng() % n;
            ll x = int(rng() % 11) - 5;
            a[p] = x;
            seg.setPos(p, x);
        } else {
            int l = rng() % n, r = rng() % n;
            if (l > r) swap(l, r);
            if (seg.range(l, r) != jumlahNaif(a, l, r)) return false;
        }
    }
    return true;
}

int main() {
    FASTIO;
    for (int s = 1; s <= 200; s++)
        if (!cekSeg(16, 80, s)) {
            cout << "WA seed=" << s << '\n';
            return 0;
        }
    cout << "ok\n";
}
```

**Jebakan:** n=0 constructor `4*0+4` aman, `build` jangan dipanggil. n=1 query `[0,0]`.

**Kompleksitas:** tes O(q n).

## Ringkasan

1. Segment Tree = pohon asosiatif. `struct` + `build` + `update` + `query`.
2. Identitas harus cocok operasi. Min ≠ 0.
3. Array 0-based, simpul `v=1`, anak `2v` dan `2v+1`, ukuran `4n`.
4. Fenwick lebih pendek untuk jumlah. Sparse Table lebih cepat untuk min statis.
5. Simpul kaya: simpan semua yang perlu untuk `gabung`.
6. Update rentang → [lazy.md](lazy.md). Versi lama → [persistent-sqrt-mo.md](persistent-sqrt-mo.md).

Latihan Day 172 di `ComprogLearning/CP`. Jangan salin berkas latihan ke sini.
