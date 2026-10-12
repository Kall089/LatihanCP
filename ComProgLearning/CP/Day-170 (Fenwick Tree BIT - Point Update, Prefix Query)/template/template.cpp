/*
============================================================
  Day 170 — Fenwick Tree (BIT) | CP Template
============================================================
  Sepuluh baris, O(log n) untuk update DAN query, konstanta sangat kecil
  (3-5x lebih cepat dari segment tree untuk operasi yang sama).

  tree[i] menanggung a[i - (i&-i) + 1 .. i]   blok sepanjang lowbit(i)
    UPDATE naik  (i += i & -i) : ke semua blok yang MEMUAT i
    QUERY  turun (i -= i & -i) : blok-blok yang MENUTUPI prefiks

  1-INDEXED WAJIB. Kalau i = 0 maka i & -i = 0 dan loop `i += 0`
  BERPUTAR SELAMANYA. Ini bug nomor satu, dan gejalanya (program hang)
  membingungkan karena tidak ada pesan error.

  SYARAT: operasi harus punya INVERS (sum, XOR), karena
  range(l,r) = query(r) - query(l-1). min/max/gcd -> segment tree.

  TIGA STRUKTUR, TIGA SYARAT
    prefix sum   : INVERS    + statis   -> O(1) query
    sparse table : IDEMPOTEN + statis   -> O(1) query
    Fenwick      : INVERS    + dinamis  -> O(log n)
    segment tree : ASOSIATIF + dinamis  -> O(log n), paling umum
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// ─── 1. BIT BAKU (hafalkan) ──────────────────────────────

struct BIT {
    int n;
    vector<ll> t;

    BIT(int n_ = 0) { init(n_); }
    void init(int n_) { n = n_; t.assign(n + 2, 0); }   // n+2: aman untuk r+1

    void update(int i, ll delta) {
        for (; i <= n; i += i & -i) t[i] += delta;
    }

    ll query(int i) const {                              // jumlah a[1..i]
        ll s = 0;
        for (; i > 0; i -= i & -i) s += t[i];
        return s;
    }

    ll range(int l, int r) const {                       // jumlah a[l..r]
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }

    // BUILD O(n), bukan O(n log n): tiap simpul mewariskan ke induknya sekali
    void build(const vector<ll>& a) {                    // a 0-indexed
        init(a.size());
        for (int i = 1; i <= n; i++) {
            t[i] += a[i - 1];
            int j = i + (i & -i);
            if (j <= n) t[j] += t[i];
        }
    }

    // Indeks terkecil i dengan query(i) >= k. O(log n), bukan O(log^2 n).
    // Berguna untuk "nilai terkecil ke-k pada multiset dinamis".
    int cariKeK(ll k) const {
        int pos = 0;
        if (n <= 0) return 1;
        for (int pw = 1 << (31 - __builtin_clz(n)); pw > 0; pw >>= 1)
            if (pos + pw <= n && t[pos + pw] < k) {
                pos += pw;
                k -= t[pos];
            }
        return pos + 1;
    }
};

// ─── 2. RANGE UPDATE, POINT QUERY ────────────────────────
// BIT atas DIFFERENCE array (Day 31). query(i) menjumlahkan seluruh
// selisih sampai i, hasilnya nilai sesungguhnya di posisi i.

struct BITRangePoint {
    BIT bit;
    BITRangePoint(int n) : bit(n) {}
    void rangeAdd(int l, int r, ll v) {
        bit.update(l, v);
        bit.update(r + 1, -v);                           // r+1 aman: t punya n+2
    }
    ll pointQuery(int i) const { return bit.query(i); }
};

// ─── 3. RANGE UPDATE, RANGE QUERY (dua BIT) ──────────────
// Rumusnya tidak intuitif; simpan dan pakai apa adanya.
// Segment tree dengan lazy (Day 176) melakukan hal sama lebih jelas.

struct BITRangeRange {
    BIT b1, b2;
    int n;
    BITRangeRange(int n_) : b1(n_), b2(n_), n(n_) {}

    void rangeAdd(int l, int r, ll v) {
        b1.update(l, v);              b1.update(r + 1, -v);
        b2.update(l, v * (l - 1));    b2.update(r + 1, -v * r);
    }
    ll prefix(int i) const { return b1.query(i) * i - b2.query(i); }
    ll range(int l, int r) const { return prefix(r) - prefix(l - 1); }
};

// ─── 4. KOMPRESI KOORDINAT (Day 38) ──────────────────────
// BIT diindeks oleh NILAI, jadi domainnya harus kecil.
// BIT dan kompresi hampir selalu muncul bersama.

struct Kompres {
    vector<ll> v;
    void tambah(ll x) { v.push_back(x); }
    void bangun() {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
    }
    int idx(ll x) const {                                // 1-BASED untuk BIT
        return int(lower_bound(v.begin(), v.end(), x) - v.begin()) + 1;
    }
    int size() const { return (int)v.size(); }
};

// ─── 5. MENGHITUNG INVERSI ───────────────────────────────
// Sapu dari KANAN, hitung yang LEBIH KECIL. Hafalkan SATU arah saja;
// mencampur arah adalah sumber bug yang tidak perlu.

ll hitungInversi(vector<ll> a) {
    Kompres k;
    for (ll x : a) k.tambah(x);
    k.bangun();

    BIT bit(k.size());
    ll inv = 0;
    for (int i = (int)a.size() - 1; i >= 0; i--) {
        int p = k.idx(a[i]);
        inv += bit.query(p - 1);                         // yang lebih KECIL
        bit.update(p, 1);
    }
    return inv;
}

// ─── 6. BERAPA YANG LEBIH KECIL DI KANAN (per posisi) ────

vector<int> lebihKecilDiKanan(vector<ll> a) {
    int n = a.size();
    Kompres k;
    for (ll x : a) k.tambah(x);
    k.bangun();

    BIT bit(k.size());
    vector<int> hasil(n);
    for (int i = n - 1; i >= 0; i--) {
        int p = k.idx(a[i]);
        hasil[i] = (int)bit.query(p - 1);
        bit.update(p, 1);
    }
    return hasil;
}

// ─── 7. BIT SEBAGAI MULTISET DINAMIS ─────────────────────
// Empat operasi ini menjadikan BIT pengganti multiset yang jauh lebih
// cepat, selama domain nilainya bisa dikompresi.

struct MultisetBIT {
    BIT bit;
    Kompres k;
    MultisetBIT(const vector<ll>& semuaNilai) {          // SEMUA nilai di awal
        for (ll x : semuaNilai) k.tambah(x);
        k.bangun();
        bit.init(k.size());
    }
    void sisip(ll x) { bit.update(k.idx(x), 1); }
    void hapus(ll x) { bit.update(k.idx(x), -1); }
    ll banyakKurangSama(ll x) const { return bit.query(k.idx(x)); }
    ll terkecilKeK(ll kk) const { return k.v[bit.cariKeK(kk) - 1]; }
};

// ─── 8. BIT DUA DIMENSI ──────────────────────────────────

struct BIT2D {
    int n, m;
    vector<vector<ll>> t;
    BIT2D(int n_, int m_) : n(n_), m(m_), t(n_ + 1, vector<ll>(m_ + 1, 0)) {}

    void update(int x, int y, ll v) {
        for (int i = x; i <= n; i += i & -i)
            for (int j = y; j <= m; j += j & -j) t[i][j] += v;
    }
    ll query(int x, int y) const {
        ll s = 0;
        for (int i = x; i > 0; i -= i & -i)
            for (int j = y; j > 0; j -= j & -j) s += t[i][j];
        return s;
    }
    // submatriks lewat inklusi-eksklusi empat sudut (Day 30)
    ll range(int x1, int y1, int x2, int y2) const {
        return query(x2, y2) - query(x1 - 1, y2)
             - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
    }
};

// ─── 9. NAIF (untuk stress test -- WAJIB dipakai) ────────

ll inversiNaif(const vector<ll>& a) {
    ll c = 0;
    for (size_t i = 0; i < a.size(); i++)
        for (size_t j = i + 1; j < a.size(); j++)
            if (a[i] > a[j]) c++;
    return c;
}

// ─── MAIN ────────────────────────────────────────────────

int main() {
    FASTIO;

    int n, q;
    if (!(cin >> n >> q)) return 0;
    vector<ll> a(n);
    for (ll& x : a) cin >> x;

    BIT bit;
    bit.build(a);

    cout << "inversi      : " << hitungInversi(a) << '\n';
    cout << "  cek naif   : " << inversiNaif(a) << '\n';
    cout << "lebih kecil di kanan :";
    for (int x : lebihKecilDiKanan(a)) cout << ' ' << x;
    cout << '\n';

    string out;
    while (q--) {
        int jenis;
        cin >> jenis;
        if (jenis == 1) {                    // update titik: a[i] += d
            int i; ll d;
            cin >> i >> d;
            bit.update(i, d);
        } else {                             // query rentang
            int l, r;
            cin >> l >> r;
            out += to_string(bit.range(l, r));
            out += '\n';
        }
    }
    cout << out;

    return 0;
}
