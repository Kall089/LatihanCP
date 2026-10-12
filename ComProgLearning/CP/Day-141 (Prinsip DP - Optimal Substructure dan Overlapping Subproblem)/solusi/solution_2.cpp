/*
============================================================
✅ Solution 2: Naik Tangga dengan K Langkah
============================================================
Approach: DP 1D dengan K transisi per state
Complexity: Time O(N x K) | Space O(N)
Key Insight:
Struktur DP-nya tidak berubah sama sekali, hanya jumlah kemungkinan
langkah terakhirnya yang bertambah dari 2 menjadi K. Ini pola yang
sangat umum: memperbanyak pilihan tidak mengubah kerangka DP, hanya
menambah satu loop di dalam.

Kalau tidak ada satu pun cara mencapai tangga ke-N, dp[N] otomatis
bernilai 0 tanpa perlu penanganan khusus.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    const ll MOD = 1000000007;
    int n, k;
    if (!(cin >> n >> k)) return 0;
    vector<int> langkah(k);
    for (int &x : langkah) cin >> x;

    vector<ll> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int l : langkah)
            if (i - l >= 0) dp[i] = (dp[i] + dp[i - l]) % MOD;

    cout << dp[n] << "\n";

    return 0;
}
