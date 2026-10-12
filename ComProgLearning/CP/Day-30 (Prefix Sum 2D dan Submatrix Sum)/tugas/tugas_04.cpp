/*
============================================================
📋 TUGAS 04: Selisih Jumlah Dua Submatriks
============================================================
Source: Original
Difficulty: Easy
Topics: Prefix Sum 2D dasar

PROBLEM:
Diberikan matriks N × M dan Q buah query.
Setiap query berisi 8 integer: r1 c1 r2 c2 r3 c3 r4 c4.
Hitung selisih mutlak dari jumlah elemen submatriks A [r1..r2][c1..c2]
dengan submatriks B [r3..r4][c3..c4]!

| Sum(A) - Sum(B) |

INPUT FORMAT:
- Baris 1: N M Q (1 ≤ N, M ≤ 500, 1 ≤ Q ≤ 10^4)
- N baris berikutnya: M integer (1 ≤ A[i][j] ≤ 10^6)
- Q baris berikutnya: 8 integer r1 c1 r2 c2 r3 c3 r4 c4

OUTPUT FORMAT:
- Q baris: selisih mutlak jumlah elemen kedua submatriks.

CONSTRAINTS:
- 1 ≤ N, M ≤ 500
- 1 ≤ Q ≤ 10^4

SAMPLE INPUT 1:
3 3 1
1 2 3
4 5 6
7 8 9
1 1 2 2  2 2 3 3

SAMPLE OUTPUT 1:
16

NOTE:
Submatriks A (1,1)->(2,2) = 1+2+4+5 = 12
Submatriks B (2,2)->(3,3) = 5+6+8+9 = 28
Selisih = |12 - 28| = 16
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
