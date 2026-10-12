/*
============================================================
✅ Solution 2: Menggabungkan Gudang Kopi (Stone Merging / Slimes)
============================================================
Approach: Range DP + 1D Prefix Sum
Complexity: Time O(N^3) | Space O(N^2)
Key Insight:
Definisikan dp[l][r] = biaya minimum menggabungkan karung dari indeks l sampai r
menjadi satu kelompok tunggal.

Karakteristik Kunci:
1. Operasi penggabungan terakhir untuk interval [l, r] pasti menggabungkan dua sub-kelompok:
   sub-kelompok kiri [l, k] dan sub-kelompok kanan [k + 1, r].
2. Biaya yang dibayar pada langkah terakhir adalah total berat kedua sub-kelompok,
   yang persis sama dengan jumlah berat semua karung dari indeks l sampai r:
   weight(l, r) = sum_{i=l}^r a[i] = pref[r + 1] - pref[l].
3. Nilai weight(l, r) ini konstan untuk semua pilihan k!
   Sehingga:
   dp[l][r] = min_{l <= k < r} (dp[l][k] + dp[k + 1][r]) + (pref[r + 1] - pref[l])

Basis: dp[i][i] = 0 (1 karung tidak butuh operasi apa pun).
Urutan evaluasi: len = 2 ... N.
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

    vector<ll> a(n);
    vector<ll> pref(n + 1, 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pref[i + 1] = pref[i] + a[i];
    }

    vector<vector<ll>> dp(n, vector<ll>(n, 0));

    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len <= n; l++) {
            int r = l + len - 1;
            dp[l][r] = INF;

            ll sum_lr = pref[r + 1] - pref[l];

            for (int k = l; k < r; k++) {
                ll cost = dp[l][k] + dp[k + 1][r] + sum_lr;
                dp[l][r] = min(dp[l][r], cost);
            }
        }
    }

    cout << dp[0][n - 1] << "\n";

    return 0;
}
