/*
============================================================
📋 TUGAS 02: Dadu Melangkah
============================================================
Source: Original
Difficulty: Easy
Topics: DP 1D banyak transisi

PROBLEM:
Kamu melangkah dengan melempar dadu. Sekali langkah boleh maju 1, 2, atau 3 petak.
Hitung banyaknya cara mencapai petak ke-N, modulo 1000000007.

INPUT FORMAT:
- Satu baris: N

OUTPUT FORMAT:
- Satu bilangan: banyaknya cara.

CONSTRAINTS:
- 1 <= N <= 10^6

SAMPLE INPUT 1:
10

SAMPLE OUTPUT 1:
274
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

        if (i >= 3)
        {
            dp[i] = dp[i - 3] + dp[i];
        }
    }

    cout << dp[n];
}