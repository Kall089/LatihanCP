/*
============================================================
📋 TUGAS 06: Cara Menyusun Koin (Permutasi)
============================================================
Source: Original
Difficulty: Medium
Topics: DP 1D permutasi

PROBLEM:
Sama seperti tugas 05, tetapi sekarang urutan pengambilan DIBEDAKAN
({1,2} dan {2,1} dihitung sebagai dua cara berbeda).
Cetak modulo 1000000007.

INPUT FORMAT:
- Baris 1: K T
- Baris 2: K nilai koin

OUTPUT FORMAT:
- Satu bilangan: banyaknya cara.

CONSTRAINTS:
- 1 <= K <= 100
- 1 <= T <= 10^6
- Petunjuk: nilai di loop LUAR

SAMPLE INPUT 1:
3 4
1 2 3

SAMPLE OUTPUT 1:
7
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, T;
    cin >> n >> T;

    vector<int> koin(n);

    for (int i = 0; i < n; i++)
    {
        cin >> koin[i];
    }

    vector<int> dp(T + 1, 0);
    dp[0] = 1;

    for (int i = 0; i <= T; i++)
    {
        for (int k : koin)
        {
            if (i >= k)
            {
                dp[i] = dp[i] + dp[i - k];
            }
        }
    }
    cout << dp[T];
}