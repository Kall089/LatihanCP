# Sparse Table — RMQ O(1)

[← Struktur data](README.md) · [Fenwick →](fenwick.md) · [Indeks CP](../README.md)

Day 169. Array **statis**, query `min` / `max` / `gcd` / `AND` / `OR` dalam O(1) setelah prahitung O(n log n).

Indeks array **0-based**. `typedef long long ll`. Template I/O:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
```

## Daftar isi

- [Ide dan syarat operasi](#ide-dan-syarat-operasi)
- [Tabel log aman](#tabel-log-aman)
- [Bangun tabel](#bangun-tabel)
- [Query dua blok](#query-dua-blok)
- [Sparse min lengkap](#sparse-min-lengkap)
- [Max, gcd, AND, OR](#max-gcd-and-or)
- [Argmin untuk LCA](#argmin-untuk-lca)
- [Range gcd dinamis? Jangan](#range-gcd-dinamis-jangan)
- [Dua dimensi singkat](#dua-dimensi-singkat)
- [Pilih lawan prefix dan pohon](#pilih-lawan-prefix-dan-pohon)
- [Uji naif](#uji-naif)
- [Ringkasan](#ringkasan)

## Ide dan syarat operasi

**Teori:** Sparse Table menyimpan jawaban setiap potongan yang panjangnya **pangkat dua**. `st[k][i]` = hasil operasi pada `a[i .. i+2^k-1]`. Blok panjang `2^k` adalah gabungan dua blok `2^{k-1}` yang berdempet:

```
st[k][i] = op(st[k-1][i], st[k-1][i + 2^{k-1}])
```

Query `[l, r]` panjang `len = r-l+1`. Ambil `k` terbesar dengan `2^k ≤ len`. Gabungkan:

```
kiri  = st[k][l]                 mencakup [l, l+2^k-1]
kanan = st[k][r-2^k+1]           mencakup [r-2^k+1, r]
```

Kedua blok **tumpang tindih** di tengah. Itu sah hanya jika operasi **idempoten**: `op(x, x) = x`. Minimum, maksimum, GCD, AND, OR semuanya idempoten. Penjumlahan **bukan**: `x+x ≠ x`, jadi overlap menggandakan nilai.

Analogi: kamu punya foto setiap jembatan sepanjang 1, 2, 4, 8 rumah. Mau foto 13 rumah? Ambil foto 8 rumah dari kiri dan foto 8 rumah dari kanan. Bagian tengah muncul dua kali. Untuk “rumah terpendek” dua kali tetap rumah itu. Untuk “jumlah tinggi” dua kali salah.

Kenapa O(1): `k` dibaca dari tabel `lg[len]`, lalu dua akses array. Tidak ada loop di query.

**Kapan:**

- Pakai: array tidak berubah, banyak query (q sampai 10^6), operasi idempoten.
- Jangan: ada update. Membangun ulang O(n log n) per update kalah dari Fenwick / Segment Tree.
- Jangan: jumlah atau XOR. Pakai [prefix](../03-array/README.md) atau [Fenwick](fenwick.md).
- Jangan: n kecil dan kamu sudah punya Segment Tree — boleh, tetapi Sparse Table lebih pendek untuk RMQ statis.

**Proses:** belum angka. Syarat dulu.

| Operasi | Idempoten? | Sparse Table? |
|---|---|---|
| `min`, `max` | ya | ya |
| `gcd`, `lcm` | ya | ya (lcm hati-hati overflow) |
| AND, OR | ya | ya |
| jumlah, XOR | tidak | tidak |
| perkalian | tidak | tidak |

**Kode:** identitas tidak dipakai di query overlap, tetapi berguna jika kamu menulis versi “gabung O(log n)” tanpa overlap (jarang perlu).

```cpp
int opMin(int a, int b) { return min(a, b); }
int opGcd(int a, int b) { return std::gcd(a, b); }
int opAnd(int a, int b) { return a & b; }
```

**Jebakan:** memakai Sparse Table untuk jumlah lalu heran hasilnya lebih besar dari prefix. Itu overlap, bukan bug indeks semata.

**Kompleksitas:** ide O(1) query, O(n log n) bangun, O(n log n) memori.

## Tabel log aman

**Teori:** `k = floor(log2(len))`. Jangan `log2` floating. `log2(8)` bisa 2.999 lalu di-cast jadi 2, padahal `2^3 = 8`. Hitung `lg` dengan integer:

```
lg[1] = 0
lg[i] = lg[i/2] + 1     untuk i >= 2
```

Setara: `31 - __builtin_clz(len)` untuk `len >= 1`. `__builtin_clz(0)` tidak terdefinisi.

**Kapan:** setiap Sparse Table. Tabel `lg` dihitung sekali sampai `n`.

**Proses:** n = 10.

```
i     1  2  3  4  5  6  7  8  9  10
lg    0  1  1  2  2  2  2  3  3   3
```

Query panjang 5 → `lg[5]=2` → blok 4. Panjang 8 → `lg[8]=3` → blok 8, overlap penuh (dua blok sama).

**Kode:**

```cpp
vector<int> bangunLg(int n) {
    vector<int> lg(n + 1, 0);
    for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
    return lg;
}

