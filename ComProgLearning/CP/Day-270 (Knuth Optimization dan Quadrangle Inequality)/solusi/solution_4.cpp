/*
============================================================
✅ Solution 4: Pohon Pencarian Biner Optimal (Optimal BST)
============================================================
Approach: Knuth Optimization for Optimal Binary Search Tree
Complexity: Time O(N^2) | Space O(N^2)
Key Insight:
1. Rekurensi OBST:
   dp[l][r] = sum(l, r) + min_{l <= k <= r} (dp[l][k-1] + dp[k+1][r]).
   Di mana k adalah kunci yang dipilih menjadi akar dari sub-pohon kunci l..r.
   Basis:
   - Jika l > r (sub-pohon kosong): dp[l][r] = 0.
   - Jika l == r (satu kunci): dp[l][l] = f[l], opt[l][l] = l.

2. Knuth Invariant:
   Titik akar optimal memenuhi sifat monotonisitas Knuth-Yao:
   opt[l][r-1] <= opt[l][r] <= opt[l+1][r].
   Sehingga pencarian k dibatasi pada rentang [opt[l][r-1], opt[l+1][r]].
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

ll solve_obst(int n, const vector<ll>& f) {
    if (n == 0) return 0;

    vector<ll> pref(n + 1, 0);
    for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + f[i];

    // dp[l][r]: menggunakan padding indeks agar penanganan k-1 dan k+1 aman
    vector<vector<ll>> dp(n + 2, vector<ll>(n + 2, 0));
    vector<vector<int>> opt(n + 2, vector<int>(n + 2, 0));

    for (int i = 1; i <= n; i++) {
        dp[i][i] = f[i - 1];
        opt[i][i] = i;
    }

    for (int len = 2; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            dp[l][r] = INF;

            int k_low  = opt[l][r - 1];
            int k_high = opt[l + 1][r];

            ll sum_f = pref[r] - pref[l - 1];

            for (int k = k_low; k <= k_high; k++) {
                ll cost = dp[l][k - 1] + dp[k + 1][r] + sum_f;
                if (cost <= dp[l][r]) {
                    dp[l][r] = cost;
                    opt[l][r] = k;
                }
            }
        }
    }

    return dp[1][n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<ll> f(n);
    for (int i = 0; i < n; i++) cin >> f[i];

    cout << solve_obst(n, f) << "\n";

    return 0;
}
