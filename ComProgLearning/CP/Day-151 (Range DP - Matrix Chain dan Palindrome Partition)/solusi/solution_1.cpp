/*
============================================================
✅ Solution 1: Rantai Filter Citra Batik (Matrix Chain Multiplication)
============================================================
Approach: Range Dynamic Programming (Interval DP)
Complexity: Time O(N^3) | Space O(N^2)
Key Insight:
Definisikan dp[l][r] = biaya perkalian skalar minimum untuk mengalikan rantai
matriks dari indeks l sampai r (0-indexed).

Matriks hasil dari perkalian rantai l..r berukuran p[l] baris x p[r+1] kolom.
Langkah perkalian terakhir membagi rantai pada titik k (l <= k < r):
- Rantai kiri: l..k (menghasilkan matriks p[l] x p[k+1])
- Rantai kanan: (k+1)..r (menghasilkan matriks p[k+1] x p[r+1])
- Biaya penggabungan akhir: p[l] * p[k+1] * p[r+1]

Transisi:
dp[l][r] = min_{l <= k < r} (dp[l][k] + dp[k+1][r] + p[l] * p[k+1] * p[r+1])

Urutan evaluasi WAJIB berdasarkan panjang interval `len = 2 ... N`.
Gunakan tipe 64-bit `long long` karena perkalian dimensi dan biaya dapat
mencapai hingga ~ 1.8 * 10^17 (melampaui 32-bit integer).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<ll> p(n + 1);
    for (int i = 0; i <= n; i++) {
        cin >> p[i];
    }

    // dp[l][r]: biaya minimum mengalikan matriks l..r (0-indexed)
    vector<vector<ll>> dp(n, vector<ll>(n, 0));

    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len <= n; l++) {
            int r = l + len - 1;
            dp[l][r] = INF;

            for (int k = l; k < r; k++) {
                ll cost = dp[l][k] + dp[k + 1][r] + p[l] * p[k + 1] * p[r + 1];
                dp[l][r] = min(dp[l][r], cost);
            }
        }
    }

    cout << dp[0][n - 1] << "\n";

    return 0;
}
