/*
============================================================
  Day 169 — Sparse Table | CP Template
============================================================
  sp[k][i] = op pada a[i .. i + 2^k - 1]

  BUILD O(n log n), QUERY O(1). TIDAK MENDUKUNG UPDATE.

  KENAPA BOLEH TUMPANG TINDIH: operasinya IDEMPOTEN, op(x,x) = x.
    BISA  : min, max, gcd, lcm, AND, OR
    TIDAK : sum (x+x = 2x), XOR (x^x = 0)  -> pakai PREFIX SUM

  TIGA DETAIL YANG PALING SERING SALAH:
    1. batas build  : i + (1 << k) <= n     (bukan i < n)
    2. blok kanan   : r - (1 << k) + 1      (jangan lupa +1)
    3. log2         : tabel atau __builtin_clz, JANGAN std::log2
                      (floating point bisa memberi log2(8) = 2.9999999)

  POHON KEPUTUSAN
    ada update?              -> segment tree / Fenwick (Day 170, 172)
    sum/xor tanpa update     -> prefix sum (Day 29)
    min/max/gcd tanpa update -> SPARSE TABLE
    jendela geser ukuran tetap -> monotonic deque (Day 37)
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// ─── 1. SPARSE TABLE MINIMUM (bentuk baku) ───────────────

struct SparseMin {
    vector<vector<int>> sp;
    vector<int> lg;

    void build(const vector<int>& a) {
        int n = a.size();
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;   // tabel log2

        int K = lg[n] + 1;
        sp.assign(K, vector<int>(n));
        sp[0] = a;                                            // basis

        for (int k = 1; k < K; k++)
            for (int i = 0; i + (1 << k) <= n; i++)           // BATAS
                sp[k][i] = min(sp[k - 1][i], sp[k - 1][i + (1 << (k - 1))]);
    }

    int query(int l, int r) const {                           // INKLUSIF
        int k = lg[r - l + 1];
        return min(sp[k][l], sp[k][r - (1 << k) + 1]);        // +1
    }
};

// ─── 2. VERSI GENERIK (operasi IDEMPOTEN apa pun) ────────
// PERINGATAN: memasukkan operasi non-idempoten (misalnya +) tetap
// KOMPILASI, tetapi jawabannya SALAH karena tumpang tindih dihitung dua kali.

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
                sp[k][i] = op(sp[k - 1][i], sp[k - 1][i + (1 << (k - 1))]);
    }

    T query(int l, int r) const {
        int k = lg[r - l + 1];
        return op(sp[k][l], sp[k][r - (1 << k) + 1]);
    }
};

// ─── 3. SPARSE TABLE YANG MENGEMBALIKAN INDEKS ───────────
// Untuk "DI MANA minimumnya", bukan sekadar nilainya.
// Dipakai LCA dengan Euler tour (Day 202) dan divide-and-conquer.

struct SparseArgMin {
    vector<vector<int>> sp;                                   // menyimpan INDEKS
    vector<int> lg, a;

    void build(const vector<int>& a_) {
        a = a_;
        int n = a.size();
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;

        int K = lg[n] + 1;
        sp.assign(K, vector<int>(n));
        for (int i = 0; i < n; i++) sp[0][i] = i;

        for (int k = 1; k < K; k++)
            for (int i = 0; i + (1 << k) <= n; i++) {
                int i1 = sp[k - 1][i], i2 = sp[k - 1][i + (1 << (k - 1))];
                sp[k][i] = (a[i1] <= a[i2]) ? i1 : i2;        // bandingkan NILAI
            }
    }

    int queryIdx(int l, int r) const {
        int k = lg[r - l + 1];
        int i1 = sp[k][l], i2 = sp[k][r - (1 << k) + 1];
        return (a[i1] <= a[i2]) ? i1 : i2;
    }
    int queryVal(int l, int r) const { return a[queryIdx(l, r)]; }
};

// ─── 4. CARA MENGHITUNG log2 ─────────────────────────────
/*
    1. TABEL (tercepat, teraman):
         lg[1] = 0; for (i = 2..n) lg[i] = lg[i/2] + 1;

    2. BUILTIN (satu instruksi CPU):
         int k  = 31 - __builtin_clz(len);      // int,  len >= 1
         int k2 = 63 - __builtin_clzll(len);    // ll,   len >= 1
       __builtin_clz(0) adalah PERILAKU TAK TERDEFINISI.

    3. std::log2  -- JANGAN.
       Floating point bisa memberi log2(8) = 2.9999999996 -> dibulatkan 2.
       Bugnya bergantung kompilator dan arsitektur, sehingga bisa lolos di
       mesinmu dan gagal di juri.
*/

// ─── 5. NAIF (untuk stress test -- WAJIB dipakai) ────────

int naifMin(const vector<int>& a, int l, int r) {
    int m = a[l];
    for (int i = l + 1; i <= r; i++) m = min(m, a[i]);
    return m;
}

// ─── MAIN ────────────────────────────────────────────────

int main() {
    FASTIO;

    int n, q;
    if (!(cin >> n >> q)) return 0;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    SparseMin st;
    st.build(a);

    SparseArgMin sa;
    sa.build(a);

    vector<ll> b(a.begin(), a.end());
    SparseTable<ll, function<ll(ll, ll)>> stGcd(
        b, [](ll x, ll y) { return __gcd(x, y); });

    string out;
    while (q--) {
        int l, r;
        cin >> l >> r;                       // 0-based, inklusif
        out += to_string(st.query(l, r));
        out += ' ';
        out += to_string(sa.queryIdx(l, r)); // indeks minimum
        out += ' ';
        out += to_string(stGcd.query(l, r));
        out += " (naif ";
        out += to_string(naifMin(a, l, r));
        out += ")\n";
    }
    cout << out;

    return 0;
}
