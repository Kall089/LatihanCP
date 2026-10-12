# 16 — Fenwick, Segment Tree, lazy, Sparse Table, Mo

[← 15 DP lanjut](15-dp-bitmask-digit-tree-optim.md) · [README](README.md) · [Lanjut 17 →](17-pohon-lca-hld-centroid.md)

Folder 10 di `DAFTAR-MATERI`: struktur data untuk **query rentang**. Setelah prefix sum dan monotonic deque (file 03–04), kamu butuh struktur yang tetap cepat kalau datanya **berubah**.

Latihan harian: `ComProgLearning/CP` Day 169 (Sparse Table), 170 (Fenwick), 172 (Segment Tree), 176 (lazy), 183 (sqrt & Mo).

Semua indeks array di kode **0-based**, kecuali Fenwick yang **1-based** di dalam struktur. `typedef long long ll`. Fungsi terpisah, bukan semua logika di `main`.

## Daftar isi

- [Peta empat struktur](#peta-empat-struktur)
- [Fenwick Tree (BIT)](#fenwick-tree-bit)
- [BIT: update rentang, query titik](#bit-update-rentang-query-titik)
- [BIT: inversi dan urutan ke-k](#bit-inversi-dan-urutan-ke-k)
- [Segment Tree](#segment-tree)
- [Segment Tree: simpul kaya](#segment-tree-simpul-kaya)
- [Lazy propagation — ide](#lazy-propagation--ide)
- [Sparse Table](#sparse-table)
- [Sqrt decomposition](#sqrt-decomposition)
- [Algoritma Mo](#algoritma-mo)
- [Tabel pilih struktur](#tabel-pilih-struktur)
- [Resep cepat](#resep-cepat)
- [Ringkasan](#ringkasan)

## Peta empat struktur

**Teori:** empat alat ini menjawab pertanyaan sejenis: “berapa jumlah / minimum / gcd pada `a[l..r]`?” Perbedaannya hanya dua: apakah array **boleh diubah**, dan apakah operasinya punya **invers** atau **idempoten**.

| Struktur | Update | Query | Syarat operasi | Analogi |
| --- | --- | --- | --- | --- |
| Prefix sum | tidak | O(1) | ada invers (`+`, `XOR`) | buku kas yang sudah dijumlah dari halaman 1 |
| Sparse table | tidak | O(1) | idempoten (`min`, `gcd`) | foto setiap blok panjang 1, 2, 4, 8 |
| Fenwick (BIT) | O(log n) | O(log n) | ada invers | tangga yang tiap anak tangga menanggung blok `lowbit` |
| Segment tree | O(log n) | O(log n) | asosiatif saja | pohon biner: kiri + kanan = ayah |

**Kapan dipakai / kapan tidak.**

- Ada update dan operasi `+` / `XOR` → Fenwick dulu (kode pendek).
- Ada update dan operasi `min` / gabungan aneh → Segment Tree.
- Tidak ada update, `min`/`max`/`gcd`, banyak query → Sparse Table.
- Tidak ada update, `sum`/`XOR` → prefix sum, bukan struktur ini.
- Query offline yang “keadaan jendela” sulit digabung → Mo atau sqrt.

**Proses:** soal “jumlah `a[l..r]`, kadang `a[i] += x`”. Prefix sum kalah karena harus dibangun ulang. Sparse table kalah karena tidak bisa update. Tersisa Fenwick dan Segment Tree. Untuk jumlah, keduanya benar; Fenwick lebih pendek.

**Jebakan:**

- Memakai Sparse Table lalu ada satu update — seluruh tabel harus dibangun ulang O(n log n).
- Memakai Fenwick untuk `min` — `range = query(r) - query(l-1)` tidak berlaku.
- Mengira Segment Tree selalu lebih lambat dari Fenwick. Konstantanya memang lebih besar, tetapi keduanya O(log n).

**Kompleksitas:** lihat tabel di atas. Memori: prefix O(n), Fenwick O(n), Segment Tree O(n), Sparse Table O(n log n).

## Fenwick Tree (BIT)

**Teori:** Fenwick menyimpan jumlah pada blok yang panjangnya **bit terendah** dari indeks. `lowbit(i) = i & -i`. Indeks `6 = 110₂` punya `lowbit = 2`, jadi `t[6]` menanggung `a[5]` dan `a[6]` (jika 1-based: posisi 5..6). Update berjalan naik ke semua blok yang memuat `i`. Query prefix berjalan turun, menjumlah blok yang menutupi `1..i`. Karena jumlah punya invers, rentang `[l, r]` = prefix `r` dikurangi prefix `l-1`.

Kenapa benar: setiap posisi `i` muncul di tepat `O(log n)` blok, dan setiap prefix bisa dipecah menjadi `O(log n)` blok yang tidak tumpang tindih. Itu sifat bilangan dan bit, bukan keajaiban.

**Kapan dipakai / kapan tidak.**

- Pakai: point update + prefix/range sum, hitung inversi, frekuensi dinamis, “nilai ke-k”.
- Jangan: `min`, `max`, `gcd` pada rentang (tidak ada invers yang bersih).
- Jangan: indeks 0. `0 & -0 = 0`, loop `i += 0` menggantung.

**Proses:** array 1-based `a = [_, 2, 1, 4, 3]`, `n = 4`.

```
i     1    2    3    4
a     2    1    4    3
lowbit 1    2    1    4
t[i]  a1  a1+a2  a3  a1+..+a4
      2     3    4     10
```

Query prefix(3): mulai `i=3`, ambil `t[3]=4`, `i -= 1` jadi 2, ambil `t[2]=3`, `i -= 2` jadi 0. Jumlah 7. Cek: 2+1+4=7.

Update `a[1] += 5`: `i=1`, `t[1]+=5` → 7; `i=2`, `t[2]+=5` → 8; `i=4`, `t[4]+=5` → 15. Prefix(3) sekarang 12 = 7+1+4.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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

    ll range(int l, int r) const {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }

    void build(const vector<ll>& a) {       // a 0-based, isi ke 1..n
        init((int)a.size());
        for (int i = 1; i <= n; i++) {
            t[i] += a[i - 1];
            int j = i + (i & -i);
            if (j <= n) t[j] += t[i];
        }
    }
};

ll jumlahNaif(const vector<ll>& a, int l, int r) { // 0-based, inklusif
    ll s = 0;
    for (int i = l; i <= r; i++) s += a[i];
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<ll> a = {2, 1, 4, 3};
    BIT bit;
    bit.build(a);
    cout << bit.range(1, 3) << '\n';        // 7
    bit.update(1, 5);
    a[0] += 5;
    cout << bit.range(1, 3) << ' ' << jumlahNaif(a, 0, 2) << '\n';
}
```

**Jebakan:**

- Indeks 0 masuk `update` → hang.
- `range(l, r)` lupa `query(l-1)` bisa dipanggil dengan `l=1` — itu aman, `query(0)=0`.
- Build O(n log n) dengan `update` berulang juga benar, tetapi `build` di atas O(n).
- Soal 0-based: geser `+1` saat masuk BIT, `-1` saat keluar.

**Kompleksitas:** update dan query O(log n), memori O(n), konstanta kecil (sering 3–5× lebih cepat dari Segment Tree untuk jumlah).

## BIT: update rentang, query titik

**Teori:** difference array (file 03) mengubah “tambah `v` pada `[l, r]`” menjadi dua update titik: `d[l]+=v`, `d[r+1]-=v`. Nilai asli `a[i]` adalah prefix `d[1]+...+d[i]`. Taruh `d` di Fenwick: update rentang jadi dua `update`, baca titik jadi satu `query` prefix.

**Kapan dipakai / kapan tidak.**

- Pakai: banyak range-add, lalu baca nilai satu posisi, atau baca semua di akhir.
- Jangan: butuh jumlah rentang **dan** update rentang sekaligus — itu butuh dua BIT atau lazy Segment Tree.

**Proses:** `n=5`, semua nol. `rangeAdd(2, 4, +3)`.

```
d:  1  2  3  4  5
    0 +3  0  0 -3
a:  0  3  3  3  0     karena prefix d
```

Lalu `rangeAdd(1, 3, +1)`:

```
d: +1 +3  0 -1 -3
a:  1  4  4  3  0
```

`pointQuery(3)` = prefix(3) = 1+3+0 = 4.

**Kode:**

```cpp
struct BITRangePoint {
    BIT bit;
    BITRangePoint(int n) { bit.init(n); }

    void rangeAdd(int l, int r, ll v) {     // 1-based inklusif
        bit.update(l, v);
        bit.update(r + 1, -v);
    }

    ll pointQuery(int i) const { return bit.query(i); }
};
```

Varian **range add + range sum** memakai dua BIT. Rumusnya kaku; hafalkan atau pakai lazy.

```cpp
struct BITRangeRange {
    BIT b1, b2;
    int n;
    BITRangeRange(int n_) : n(n_) { b1.init(n_); b2.init(n_); }

    void rangeAdd(int l, int r, ll v) {
        b1.update(l, v);
        b1.update(r + 1, -v);
        b2.update(l, v * (l - 1));
        b2.update(r + 1, -v * r);
    }

    ll prefix(int i) const { return b1.query(i) * i - b2.query(i); }
    ll range(int l, int r) const { return prefix(r) - prefix(l - 1); }
};
```

Kenapa dua BIT: setelah menambahkan `v` pada `[l, r]`, prefix sampai `i` bertambah `v * (banyak posisi terpengaruh)`. Itu fungsi linear terhadap `i`, jadi satu BIT menyimpan koefisien, satu lagi menyimpan konstanta.

**Jebakan:** `update(r+1)` butuh array ukuran `n+2`. Lupa `n+2` → akses di luar. Jangan campur BIT biasa (menyimpan `a`) dengan BIT difference (menyimpan `d`) tanpa komentar.

**Kompleksitas:** sama O(log n) per operasi. Dua BIT = dua kali memori, masih O(n).

## BIT: inversi dan urutan ke-k

**Teori:** inversi = pasangan `i < j` dengan `a[i] > a[j]`. Sapu dari **kanan**. BIT menyimpan frekuensi nilai yang sudah dilihat. Saat di `a[i]`, jumlah nilai **lebih kecil** yang sudah ada = banyak inversi yang melibatkan `i` sebagai kiri. Lalu masukkan `a[i]` ke BIT.

Urutan ke-k: BIT sebagai multiset. `t[i]` = banyak elemen di blok itu. Naik dari bit besar: jika `t[pos+pw] < k`, lompat ke kanan dan kurangi `k`. Ini binary lifting di dalam pohon Fenwick.

**Kapan dipakai / kapan tidak.**

- Pakai: hitung inversi O(n log n), “berapa yang lebih kecil di kanan”, order-statistic dinamis jika domain bisa dikompresi.
- Jangan: nilai sampai 10^18 tanpa kompresi — indeks BIT meledak.
- `std::multiset` lebih mudah jika n kecil atau operasi campur yang tidak cocok BIT.

**Proses:** `a = [3, 1, 2]`. Kompresi: 1→1, 2→2, 3→3.

```
i=2 (nilai 2): BIT kosong, lebih kecil = 0, masukkan 2
i=1 (nilai 1): query(0)=0, masukkan 1
i=0 (nilai 3): query(2)=2  → dua yang lebih kecil di kanan
inversi = 0+0+2 = 2     pasangan (3,1) dan (3,2)
```

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
    bit.init(k.v.size());
    ll inv = 0;
    for (int i = (int)a.size() - 1; i >= 0; i--) {
        int p = k.idx(a[i]);
        inv += bit.query(p - 1);
        bit.update(p, 1);
    }
    return inv;
}

int cariKeK(const BIT& bit, ll k) {         // indeks 1-based terkecil, prefix >= k
    int pos = 0, n = bit.n;
    if (n <= 0) return 1;
    for (int pw = 1 << (31 - __builtin_clz(n)); pw > 0; pw >>= 1) {
        if (pos + pw <= n && bit.t[pos + pw] < k) {
            pos += pw;
            k -= bit.t[pos];
        }
    }
    return pos + 1;
}
```

**Jebakan:** sapu dari kiri lalu menghitung “lebih besar” tanpa membalik rumus — mudah terbalik. Duplikat: kompresi `unique` membuat nilai sama berbagi indeks; untuk inversi ketat `>` itu benar. `cariKeK` rusak jika `k` lebih besar dari jumlah elemen.

**Kompleksitas:** inversi O(n log n) waktu, O(n) memori. `cariKeK` O(log n).

## Segment Tree

**Teori:** pecah array jadi pohon. Daun = satu elemen. Ayah = gabungan dua anak. Operasi harus **asosiatif**: `(a⊕b)⊕c = a⊕(b⊕c)`. Jumlah, min, max, gcd, XOR, perkalian modulo, semua asosiatif. Query `[L, R]` memotong rentang menjadi O(log n) simpul yang sudah dihitung. Update titik menaiki satu jalur ke akar, O(log n).

Kenapa O(log n): tinggi pohon ≈ log₂ n. Query tidak pernah mengambil lebih dari dua simpul per tingkat (gambar standar: potongan kiri dan kanan).

Analogi: peta kota. Simpul akar = seluruh jalan. Anak kiri = barat, anak kanan = timur. Mau tahu macet di beberapa kelurahan? Ambil kotak peta yang sudah jadi, jangan hitung tiap rumah.

**Kapan dipakai / kapan tidak.**

- Pakai: update + query rentang, operasi asosiatif apa pun, termasuk yang **tidak** punya invers.
- Pakai: “cari posisi paling kiri yang jumlahnya ≥ x” (jalan di pohon).
- Jangan: data statis + min — Sparse Table lebih cepat di query.
- Jangan: n = 10^7 di memori ketat jika kamu mengalokasi `vector(4*n)` of fat struct.

**Proses:** `a = [2, 1, 4, 3]`, 0-based, simpul 1-based di pohon.

```
            v=1 [0..3] sum=10
           /                \
     v=2 [0..1] = 3      v=3 [2..3] = 7
      /        \          /        \
  v=4 [0]=2  v=5 [1]=1  v=6 [2]=4  v=7 [3]=3
```

Query `[1, 2]` (nilai 1 dan 4):

1. Akar `[0..3]` tidak termuat penuh, pecah.
2. Kiri `[0..1]`: potong jadi daun `v=5` = 1.
3. Kanan `[2..3]`: potong jadi daun `v=6` = 4.
4. Jawaban 5.

Update `a[1] = 8`: daun `v=5` jadi 8, ayah `v=2` jadi 10, akar jadi 17.

**Kode:**

```cpp
struct SegTree {
    int n;
    vector<ll> t;

    SegTree(int n_) : n(n_), t(4 * n_ + 4, 0) {}

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
        if (qr < l || r < ql) return 0;     // identitas penjumlahan
        if (ql <= l && r <= qr) return t[v];
        int m = (l + r) / 2;
        return query(2 * v, l, m, ql, qr) + query(2 * v + 1, m + 1, r, ql, qr);
    }
};

// pembungkus biar pemanggilan pendek
struct SegSum {
    SegTree st;
    int n;
    SegSum(const vector<ll>& a) : st((int)a.size()), n((int)a.size()) {
        if (n) st.build(1, 0, n - 1, a);
    }
    void setPos(int i, ll x) { st.update(1, 0, n - 1, i, x); }
    ll range(int l, int r) { return st.query(1, 0, n - 1, l, r); }
};
```

Identitas harus cocok operasi:

| Operasi | Identitas (simpul kosong) |
| --- | --- |
| jumlah | 0 |
| XOR | 0 |
| min | `+∞` (`LLONG_MAX`) |
| max | `−∞` (`LLONG_MIN`) |
| gcd | 0 (`gcd(0, x) = x`) |
| perkalian | 1 |

**Jebakan:**

- Ukuran `2*n` kadang cukup di n pangkat dua, sering **bocor** — pakai `4*n`.
- Identitas min = 0 → minimum negatif hilang.
- `m = (l+r)/2` lalu anak kiri `[l, m]`, kanan `[m+1, r]`. Jangan `[l, m-1]`.
- Recursion depth aman untuk n ≤ 2·10^6 di C++ biasa; jangan khawatir stack kecuali n raksasa + compiler ketat.

**Kompleksitas:** build O(n), update/query O(log n), memori O(n).

## Segment Tree: simpul kaya

**Teori:** simpul tidak harus menyimpan satu angka. Ia bisa menyimpan **beberapa ringkasan** yang cukup untuk menggabungkan dua sisi. Contoh klasik: jumlah subarray maksimum (Kadane per segmen). Simpul butuh `sum`, `pref`, `suf`, `ans`. Gabungan:

```
sum  = kiri.sum + kanan.sum
pref = max(kiri.pref, kiri.sum + kanan.pref)
suf  = max(kanan.suf, kanan.sum + kiri.suf)
ans  = max(kiri.ans, kanan.ans, kiri.suf + kanan.pref)
```

Ini benar karena subarray terbaik di `[L, R]` seluruhnya di kiri, seluruhnya di kanan, atau menyeberang tengah. Tiga kasus itu tercakup.

**Kapan dipakai / kapan tidak.**

- Pakai: query “subarray max pada rentang”, “longest consecutive”, “berapa segmen bagus”.
- Jangan: memaksa satu `ll` jika gabungan butuh lebih dari satu angka.

**Proses:** `a = [2, -5, 3]`.

```
daun [2]:        sum=2, pref=2, suf=2, ans=2
daun [-5]:       sum=-5, pref=-5, suf=-5, ans=-5
daun [3]:        sum=3, pref=3, suf=3, ans=3
gabung [-5,3]:   sum=-2, pref=max(-5,-5+3)=-2, suf=max(3,3-5)=3, ans=max(-5,3,-5+3)=3
gabung semua:    sum=1, pref=max(2,2-2)=2, suf=max(3,-2+2)=3,
                 ans=max(2, 3, 2 + (-2) wait: kiri.suf + kanan.pref = 2 + (-2) = 0)
                 ans = max(2, 3, 0) = 3     yaitu elemen 3
```

**Kode:**

```cpp
struct Node {
    ll sum, pref, suf, ans;
};

Node buat(ll x) {
    Node p;
    p.sum = x;
    p.pref = p.suf = p.ans = x;             // satu elemen: boleh negatif
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

const Node ID = {0, (ll)-4e18, (ll)-4e18, (ll)-4e18};

struct SegKadane {
    int n;
    vector<Node> t;
    SegKadane(const vector<ll>& a) : n((int)a.size()), t(4 * n + 4) {
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
    Node query(int v, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return ID;
        if (ql <= l && r <= qr) return t[v];
        int m = (l + r) / 2;
        return gabung(query(2 * v, l, m, ql, qr),
                      query(2 * v + 1, m + 1, r, ql, qr));
    }
};
```

Jalan di pohon (cari kiri-paling yang prefix ≥ k):

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
```

**Jebakan:** identitas Kadane jangan `{0,0,0,0}` — query kosong akan “menang” atas subarray negatif. `gabung(ID, x)` harus = `x` untuk sisi yang valid; `pref/suf/ans` identitas harus −∞, `sum` 0.

**Kompleksitas:** tetap O(log n) per query; konstanta naik karena struct lebih gemuk.

## Lazy propagation — ide

**Teori:** update satu titik murah. Update **satu juta posisi** satu-satu mahal. Ide lazy: kalau sebuah simpul **seluruhnya** masuk rentang update, jangan turun ke daun. Tandai “anak-anakku nanti harus ditambah `v`”, lalu selesai. Tanda itu disebut **lazy**. Baru ketika suatu query/update **butuh** anak, tanda didorong ke bawah (`push`).

Kenapa benar: simpul menyimpan nilai **sudah termasuk** update yang tertunda di dirinya. Anak belum tahu. `push` menerapkan angka yang sama ke dua anak, lalu mengosongkan lazy ayah. Urutan “tulis dulu di ayah, turunkan saat perlu” setara menulis ke semua daun, hanya ditunda.

Analogi: pengumuman kelas. Kepala sekolah menempel kertas di pintu gedung: “semua siswa lantai 2 +10 poin.” Tidak perlu menemui tiap siswa sekarang. Saat kamu membuka pintu kelas, baru kertas itu disalin ke papan kelas.

Dua jenis lazy yang sering:

1. **Range add:** `a[i] += v` untuk semua i di `[L, R]`.
2. **Range assign:** `a[i] = v` untuk semua i di `[L, R]`. Assign menimpa add yang belum didorong — butuh prioritas.

**Kapan dipakai / kapan tidak.**

- Pakai: update rentang + query rentang, n,q sampai 2·10^5.
- Jangan: hanya point update — lazy hanya menambah bug.
- Jangan: update yang tidak seragam di seluruh segmen (misalnya “tambah i pada posisi i”) tanpa rumus tertutup.

**Proses:** `a = [1, 2, 3, 4]`. Update add +5 pada `[1, 2]` (nilai 2 dan 3).

```
Akar [0..3] tidak termuat penuh → pecah
Kiri [0..1]: tidak penuh → pecah
  daun [1]: apply +5, sum daun jadi 7
Kanan [2..3]: tidak penuh → pecah
  daun [2]: apply +5, sum daun jadi 8
Naik: kiri sum = 1+7=8, kanan = 8+4=12, akar = 20
```

Jika n besar dan `[0, 3]` di-update sekaligus: `apply` di akar saja, `lz[akar]=+5`, `t[akar]+=5*4`. Daun belum disentuh. Query `[0, 0]` baru `push` ke bawah.

**Kode:**

```cpp
struct LazyAdd {
    int n;
    vector<ll> t, lz;

    LazyAdd(int n_) : n(n_), t(4 * n_ + 4, 0), lz(4 * n_ + 4, 0) {}

    void apply(int v, int l, int r, ll add) {
        t[v] += add * (r - l + 1);
        lz[v] += add;
    }

    void push(int v, int l, int r) {
        if (lz[v] == 0 || l == r) return;
        int m = (l + r) / 2;
        apply(2 * v, l, m, lz[v]);
        apply(2 * v + 1, m + 1, r, lz[v]);
        lz[v] = 0;
    }

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

    void update(int v, int l, int r, int ql, int qr, ll add) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            apply(v, l, r, add);
            return;
        }
        push(v, l, r);
        int m = (l + r) / 2;
        update(2 * v, l, m, ql, qr, add);
        update(2 * v + 1, m + 1, r, ql, qr, add);
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    ll query(int v, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return t[v];
        push(v, l, r);
        int m = (l + r) / 2;
        return query(2 * v, l, m, ql, qr) + query(2 * v + 1, m + 1, r, ql, qr);
    }
};
```

Ide **persisten** (Day 179, singkat): update tidak menimpa simpul lama. Tiap update membuat O(log n) simpul baru di jalur akar–daun. Akar versi `k` tetap hidup. Berguna untuk “kembalikan array ke versi dulu” atau “k-th pada prefix”. Jangan tulis persisten di kontes 2 jam kecuali sudah hafal; untuk latihan, pahami dulu bahwa **versi = akar baru**.

**Jebakan:**

- Lupa `push` sebelum turun — anak memakai nilai basi.
- `apply` menambah `v * panjang`, tetapi lazy hanya menyimpan `v` (bukan `v * panjang`). Jangan dobel.
- Recursion `update` yang sudah `apply` di simpul penuh **tidak** boleh `push` dulu lalu menimpa.
- Range assign + range add campur: butuh dua tanda atau satu tanda dengan tipe.

**Kompleksitas:** update/query tetap O(log n). Memori O(n). Persisten: O(n + q log n) simpul.

## Sparse Table

**Teori:** precompute semua blok panjang **pangkat dua**. `sp[k][i] = op(a[i .. i+2^k-1])`. Blok panjang `2^k` = gabungan dua blok `2^{k-1}`. Query `[l, r]` panjang `len`: ambil `k` terbesar dengan `2^k ≤ len`, lalu gabungkan blok kiri `[l, l+2^k-1]` dan blok kanan `[r-2^k+1, r]`. Kedua blok **tumpang tindih**. Itu boleh hanya jika `op(x, x) = x` (idempoten). `min(x,x)=x`, `gcd(x,x)=x`. `x+x ≠ x`, jadi **bukan untuk jumlah**.

**Kapan dipakai / kapan tidak.**

- Pakai: RMQ, range gcd, range AND/OR, array **tidak berubah**, q besar (10^6).
- Jangan: ada update.
- Jangan: sum/XOR — pakai prefix.
- Jangan: `std::log2` untuk mencari `k`.

**Proses:** `a = [5, 1, 9, 3]`, op = min.

```
k=0:  5  1  9  3          panjang 1
k=1:  min(5,1)=1, min(1,9)=1, min(9,3)=3     panjang 2
k=2:  min(1,3)=1  (dari indeks 0, panjang 4)
```

Query `[1, 3]` len=3, `k=1` karena 2≤3<4.

- kiri: `sp[1][1] = min(1,9) = 1`
- kanan: `sp[1][3-2+1] = sp[1][2] = min(9,3) = 3`
- min(1, 3) = 1. Benar.

**Kode:**

```cpp
struct SparseMin {
    vector<vector<int>> sp;
    vector<int> lg;

    void build(const vector<int>& a) {
        int n = (int)a.size();
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
        int K = lg[n] + 1;
        sp.assign(K, vector<int>(n));
        if (n) sp[0] = a;
        for (int k = 1; k < K; k++)
            for (int i = 0; i + (1 << k) <= n; i++)
                sp[k][i] = min(sp[k - 1][i],
                               sp[k - 1][i + (1 << (k - 1))]);
    }

    int query(int l, int r) const {         // inklusif, l <= r
        int k = lg[r - l + 1];
        return min(sp[k][l], sp[k][r - (1 << k) + 1]);
    }
};
```

Log aman tanpa `log2`:

```cpp
int floorLog2(int len) {                    // len >= 1
    return 31 - __builtin_clz(len);
}
```

`__builtin_clz(0)` tidak terdefinisi. Jangan panggil pada panjang 0.

**Jebakan:**

- Batas build `i < n` tanpa `i + (1<<k) <= n` → baca di luar.
- Blok kanan lupa `+1`.
- `lg` dihitung `log2` floating: `log2(8)` bisa 2.999 → `k=2` salah (mestinya 3).
- Memakai Sparse Table untuk jumlah lalu heran hasilnya dobel di tumpang tindih.

**Kompleksitas:** build O(n log n), query O(1), memori O(n log n). Untuk n=2·10^5, `int`: sekitar 14 MB.

## Sqrt decomposition

**Teori:** potong array jadi blok berukuran ≈ √n. Precompute jawaban tiap blok. Query = sedikit elemen di ekor kiri + beberapa blok utuh + ekor kanan. Update titik: ubah elemen, bangun ulang **satu blok**.

Ini jembatan mental ke Mo: keduanya hidup dari “blok berukuran akar”.

**Kapan dipakai / kapan tidak.**

- Pakai: operasi yang sulit masuk Segment Tree (misalnya mode, banyak nilai unik di blok, rebuild murah).
- Jangan: kalau Segment Tree sudah cukup — kodenya lebih rapi dan biasanya lebih cepat.

**Proses:** `n=9`, `B=3`, `a = [4, 1, 3, 2, 8, 5, 7, 6, 0]`.

```
blok 0: 4 1 3   min=1
blok 1: 2 8 5   min=2
blok 2: 7 6 0   min=0
```

Query min `[2, 7]` = min(ekor `3`, blok utuh `2`, ekor `7 6`) = min(3, 2, 7, 6) = 2.

**Kode:**

```cpp
struct SqrtMin {
    int n, B, nb;
    vector<int> a, blk;

    SqrtMin(const vector<int>& a_) : a(a_) {
        n = (int)a.size();
        B = max(1, (int)sqrt(n));
        nb = (n + B - 1) / B;
        blk.assign(nb, INT_MAX);
        for (int i = 0; i < n; i++) blk[i / B] = min(blk[i / B], a[i]);
    }

    void setPos(int i, int x) {
        a[i] = x;
        int b = i / B;
        int L = b * B, R = min(n, L + B);
        blk[b] = INT_MAX;
        for (int j = L; j < R; j++) blk[b] = min(blk[b], a[j]);
    }

    int query(int l, int r) const {         // inklusif
        int ans = INT_MAX;
        while (l <= r && l % B != 0) ans = min(ans, a[l++]);
        while (l + B - 1 <= r) {
            ans = min(ans, blk[l / B]);
            l += B;
        }
        while (l <= r) ans = min(ans, a[l++]);
        return ans;
    }
};
```

**Jebakan:** `B=0` jika n=0. Rebuild blok lupa batas `min(n, L+B)`. Query yang seluruhnya di dalam satu blok harus tetap benar (loop ekor saja).

**Kompleksitas:** build O(n), query O(√n), update O(√n) jika rebuild blok. Memori O(n).

## Algoritma Mo

**Teori:** ada q query `[l, r]` **offline** (semua diketahui di awal). Kamu punya cara menambah/menghapus **satu indeks** ke “jendela” dan menjaga jawaban (misalnya banyak nilai unik). Naif: tiap query menggeser jendela dari nol, O(n) per query.

Mo mengurutkan query supaya jendela **jarang loncat**. Potong kiri menjadi blok √n. Urutkan: blok kiri dulu; di dalam blok yang sama, urutkan `r`. Jendela berjalan monoton di `r` dalam satu blok, dan `l` hanya bergerak O(√n) antar query tetangga.

Total pergerakan kira-kira O((n+q) √n) add/remove.

Analogi: perpustakaan. Jangan ambil buku lantai 1, lalu 8, lalu 2. Kelompokkan permintaan per lorong, baru geser trolley pelan-pelan.

**Kapan dipakai / kapan tidak.**

- Pakai: query offline, add/remove O(1) atau O(log n), n,q ≈ 10^5 (√n ≈ 300, total ~ 3·10^7).
- Jangan: ada update array di tengah (itu Mo dengan waktu, lebih rumit).
- Jangan: butuh jawaban online (query berikutnya bergantung jawaban sebelumnya).
- Jangan: add/remove mahal — Mo tidak menyelamatkan.

**Proses:** `a = [1, 2, 1, 3]`, query unik: Q0=`[0,2]`, Q1=`[1,3]`, Q2=`[0,3]`. `B=2`.

```
Q0 l=0 r=2  blok 0
Q2 l=0 r=3  blok 0
Q1 l=1 r=3  blok 0
semua blok 0, urut r: Q0, Q2, Q1
```

Jendela mulai kosong `cl=0, cr=-1`.

1. Q0: `cr` ke 2, add 0,1,2. unik: 1,2,1 → 2.
2. Q2: `cr` ke 3, add 3. unik 3.
3. Q1: `cl` ke 1, del 0. unik 3.

Add/remove:

```
cnt[x]++ : jika dari 0 ke 1, jawaban unik +1
cnt[x]-- : jika dari 1 ke 0, jawaban unik -1
```

**Kode:**

```cpp
struct Query {
    int l, r, idx;
};

int Bmo;

bool moKurang(const Query& a, const Query& b) {
    int ba = a.l / Bmo, bb = b.l / Bmo;
    if (ba != bb) return ba < bb;
    if (ba & 1) return a.r > b.r;           // zigzag: kurangi geser r
    return a.r < b.r;
}

vector<int> moUnik(const vector<int>& a, vector<Query> qs) {
    int n = (int)a.size(), q = (int)qs.size();
    Bmo = max(1, (int)sqrt(n));
    sort(qs.begin(), qs.end(), moKurang);

    vector<int> cnt(n + 5), ans(q);         // kompres dulu jika a[i] besar
    int cur = 0, cl = 0, cr = -1;

    auto add = [&](int i) {
        if (cnt[a[i]]++ == 0) cur++;
    };
    auto del = [&](int i) {
        if (--cnt[a[i]] == 0) cur--;
    };

    for (auto qu : qs) {
        while (cr < qu.r) add(++cr);
        while (cr > qu.r) del(cr--);
        while (cl < qu.l) del(cl++);
        while (cl > qu.l) add(--cl);
        ans[qu.idx] = cur;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<int> a = {1, 2, 1, 3};
    vector<Query> qs = {{0, 2, 0}, {1, 3, 1}, {0, 3, 2}};
    // kompresi kecil
    vector<int> b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    for (int& x : a) x = int(lower_bound(b.begin(), b.end(), x) - b.begin());
    auto ans = moUnik(a, qs);
    for (int x : ans) cout << x << ' ';     // 2 3 3
    cout << '\n';
}
```

**Jebakan:**

- Urutan add/remove salah: harus `++cr` dulu baru `add`, `del` dulu baru `cr--`. Vertikal ini sumber WA abadi.
- `cnt` diindeks nilai mentah 10^9 → crash. Kompres.
- `B = sqrt(n)` untuk n=1 → 1, aman. Untuk n=0, jaga.
- Menulis jawaban ke `qs` yang sudah di-sort tanpa `idx` → urutan acak.
- Update online: Mo murni tidak bisa.

**Kompleksitas:** O((n+q) √n · biaya add/remove). Memori O(n+q). Hilbert order kadang mempercepat konstanta; blok zigzag di atas sudah cukup sering.

## Tabel pilih struktur

| Soal berbunyi | Pilih |
| --- | --- |
| jumlah `[l, r]`, array mati | prefix sum |
| min/max/gcd `[l, r]`, array mati | Sparse Table |
| `a[i] += x`, jumlah `[l, r]` | Fenwick |
| `a[i] = x`, min `[l, r]` | Segment Tree |
| `a[l..r] += x`, jumlah `[L, R]` | lazy **atau** dua BIT |
| banyak nilai unik `[l, r]`, offline | Mo |
| k-th terkecil dinamis, nilai terkompresi | Fenwick `cariKeK` |
| subarray max pada rentang | Segment Tree simpul kaya |
| “kembalikan ke versi t” | Segment Tree persisten (ide) |
| jendela geser ukuran tetap, min | monotonic deque (file 04), bukan Mo |

Batasan kasar (2 detik, C++):

```
n, q ≤ 1e5 .. 2e5     O((n+q) log n) nyaman
n, q ≤ 1e5            Mo O(n √n) pas-pasan, add harus O(1)
n ≤ 1e6, q ≤ 1e6      Sparse Table query O(1) atau Fenwick
n ≤ 5000              O(n²) kadang lebih mudah dari Mo
```

## Resep cepat

**Hitung inversi lalu jawab query jumlah.** Bangun BIT frekuensi dari kanan. Jangan campur BIT jumlah nilai dengan BIT frekuensi tanpa nama berbeda.

**RMQ statis untuk LCA.** Euler tour + Sparse Table argmin (file 17). Di sini cukup Sparse Table yang menyimpan **indeks**, bukan nilai.

```cpp
struct SparseArgMin {
    vector<vector<int>> sp;
    vector<int> lg, a;

    void build(const vector<int>& a_) {
        a = a_;
        int n = (int)a.size();
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
        int K = (n ? lg[n] + 1 : 1);
        sp.assign(K, vector<int>(n));
        for (int i = 0; i < n; i++) sp[0][i] = i;
        for (int k = 1; k < K; k++)
            for (int i = 0; i + (1 << k) <= n; i++) {
                int x = sp[k - 1][i];
                int y = sp[k - 1][i + (1 << (k - 1))];
                sp[k][i] = (a[x] <= a[y] ? x : y);
            }
    }

    int queryIdx(int l, int r) const {
        int k = lg[r - l + 1];
        int x = sp[k][l], y = sp[k][r - (1 << k) + 1];
        return a[x] <= a[y] ? x : y;
    }
};
```

**Stress test struktur (wajib).** Generator array kecil, bandingkan dengan naif. Pola lengkap di file 19.

```cpp
bool cekBit(int n, int q) {
    vector<ll> a(n);
    mt19937 rng(42);
    for (ll& x : a) x = rng() % 100;
    BIT bit;
    bit.build(a);
    for (int i = 0; i < q; i++) {
        if (rng() & 1) {
            int p = rng() % n;
            ll d = (int)(rng() % 11) - 5;
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
```

## Ringkasan

1. Pilih dulu **operasi** dan **ada tidaknya update**. Baru pilih struktur.
2. Fenwick = tangga `lowbit`, 1-based, butuh invers. Hafalkan sepuluh baris `update`/`query`.
3. Segment Tree = pohon asosiatif. Ganti identitas dan `gabung`, sisanya sama.
4. Lazy = tunda pekerjaan ke anak. `apply` mengubah nilai + menandai, `push` menurunkan.
5. Sparse Table = foto pangkat dua, query O(1), **idempoten**, **statis**.
6. Mo = urutkan query, geser jendela. Bukan struktur, melainkan **jadwal**.

Latihan: kerjakan CSES *Range Queries* dan Day 169–183 di `ComProgLearning/CP` sebelum lanjut HLD di file 17. HLD hanyalah Segment Tree yang diletakkan di jalur pohon.
