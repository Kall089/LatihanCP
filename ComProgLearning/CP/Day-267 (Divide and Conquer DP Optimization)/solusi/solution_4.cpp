/*
============================================================
✅ Solution 4: Partisi Varians Minimum (Minimum Variance Partition)
============================================================
Approach: Divide and Conquer DP Optimization with Dual Prefix Sums
Complexity: Time O(K * N log N) | Space O(N)
Key Insight:
1. Evaluasi O(1) untuk Pairwise Difference Squared:
   sum_{l <= i < j <= r} (a[i] - a[j])^2
   = len * \sum a_i^2 - (\sum a_i)^2.
   Dengan pref[i] = \sum a_i dan pref_sq[i] = \sum a_i^2, nilai ini dapat dihitung dalam O(1).

2. Sifat Monge:
   Biaya varians skalar memenuhi Quadrangle Inequality pada barisan elemen terurut.
   Oleh karenanya, pembagian optimum opt[g][i] monoton tidak menurun.

3. Divide & Conquer DP:
   Setiap layer g dihitung dengan membagi rentang pencarian secara rekursif.
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

    vector<ll> a(n + 1);
    vector<ll> pref(n + 1, 0);
    vector<ll> pref_sq(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pref[i] = pref[i - 1] + a[i];
        pref_sq[i] = pref_sq[i - 1] + a[i] * a[i];
    }

    auto cost = [&](int l, int r) -> ll {
        ll len = r - l + 1;
        ll sum_sq = pref_sq[r] - pref_sq[l - 1];
        ll sum_val = pref[r] - pref[l - 1];
        return len * sum_sq - sum_val * sum_val;
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
