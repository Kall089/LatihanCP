/*
============================================================
✅ Solution 3: Bus Tambahan, Anggaran Tambahan (Flexible Groups D&C DP)
============================================================
Approach: Divide and Conquer DP Optimization across all group counts
Complexity: Time O(K * N log N) | Space O(N + K)
Key Insight:
1. Dekomposisi Masalah:
   Biaya tetap g * F hanya bergantung pada jumlah grup g, bukan pada bagaimana elemen dipartisi.
   Oleh karena itu, kita dapat menyelesaikan partisi murni dp[g][N] terlebih dahulu untuk setiap g = 1..K.

2. D&C DP Optimization:
   Untuk setiap layer g dari 1 sampai K, kita gunakan fungsi optimize berbasis Divide & Conquer
   dengan fungsi biaya (pref[r] - pref[l-1])^2.
   Hasil dp[g][N] disimpan dalam array `ans[g]`.

3. Pemilihan Kebijakan:
   Setelah seluruh ans[1..K] didapat, cari g \in [1, K] yang meminimalkan ans[g] + g * fee.
   Jika bernilai sama, g yang lebih kecil dipilih secara alami dengan operator `<`.
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
    ll fee;
    if (!(cin >> n >> k >> fee)) return 0;

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
    vector<ll> ans(k + 1, INF);
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
        ans[g] = dp_prev[n];
    }

    ll best_total = INF;
    int best_g = 1;

    for (int g = 1; g <= k; g++) {
        if (ans[g] == INF) continue;
        ll total = ans[g] + (ll)g * fee;
        if (total < best_total) {
            best_total = total;
            best_g = g;
        }
    }

    cout << best_total << " " << best_g << "\n";

    return 0;
}
