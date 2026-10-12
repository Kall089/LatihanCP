/*
============================================================
📋 TUGAS 07: Subarray Jumlah Terbesar
============================================================
Source: Original
Difficulty: Medium
Topics: DP 1D (Kadane)

PROBLEM:
Diberikan N bilangan (boleh negatif). Cari jumlah terbesar dari sebuah
subarray berurutan yang tidak kosong.
Petunjuk: dp[i] = jumlah subarray terbaik yang BERAKHIR di i.

INPUT FORMAT:
- Baris 1: N
- Baris 2: N bilangan a[i]

OUTPUT FORMAT:
- Satu bilangan: jumlah subarray terbesar.

CONSTRAINTS:
- 1 <= N <= 10^6
- -10^9 <= a[i] <= 10^9

SAMPLE INPUT 1:
9
-2 1 -3 4 -1 2 1 -5 4

SAMPLE OUTPUT 1:
6
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

    int curr = a[0];
    int best = a[0];

    for (int i = 1; i < n; i++)
    {
        curr = max(a[i], curr + a[i]);
        best = max(best, curr);
    }

    cout << best;
}