#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-150 (DP pada Grid - Path Counting dan Minimum Path Sum)
 * Latihan 6: Dua Jalur Sekaligus
 *
 * Grid R x C berisi jumlah permen (non-negatif). DUA orang berjalan dari
 * (0,0) ke (R-1,C-1), keduanya hanya boleh kanan/bawah. Sel yang dilewati
 * KEDUANYA hanya dihitung sekali. Maksimalkan total permen yang terkumpul.
 *
 * Batas: 1 <= R, C <= 100, 0 <= a[i][j] <= 10^6
 *
// Test Case 1:
// Input:
// 2 2
// 1 2
// 3 4
// Output:
// 10
// (satu lewat kanan-bawah, satu lewat bawah-kanan; 1+2+4 dan 3 tambahan)
//
// Test Case 2 (satu sel):
// Input:
// 1 1
// 5
// Output:
// 5
//
// Test Case 3 (satu baris - keduanya terpaksa lewat jalur yang sama):
// Input:
// 1 4
// 1 2 3 4
// Output:
// 10
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int r, c;
    cin >> r >> c;

    vector<vector<int>> a(r, vector<int>(c, 0));
    vector<vector<int>> dp(r, vector<int>(c, 0));

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> a[i][j];
        }
    }

    dp[0][0] = a[0][0];

    for (int i = 1; i < r; i++)
    {
        for (int j = 1; j < c; j++)
        {
                }
    }
}