int floorLog2(int len) {                    // len >= 1
    return 31 - __builtin_clz(len);
}
```

**Jebakan:** `lg` berukuran `n` bukan `n+1` lalu `lg[n]` keluar batas saat query menutup seluruh array. `clz(0)` saat `l > r`.

**Kompleksitas:** O(n) untuk tabel, O(1) per `floorLog2`.

## Bangun tabel

**Teori:** baris `k = 0` salin array. Baris berikutnya menggabungkan dua setengah. Loop `i` hanya sampai `i + 2^k <= n` supaya tidak membaca di luar.

**Kapan:** sekali di awal. Jika array berubah, buang struktur ini.

**Proses:** `a = [5, 1, 9, 3]`, operasi min, n = 4.

```
k=0 panjang 1:
  i=0: 5
  i=1: 1
  i=2: 9
  i=3: 3

k=1 panjang 2:
  i=0: min(5,1) = 1
  i=1: min(1,9) = 1
  i=2: min(9,3) = 3
  i=3: i+2=5 > 4  tidak diisi

k=2 panjang 4:
  i=0: min(st[1][0], st[1][2]) = min(1,3) = 1
  i=1: i+4=5 > 4  tidak
```

Cek tangan: min seluruh array = 1. Cocok.

**Kode:**

```cpp
void isiMin(vector<vector<int>>& st, const vector<int>& a, const vector<int>& lg) {
    int n = (int)a.size();
    int K = (n ? lg[n] + 1 : 1);
    st.assign(K, vector<int>(n));
    if (n) st[0] = a;
    for (int k = 1; k < K; k++) {
        int panjang = 1 << k;
        int setengah = 1 << (k - 1);
        for (int i = 0; i + panjang <= n; i++)
            st[k][i] = min(st[k - 1][i], st[k - 1][i + setengah]);
    }
}
```

**Jebakan:** syarat loop `i < n` tanpa `i + (1<<k) <= n` membaca `st[k-1][i+setengah]` di luar. `K = lg[n]` tanpa `+1` kehilangan baris terakhir saat n pangkat dua.

**Kompleksitas:** O(n log n) isi, memori O(n log n). Untuk n = 2·10^5, `int`: kira-kira 18 baris × 2·10^5 × 4 B ≈ 14 MB.

## Query dua blok

**Teori:** `k = lg[r-l+1]`. Jawaban `op(st[k][l], st[k][r-(1<<k)+1])`. Gambar panjang 13, k = 3, blok 8:

```
indeks:  l  l+1 ...          r
blok L:  [========8========]
blok R:           [========8========]
```

Bagian tengah ditutup dua kali. Min/max/gcd aman.

**Kapan:** `l <= r`, indeks valid. Query kosong tidak didefinisikan — jangan panggil.

**Proses:** `a = [5, 1, 9, 3]`, query `[1, 3]` (nilai 1, 9, 3).

```
len = 3, lg[3] = 1, 2^1 = 2
kiri  = st[1][1] = min(1, 9) = 1
kanan = st[1][3-2+1] = st[1][2] = min(9, 3) = 3
min(1, 3) = 1
```

Query `[0, 0]`: len = 1, k = 0, kiri = kanan = 5.

Query `[0, 3]`: len = 4, k = 2, kiri = st[2][0] = 1, kanan = st[2][0] = 1.

**Kode:**

```cpp
int queryMin(const vector<vector<int>>& st, const vector<int>& lg, int l, int r) {
    int k = lg[r - l + 1];
    return min(st[k][l], st[k][r - (1 << k) + 1]);
}
```

**Jebakan:** rumus kanan `r - (1<<k)` lupa `+1` bergeser satu ke kiri, kadang masih kebetulan benar pada tes kecil. Query `l > r` membuat `len` negatif, `lg` crash.

**Kompleksitas:** O(1).

## Sparse min lengkap

**Teori:** bungkus tabel, `lg`, dan query dalam satu `struct`. `build` dari vektor 0-based. `query(l, r)` inklusif.

**Kapan:** RMQ klasik, “indeks pertama minimum di `[l,r]`” butuh varian argmin di bawah.

**Proses:** array `[4, 2, 4, 2, 3]`.

```
query(0,4) = 2
query(4,4) = 3
query(2,3) = 2
```

**Kode:**

```cpp
struct SparseMin {
    vector<vector<int>> st;
    vector<int> lg;

