/*
============================================================
📦 TEMPLATE BOILERPLATE: Optimasi Memori DP (Rolling Array, 1D, & Bitset)
============================================================
Day: 153 | Topic: Memory-Optimized Dynamic Programming
Standard: C++17 Competitive Programming Template

Fungsi-fungsi pembantu yang tersedia di template ini:
1. `knapsack01_1D(w, v, W)`:
   0/1 Knapsack dengan 1 baris array berdimensi kapasitas O(W) menggunakan backward loop.
2. `knapsackUnbounded_1D(w, v, W)`:
   Unbounded Knapsack dengan 1 baris array berdimensi kapasitas O(W) menggunakan forward loop.
3. `lcsLength_2Row(s, t)`:
   Menghitung panjang LCS dengan 2 baris bergantian O(min(|s|, |t|)) memori via swap.
4. `editDistance_2Row(a, b)`:
   Menghitung Edit Distance dengan 2 baris bergantian O(min(|a|, |b|)) memori.
5. `gridMinPath_1D(grid)`:
   Menghitung jarak terpendek pada grid menggunakan 1 baris in-place O(C) memori.
6. `houseRobber_O1(nums)`:
   House Robber / Fibonacci DP dengan O(1) memori (sliding window 2 variabel).
7. `subsetSum_Bitset<MAX_T>(weights, target)`:
   Subset Sum boolean reachability dengan akselerasi 64x bitwise via std::bitset.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

// 1. 0/1 Knapsack dengan 1 Baris Array O(W) - Loop Mundur
ll knapsack01_1D(const vector<int>& w, const vector<ll>& v, int W) {
    int n = w.size();
    vector<ll> dp(W + 1, 0);

    for (int i = 0; i < n; i++) {
        for (int s = W; s >= w[i]; s--) {
            dp[s] = max(dp[s], dp[s - w[i]] + v[i]);
        }
    }
    return dp[W];
}

// 2. Unbounded Knapsack dengan 1 Baris Array O(W) - Loop Maju
ll knapsackUnbounded_1D(const vector<int>& w, const vector<ll>& v, int W) {
    int n = w.size();
    vector<ll> dp(W + 1, 0);

    for (int i = 0; i < n; i++) {
        for (int s = w[i]; s <= W; s++) {
            dp[s] = max(dp[s], dp[s - w[i]] + v[i]);
        }
    }
    return dp[W];
}

// 3. LCS Length dengan 2 Baris Bergantian O(min(N, M))
int lcsLength_2Row(string s, string t) {
    if (t.size() > s.size()) swap(s, t);
    int n = s.size(), m = t.size();
    vector<int> prev(m + 1, 0), cur(m + 1, 0);

    for (int i = 1; i <= n; i++) {
        cur[0] = 0;
        for (int j = 1; j <= m; j++) {
            if (s[i - 1] == t[j - 1]) {
                cur[j] = prev[j - 1] + 1;
            } else {
                cur[j] = max(prev[j], cur[j - 1]);
            }
        }
        prev.swap(cur);
    }
    return prev[m];
}

// 4. Edit Distance dengan 2 Baris Bergantian O(min(N, M))
int editDistance_2Row(string a, string b) {
    if (b.size() > a.size()) swap(a, b);
    int n = a.size(), m = b.size();
    vector<int> prev(m + 1), cur(m + 1);

    for (int j = 0; j <= m; j++) prev[j] = j;

    for (int i = 1; i <= n; i++) {
        cur[0] = i;
        for (int j = 1; j <= m; j++) {
            int cost = (a[i - 1] == b[j - 1] ? 0 : 1);
            cur[j] = min({prev[j] + 1, cur[j - 1] + 1, prev[j - 1] + cost});
        }
        prev.swap(cur);
    }
    return prev[m];
}

// 5. Grid Min Path dengan 1 Baris In-Place O(C)
ll gridMinPath_1D(const vector<vector<ll>>& grid) {
    int R = grid.size(), C = grid[0].size();
    vector<ll> dp(C, INF);

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (i == 0 && j == 0) {
                dp[j] = grid[i][j];
            } else {
                ll from_up = dp[j];
                ll from_left = (j > 0 ? dp[j - 1] : INF);
                dp[j] = grid[i][j] + min(from_up, from_left);
            }
        }
    }
    return dp[C - 1];
}

// 6. House Robber dengan O(1) Memory (2 State Variables)
ll houseRobber_O1(const vector<ll>& nums) {
    ll prev2 = 0; // dp[i-2]
    ll prev1 = 0; // dp[i-1]

    for (ll x : nums) {
        ll cur = max(prev1, prev2 + x);
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

// 7. Subset Sum Boolean dengan Bitset O(T / 8) Memory & 64x Speedup
template <size_t MAX_T>
bool subsetSum_Bitset(const vector<int>& weights, int target) {
    if (target < 0 || target >= (int)MAX_T) return false;
    bitset<MAX_T> bs;
    bs[0] = 1;

    for (int w : weights) {
        if (w <= target) {
            bs |= (bs << w);
        }
    }
    return bs[target];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s, t;
    if (cin >> s >> t) {
        cout << "LCS Length: " << lcsLength_2Row(s, t) << "\n";
    }

    return 0;
}
