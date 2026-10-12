/*
============================================================
✅ Solution 6: Gondola dan Indeks Ketidaksukaan (Ciel and Gondolas D&C DP)
============================================================
Approach: Divide and Conquer DP Optimization with 2D Prefix Sums
Complexity: Time O(K * N log N) | Space O(N^2) for prefix sum, O(N) for DP
Key Insight:
1. Perhitungan Biaya Segmen dalam O(1):
   Total ketidaksukaan pasangan dalam rentang [l, r]:
   Cost(l, r) = \sum_{l <= i < j <= r} u[i][j]
              = (\sum_{i=l}^r \sum_{j=l}^r u[i][j]) / 2.
   Dengan 2D prefix sum: pref[r][r] - pref[l-1][r] - pref[r][l-1] + pref[l-1][l-1],
   biaya submatriks dapat dievaluasi dalam O(1).

2. Sifat Monge:
   Penjumlahan submatriks non-negatif memenuhi Quadrangle Inequality.
   Oleh karena itu, titik potong optimal opt[g][i] bersifat monoton.

3. Divide & Conquer:
   Layer g dihitung dengan membagi interval [l, r] secara rekursif dan mempersempit
   pencarian titik potong terbaik ke [opt_l, opt_r].
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<vector<int>> pref(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int val;
            cin >> val;
            pref[i][j] = val + pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
        }
    }

    auto cost = [&](int l, int r) -> ll {
        int total = pref[r][r] - pref[l - 1][r] - pref[r][l - 1] + pref[l - 1][l - 1];
        return total / 2;
    };

    vector<ll> dp_prev(n + 1, INF);
    vector<ll> dp_curr(n + 1, INF);
    dp_prev[0] = 0;

    for (int g = 1; g <= k; g++) {
        fill(dp_curr.begin(), dp_curr.end(), INF);

        function<void(int, int, int, int)> compute = [&](int l, int r, int opt_l, int opt_r) {
            if (l > r) return;

            int mid = l + (r - l) / 2;
            int best_j = opt_l;
            ll best_val = INF;

            for (int j = opt_l; j <= min(opt_r, mid - 1); j++) {
                if (dp_prev[j] == INF) continue;
                ll cand = dp_prev[j] + cost(j + 1, mid);
                if (cand < best_val) {
                    best_val = cand;
                    best_j = j;
                }
            }

            dp_curr[mid] = best_val;

            compute(l, mid - 1, opt_l, best_j);
            compute(mid + 1, r, best_j, opt_r);
        };

        compute(g, n, g - 1, n - 1);
        dp_prev = dp_curr;
    }

    cout << dp_prev[n] << "\n";

    return 0;
}
