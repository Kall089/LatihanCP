/*
============================================================
📋 TUGAS 05: Cara Menyusun Koin (Kombinasi)
============================================================
Source: Original
Difficulty: Medium
Topics: DP 1D kombinasi

PROBLEM:
Diberikan K jenis koin dan target T. Hitung banyaknya cara membentuk T,
di mana urutan pengambilan TIDAK dibedakan ({1,2} sama dengan {2,1}).
Cetak modulo 1000000007.

INPUT FORMAT:
- Baris 1: K T
- Baris 2: K nilai koin

OUTPUT FORMAT:
- Satu bilangan: banyaknya cara.

CONSTRAINTS:
- 1 <= K <= 100
- 1 <= T <= 10^6
- Petunjuk: koin di loop LUAR

SAMPLE INPUT 1:
3 4
1 2 3

SAMPLE OUTPUT 1:
4
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

    for (int k : koin)
    {
        for (int i = k; i <= T; i++)
        {
            dp[i] = dp[i] + dp[i - k];
        }
    }

    cout << dp[T];
}
