/*
============================================================
✅ Solution 1: Konvoi Logistik Festival (Sum Squared Partition D&C DP)
============================================================
Approach: Divide and Conquer DP Optimization
Complexity: Time O(K * N log N) | Space O(N) rolling array
Key Insight:
1. Rekurensi DP:
   dp[g][i] = min_{g-1 <= j < i} (dp[g-1][j] + (pref[i] - pref[j])^2).
   Dengan basis: dp[0][0] = 0, lainnya INF.

2. Sifat Monge:
   Fungsi biaya C(l, r) = (pref[r] - pref[l-1])^2 memenuhi sifat Monge karena elemen non-negatif.
   Maka titik potong optimal opt[g][i] tidak pernah mundur saat i bertambah.

3. Divide & Conquer:
   Untuk menghitung dp[g][mid], kita cari titik potong terbaik j di rentang [opt_l, min(opt_r, mid-1)].
   Kemudian subproblem kiri dibatasi [opt_l, best_j] dan subproblem kanan [best_j, opt_r].
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

    vector<ll> pref(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        ll val;
        cin >> val;
        pref[i] = pref[i - 1] + val;
    }

    auto cost = [&](int l, int r) -> ll {
        ll sum = pref[r] - pref[l - 1];
        return sum * sum;
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
