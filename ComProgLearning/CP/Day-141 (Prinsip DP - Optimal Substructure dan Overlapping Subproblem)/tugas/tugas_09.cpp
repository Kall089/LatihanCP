/*
============================================================
📋 TUGAS 09: Menghapus Digit
============================================================
Source: Original
Difficulty: Medium-Hard
Topics: DP 1D pada nilai angka

PROBLEM:
Diberikan bilangan N. Dalam satu langkah kamu boleh mengurangi N dengan
salah satu digit yang ADA di dalam N saat itu.
Tentukan jumlah langkah minimal agar N menjadi 0.
Contoh: 27 -> 20 -> 18 -> 10 -> 9 -> 0, yaitu 5 langkah.

INPUT FORMAT:
- Satu baris: N

OUTPUT FORMAT:
- Satu bilangan: langkah minimal.

CONSTRAINTS:
- 1 <= N <= 10^6

SAMPLE INPUT 1:
27

SAMPLE OUTPUT 1:
5
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> dp(n + 1, 1e9);
    dp[0] = 0;

    for (int i = 1; i <= n; i++)
    {
        int temp = i;

        while (temp > 0)
        {
            int d = temp % 10;
            if (d > 0)
            {
                dp[i] = min(dp[i], dp[i - d] + 1);
            }
            temp /= 10;
        }
    }

    cout << dp[n];
}