/*
============================================================
✅ Solution 1: Paket Logistik Pulau (Bounded Knapsack Klasik)
============================================================
Approach: Bounded Knapsack dengan Dekomposisi Biner
Complexity: Time O(W * sum(log(c_eff + 1))) | Space O(W)
Key Insight:
Mengulang barang sebanyak stok c[i] memicu TLE saat c[i] bernilai besar.
Dengan memecah stok efektif c_eff = min(c[i], W / w[i]) menjadi paket pangkat
dua {1, 2, 4, ..., sisa}, kita mereduksi kuantitas barang menjadi O(log c_eff).

Setiap paket berukuran q unit memiliki:
- Bobot = q * w[i]
- Nilai = q * v[i]

Karena setiap paket hanya boleh diambil paling banyak 1 kali, kita mengevaluasi
setiap paket menggunakan 0/1 Knapsack dengan LOOP MUNDUR:
for (int s = W; s >= weight; s--) {
    dp[s] = max(dp[s], dp[s - weight] + value);
}

Karakteristik penting:
- Gunakan tipe data `long long` untuk nilai DP dan perkalian nilai paket.
- Clipping `c_eff = min(c[i], W / w[i])` mengamankan dari integer overflow.
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

    vector<ll> dp(W + 1, 0);

    for (int i = 0; i < n; i++) {
        int weight;
        ll value, count;
        cin >> weight >> value >> count;

        if (weight <= 0 || count <= 0 || W <= 0) continue;

        // Batasi stok efektif yang mungkin muat di ransel
        ll c_eff = min(count, (ll)(W / weight));

        // Dekomposisi biner
        ll p = 1;
        while (c_eff > 0) {
            ll q = min(p, c_eff);
            c_eff -= q;

            int pkg_weight = q * weight;
            ll pkg_value = q * value;

            // 0/1 Knapsack loop mundur
            for (int s = W; s >= pkg_weight; s--) {
                dp[s] = max(dp[s], dp[s - pkg_weight] + pkg_value);
            }

            p *= 2;
        }
    }

    cout << dp[W] << "\n";

    return 0;
}
