/*
============================================================
✅ Solution 1: Peti yang Hanya Bisa Digabung dari Samping
============================================================
Approach: Knuth Optimization for Range DP
Complexity: Time O(N^2) | Space O(N^2)
Key Insight:
1. Rekurensi Range DP:
   dp[l][r] = sum(l, r) + min_{l <= k < r} (dp[l][k] + dp[k+1][r]).
   Basis: dp[i][i] = 0 untuk semua i.

2. Quadrangle Inequality:
   Fungsi biaya interval C(l, r) = prefix[r+1] - prefix[l] adalah aditif,
   sehingga memenuhi C(a, c) + C(b, d) = C(a, d) + C(b, c) (persamaan Quadrangle).
   Selain itu, bobot a[i] >= 0 menjamin monotonisitas interval.

3. Batasan Knuth:
   opt[l][r-1] <= opt[l][r] <= opt[l+1][r].
   Loop k hanya berjalan di rentang tersebut, sehingga total iterasi loop terdalam
   membentuk deret teleskopik dengan total waktu O(N^2).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

ll solve_merge(int n, const vector<ll>& a) {
    if (n <= 1) return 0;

    vector<ll> pref(n + 1, 0);
    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] + a[i];
    }

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

    int n;
    if (!(cin >> n)) return 0;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    cout << solve_merge(n, a) << "\n";

    return 0;
}
