/*
============================================================
  Day 30 — Prefix Sum 2D & Submatrix Sum | CP Template
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
const int MAXN = 1005;

// ─── PREFIX SUM 2D (ARRAY STATIS) ────────────────────────

ll a[MAXN][MAXN];
ll psum[MAXN][MAXN];  // psum[i][j] = jumlah elemen A[1..i][1..j]

// Build prefix sum 2D dari matriks a[1..n][1..m]
// Baris 0 dan kolom 0 otomatis 0 (global array)
void buildPrefixSum2D(int n, int m) {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            psum[i][j] = a[i][j]
                       + psum[i-1][j]
                       + psum[i][j-1]
                       - psum[i-1][j-1];
}

// Query: jumlah elemen di submatriks [r1..r2][c1..c2]
// Syarat: 1 ≤ r1 ≤ r2 ≤ n, 1 ≤ c1 ≤ c2 ≤ m
ll querySum(int r1, int c1, int r2, int c2) {
    return psum[r2][c2]
         - psum[r1-1][c2]
         - psum[r2][c1-1]
         + psum[r1-1][c1-1];
}

// ─── PREFIX SUM 2D (VECTOR / DINAMIS) ────────────────────

struct PrefixSum2D {
    int n, m;
    vector<vector<ll>> ps;
    
    PrefixSum2D() : n(0), m(0) {}
    
    // Bangun dari matriks 1-indexed (baris 1..n, kolom 1..m)
    void build(vector<vector<ll>>& mat, int _n, int _m) {
        n = _n; m = _m;
        ps.assign(n + 1, vector<ll>(m + 1, 0));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                ps[i][j] = mat[i][j]
                         + ps[i-1][j]
                         + ps[i][j-1]
                         - ps[i-1][j-1];
    }
    
    // Query jumlah submatriks [r1..r2][c1..c2]
    ll query(int r1, int c1, int r2, int c2) {
        return ps[r2][c2]
             - ps[r1-1][c2]
             - ps[r2][c1-1]
             + ps[r1-1][c1-1];
    }
};

// ─── DIFFERENCE ARRAY 2D ─────────────────────────────────

ll diff[MAXN][MAXN];

// Update: tambahkan val ke semua elemen di [r1..r2][c1..c2]
void rangeAdd2D(int r1, int c1, int r2, int c2, ll val) {
    diff[r1][c1]     += val;
    diff[r1][c2+1]   -= val;
    diff[r2+1][c1]   -= val;
    diff[r2+1][c2+1] += val;
}

// Reconstruct: jalankan prefix sum 2D pada diff untuk dapat nilai akhir
void reconstructDiff2D(int n, int m) {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            diff[i][j] += diff[i-1][j] + diff[i][j-1] - diff[i-1][j-1];
}

// ─── HELPER: MAX SUBMATRIX SUM (FIXED SIZE K×L) ─────────

// Cari submatriks berukuran K×L dengan jumlah terbesar
ll maxSubmatrixSum(int n, int m, int K, int L) {
    ll best = LLONG_MIN;
    for (int i = K; i <= n; i++) {
        for (int j = L; j <= m; j++) {
            ll sum = querySum(i - K + 1, j - L + 1, i, j);
            best = max(best, sum);
        }
    }
    return best;
}

// ─── SHORTHAND ────────────────────────────────────────────

#define all(x)  (x).begin(), (x).end()
#define sz(x)   (int)(x).size()
#define pb      push_back
#define mp      make_pair

#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << "\n"
#else
#define dbg(x)
#endif

int main() {
    FASTIO;

    int n, m;
    cin >> n >> m;

    // Baca matriks (1-indexed)
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];

    // Build prefix sum 2D
    buildPrefixSum2D(n, m);

    // Jawab query
    int q;
    cin >> q;
    while (q--) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        cout << querySum(r1, c1, r2, c2) << '\n';
    }

    return 0;
}
