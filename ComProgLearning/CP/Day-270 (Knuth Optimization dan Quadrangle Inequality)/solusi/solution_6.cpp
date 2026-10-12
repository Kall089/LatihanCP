/*
============================================================
✅ Solution 6: Penggabungan File Arsip dengan Faktor Kompresi
============================================================
Approach: Scaled Cost Knuth Optimization
Complexity: Time O(N^2) | Space O(N^2)
Key Insight:
1. Skalar Positif:
   Fungsi biaya interval C(l, r) = M * sum_{t=l}^r s[t] dengan M > 0 tetap memenuhi
   Quadrangle Inequality dan monotonisitas secara sempurna.

2. Invariant Knuth:
   opt[l][r-1] <= opt[l][r] <= opt[l+1][r].
   Loop k dibatasi pada rentang tersebut.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

ll solve_archive(int n, ll m_mult, const vector<ll>& s) {
    if (n <= 1) return 0;

    vector<ll> pref(n + 1, 0);
    for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + s[i];

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

            ll interval_cost = m_mult * (pref[r + 1] - pref[l]);

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
    ll m;
    if (!(cin >> n >> m)) return 0;

    vector<ll> s(n);
    for (int i = 0; i < n; i++) cin >> s[i];

    cout << solve_archive(n, m, s) << "\n";

    return 0;
}
