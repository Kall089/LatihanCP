/*
============================================================
✅ Solution 2: Posko di Jalan Panjang (Median Distance Cost D&C DP)
============================================================
Approach: Divide and Conquer DP Optimization with Prefix Sums
Complexity: Time O(K * N log N) | Space O(N)
Key Insight:
1. Optimalitas Median:
   Untuk meminimalkan \sum_{i=l}^r |x_i - p|, titik p terbaik adalah median m = (l + r) / 2.
   Total biaya segmen [l, r]:
   Cost(l, r) = \sum_{i=l}^m (x_m - x_i) + \sum_{i=m+1}^r (x_i - x_m)
              = x_m * (m - l + 1) - (pref[m] - pref[l-1])
                + (pref[r] - pref[m]) - x_m * (r - m).

2. Sifat Monge:
   Biaya jarak absolut ke median pada array terurut terbukti memenuhi Quadrangle Inequality.
   Oleh karena itu, titik potong optimal opt[g][i] monoton tidak menurun.

3. Divide & Conquer:
   Layer g dihitung dari layer g - 1 dalam waktu O(N log N) menggunakan pembagian biner rentang.
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
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pref[i] = pref[i - 1] + a[i];
    }

    auto cost = [&](int l, int r) -> ll {
        int m = l + (r - l) / 2;
        ll left_cost = a[m] * (m - l + 1) - (pref[m] - pref[l - 1]);
        ll right_cost = (pref[r] - pref[m]) - a[m] * (r - m);
        return left_cost + right_cost;
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
