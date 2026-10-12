/*
============================================================
TEMPLATE Day 150 — DP pada Grid
============================================================
Grid kanan-bawah = DAG (i+j selalu naik). Urutan topologisnya GRATIS.
SENTINEL = elemen identitas operator gabung: 0 untuk +, INF untuk min,
-INF untuk max.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007LL;
const ll INF = LLONG_MAX / 4;
const ll NEG = LLONG_MIN / 4;

// ------------------------------------------------------------------
// 1. HITUNG JALUR — tanpa halangan, versi padding (indeks 1..R, 1..C)
// ------------------------------------------------------------------
ll countPaths(int R, int C) {
    vector<vector<ll>> dp(R + 1, vector<ll>(C + 1, 0));
    dp[1][1] = 1;                                   // set MANUAL
    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= C; j++) {
            if (i == 1 && j == 1) continue;         // JANGAN ditimpa
            dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % MOD;
        }
    return dp[R][C];
}

// ------------------------------------------------------------------
// 2. HITUNG JALUR DENGAN HALANGAN  ('#' = terhalang)
//    halangan -> dp = 0 (identitas penjumlahan: jalur otomatis mati)
// ------------------------------------------------------------------
ll countPathsObstacle(const vector<string>& g) {
    int R = g.size(), C = g[0].size();
    if (g[0][0] == '#' || g[R-1][C-1] == '#') return 0;   // PERIKSA DULU
    vector<vector<ll>> dp(R + 1, vector<ll>(C + 1, 0));
    dp[1][1] = 1;
    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= C; j++) {
            if (g[i-1][j-1] == '#') { dp[i][j] = 0; continue; }  // TUGASKAN 0
            if (i == 1 && j == 1) continue;
            dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % MOD;
        }
    return dp[R][C];
}

// ------------------------------------------------------------------
// 3. JUMLAH JALUR MINIMUM (tanpa halangan)
// ------------------------------------------------------------------
ll minPathSum(const vector<vector<ll>>& a) {
    int R = a.size(), C = a[0].size();
    vector<vector<ll>> dp(R, vector<ll>(C, 0));
    dp[0][0] = a[0][0];
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) {
            if (i == 0 && j == 0) continue;
            ll best = INF;
            if (i > 0) best = min(best, dp[i-1][j]);
            if (j > 0) best = min(best, dp[i][j-1]);
            dp[i][j] = a[i][j] + best;
        }
    return dp[R-1][C-1];
}

// ------------------------------------------------------------------
// 4. MINIMUM DENGAN HALANGAN — sentinel INF, dan HARUS DILEWATI
// ------------------------------------------------------------------
ll minPathObstacle(const vector<vector<ll>>& a, const vector<string>& g) {
    int R = a.size(), C = a[0].size();
    vector<vector<ll>> dp(R, vector<ll>(C, INF));
    if (g[0][0] == '#') return -1;
    dp[0][0] = a[0][0];
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) {
            if (g[i][j] == '#') { dp[i][j] = INF; continue; }
            if (i == 0 && j == 0) continue;
            ll best = INF;
            if (i > 0) best = min(best, dp[i-1][j]);
            if (j > 0) best = min(best, dp[i][j-1]);
            if (best >= INF) dp[i][j] = INF;        // JANGAN INF + a
            else             dp[i][j] = a[i][j] + best;
        }
    return dp[R-1][C-1] >= INF ? -1 : dp[R-1][C-1];
}

// ------------------------------------------------------------------
// 5. REKONSTRUKSI JALUR MINIMUM (butuh tabel PENUH)
// ------------------------------------------------------------------
vector<pair<int,int>> minPathTrace(const vector<vector<ll>>& dp) {
    int R = dp.size(), C = dp[0].size();
    vector<pair<int,int>> path;
    int i = R - 1, j = C - 1;
    while (i > 0 || j > 0) {                        // "||", BUKAN "&&"
        path.push_back({i, j});
        if (i == 0)                        j--;
        else if (j == 0)                   i--;
        else if (dp[i-1][j] <= dp[i][j-1]) i--;
        else                               j--;
    }
    path.push_back({0, 0});
    reverse(path.begin(), path.end());
    return path;
}

// ------------------------------------------------------------------
// 6. ROLLING ARRAY — memori O(C). Loop j KIRI KE KANAN.
//    Rekonstruksi menjadi mustahil.
// ------------------------------------------------------------------
ll countPathsRolling(const vector<string>& g) {
    int R = g.size(), C = g[0].size();
    if (g[0][0] == '#') return 0;
    vector<ll> dp(C, 0);
    dp[0] = 1;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) {
            if (g[i][j] == '#') { dp[j] = 0; continue; }
            if (j > 0) dp[j] = (dp[j] + dp[j-1]) % MOD;
            // dp[j] sebelum ditulis = baris ATAS ; dp[j-1] = KIRI
        }
    return dp[C-1];
}

// ------------------------------------------------------------------
// 7. TANPA HALANGAN -> KOMBINATORIKA C(R+C-2, R-1), O(R+C)
//    Dipakai kalau R, C sampai 10^6 sehingga tabel tidak muat.
// ------------------------------------------------------------------
ll power(ll b, ll e, ll m) { ll r = 1; b %= m; while (e) { if (e & 1) r = r*b%m; b = b*b%m; e >>= 1; } return r; }

ll countPathsCombinatoric(int R, int C) {
    int n = R + C - 2, k = R - 1;
    vector<ll> f(n + 1, 1);
    for (int i = 1; i <= n; i++) f[i] = f[i-1] * i % MOD;
    ll inv = power(f[k] * f[n-k] % MOD, MOD - 2, MOD);   // Fermat
    return f[n] * inv % MOD;
}

// ------------------------------------------------------------------
// 8. DUA JALUR SEKALIGUS — dp[k][i1][i2], k = i+j (langkah bersamaan)
//    Sel yang dilewati KEDUANYA hanya dihitung sekali.
//    O(R*C*R), bukan O((R*C)^2).
// ------------------------------------------------------------------
ll twoPaths(const vector<vector<ll>>& a) {
    int R = a.size(), C = a[0].size();
    int K = R + C - 2;
    vector<vector<ll>> cur(R, vector<ll>(R, NEG)), nxt;
    cur[0][0] = a[0][0];
    for (int k = 0; k < K; k++) {
        nxt.assign(R, vector<ll>(R, NEG));
        for (int i1 = 0; i1 < R; i1++)
            for (int i2 = 0; i2 < R; i2++) {
                if (cur[i1][i2] == NEG) continue;          // LEWATI sentinel
                for (int d1 = 0; d1 < 2; d1++)
                    for (int d2 = 0; d2 < 2; d2++) {
                        int n1 = i1 + d1, n2 = i2 + d2;
                        int j1 = k + 1 - n1, j2 = k + 1 - n2;
                        if (n1 >= R || n2 >= R) continue;
                        if (j1 < 0 || j1 >= C || j2 < 0 || j2 >= C) continue;
                        ll add = a[n1][j1] + (n1 == n2 ? 0 : a[n2][j2]);
                        nxt[n1][n2] = max(nxt[n1][n2], cur[i1][i2] + add);
                    }
            }
        cur = nxt;
    }
    return cur[R-1][R-1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // Salin bagian yang dibutuhkan ke solusimu.
    return 0;
}
