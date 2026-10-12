/*
============================================================
📋 TUGAS 03: Jumlah Elemen Genap di Submatriks
============================================================
Source: Original
Difficulty: Easy
Topics: Prefix Sum 2D, Parity / Modular Arithmetic

PROBLEM:
Diberikan matriks N × M. Untuk Q buah query, hitunglah BANYAKNYA ELEMEN GENAP
di dalam submatriks dari (r1, c1) hingga (r2, c2).

INPUT FORMAT:
- Baris 1: N M Q (1 ≤ N, M ≤ 500, 1 ≤ Q ≤ 10^4)
- N baris berikutnya: M integer (1 ≤ A[i][j] ≤ 10^9)
- Q baris berikutnya: r1 c1 r2 c2

OUTPUT FORMAT:
- Q baris: banyaknya elemen genap untuk setiap query.

CONSTRAINTS:
- 1 ≤ N, M ≤ 500
- 1 ≤ Q ≤ 10^4

SAMPLE INPUT 1:
2 3 2
2 4 5
1 8 10
1 1 2 3
1 2 2 3

SAMPLE OUTPUT 1:
4
3

NOTE:
Semua elemen genap: 2, 4, 8, 10 (total 4).
Submatriks (1,2) ke (2,3) berisi: [4, 5], [8, 10] -> genap: 4, 8, 10 (total 3).
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
