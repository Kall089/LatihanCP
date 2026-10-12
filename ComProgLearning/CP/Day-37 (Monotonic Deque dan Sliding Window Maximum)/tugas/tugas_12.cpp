/*
============================================================
📋 TUGAS 12: Jump Game VI
============================================================
Source: Original
Difficulty: Hard
Topics: deque, DP, sliding window

PROBLEM:
Diberikan array A dan integer k. Mulai dari index 0, tiap langkah bisa
jump 1 s.d. k posisi ke depan. Tiba di index n-1. Maksimalkan jumlah
nilai A yang dikunjungi (termasuk A[0] dan A[n-1]).

INPUT FORMAT:
- Baris 1: dua integer n dan k
- Baris 2: n integer (array A, bisa negatif)

OUTPUT FORMAT:
- Satu baris: long long (skor maksimum)

CONSTRAINTS:
- 1 ≤ k ≤ n ≤ 10^5
- -10^4 ≤ A[i] ≤ 10^4

SAMPLE INPUT 1:
6 2
1 -1 -2 4 -7 3

SAMPLE OUTPUT 1:
7

SAMPLE INPUT 2:
4 3
10 -5 -2 4

SAMPLE OUTPUT 2:
14

NOTE: dp[i] = skor maksimum mencapai index i.
      dp[i] = A[i] + max(dp[i-k..i-1]).
      Gunakan sliding window maximum dengan deque untuk O(n).
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
