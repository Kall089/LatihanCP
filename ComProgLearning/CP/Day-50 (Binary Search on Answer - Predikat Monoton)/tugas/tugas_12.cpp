/*
============================================================
📋 Tugas 12: Split Array Largest Sum (LeetCode 410)
============================================================
Day: 50 | Difficulty: Hard
Topic: Binary Search on Answer

PROBLEM STATEMENT:
Diberikan array A berukuran N dan integer M.
Bagi array A menjadi M buah sub-array kontigu tak kosong.
Minimalkan LARGEST SUBARRAY SUM di antara M sub-array tersebut.

INPUT FORMAT:
- Baris 1: N M
- Baris 2: N integer A[1..N]

OUTPUT FORMAT:
- Satu integer: nilai largest subarray sum minimum.

CONSTRAINTS:
- 1 ≤ N ≤ 100.000
- 1 ≤ M ≤ min(N, 5000)
- 0 ≤ A[i] ≤ 10^9

SAMPLE INPUT 1:
5 2
7 2 5 10 8

SAMPLE OUTPUT 1:
18

PENJELASAN SAMPLE 1:
Bagi menjadi 2 bagian: [7, 2, 5] (sum = 14) dan [10, 8] (sum = 18).
Sum maksimum = 18.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // TODO: Binary search pada max sum

    return 0;
}
