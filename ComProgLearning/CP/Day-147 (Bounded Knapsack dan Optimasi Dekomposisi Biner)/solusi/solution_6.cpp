/*
============================================================
✅ Solution 6: Bounded Knapsack Kapasitas Tepat (Exact Target)
============================================================
Approach: Bounded Knapsack Dekomposisi Biner + Exact Reachability Tracking
Complexity: Time O(W * sum(log(c_eff + 1))) | Space O(W)
Key Insight:
Pada Exact Target Knapsack, kapasitas ransel harus terisi TEPAT sebesar W.

Inisialisasi:
- `vector<ll> dp(W + 1, -1);` (semua bernilai -1, menandakan belum terjangkau secara tepat).
- `dp[0] = 0;` (kapasitas 0 terjangkau dengan mengambil 0 barang bernilai 0).

Transisi Paket Biner (Loop Mundur):
Untuk setiap paket (pkg_weight, pkg_value):
for (int s = W; s >= pkg_weight; s--) {
    if (dp[s - pkg_weight] != -1) {
        dp[s] = max(dp[s], dp[s - pkg_weight] + pkg_value);
    }
}

Hasil akhir: `dp[W]`. Jika tetap -1, artinya tidak ada kombinasi kuantitas barang
yang menghasilkan total bobot tepat W.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, W;
    if (!(cin >> n >> W)) return 0;

    vector<ll> dp(W + 1, -1);
    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        int weight;
        ll value, count;
        cin >> weight >> value >> count;

        if (weight <= 0 || count <= 0 || W < 0) continue;

        ll c_eff = min(count, (ll)(W / weight));

        ll p = 1;
        while (c_eff > 0) {
            ll q = min(p, c_eff);
            c_eff -= q;

            int pkg_weight = q * weight;
            ll pkg_value = q * value;

            for (int s = W; s >= pkg_weight; s--) {
                if (dp[s - pkg_weight] != -1) {
                    dp[s] = max(dp[s], dp[s - pkg_weight] + pkg_value);
                }
            }

            p *= 2;
        }
    }

    cout << dp[W] << "\n";

    return 0;
}