    void build(const vector<int>& a) {
        int n = (int)a.size();
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
        int K = (n ? lg[n] + 1 : 1);
        st.assign(K, vector<int>(n));
        if (n) st[0] = a;
        for (int k = 1; k < K; k++)
            for (int i = 0; i + (1 << k) <= n; i++)
                st[k][i] = min(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
    }

    int query(int l, int r) const {         // inklusif, l <= r
        int k = lg[r - l + 1];
        return min(st[k][l], st[k][r - (1 << k) + 1]);
    }
};

int minNaif(const vector<int>& a, int l, int r) {
    int ans = a[l];
    for (int i = l + 1; i <= r; i++) ans = min(ans, a[i]);
    return ans;
}

int main() {
    FASTIO;
    vector<int> a = {5, 1, 9, 3};
    SparseMin st;
    st.build(a);
    cout << st.query(1, 3) << '\n';         // 1
    cout << minNaif(a, 1, 3) << '\n';
}
```

**Jebakan:** `build` dipanggil dua kali tanpa `assign` ulang pada `lg` — versi ini aman karena `assign`. Query sebelum `build` pada n = 0.

**Kompleksitas:** build O(n log n), query O(1), memori O(n log n).

## Max, gcd, AND, OR

**Teori:** ganti `min` jadi operasi lain yang idempoten. GCD memakai `std::gcd` (C++17). AND/OR bit: overlap tidak merusak karena `x & x = x`.

Range GCD statis sering muncul: “berapa GCD `[l,r]`”. Sparse Table langsung. Jika ada update, Segment Tree GCD.

**Kapan:** sama seperti min, ganti operator. Campur dua operasi di satu tabel? Jangan — buat dua tabel, atau simpan struct jika kamu sadar overlap tetap idempoten per field.

**Proses:** `a = [12, 18, 30, 42]`.

```
gcd[0,1] = gcd(12,18) = 6
gcd[1,3] = gcd(18,30,42) = 6
gcd[2,2] = 30
AND dari [12, 18] = 12 & 18 = 2
OR  dari [12, 18] = 12 | 18 = 30
```

Build GCD k = 1:

```
st[1][0] = gcd(12,18) = 6
st[1][1] = gcd(18,30) = 6
st[1][2] = gcd(30,42) = 6
```

Query `[0, 3]` len = 4, k = 2: `gcd(st[2][0], st[2][0])`. `st[2][0] = gcd(6, 6) = 6`. Cek: gcd(12,18,30,42) = 6.

**Kode:**

```cpp
struct SparseGcd {
    vector<vector<int>> st;
    vector<int> lg;

