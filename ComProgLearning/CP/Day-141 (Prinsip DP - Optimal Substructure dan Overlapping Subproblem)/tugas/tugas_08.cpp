/*
============================================================
📋 TUGAS 08: Biaya Naik Tangga Minimum
============================================================
Source: Original
Difficulty: Medium
Topics: DP 1D minimum + dua titik awal

PROBLEM:
Ada N anak tangga, menginjak tangga ke-i memerlukan biaya c[i].
Kamu boleh mulai dari tangga ke-1 atau ke-2, dan sekali melangkah
boleh naik 1 atau 2 tangga. Tentukan biaya minimal untuk melewati
seluruh tangga (mencapai posisi tepat setelah tangga terakhir).

INPUT FORMAT:
- Baris 1: N
- Baris 2: N bilangan c[i]

OUTPUT FORMAT:
- Satu bilangan: biaya minimal.

CONSTRAINTS:
- 1 <= N <= 10^6
- 0 <= c[i] <= 10^9

SAMPLE INPUT 1:
3
10 15 20

SAMPLE OUTPUT 1:
15
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

    vector<int> dp(n + 1, 0);

    for (int i = 2; i <= n; i++)
    {
        int lompat1 = dp[i - 1] + a[i - 1];
        int lompat2 = dp[i - 2] + a[i - 2];

        dp[i] = min(lompat1, lompat2);
    }

    cout << dp[n];
}