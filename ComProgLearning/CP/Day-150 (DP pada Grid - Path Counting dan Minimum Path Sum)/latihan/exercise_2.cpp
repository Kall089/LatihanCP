

/**
 * Topik: Day-150 (DP pada Grid - Path Counting dan Minimum Path Sum)
 * Latihan 2: Jalur dengan Halangan
 *
 * Grid R x C berisi '.' (bebas) dan '#' (terhalang). Hitung banyak jalur dari
 * kiri-atas ke kanan-bawah dengan gerakan kanan/bawah, modulo 10^9+7.
 * Jalur tidak boleh menginjak '#'.
 *
 * Batas: 1 <= R, C <= 1000
 *
// Test Case 1:
// Input:
// 3 4
// ...#
// .#..
// ....
// Output:
// 3
//
// Test Case 2 (jalan buntu total):
// Input:
// 2 2
// .#
// #.
// Output:
// 0
//
// Test Case 3 (SEL AWAL terhalang - jebakan klasik):
// Input:
// 2 2
// #.
// ..
// Output:
// 0
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int r, c;
    cin >> r >> c;

    vector<string> g(r);

    for (int i = 0; i < r; i++)
    {
        cin >> g[i];
    }

    vector<vector<int>> dp(r, vector<int>(c + 1, 0));

    if (g[0][0] == '.')
    {
        dp[0][0] = 1;
    }

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {

            if (g[i][j] == '#')
            {
                continue;
            }

            if (i >= 1)
            {
                dp[i][j] = dp[i][j] + dp[i - 1][j];
            }

            if (j >= 1)
            {
                dp[i][j] = dp[i][j] + dp[i][j - 1];
            }
        }
    }

    cout << dp[r - 1][c - 1];
}