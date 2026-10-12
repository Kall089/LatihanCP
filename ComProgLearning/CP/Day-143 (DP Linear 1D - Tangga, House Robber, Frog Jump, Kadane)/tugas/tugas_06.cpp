/*
============================================================
📋 TUGAS 06: Maximum Subarray
============================================================
Source: LC 53
Difficulty: Easy
Topics: Kadane

PROBLEM:
Cari subarray TIDAK KOSONG dengan jumlah maksimum.

INPUT FORMAT:
- Baris 1: N
- Baris 2: N bilangan
OUTPUT FORMAT: satu bilangan
CONSTRAINTS: 1 <= N <= 2*10^5, |a[i]| <= 10^9

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
9                      6
-2 1 -3 4 -1 2 1 -5 4

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
1                      1
1

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
4                      -1
-5 -1 -3 -2
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> a(n);

    int currBest = 0;
    int best = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        currBest = max(a[i], currBest + a[i]);
        best = max(currBest, best);
    }
    cout << best;
}