/*
============================================================
📦 TEMPLATE BOILERPLATE: Rekonstruksi Jalur & Jawaban DP
============================================================
Day: 152 | Topic: DP Path Reconstruction, Parent Array, & Table Backtracking
Standard: C++17 Competitive Programming Template

Fungsi-fungsi pembantu yang tersedia di template ini:
1. `reconstructKnapsack01(weights, values, W)`:
   Knapsack 0/1 standar dengan penelusuran mundur tabel untuk mengembalikan
   nilai maksimum beserta daftar indeks barang yang dipilih (1-indexed).
2. `reconstructLCS(s, t)`:
   Longest Common Subsequence dengan penelusuran mundur tabel 2D untuk
   mengembalikan string LCS konkret.
3. `reconstructGridMinPath(grid)`:
   Mencari biaya minimum dan string langkah ('D' / 'R') dari pojok kiri atas
   ke pojok kanan bawah menggunakan Suffix DP (leksikografis 'D' < 'R').
4. `reconstructLIS(arr)`:
   Longest Increasing Subsequence dengan Pola Parent Array untuk mengembalikan
   panjang LIS beserta elemen-elemen barisan aslinya.
5. `reconstructCoinChange(coins, amount)`:
   Unbounded Coin Change dengan greedy-forward traversal untuk mengembalikan
   kombinasi koin minimum yang terkecil secara leksikografis.
6. `reconstructFrogJump(h)`:
   Frog Jump dengan Suffix DP untuk mengembalikan biaya energi minimum beserta
   daftar nomor pos yang dikunjungi terurut leksikografis.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

// 1. 0/1 Knapsack Reconstruction (Table Backtracking)
pair<ll, vector<int>> reconstructKnapsack01(const vector<ll>& w, const vector<ll>& v, int W) {
    int n = w.size();
    vector<vector<ll>> dp(n + 1, vector<ll>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= w[i - 1]) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - w[i - 1]] + v[i - 1]);
            }
        }
    }

    vector<int> chosen;
    int cur_w = W;
    for (int i = n; i >= 1; i--) {
        if (dp[i][cur_w] != dp[i - 1][cur_w]) {
            chosen.push_back(i); // 1-indexed
            cur_w -= w[i - 1];
        }
    }
    reverse(chosen.begin(), chosen.end());
    return {dp[n][W], chosen};
}

// 2. LCS String Reconstruction (Table Backtracking)
string reconstructLCS(const string& s, const string& t) {
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

    string res = "";
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (s[i - 1] == t[j - 1]) {
            res.push_back(s[i - 1]);
            i--; j--;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    reverse(res.begin(), res.end());
    return res;
}

// 3. Grid Min Path ('D' and 'R' Lexicographical via Suffix DP)
pair<ll, string> reconstructGridMinPath(const vector<vector<ll>>& grid) {
    int R = grid.size();
    int C = grid[0].size();
    vector<vector<ll>> dp(R, vector<ll>(C, INF));
    dp[R - 1][C - 1] = grid[R - 1][C - 1];

    for (int r = R - 1; r >= 0; r--) {
        for (int c = C - 1; c >= 0; c--) {
            if (r == R - 1 && c == C - 1) continue;
            ll nxt = INF;
            if (r + 1 < R) nxt = min(nxt, dp[r + 1][c]);
            if (c + 1 < C) nxt = min(nxt, dp[r][c + 1]);
            dp[r][c] = grid[r][c] + nxt;
        }
    }

    string path = "";
    int r = 0, c = 0;
    while (r < R - 1 || c < C - 1) {
        if (r + 1 < R && dp[r][c] == grid[r][c] + dp[r + 1][c]) {
            path.push_back('D');
            r++;
        } else {
            path.push_back('R');
            c++;
        }
    }
    return {dp[0][0], path};
}

// 4. LIS Reconstruction (Parent Array Pattern)
pair<int, vector<int>> reconstructLIS(const vector<int>& a) {
    int n = a.size();
    if (n == 0) return {0, {}};

    vector<int> dp(n, 1);
    vector<int> parent(n, -1);
    int best_len = 1, best_idx = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
        if (dp[i] > best_len) {
            best_len = dp[i];
            best_idx = i;
        }
    }

    vector<int> lis;
    int cur = best_idx;
    while (cur != -1) {
        lis.push_back(a[cur]);
        cur = parent[cur];
    }
    reverse(lis.begin(), lis.end());
    return {best_len, lis};
}

// 5. Lexicographical Coin Change (Greedy Forward)
pair<int, vector<int>> reconstructCoinChange(vector<int> c, int x) {
    sort(c.begin(), c.end());
    const int INF_INT = 1e9;
    vector<int> dp(x + 1, INF_INT);
    dp[0] = 0;

    for (int s = 1; s <= x; s++) {
        for (int v : c) {
            if (v <= s && dp[s - v] != INF_INT) {
                dp[s] = min(dp[s], dp[s - v] + 1);
            }
        }
    }

    if (dp[x] == INF_INT) return {-1, {}};
    vector<int> res;
    int cur = x;
    while (cur > 0) {
        for (int v : c) {
            if (v <= cur && dp[cur] == dp[cur - v] + 1) {
                res.push_back(v);
                cur -= v;
                break;
            }
        }
    }
    return {dp[x], res};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s, t;
    if (cin >> s >> t) {
        cout << reconstructLCS(s, t) << "\n";
    }

    return 0;
}
