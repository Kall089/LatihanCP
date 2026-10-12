/*
============================================================
📋 TUGAS 05: Frog 1 & Frog 2
============================================================
Source: AtCoder DP-A dan DP-B
Difficulty: Easy
Topics: min atas jendela K

PROBLEM:
N batu berketinggian h. Dari batu i boleh melompat ke i+1..i+K dengan biaya
|h[i]-h[j]|. Cari biaya minimum sampai batu N-1.

INPUT FORMAT:
- Baris 1: N K
- Baris 2: N bilangan
OUTPUT FORMAT: satu bilangan
CONSTRAINTS: 2 <= N <= 10^5, 1 <= K <= 100

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
4 1                    50
10 30 40 20
Penjelasan: K=1 berarti wajib lewat setiap batu: 20 + 10 + 20 = 50.

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
5 3                    30
10 30 40 50 20

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
2 100                  0
10 10
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
}
