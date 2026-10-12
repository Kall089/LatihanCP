/*
============================================================
✅ Solution 5: Letusan Balon Karnaval (Burst Balloons)
============================================================
Approach: Reverse Range DP (Interval Terbuka + Elemen Terakhir)
Complexity: Time O(N^3) | Space O(N^2)
Key Insight:
Jika kita mencoba mencari balon mana yang meletus PERTAMA, balon-balon di sebelah kiri
dan kanannya akan menjadi bertetangga, sehingga sub-masalah menjadi bergantung
pada balon-balon di luar rentang.

Solusi Elegannya: Pikirkan balon mana yang meletus TERAKHIR dalam rentang terbuka (l, r)!
Jika balon k adalah balon terakhir yang meletus di antara l dan r (l < k < r):
1. Semua balon di (l, k) sudah meletus sebelumnya.
2. Semua balon di (k, r) sudah meletus sebelumnya.
3. Oleh karena itu, saat balon k meletus, tetangga kiri langsungnya PASTI adalah balon l,
   dan tetangga kanan langsungnya PASTI adalah balon r!
4. Koin yang didapat dari meletusnya balon k adalah: nums[l] * nums[k] * nums[r].

Transisi:
dp[l][r] = max_{l < k < r} (dp[l][k] + dp[k][r] + nums[l] * nums[k] * nums[r])

Basis: dp[l][l + 1] = 0 (tidak ada balon di antara l dan l + 1).
Jawaban: dp[0][n + 1].
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // Tambahkan pembatas 1 di kedua ujung
    vector<ll> nums(n + 2);
    nums[0] = 1;
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
    }
    nums[n + 1] = 1;

    int total_len = n + 2;
    vector<vector<ll>> dp(total_len, vector<ll>(total_len, 0));

    // len adalah jarak antara batas l dan r (r - l)
    for (int len = 2; len < total_len; len++) {
        for (int l = 0; l + len < total_len; l++) {
            int r = l + len;
            for (int k = l + 1; k < r; k++) {
                ll gain = dp[l][k] + dp[k][r] + nums[l] * nums[k] * nums[r];
                dp[l][r] = max(dp[l][r], gain);
            }
        }
    }

    cout << dp[0][n + 1] << "\n";

    return 0;
}
