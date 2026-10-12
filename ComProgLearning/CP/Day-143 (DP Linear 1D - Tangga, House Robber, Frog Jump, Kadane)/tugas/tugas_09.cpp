/*
============================================================
📋 TUGAS 09: Dice Combinations
============================================================
Source: CSES 1633
Difficulty: Easy
Topics: tangga dengan langkah 1..6

PROBLEM:
Berapa banyak cara membentuk jumlah N dengan lemparan dadu (nilai 1..6),
di mana URUTAN diperhatikan? Cetak modulo 10^9+7.

INPUT FORMAT: satu bilangan N
OUTPUT FORMAT: satu bilangan
CONSTRAINTS: 1 <= N <= 10^6

SAMPLE INPUT 1:   SAMPLE OUTPUT 1:
3                 4

SAMPLE INPUT 2:   SAMPLE OUTPUT 2:
1                 1

SAMPLE INPUT 3:   SAMPLE OUTPUT 3:
10                492
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<long long> dp(n + 1, 0);
    dp[0] = 1;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= 6; j++)
        {
            if (i >= j)
            {
                dp[i] = dp[i] + dp[i - j];
            }
        }
    }

    cout << dp[n];
}
