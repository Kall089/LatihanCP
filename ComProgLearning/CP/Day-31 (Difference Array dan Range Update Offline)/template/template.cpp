/*
============================================================
  Day 29 — Difference Array & Range Update | CP Template
============================================================
  Pola inti:
    UPDATE  a[l..r] += v   ->  diff[l] += v; diff[r+1] -= v;   O(1)
    HASIL   a[i]           ->  prefix sum dari diff            O(n)

  WAJIB DIINGAT:
    1. Ukuran array n + 2 (butuh slot untuk r+1 saat r = n)
    2. Pakai long long (Q x v gampang melewati batas int)
    3. Pengurang di r+1, BUKAN r
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int INF = 1e9;
const ll LLINF = 1e18;
const int MAXN = 200005;

// ─── DIFFERENCE ARRAY 1D (ARRAY STATIS) ──────────────────

ll diff[MAXN];      // diff[i] = selisih yang mulai berlaku di indeks i

// Tambahkan v ke seluruh a[l..r]. Kompleksitas O(1).
// Syarat: 1 <= l <= r <= n
inline void rangeUpdate(int l, int r, ll v) {
    diff[l]     += v;
    diff[r + 1] -= v;      // efeknya berhenti SETELAH r
}

// Rekonstruksi array final ke dalam diff itu sendiri (in-place).
// Setelah dipanggil, diff[i] berisi nilai akhir a[i].
inline void rekonstruksi(int n) {
    for (int i = 1; i <= n; i++)
        diff[i] += diff[i - 1];
}

// Reset sebelum test case berikutnya.
inline void resetDiff(int n) {
    for (int i = 0; i <= n + 1; i++) diff[i] = 0;
}

// ─── DIFFERENCE ARRAY 1D (VECTOR / DINAMIS) ──────────────

struct DiffArray {
    int n;
    vector<ll> d;

    // Mulai dari array nol
    explicit DiffArray(int n_) : n(n_), d(n_ + 2, 0) {}

    // Mulai dari array awal a[1..n] yang sudah ada isinya
    DiffArray(int n_, const vector<ll>& a) : n(n_), d(n_ + 2, 0) {
        for (int i = 1; i <= n; i++) d[i] = a[i] - a[i - 1];
    }

    void update(int l, int r, ll v) {
        d[l]     += v;
        d[r + 1] -= v;
    }

    // Kembalikan array final a[1..n]
    vector<ll> build() {
        vector<ll> a(n + 1, 0);
        ll jalan = 0;
        for (int i = 1; i <= n; i++) {
            jalan += d[i];
            a[i] = jalan;
        }
        return a;
    }

    // Nilai maksimum setelah semua update, tanpa menyimpan array
    ll maksimum() {
        ll jalan = 0, best = LLONG_MIN;
        for (int i = 1; i <= n; i++) {
            jalan += d[i];
            best = max(best, jalan);
        }
        return best;
    }
};

// ─── SWEEP LINE / EVENT COUNTING (koordinat besar) ───────
// Dipakai kalau posisi sampai 1e9 tapi jumlah interval kecil.
// Interval [s, e) artinya aktif mulai s, berhenti tepat sebelum e.

struct SweepLine {
    map<ll, ll> ev;                   // posisi -> perubahan

    void tambahInterval(ll s, ll e, ll v = 1) {
        ev[s] += v;
        ev[e] -= v;
    }

    // Jumlah maksimum yang aktif bersamaan
    ll maksimumBersamaan() {
        ll jalan = 0, best = 0;
        for (auto& [pos, delta] : ev) {
            jalan += delta;
            best = max(best, jalan);
        }
        return best;
    }
};

// ─── DIFFERENCE ARRAY 2D (UPDATE SUBMATRIKS) ─────────────

const int MAXG = 1005;
ll diff2[MAXG][MAXG];

// Tambahkan v ke submatriks (r1,c1) sampai (r2,c2). O(1).
inline void rangeUpdate2D(int r1, int c1, int r2, int c2, ll v) {
    diff2[r1][c1]         += v;
    diff2[r1][c2 + 1]     -= v;
    diff2[r2 + 1][c1]     -= v;
    diff2[r2 + 1][c2 + 1] += v;   // pojok terlanjur dikurangi 2x, kembalikan 1x
}

// Rekonstruksi grid final (prefix sum 2D in-place). O(n*m).
inline void rekonstruksi2D(int n, int m) {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            diff2[i][j] += diff2[i-1][j] + diff2[i][j-1] - diff2[i-1][j-1];
}

// ─── MAIN ────────────────────────────────────────────────

int main() {
    FASTIO;

    // Contoh pemakaian: n elemen, q update, cetak array akhir
    int n, q;
    if (!(cin >> n >> q)) return 0;

    DiffArray da(n);
    for (int i = 0; i < q; i++) {
        int l, r;
        ll v;
        cin >> l >> r >> v;
        da.update(l, r, v);
    }

    vector<ll> a = da.build();
    for (int i = 1; i <= n; i++)
        cout << a[i] << " \n"[i == n];

    return 0;
}
