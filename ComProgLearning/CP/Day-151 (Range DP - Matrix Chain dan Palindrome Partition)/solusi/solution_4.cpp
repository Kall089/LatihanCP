/*
============================================================
✅ Solution 4: Rekonstruksi Kurung Perkalian Matriks
============================================================
Approach: Range DP + Decision Split Backtracking
Complexity: Time O(N^3) | Space O(N^2)
Key Insight:
Untuk merekonstruksi urutan pengelompokan tanda kurung, kita mencatat indeks
titik pecah `k` yang menghasilkan biaya minimum ke dalam tabel `split[l][r]`.

Tabel Transisi:
Setiap kali `cost < dp[l][r]`:
  dp[l][r] = cost;
  split[l][r] = k;

Rekonstruksi Rekursif `buildExpr(l, r)`:
- Basis: Jika l == r, matriks tunggal A_{l+1}, return "A" + to_string(l + 1).
- Rekursi:
  int k = split[l][r];
  return "(" + buildExpr(l, k) + " x " + buildExpr(k + 1, r) + ")";
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

int n;
vector<vector<int>> split_pos;

string buildExpr(int l, int r) {
    if (l == r) {
        return "A" + to_string(l + 1);
    }
    int k = split_pos[l][r];
    return "(" + buildExpr(l, k) + " x " + buildExpr(k + 1, r) + ")";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;

    vector<ll> p(n + 1);
    for (int i = 0; i <= n; i++) {
        cin >> p[i];
    }

    vector<vector<ll>> dp(n, vector<ll>(n, 0));
    split_pos.assign(n, vector<int>(n, -1));

    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len <= n; l++) {
            int r = l + len - 1;
            dp[l][r] = INF;

            for (int k = l; k < r; k++) {
                ll cost = dp[l][k] + dp[k + 1][r] + p[l] * p[k + 1] * p[r + 1];
                if (cost < dp[l][r]) {
                    dp[l][r] = cost;
                    split_pos[l][r] = k;
                }
            }
        }
    }

    cout << dp[0][n - 1] << "\n";
    cout << buildExpr(0, n - 1) << "\n";

    return 0;
}
