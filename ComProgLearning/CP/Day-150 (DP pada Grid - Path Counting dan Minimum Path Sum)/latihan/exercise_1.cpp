
/**
 * Topik: Day-150 (DP pada Grid - Path Counting dan Minimum Path Sum)
 * Latihan 1: Menghitung Jalur
 *
 * Grid berukuran R x C. Dari sudut kiri-atas ke sudut kanan-bawah, hanya boleh
 * bergerak KE KANAN atau KE BAWAH. Cetak banyak jalur berbeda, modulo 10^9+7.
 *
 * Batas: 1 <= R, C <= 1000
 *
// Test Case 1:
// Input:
// 3 7
// Output:
// 28
//
// Test Case 2 (satu baris - hanya satu jalur):
// Input:
// 1 5
// Output:
// 1
//
// Test Case 3 (uji modulo; hasil sesungguhnya sangat besar):
// Input:
// 100 100
// Output:
// 690285631
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int r, c;
    cin >> r >> c;

    vector<vector<int>> dp(r, vector<int>(c, 0));

    dp[0][0] = 1;

    for (int i = 0; i < r; i++)
    {

        for (int j = 0; j < c; j++)
        {
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
