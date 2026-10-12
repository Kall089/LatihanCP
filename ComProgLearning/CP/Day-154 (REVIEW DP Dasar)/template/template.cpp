/*
============================================================
📦 TEMPLATE BOILERPLATE: Sintesis & Master Template DP Dasar
============================================================
Day: 154 | Topic: Review DP Dasar (5 Arketipe Kode Universal)
Standard: C++17 Competitive Programming Master Template

Template ini merangkum 5 arketipe inti DP dasar yang paling sering muncul di CP:
1. `dp_1D_sequence(nums)`:
   DP 1D dasar (House Robber / Jendela dependensi konstan).
2. `knapsack_01(w, v, W)`:
   0/1 Knapsack dengan 1 baris array berdimensi kapasitas O(W) loop mundur.
3. `two_strings_lcs(s, t)`:
   DP 2D Dua String (LCS / Edit Distance / String Alignment).
4. `grid_min_path(grid)`:
   DP 2D Grid (Min/Max Path Sum / Unique Paths).
5. `interval_range_dp(A)`:
   Range / Interval DP (Matrix Chain Multiplication / Stick Cutting, loop atas panjang L).
6. `coin_change_synthesis(coins, target)`:
   Sintesis Unbounded Optimization (Min Coins) + Unbounded Counting (Ways).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;
const int MOD = 1e9 + 7;

// 1. Kerangka DP 1D: House Robber / Barisan
ll dp_1D_sequence(const vector<ll>& nums) {
    ll prev2 = 0; // dp[i - 2]
    ll prev1 = 0; // dp[i - 1]

    for (ll x : nums) {
        ll cur = max(prev1, prev2 + x);
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

// 2. Kerangka Knapsack 0/1: Loop Kapasitas Mundur
ll knapsack_01(const vector<int>& w, const vector<ll>& v, int W) {
    int n = w.size();
    vector<ll> dp(W + 1, 0);

    for (int i = 0; i < n; i++) {
        for (int s = W; s >= w[i]; s--) {
            dp[s] = max(dp[s], dp[s - w[i]] + v[i]);
        }
    }
    return dp[W];
}

// 3. Kerangka Dua String: LCS 2D
int two_strings_lcs(const string& s, const string& t) {
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i - 1] == t[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][m];
}

// 4. Kerangka Grid 2D: Min Path Sum
ll grid_min_path(const vector<vector<ll>>& grid) {
    int r = grid.size(), c = grid[0].size();
    vector<vector<ll>> dp(r, vector<ll>(c, INF));
    dp[0][0] = grid[0][0];

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (i > 0) dp[i][j] = min(dp[i][j], dp[i - 1][j] + grid[i][j]);
            if (j > 0) dp[i][j] = min(dp[i][j], dp[i][j - 1] + grid[i][j]);
        }
    }
    return dp[r - 1][c - 1];
}

// 5. Kerangka Interval / Range DP: Matrix Chain Multiplication Pattern
ll interval_range_dp(const vector<ll>& arr) {
    int n = arr.size(); // n dimensi matriks, ada n-1 matriks
    vector<vector<ll>> dp(n, vector<ll>(n, 0));

    // Loop terluar WAJIB panjang interval L dari 2 ke n-1
    for (int L = 2; L < n; L++) {
        for (int i = 1; i < n - L + 1; i++) {
            int j = i + L - 1;
            dp[i][j] = INF;
            for (int k = i; k < j; k++) {
                ll cost = dp[i][k] + dp[k + 1][j] + arr[i - 1] * arr[k] * arr[j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }
    return dp[1][n - 1];
}

// 6. Kerangka Sintesis Coin Change: Min Coins & Ways
pair<int, int> coin_change_synthesis(const vector<int>& coins, int target) {
    const int INF_C = 1e9;
    vector<int> min_coins(target + 1, INF_C);
    vector<int> ways(target + 1, 0);

    min_coins[0] = 0;
    ways[0] = 1;

    for (int c : coins) {
        for (int s = c; s <= target; s++) {
            if (min_coins[s - c] != INF_C) {
                min_coins[s] = min(min_coins[s], min_coins[s - c] + 1);
            }
            ways[s] = (ways[s] + ways[s - c]) % MOD;
        }
    }

    int best_c = (min_coins[target] == INF_C ? -1 : min_coins[target]);
    return {best_c, ways[target]};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== MASTER TEMPLATE REVIEW DP DASAR ===\n";
    cout << "Semua modul siap digunakan untuk menyelesaikan 5 arketipe DP klasik.\n";

    return 0;
}
