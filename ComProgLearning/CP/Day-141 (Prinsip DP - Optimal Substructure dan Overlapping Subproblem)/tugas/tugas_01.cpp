/*
============================================================
📋 TUGAS 01: Naik Tangga N=7
============================================================
Source: Original
Difficulty: Easy
Topics: DP 1D berapa cara

PROBLEM:
Ada N anak tangga, sekali melangkah boleh naik 1 atau 2 tangga.
Hitung banyaknya cara mencapai tangga ke-N, modulo 1000000007.

INPUT FORMAT:
- Satu baris: N

OUTPUT FORMAT:
- Satu bilangan: banyaknya cara.

CONSTRAINTS:
- 1 <= N <= 10^6

SAMPLE INPUT 1:
7

SAMPLE OUTPUT 1:
21
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

    cout << dp[n];
}