/*
============================================================
✅ Solution 3: Manifest Kapasitas Penuh (Exact Knapsack O(W) Space)
============================================================
Approach: 1D Knapsack DP with Backward Iteration
Complexity: Time O(N * W) | Space O(W)
Key Insight:
1. Mengapa 1D Knapsack Wajib Loop Mundur?
   Jika loop kapasitas bergerak maju dari w ke W:
   Saat s = 2w, dp[s] akan membaca dp[s - w] yang BARU SAJA diperbarui oleh barang ini,
   sehingga barang ini dipakai 2 kali (menjadi Unbounded Knapsack!).
   Dengan loop MUNDUR dari W turun ke w:
   dp[s - w] dijamin masih menyimpan nilai dari sebelum barang saat ini dipertimbangkan.
   Ini menjamin setiap barang dipakai paling banyak 1 kali.

2. State Exact Weight:
   dp[s] = nilai maksimum untuk mencapai berat TEPAT s.
   Basis:
   dp[0] = 0 (berat 0 dapat dicapai tanpa barang dengan nilai 0).
   dp[s] = -1 untuk s > 0 (awalnya semua kapasitas belum terjangkau).
   
   Saat iterasi mundur:
   if (dp[s - w] != -1) {
       dp[s] = max(dp[s], dp[s - w] + v);
   }

3. Efisiensi Memori:
   Hanya ada satu vector<ll> dp(W + 1) sebesar ~240 KB untuk W = 30.000.
   Barang dibaca langsung per baris (streaming input).
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

    // dp[s]: nilai maksimum untuk berat tepat s (-1 jika tidak mungkin)
    vector<ll> dp(W + 1, -1);
    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        int w;
        ll v;
        cin >> w >> v;

        // Loop kapasitas secara MUNDUR
        for (int s = W; s >= w; s--) {
            if (dp[s - w] != -1) {
                dp[s] = max(dp[s], dp[s - w] + v);
            }
        }
    }

    cout << dp[W] << "\n";

    return 0;
}