    void build(const vector<int>& a) {
        int n = (int)a.size();
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
        int K = (n ? lg[n] + 1 : 1);
        st.assign(K, vector<int>(n));
        if (n) st[0] = a;
        for (int k = 1; k < K; k++)
            for (int i = 0; i + (1 << k) <= n; i++)
                st[k][i] = std::gcd(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
    }

    int query(int l, int r) const {
        int k = lg[r - l + 1];
        return std::gcd(st[k][l], st[k][r - (1 << k) + 1]);
    }
};

struct SparseAnd {
    vector<vector<int>> st;
    vector<int> lg;
    void build(const vector<int>& a) {
        int n = (int)a.size();
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
        int K = (n ? lg[n] + 1 : 1);
        st.assign(K, vector<int>(n, ~0));
        if (n) st[0] = a;
        for (int k = 1; k < K; k++)
            for (int i = 0; i + (1 << k) <= n; i++)
                st[k][i] = st[k - 1][i] & st[k - 1][i + (1 << (k - 1))];
    }
    int query(int l, int r) const {
        int k = lg[r - l + 1];
        return st[k][l] & st[k][r - (1 << k) + 1];
    }
};
```

**Jebakan:** `gcd(0, x) = x`. Nol di array membuat GCD rentang yang memuat nol dan x menjadi 0 jika ada 0. Itu benar secara matematis. LCM: hitung `a/gcd*b` dengan `ll` dan cek overflow.

**Kompleksitas:** sama O(n log n) / O(1). `gcd` sedikit lebih mahal konstan.

## Argmin untuk LCA

**Teori:** kadang kamu butuh **indeks** elemen terkecil, bukan nilainya. Simpan indeks di `st[k][i]`. Saat gabung, pilih indeks yang nilainya lebih kecil (tie: kiri, supaya stabil).

Ini bahan [LCA Euler + RMQ](../11-pohon/lca.md): array kedalaman, cari posisi paling dangkal.

**Kapan:** LCA O(1), “posisi minimum pertama”, sliding window indeks.

**Proses:** `a = [4, 2, 4, 2]`, indeks 0..3.

```
st[0] = 0,1,2,3
st[1][0] = argmin(4,2) = 1
st[1][1] = argmin(2,4) = 1
st[1][2] = argmin(4,2) = 3
query indeks [0,3]: k=2, banding 0 vs 0 jika hanya n=4 dan st[2][0]
nilai 2 di indeks 1 dan 3; pilih 1 jika tie <=.
```

**Kode:**

```cpp
struct SparseArgMin {
    vector<vector<int>> st;
    vector<int> lg, a;

    void build(const vector<int>& a_) {
        a = a_;
        int n = (int)a.size();
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
        int K = (n ? lg[n] + 1 : 1);
        st.assign(K, vector<int>(n));
        for (int i = 0; i < n; i++) st[0][i] = i;
        for (int k = 1; k < K; k++)
            for (int i = 0; i + (1 << k) <= n; i++) {
                int x = st[k - 1][i];
                int y = st[k - 1][i + (1 << (k - 1))];
                st[k][i] = (a[x] <= a[y] ? x : y);
            }
    }

    int queryIdx(int l, int r) const {
        int k = lg[r - l + 1];
        int x = st[k][l], y = st[k][r - (1 << k) + 1];
        return a[x] <= a[y] ? x : y;
    }

