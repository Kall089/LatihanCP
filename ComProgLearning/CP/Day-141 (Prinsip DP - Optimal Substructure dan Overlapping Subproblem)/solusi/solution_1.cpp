/*
============================================================
✅ Solution 1: Naik Tangga
============================================================
Approach: DP 1D bottom-up (tabulasi)
Complexity: Time O(N) | Space O(N)
Key Insight:
Kunci merancang DP adalah memikirkan LANGKAH TERAKHIR. Untuk sampai di
tangga ke-i, langkah terakhir hanya bisa berasal dari tangga (i-1) atau
(i-2). Kedua kemungkinan itu tidak bertumpang tindih dan mencakup semua
kasus, sehingga banyaknya cara tinggal dijumlahkan.

Basis dp[0] = 1 sering membingungkan. Bacanya: "ada satu cara untuk
berada di titik awal, yaitu tidak melakukan apa pun". Kalau diisi 0,
seluruh tabel akan menjadi 0.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    const ll MOD = 1000000007;
    int n;
    if (!(cin >> n))
        return 0;

    vector<ll> dp(n + 1, 0);
    dp[0] = 1; // basis: 1 cara untuk tidak melangkah
    for (int i = 1; i <= n; i++)
    {
        dp[i] = dp[i - 1]; // langkah terakhir = 1 tangga
        if (i >= 2)
            dp[i] = (dp[i] + dp[i - 2]) % MOD; // langkah terakhir = 2 tangga
    }

    cout << dp[n] << "\n";

    return 0;
}
