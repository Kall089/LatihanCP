/*
============================================================
📋 TUGAS 04: Grid 1 (Banyak Jalur di Grid)
============================================================
Source: AtCoder DP-H
Difficulty: Easy
Topics: DAG tersembunyi di grid

PROBLEM:
Grid H x W berisi '.' dan '#'. Dari (1,1) ke (H,W), hanya boleh bergerak ke
kanan atau ke bawah, dan tidak boleh menginjak '#'. Hitung banyak jalur
modulo 10^9+7.

INPUT FORMAT:
- Baris 1: H W
- H baris berisi W karakter

OUTPUT FORMAT:
- satu bilangan

CONSTRAINTS:
- 2 <= H, W <= 1000

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
3 4                    3
...#
.#..
....

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
2 2                    0
.#
#.

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
2 3                    3
...
...
============================================================
*/

#include <bits/stdc++.h>

using namespace std;

int main()
{
    int r, c;
    cin >> r >> c;

    vector<int> s_row;

    for (int i = 0; i < r; i++)
    {
        cin >> s_row[i];
    }

    vector<vector<int>> dp(r, vector<int>(c));

    dp[0][0] = 1;

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }

            if (i >=)
        }
    }
}