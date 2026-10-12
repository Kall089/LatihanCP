/*
============================================================
📋 TUGAS 10: Subsequence Menaik Terpanjang
============================================================
Source: Original
Difficulty: Medium-Hard
Topics: DP 1D O(n^2)

PROBLEM:
Diberikan N bilangan. Cari panjang subsequence menaik terpanjang
(boleh melompat, tetapi urutan indeks harus menaik).
Petunjuk: dp[i] = LIS yang berakhir tepat di indeks i.

INPUT FORMAT:
- Baris 1: N
- Baris 2: N bilangan a[i]

OUTPUT FORMAT:
- Satu bilangan: panjang LIS.

CONSTRAINTS:
- 1 <= N <= 5000
- Versi O(n log n) dipelajari di Day 88

SAMPLE INPUT 1:
8
10 9 2 5 3 7 101 18

SAMPLE OUTPUT 1:
4
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

    vector<int> dp(n, 1);
    int ans = 1;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (a[j] < a[i])
            {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        ans = max(dp[i], ans);
    }

    cout << ans;
}