#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-150 (DP pada Grid - Path Counting dan Minimum Path Sum)
 * Latihan 5: Maksimum Permen dengan Halangan
 *
 * Grid R x C. Setiap sel berisi bilangan: -1 berarti TEMBOK (tidak boleh
 * diinjak), selain itu jumlah permen di sel itu. Dari kiri-atas ke kanan-bawah
 * dengan gerakan kanan/bawah, maksimalkan total permen.
 * Cetak -1 jika tidak ada jalur sama sekali.
 *
 * Batas: 1 <= R, C <= 1000, -1 <= a[i][j] <= 10^9
 *
// Test Case 1:
// Input:
// 3 3
// 1 2 3
// -1 -1 4
// 7 8 5
// Output:
// 15
// (1+2+3+4+5 = 15)
//
// Test Case 2 (tembok memblokir total):
// Input:
// 2 2
// 1 -1
// -1 1
// Output:
// -1
//
// Test Case 3 (tanpa tembok):
// Input:
// 2 2
// 1 2
// 3 4
// Output:
// 8
// (1+3+4 = 8, lebih besar daripada 1+2+4 = 7)
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int r, c;
    cin >> r >> c;

    vector<vector<int>> a(r, vector<int>(c, 0));
    vector<vector<int>> dp(r, vector<int>(c, -1));

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> a[i][j];
        }
    }

    if (a[0][0] != -1)
    {
        dp[0][0] = a[0][0];
    }

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if ((i == 0 && j == 0) || a[i][j] == -1)
            {
                continue;
            }

            int best = -1;

            if (i >= 1)
            {
                best = max(best, dp[i - 1][j]);
            }

            if (j >= 1)
            {
                best = max(best, dp[i][j - 1]);
            }

            if (best != -1)
            {
                dp[i][j] = best + a[i][j];
            }
        }
    }

    cout << dp[r - 1][c - 1];
}