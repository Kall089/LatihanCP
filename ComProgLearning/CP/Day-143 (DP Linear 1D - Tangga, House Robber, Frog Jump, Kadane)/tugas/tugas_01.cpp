/*
============================================================
📋 TUGAS 01: Climbing Stairs
============================================================
Source: LC 70
Difficulty: Easy
Topics: dp[i] = dp[i-1] + dp[i-2]

PROBLEM:
Berapa banyak cara mencapai anak tangga ke-N dengan langkah 1 atau 2?

INPUT FORMAT: satu bilangan N
OUTPUT FORMAT: satu bilangan (mod 10^9+7)
CONSTRAINTS: 1 <= N <= 10^6

SAMPLE INPUT 1:   SAMPLE OUTPUT 1:
2                 2

SAMPLE INPUT 2:   SAMPLE OUTPUT 2:
5                 8

SAMPLE INPUT 3:   SAMPLE OUTPUT 3:
45                1836311903
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        if (i >= 1)
        {
            dp[i] = dp[i - 1] + dp[i];
        }

        if (i >= 2)
        {
            dp[i] = dp[i - 2] + dp[i];
        }
    }

    for (int i = 0; i <= n; i++)
    {
        cout << dp[i] << " ";
    }
}