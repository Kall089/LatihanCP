/*
============================================================
✅ Solution 6: Penukaran Koin dengan Biaya Transaksi
============================================================
Approach: Dynamic Programming 1D (Weighted Unbounded Knapsack - Minimum Cost)
Complexity: Time O(N * X) | Space O(X)
Key Insight:
Setiap kali pecahan ke-k bernilai c[k] digunakan, kita mengeluarkan biaya p[k].
Tujuan kita adalah mencapai EXACT nominal X dengan akumulasi biaya minimum.

Kita mendefinisikan:
dp[i] = biaya minimum untuk membentuk tepat nominal i.

Base case:
dp[0] = 0 (nominal 0 berbiaya 0).
dp[1...X] = INF (1e18, menandakan nominal belum dapat dicapai).

Transisi:
Untuk setiap pecahan k (0 <= k < N):
  Untuk nominal i dari c[k] ke X (loop MAJU agar pecahan boleh dipakai berulang):
    if (dp[i - c[k]] != INF) {
        dp[i] = min(dp[i], dp[i - c[k]] + p[k]);
    }

Penggunaan tipe data long long sangat krusial karena akumulasi biaya
bisa melampaui batas representasi 32-bit (2 * 10^9).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    if (!(cin >> n >> x)) return 0;

    vector<int> c(n);
    vector<ll> p(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i] >> p[i];
    }

    // Step 1: Inisialisasi DP dengan INF
    vector<ll> dp(x + 1, INF);
    dp[0] = 0;

    // Step 2: Tabulasi Unbounded Knapsack Minimum Cost
    for (int k = 0; k < n; k++) {
        for (int i = c[k]; i <= x; i++) {
            if (dp[i - c[k]] != INF) {
                dp[i] = min(dp[i], dp[i - c[k]] + p[k]);
            }
        }
    }

    // Step 3: Output hasil
    if (dp[x] == INF) {
        cout << -1 << "\n";
    } else {
        cout << dp[x] << "\n";
    }

    return 0;
}
