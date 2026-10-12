/*
============================================================
✅ Solution 5: Pembangunan Rantai Menara Telekomunikasi
============================================================
Approach: Knuth Optimization with Base Overhead Cost K
Complexity: Time O(N^2) | Space O(N^2)
Key Insight:
1. Fungsi Biaya:
   C(l, r) = sum_{t=l}^r w[t] + K.
   Karena C(a, c) + C(b, d) = C(a, d) + C(b, c) tetap berupa kesamaan eksak,
   Quadrangle Inequality berlaku secara ketat.

2. Invariant Knuth:
   opt[l][r-1] <= opt[l][r] <= opt[l+1][r].
   Loop k pada pencarian split terbaik untuk rentang [l, r]
   dibatasi oleh opt[l][r-1] dan opt[l+1][r].
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

ll solve_towers(int n, ll k_cost, const vector<ll>& w) {
    if (n <= 1) return 0;

    vector<ll> pref(n + 1, 0);
    for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + w[i];

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

            ll interval_cost = (pref[r + 1] - pref[l]) + k_cost;

            for (int k = k_low; k <= k_high; k++) {
                ll cost = dp[l][k] + dp[k + 1][r] + interval_cost;
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

    int n;
    ll k;
    if (!(cin >> n >> k)) return 0;

    vector<ll> w(n);
    for (int i = 0; i < n; i++) cin >> w[i];

    cout << solve_towers(n, k, w) << "\n";

    return 0;
}
