#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-143 (DP Linear 1D)
 * Latihan 1: Menaiki Tangga
 *
 * Ada N anak tangga. Sekali melangkah boleh naik 1 atau 2 anak tangga.
 * Cetak banyak cara mencapai anak tangga ke-N, modulo 10^9+7.
 *
 * Batas: 1 <= N <= 10^6
 *
// Test Case 1:
// Input:
// 4
// Output:
// 5
// (1+1+1+1, 1+1+2, 1+2+1, 2+1+1, 2+2)
//
// Test Case 2 (batas bawah):
// Input:
// 1
// Output:
// 1
//
// Test Case 3 (uji modulo, hasil pasti > 10^9+7):
// Input:
// 100
// Output:
// 782204094
 */

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;

int main()
{
    int n;
    cin >> n;

    vector<long long> dp(n + 1, 0);

    dp[0] = 1;

    for (int i = 1; i <= n; i++)
    {
        if (i >= 1)
        {
            dp[i] = (dp[i - 1] + dp[i]) % MOD;
        }

        if (i >= 2)
        {
            dp[i] = (dp[i - 2] + dp[i]) % MOD;
        }
    }

    cout << dp[n];
}