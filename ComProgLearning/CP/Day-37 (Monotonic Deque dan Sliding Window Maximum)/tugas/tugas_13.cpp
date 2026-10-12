/*
============================================================
📋 TUGAS 13: Shortest Subarray with Sum >= K
============================================================
Source: Original
Difficulty: Hard
Topics: deque, prefix sum, sliding window

PROBLEM:
Diberikan array A (bisa negatif) dan integer K.
Temukan panjang subarray terpendek dengan jumlah >= K.
Jika tidak ada, cetak -1.

INPUT FORMAT:
- Baris 1: dua integer n dan K
- Baris 2: n integer (A, bisa negatif)

OUTPUT FORMAT:
- Satu baris: integer (panjang minimum, atau -1)

CONSTRAINTS:
- 1 ≤ n ≤ 10^5
- -10^5 ≤ A[i] ≤ 10^5
- -10^9 ≤ K ≤ 10^9

SAMPLE INPUT 1:
5 7
2 -1 2 3 4

SAMPLE OUTPUT 1:
3

SAMPLE INPUT 2:
4 15
1 2 3 4

SAMPLE OUTPUT 2:
-1

NOTE: Bangun prefix sum P[]. Cari j > i dengan P[j]-P[i] >= K dan j-i minimal.
      Gunakan monotonic deque pada prefix sum.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO
    return 0;
}
