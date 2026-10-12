/*
============================================================
✅ Solution 2: Kasir dengan Laci Terbatas (Bounded Coin Change Min)
============================================================
Approach: Bounded Knapsack Dekomposisi Biner (Minimum Coins)
Complexity: Time O(X * sum(log(c_eff + 1))) | Space O(X)
Key Insight:
Pada Bounded Coin Change Minimum, kita ingin meminimalkan jumlah total keping koin
yang dipakai untuk mencapai EXACT target X rupiah.

Pecah stok koin jenis i menjadi paket-paket biner q keping.
Paket berukuran q keping memiliki:
- Nilai total nominal = q * w[i]
- Biaya penambahan keping = q keping (PENTING: biayanya adalah q, bukan 1!)

Inisialisasi:
- dp[0] = 0 (nominal 0 butuh 0 koin)
- dp[1...X] = INF (1e9, menandakan belum terjangkau)

Transisi 0/1 Knapsack loop mundur:
for (int s = X; s >= pkg_weight; s--) {
    if (dp[s - pkg_weight] != INF) {
        dp[s] = min(dp[s], dp[s - pkg_weight] + q);
    }
}
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    if (!(cin >> n >> x)) return 0;

    vector<int> dp(x + 1, INF);
    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        int weight;
        long long count;
        cin >> weight >> count;

        if (weight <= 0 || count <= 0 || x <= 0) continue;

        long long c_eff = min(count, (long long)(x / weight));

        long long p = 1;
        while (c_eff > 0) {
            long long q = min(p, c_eff);
            c_eff -= q;

            int pkg_weight = q * weight;
            int pkg_cost = q; // q keping koin

            for (int s = x; s >= pkg_weight; s--) {
                if (dp[s - pkg_weight] != INF) {
                    dp[s] = min(dp[s], dp[s - pkg_weight] + pkg_cost);
                }
            }

            p *= 2;
        }
    }

    if (dp[x] == INF) {
        cout << -1 << "\n";
    } else {
        cout << dp[x] << "\n";
    }

    return 0;
}
