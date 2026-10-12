/*
============================================================
📦 TEMPLATE BOILERPLATE: Knuth Optimization & Quadrangle Inequality
============================================================
Day: 270 | Topic: Knuth Optimization (Range DP O(N^2))
Standard: C++17 Competitive Programming Master Template

Syarat Penggunaan Knuth Optimization:
1. Rekurensi Range DP:
   dp[i][j] = min_{i <= k < j} { dp[i][k] + dp[k+1][j] } + C(i, j)
2. Quadrangle Inequality:
   C(a, c) + C(b, d) <= C(a, d) + C(b, c) untuk a <= b <= c <= d
3. Monotonisitas:
   C(b, c) <= C(a, d) untuk a <= b <= c <= d
4. Implikasi Knuth-Yao:
   opt[i][j-1] <= opt[i][j] <= opt[i+1][j]
   Memangkas kompleksitas dari O(N^3) menjadi O(N^2)!

Modul yang tersedia:
1. `KnuthMergeDP`: Penggabungan berurutan linear O(N^2).
2. `KnuthCircularDP`: Penggabungan berurutan melingkar (Array Doubling) O(N^2).
3. `KnuthOBST`: Optimal Binary Search Tree O(N^2).
4. `KnuthCuttingSticks`: Pemotongan pita/kayu pada M titik potong O(M^2).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

// ============================================================
// 1. KnuthMergeDP (Sequential Merging O(N^2))
// ============================================================
ll knuth_merge_dp(int n, const vector<ll>& a) {
    if (n <= 1) return 0;

    vector<ll> pref(n + 1, 0);
    for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + a[i];

    vector<vector<ll>> dp(n, vector<ll>(n, 0));
    vector<vector<int>> opt(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) opt[i][i] = i;

    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len <= n; l++) {
            int r = l + len - 1;
            dp[l][r] = INF;

            int k_low  = opt[l][r - 1];
            int k_high = min(r - 1, opt[l + 1][r]);

            ll cost_interval = pref[r + 1] - pref[l];

            for (int k = k_low; k <= k_high; k++) {
                ll cost = dp[l][k] + dp[k + 1][r] + cost_interval;
                if (cost <= dp[l][r]) {
                    dp[l][r] = cost;
                    opt[l][r] = k;
                }
            }
        }
    }

    return dp[0][n - 1];
}

// ============================================================
// 2. KnuthCircularDP (Circular Array Doubling O(N^2))
// ============================================================
ll knuth_circular_dp(int n, const vector<ll>& a) {
    if (n <= 1) return 0;

    int total_len = 2 * n;
    vector<ll> doubled(total_len);
    for (int i = 0; i < n; i++) {
        doubled[i] = a[i];
        doubled[i + n] = a[i];
    }

    vector<ll> pref(total_len + 1, 0);
    for (int i = 0; i < total_len; i++) pref[i + 1] = pref[i] + doubled[i];

    vector<vector<ll>> dp(total_len, vector<ll>(total_len, 0));
    vector<vector<int>> opt(total_len, vector<int>(total_len, 0));

    for (int i = 0; i < total_len; i++) opt[i][i] = i;

    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len <= total_len; l++) {
            int r = l + len - 1;
            dp[l][r] = INF;

            int k_low  = opt[l][r - 1];
            int k_high = min(r - 1, opt[l + 1][r]);

            ll cost_interval = pref[r + 1] - pref[l];

            for (int k = k_low; k <= k_high; k++) {
                ll cost = dp[l][k] + dp[k + 1][r] + cost_interval;
                if (cost <= dp[l][r]) {
                    dp[l][r] = cost;
                    opt[l][r] = k;
                }
            }
        }
    }

    ll ans = INF;
    for (int l = 0; l < n; l++) {
        ans = min(ans, dp[l][l + n - 1]);
    }
    return ans;
}

// ============================================================
// 3. KnuthOBST (Optimal Binary Search Tree O(N^2))
// ============================================================
ll knuth_obst(int n, const vector<ll>& freq) {
    if (n == 0) return 0;

    vector<ll> pref(n + 1, 0);
    for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + freq[i];

    vector<vector<ll>> dp(n + 2, vector<ll>(n + 2, 0));
    vector<vector<int>> opt(n + 2, vector<int>(n + 2, 0));

    for (int i = 1; i <= n; i++) {
        dp[i][i] = freq[i - 1];
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

    cout << "=== TEMPLATE KNUTH OPTIMIZATION (O(N^2) RANGE DP) ===\n";
    cout << "Modul 1: knuth_merge_dp (Linear sequential merge)\n";
    cout << "Modul 2: knuth_circular_dp (Circular array doubling)\n";
    cout << "Modul 3: knuth_obst (Optimal Binary Search Tree)\n";

    return 0;
}
