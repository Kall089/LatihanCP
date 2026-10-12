/*
============================================================
📦 TEMPLATE BOILERPLATE: Range DP (Interval Dynamic Programming)
============================================================
Day: 151 | Topic: Range DP, Titik Pecah, & Pengisian Berdasarkan Panjang
Standard: C++17 Competitive Programming Template

Fungsi-fungsi pembantu yang tersedia di template ini:
1. `matrixChainMultiplication(p)`:
   Menghitung biaya skalar minimum perkalian rantai matriks dimensi p[0..N].
2. `matrixChainWithParens(p)`:
   Menghitung biaya minimum sekaligus mengembalikan string ekspresi tanda kurung.
3. `stoneMerging(a)`:
   Menghitung biaya minimum penggabungan N elemen bersebelahan (AtCoder Slimes).
4. `minPalindromePartitionCuts(s)`:
   Menghitung jumlah garis pemotongan minimum agar setiap bagian merupakan palindrom.
5. `burstBalloons(a)`:
   Reverse Range DP untuk meletuskan balon dengan perolehan koin maksimum.
6. `minCostToCutStick(L, cuts)`:
   Range DP pada koordinat pemotongan terurut untuk memotong batang berpanjang L.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

// 1. Matrix Chain Multiplication
ll matrixChainMultiplication(const vector<ll>& p) {
    int n = p.size() - 1;
    if (n <= 1) return 0;

    vector<vector<ll>> dp(n, vector<ll>(n, 0));

    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len <= n; l++) {
            int r = l + len - 1;
            dp[l][r] = INF;

            for (int k = l; k < r; k++) {
                ll cost = dp[l][k] + dp[k + 1][r] + p[l] * p[k + 1] * p[r + 1];
                dp[l][r] = min(dp[l][r], cost);
            }
        }
    }
    return dp[0][n - 1];
}

// 2. Matrix Chain Multiplication + Parentheses Reconstruction
pair<ll, string> matrixChainWithParens(const vector<ll>& p) {
    int n = p.size() - 1;
    if (n == 0) return {0, ""};
    if (n == 1) return {0, "A1"};

    vector<vector<ll>> dp(n, vector<ll>(n, 0));
    vector<vector<int>> split(n, vector<int>(n, -1));

    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len <= n; l++) {
            int r = l + len - 1;
            dp[l][r] = INF;

            for (int k = l; k < r; k++) {
                ll cost = dp[l][k] + dp[k + 1][r] + p[l] * p[k + 1] * p[r + 1];
                if (cost < dp[l][r]) {
                    dp[l][r] = cost;
                    split[l][r] = k;
                }
            }
        }
    }

    function<string(int, int)> build = [&](int l, int r) -> string {
        if (l == r) return "A" + to_string(l + 1);
        int k = split[l][r];
        return "(" + build(l, k) + " x " + build(k + 1, r) + ")";
    };

    return {dp[0][n - 1], build(0, n - 1)};
}

// 3. Stone Merging / Slimes (Adjacent Merge with Prefix Sums)
ll stoneMerging(const vector<ll>& a) {
    int n = a.size();
    if (n <= 1) return 0;

    vector<ll> pref(n + 1, 0);
    for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + a[i];

    vector<vector<ll>> dp(n, vector<ll>(n, 0));

    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len <= n; l++) {
            int r = l + len - 1;
            dp[l][r] = INF;
            ll sum_lr = pref[r + 1] - pref[l];

            for (int k = l; k < r; k++) {
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r] + sum_lr);
            }
        }
    }
    return dp[0][n - 1];
}

// 4. Palindrome Partitioning Minimum Cuts
int minPalindromePartitionCuts(const string& s) {
    int n = s.size();
    if (n <= 1) return 0;

    vector<vector<bool>> is_pal(n, vector<bool>(n, false));
    for (int len = 1; len <= n; len++) {
        for (int l = 0; l + len <= n; l++) {
            int r = l + len - 1;
            if (s[l] == s[r]) {
                is_pal[l][r] = (len <= 2 || is_pal[l + 1][r - 1]);
            }
        }
    }

    vector<int> dp(n + 1, n + 1);
    dp[0] = 0;
    for (int r = 1; r <= n; r++) {
        for (int l = 0; l < r; l++) {
            if (is_pal[l][r - 1]) {
                dp[r] = min(dp[r], dp[l] + 1);
            }
        }
    }
    return dp[n] - 1;
}

// 5. Burst Balloons (Reverse Range DP)
ll burstBalloons(const vector<int>& a) {
    int n = a.size();
    if (n == 0) return 0;

    vector<ll> nums(n + 2, 1);
    for (int i = 0; i < n; i++) nums[i + 1] = a[i];

    int m = n + 2;
    vector<vector<ll>> dp(m, vector<ll>(m, 0));

    for (int len = 2; len < m; len++) {
        for (int l = 0; l + len < m; l++) {
            int r = l + len;
            for (int k = l + 1; k < r; k++) {
                ll gain = dp[l][k] + dp[k][r] + nums[l] * nums[k] * nums[r];
                dp[l][r] = max(dp[l][r], gain);
            }
        }
    }
    return dp[0][m - 1];
}

// 6. Minimum Cost to Cut a Stick
ll minCostToCutStick(ll L, vector<int> cuts) {
    cuts.push_back(0);
    cuts.push_back(L);
    sort(cuts.begin(), cuts.end());

    int m = cuts.size();
    vector<vector<ll>> dp(m, vector<ll>(m, 0));

    for (int len = 2; len < m; len++) {
        for (int l = 0; l + len < m; l++) {
            int r = l + len;
            dp[l][r] = INF;
            ll cost_seg = cuts[r] - cuts[l];

            for (int k = l + 1; k < r; k++) {
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k][r] + cost_seg);
            }
        }
    }
    return dp[0][m - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        vector<ll> p(n + 1);
        for (int i = 0; i <= n; i++) cin >> p[i];
        auto res = matrixChainWithParens(p);
        cout << res.first << "\n" << res.second << "\n";
    }

    return 0;
}
