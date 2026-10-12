#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-150 (DP pada Grid - Path Counting dan Minimum Path Sum)
 * Latihan 3: Jumlah Jalur Minimum
 *
 * Grid R x C berisi biaya non-negatif. Dari kiri-atas ke kanan-bawah dengan
 * gerakan kanan/bawah, cari total biaya terkecil (termasuk sel awal dan
 * tujuan).
 *
 * Batas: 1 <= R, C <= 1000, 0 <= a[i][j] <= 10^9
 *
// Test Case 1:
// Input:
// 3 3
// 1 3 1
// 1 5 1
// 4 2 1
// Output:
// 7
// (1 -> 3 -> 1 -> 1 -> 1)
//
// Test Case 2 (satu kolom):
// Input:
// 3 1
// 5
// 2
// 8
// Output:
// 15
//
// Test Case 3 (uji overflow: 1000x1 dengan nilai besar disederhanakan):
// Input:
// 2 2
// 1000000000 1000000000
// 1000000000 1000000000
// Output:
// 3000000000
 */

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main()
{
    int r, c;
    cin >> r >> c;

    vector<vector<int>> a(r, vector<int>(c));
    vector<vector<int>> dp(r, vector<int>(c, 0));

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> a[i][j];
        }
    }

    dp[0][0] = a[0][0];

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }

            int best = INF;

            if (i >= 1)
            {
                best = min(best, dp[i - 1][j]);
            }

            if (j >= 1)
            {
                best = min(best, dp[i][j - 1]);
            }

            dp[i][j] = a[i][j] + best;
        }
    }

    cout << dp[r - 1][c - 1];
}