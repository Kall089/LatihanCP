/*
============================================================
✅ Solution 5: Hybrid Bounded Knapsack (Pintasan Unbounded)
============================================================
Approach: Complete Knapsack Hybrid (Unbounded Shortcut + Binary Splitting)
Complexity: Time <= O(W * sum(log(c_eff + 1))) | Space O(W)
Key Insight:
Jika c[i] * w[i] >= W, artinya stok barang tersebut tidak akan pernah habis
sebelum kapasitas tas ransel W terlampaui. Maka barang tersebut berperilaku
persis seperti Unbounded Knapsack, di mana setiap kapasitas s >= w[i] dapat
menggunakan kembali hasil perhitungan sebelumnya pada kapasitas (s - w[i]).

Struktur Algoritma Hybrid:
Untuk setiap barang i:
1. Jika (ll)count * weight >= W:
   // Jalankan Unbounded Knapsack (LOOP MAJU)
   for (int s = weight; s <= W; s++) {
       dp[s] = max(dp[s], dp[s - weight] + value);
   }
2. Jika (ll)count * weight < W:
   // Jalankan Bounded Knapsack Dekomposisi Biner (LOOP MUNDUR)
   ll p = 1, sisa = count;
   while (sisa > 0) {
       ll q = min(p, sisa);
       sisa -= q;
       int pkg_wt = q * weight;
       ll pkg_val = q * value;
       for (int s = W; s >= pkg_wt; s--) {
           dp[s] = max(dp[s], dp[s - pkg_wt] + pkg_val);
       }
       p *= 2;
   }

Keunggulan: Memangkas faktor logaritma menjadi tepat O(W) untuk setiap barang
yang stoknya melimpah!
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

        if (weight <= 0 || value < 0 || count <= 0 || W <= 0) continue;

        // Pintasan Unbounded
        if (count * (ll)weight >= W) {
            for (int s = weight; s <= W; s++) {
                dp[s] = max(dp[s], dp[s - weight] + value);
            }
        } else {
            // Dekomposisi Biner
            ll p = 1;
            ll sisa = count;
            while (sisa > 0) {
                ll q = min(p, sisa);
                sisa -= q;

                int pkg_weight = q * weight;
                ll pkg_value = q * value;

                for (int s = W; s >= pkg_weight; s--) {
                    dp[s] = max(dp[s], dp[s - pkg_weight] + pkg_value);
                }

                p *= 2;
            }
        }
    }

    cout << dp[W] << "\n";

    return 0;
}
