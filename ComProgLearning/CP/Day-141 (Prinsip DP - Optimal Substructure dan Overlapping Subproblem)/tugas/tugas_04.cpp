/*
============================================================
📋 TUGAS 04: Koin Minimum
============================================================
Source: Original
Difficulty: Medium
Topics: DP 1D minimum

PROBLEM:
Diberikan K jenis koin (tak terbatas jumlahnya) dan target T.
Cetak jumlah koin minimal untuk membentuk T, atau -1 jika mustahil.

INPUT FORMAT:
- Baris 1: K T
- Baris 2: K nilai koin

OUTPUT FORMAT:
- Satu bilangan: koin minimal atau -1.

CONSTRAINTS:
- 1 <= K <= 100
- 1 <= T <= 10^6

SAMPLE INPUT 1:
3 12
2 5 9

SAMPLE OUTPUT 1:
3
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main()
{
    int n, T;
    cin >> n >> T;

    vector<int> koin(n);

    for (int i = 0; i < n; i++)
    {
        cin >> koin[i];
    }

    vector<int> dp(T + 1, INF);

    dp[0] = 0;

    for (int i = 0; i <= T; i++)
    {
        for (int x : koin)
        {
            if (i >= x && dp[i - x] != INF)
            {
                dp[i] = min(dp[i], dp[i - x] + 1);
            }
        }
    }

    cout << dp[T];
}