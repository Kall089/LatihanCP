/*
============================================================
📋 TUGAS 02: Min Cost Climbing Stairs
============================================================
Source: LC 746
Difficulty: Easy
Topics: min, biaya saat menginjak

PROBLEM:
Array cost[0..N-1]. Membayar cost[i] saat MENGINJAK anak tangga i, lalu boleh
naik 1 atau 2. Boleh memulai dari indeks 0 atau 1. Cari biaya minimum untuk
melewati puncak (indeks N).

INPUT FORMAT:
- Baris 1: N
- Baris 2: N bilangan
OUTPUT FORMAT: satu bilangan
CONSTRAINTS: 2 <= N <= 10^5, 0 <= cost[i] <= 999

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
3                      15
10 15 20

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
10                     6
1 100 1 1 1 100 1 1 100 1

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
2                      1
1 100
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // dp[i] = min(dp[i-1] + cost[i-1], dp[i-2] + cost[i-2]); dp[0]=dp[1]=0.

    int n;
    cin >> n;
    vector<int> a(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    vector<int> dp(n + 1, 0);
    dp[0] = dp[1] = 0;

    for (int i = 2; i <= n; i++)
    {
        dp[i] = min(dp[i - 1] + a[i - 1], dp[i - 2] + a[i - 2]);
    }

    for (int i = 0; i <= n; i++)
    {
        cout << dp[i] << " ";
    }
    cout << endl;

    cout << dp[n];
    return 0;
}
