/*
============================================================
✅ Solution 2: Memotong Pita Panggung (Cutting Stick DP)
============================================================
Approach: Reduction to Sequential Merging + Knuth Optimization
Complexity: Time O((M+1)^2) | Space O((M+1)^2)
Key Insight:
1. Pembalikan Masalah:
   Memotong pita panjang L pada M titik potong berbiaya sama persis dengan
   menggabungkan (M + 1) segmen potongan dari dalam ke luar.
   Segmen ke-i berukuran a[i] = p[i+1] - p[i] untuk i in [0, M],
   dengan p[0] = 0 dan p[M+1] = L.

2. Knuth Optimization:
   Karena a[i] > 0, jumlah segmen memenuhi Quadrangle Inequality dan monotonisitas.
   Titik pemisah optimal memenuhi opt[l][r-1] <= opt[l][r] <= opt[l+1][r].
   Sehingga DP berjalan dalam O((M+1)^2).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

ll solve_cuts(ll length, int m, const vector<ll>& cuts) {
    if (m == 0) return 0;

    int n = m + 1;
    vector<ll> p(m + 2);
    p[0] = 0;
    for (int i = 1; i <= m; i++) p[i] = cuts[i - 1];
    p[m + 1] = length;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) a[i] = p[i + 1] - p[i];

    vector<ll> pref(n + 1, 0);
    for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + a[i];

    vector<vector<ll>> dp(n, vector<ll>(n, 0));
    vector<vector<int>> opt(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        opt[i][i] = i;
    }

    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len <= n; l++) {
            int r = l + len - 1;
            dp[l][r] = INF;

            int k_low  = opt[l][r - 1];
            int k_high = min(r - 1, opt[l + 1][r]);

            for (int k = k_low; k <= k_high; k++) {
                ll cost = dp[l][k] + dp[k + 1][r] + (pref[r + 1] - pref[l]);
                if (cost <= dp[l][r]) {
                    dp[l][r] = cost;
                    opt[l][r] = k;
                }
            }
        }
    }

    return dp[0][n - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll l;
    int m;
    if (!(cin >> l >> m)) return 0;

    vector<ll> cuts(m);
    for (int i = 0; i < m; i++) cin >> cuts[i];

    cout << solve_cuts(l, m, cuts) << "\n";

    return 0;
}