    int queryVal(int l, int r) const { return a[queryIdx(l, r)]; }
};
```

**Jebakan:** menyimpan nilai di tabel argmin lalu mengembalikan nilai saat kamu butuh indeks. Tie `<=` vs `<` mengubah “paling kiri” vs “paling kanan”. Untuk LCA, kedalaman sama: simpul mana pun di kedalaman itu pada segmen Euler yang benar tetap LCA (segmen antara first[u] dan first[v] punya tepat satu minimum global di LCA).

**Kompleksitas:** sama. Memori sama, isi `int` indeks.

## Range gcd dinamis? Jangan

**Teori:** orang tergoda “Sparse Table cepat, saya update satu titik lalu rebuild”. Rebuild O(n log n). Satu update + 1 query = mahal. q update → O(q n log n).

Segment Tree GCD: update O(log n), query O(log n). Itu alat yang benar.

Kapan Sparse Table masih lolos dengan rebuild: q kecil, atau update sangat jarang (q_update · n log n ≤ 10^8).

**Kapan:** hampir tidak. Tulis Segment Tree.

**Proses:** n = 2·10^5, q = 2·10^5 update. Rebuild setiap kali ≈ 2·10^5 · 2·10^5 · 18 ≈ 7·10^11 operasi. TLE mutlak.

**Kode:** kerangka yang **salah** untuk soal dinamis — ditaruh supaya kelihatan:

```cpp
// JANGAN dipakai jika ada banyak update
void updateSalah(SparseMin& st, vector<int>& a, int i, int x) {
    a[i] = x;
    st.build(a);                            // O(n log n)
}
```

**Jebakan:** tes contoh n = 5 lulus, tes besar TLE. Baca constraint: jika ada `1 i x` update, bukan Sparse Table.

**Kompleksitas:** rebuild O(n log n) — terlalu mahal sebagai “update”.

## Dua dimensi singkat

**Teori:** `st[k][i][p][j]` = min subpersegi pangkat dua. Memori O(n m log n log m). Untuk n,m = 500, log ≈ 9, masih muat jika hati-hati. Query overlap 4 persegi, idempoten wajib.

Sering lebih mudah: Sparse Table 1D per baris, lalu query kolom [l,r] di tiap baris pada `[x1,x2]` — O(tinggi) atau Sparse lagi pada hasil.

**Kapan:** RMQ 2D statis, n kecil. Jangan di n = 2000 × 2000 × 11 × 11 `int` tanpa hitung memori.

**Proses:** matriks 2×3:

```
1 4 3
2 0 5
```

Min seluruh = 0. Min sub `[0..1]×[1..2]` = min(4,3,0,5) = 0.

**Kode:** min per baris + Sparse 1D, query kotak O(jumlah baris):

```cpp
int minKotak(const vector<SparseMin>& baris, int x1, int y1, int x2, int y2) {
    int ans = INT_MAX;
    for (int i = x1; i <= x2; i++) ans = min(ans, baris[i].query(y1, y2));
    return ans;
}
```

**Jebakan:** 4D vector inisialisasi lambat. Hitung MB dulu.

**Kompleksitas:** per baris O(m log m) build, query kotak O((x2-x1+1)).

## Pilih lawan prefix dan pohon

**Teori:** empat alat query rentang. Sparse Table hanya menang di cabang “statis + idempoten + banyak query”.

| Kebutuhan | Alat |
|---|---|
| sum/XOR, array mati | prefix |
| min/gcd, array mati | Sparse Table |
| sum, ada update titik | [Fenwick](fenwick.md) |
| min, ada update | [Segment Tree](segment-tree.md) |
| update rentang | [lazy](lazy.md) |

**Kapan:** baca soal: ada baris “ubah a[i]”? Jika ya, keluar dari file ini.

**Proses:** soal “n,q ≤ 10^6, hanya min `[l,r]`”. Prefix tidak bisa min. Fenwick tidak punya invers min. Segment Tree O(log n) juga lolos, Sparse Table query lebih rapat di 10^6.

**Kode:** tidak ada. Ini peta.

**Jebakan:** “hampir statis” (1 update) tetap Segment Tree. Jangan rebuild.

**Kompleksitas:** target kontes 10^6 query O(1) = nyaman; O(log n) juga sering lolos.

## Uji naif

**Teori:** generator array kecil, semua pasangan `[l,r]`, bandingkan dengan loop. Ini stress edukatif, bukan perangkat penyerangan.

**Kapan:** setelah menulis `build`/`query`, sebelum menempel ke soal.

**Proses:** n = 4, a = [5,1,9,3], 10 pasangan, semua harus sama.

**Kode:**

```cpp
bool ujiSemua(const vector<int>& a) {
    SparseMin st;
    st.build(a);
    int n = (int)a.size();
    for (int l = 0; l < n; l++)
        for (int r = l; r < n; r++)
            if (st.query(l, r) != minNaif(a, l, r)) return false;
    return true;
}

bool ujiAcak(int n, int seed) {
    mt19937 rng(seed);
    vector<int> a(n);
    for (int& x : a) x = int(rng() % 21) - 10;
    return ujiSemua(a);
}

int main() {
    FASTIO;
    for (int n = 1; n <= 30; n++)
        for (int s = 0; s < 5; s++)
            if (!ujiAcak(n, n * 100 + s)) {
                cout << "beda n=" << n << " seed=" << s << '\n';
                return 0;
            }
    cout << "ok\n";
}
```

**Jebakan:** menguji hanya query penuh `[0,n-1]`. Bug rumus kanan lolos. Uji n = 1.

**Kompleksitas:** O(n^2) naif × banyak tes. n ≤ 40 nyaman.

## Ringkasan

1. Sparse Table = foto blok pangkat dua. Query = dua foto yang boleh tumpang tindih.
2. Operasi harus idempoten. Jumlah memakai prefix, bukan file ini.
3. `lg` integer, bukan `log2`.
4. Build O(n log n), query O(1), tidak ada update.
5. Argmin menyimpan indeks — bahan LCA Euler.
6. Ada update → [Fenwick](fenwick.md) atau [Segment Tree](segment-tree.md).

Latihan harian ada di `ComprogLearning/CP` Day 169. Jangan salin folder latihan ke sini.
