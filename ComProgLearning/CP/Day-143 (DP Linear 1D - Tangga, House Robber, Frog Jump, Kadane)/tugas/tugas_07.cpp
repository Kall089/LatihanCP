/*
============================================================
📋 TUGAS 07: Maximum Sum Circular Subarray
============================================================
Source: LC 918
Difficulty: Medium
Topics: Kadane melingkar

PROBLEM:
Subarray boleh melingkar dari akhir ke awal (tetap tidak kosong, dan setiap
elemen dipakai paling banyak sekali). Cari jumlah maksimum.

INPUT FORMAT:
- Baris 1: N
- Baris 2: N bilangan
OUTPUT FORMAT: satu bilangan
CONSTRAINTS: 1 <= N <= 2*10^5, |a[i]| <= 10^9

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
4                      3
1 -2 3 -2

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
3                      10
5 -3 5
Penjelasan: subarray melingkar [5, 5] (elemen terakhir lalu elemen pertama).

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
3                      -1
-3 -2 -1
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> a(n);

    int curr_worst = 0;
    int worst = INT_MAX;

    int curr_best = 0;
    int best = INT_MIN;

    int total = 0;

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        total += a[i];

        curr_worst = min(a[i], curr_worst + a[i]);
        worst = min(curr_worst, worst);

        curr_best = max(a[i], curr_best + a[i]);
        best = max(curr_best, best);
    }

    if (best < 0)
    {
        cout << best;
    }
    else
    {
        cout << max(best, total - worst);
    }
}