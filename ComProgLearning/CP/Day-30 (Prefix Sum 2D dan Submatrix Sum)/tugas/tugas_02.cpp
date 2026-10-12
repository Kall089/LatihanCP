/*
============================================================
📋 TUGAS 02: Total Elemen Positif di Submatriks
============================================================
Source: Original
Difficulty: Easy
Topics: Prefix Sum 2D, Filtering / Boolean Array

PROBLEM:
Diberikan matriks N × M yang dapat berisi angka positif, negatif, atau 0.
Untuk Q buah query, hitunglah BANYAKNYA ELEMEN POSITIF (nilai > 0) di dalam submatriks (r1, c1) hingga (r2, c2).

INPUT FORMAT:
- Baris 1: N M Q (1 ≤ N, M ≤ 500, 1 ≤ Q ≤ 10^4)
- N baris berikutnya: M integer (-10^6 ≤ A[i][j] ≤ 10^6)
- Q baris berikutnya: r1 c1 r2 c2

OUTPUT FORMAT:
- Q baris: jumlah elemen bernilai > 0 di submatriks.

CONSTRAINTS:
- 1 ≤ N, M ≤ 500
- 1 ≤ Q ≤ 10^4

SAMPLE INPUT 1:
3 3 2
-1 2 3
4 -5 6
-7 -8 9
1 1 3 3
2 2 3 3

SAMPLE OUTPUT 1:
5
2

NOTE:
Di seluruh matriks ada 5 angka positif (2, 3, 4, 6, 9).
Di submatriks (2,2) ke (3,3) angka positifnya 6 dan 9 (banyaknya = 2).
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini

    return 0;
}
