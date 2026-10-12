/*
============================================================
📋 TUGAS 03: House Robber
============================================================
Source: LC 198
Difficulty: Easy
Topics: larangan tetangga

PROBLEM:
Maksimalkan total tanpa mengambil dua elemen bersebelahan.

INPUT FORMAT:
- Baris 1: N
- Baris 2: N bilangan
OUTPUT FORMAT: satu bilangan
CONSTRAINTS: 1 <= N <= 2*10^5, 0 <= a[i] <= 10^9

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
4                      4
1 2 3 1

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
5                      12
2 7 9 3 1

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
2                      2
2 1
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    vector<int> dp(n, 0);

    dp[0] = a[0];
    dp[1] = max(dp[0], dp[1]);

    if (a.size() <= 2)
    {
        cout << dp[1];
        return 0;
    }

    for (int i = 2; i < n; i++)
    {
        dp[i] = max(dp[i - 1], dp[i - 2] + a[i]);
    }

    cout << dp[n - 1];
}