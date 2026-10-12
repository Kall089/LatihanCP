/*
============================================================
✅ Solution 3: Kurasi Paket Tepat Berat (Exact Knapsack Reconstruction)
============================================================
Approach: Suffix 2D DP + Lexicographical 0/1 Decision String
Complexity: Time O(N * W) | Space O(N * W)
Key Insight:
1. Mengapa Suffix DP?
   Kita diminta menghasilkan string keputusan biner yang leksikografis terkecil
   dengan aturan '0' < '1'. Keputusan pada indeks barang yang lebih awal (i = 0, 1, ...)
   sangat mendominasi leksikografi seluruh string.
   Dengan Suffix DP:
   dp[i][s] = biaya minimum untuk memenuhi sisa berat tepat s menggunakan barang dari indeks i s.d. n - 1.
   Basis: dp[n][0] = 0, dp[n][s] = INF untuk s > 0.
   Transisi mundur i dari n - 1 ke 0:
     Pilihan 0 (Skip barang i): dp[i+1][s]
     Pilihan 1 (Take barang i): c[i] + dp[i+1][s - w[i]] (jika s >= w[i])
     dp[i][s] = min(Pilihan 0, Pilihan 1)

2. Rekonstruksi Maju:
   Mulai dari i = 0 dan s = W:
   Jika dp[i][s] == dp[i+1][s]:
     Artinya melewatkan barang i ('0') masih memungkinkan tercapainya biaya minimum!
     Maka kita PILIH '0' (tidak mengambil barang i, s tetap).
   Jika tidak sama:
     Kita terpaksa mengambil barang i ('1'), cetak '1' dan s = s - w[i].
   Proses ini berlangsung sampai i = n - 1.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, W;
    if (!(cin >> n >> W)) return 0;

    vector<int> w(n);
    vector<ll> c(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> c[i];
    }

    // dp[i][s]: biaya minimum untuk sisa berat s dari barang i s.d. n-1
    vector<vector<ll>> dp(n + 1, vector<ll>(W + 1, INF));
    dp[n][0] = 0;

    for (int i = n - 1; i >= 0; i--) {
        for (int s = 0; s <= W; s++) {
            // Pilihan 0: Tidak ambil barang i
            dp[i][s] = dp[i + 1][s];

            // Pilihan 1: Ambil barang i
            if (s >= w[i] && dp[i + 1][s - w[i]] != INF) {
                dp[i][s] = min(dp[i][s], c[i] + dp[i + 1][s - w[i]]);
            }
        }
    }

    if (dp[0][W] >= INF / 2) {
        cout << -1 << "\n";
        return 0;
    }

    cout << dp[0][W] << "\n";

    // Rekonstruksi string biner leksikografis terkecil ('0' < '1')
    string decision = "";
    int s = W;
    for (int i = 0; i < n; i++) {
        if (dp[i][s] == dp[i + 1][s]) {
            // Pilihan 0 valid dan optimal -> pilih '0'
            decision.push_back('0');
        } else {
            // Harus ambil barang i
            decision.push_back('1');
            s -= w[i];
        }
    }

    cout << decision << "\n";

    return 0;
}
