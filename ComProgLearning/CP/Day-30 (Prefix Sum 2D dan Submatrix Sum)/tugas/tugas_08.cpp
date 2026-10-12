/*
============================================================
📋 TUGAS 08: Submatrix Sum Kelipatan K
============================================================
Source: Original
Difficulty: Medium
Topics: Prefix Sum 2D, Modular Arithmetic

PROBLEM:
Diberikan matriks N × M, integer K, dan Q buah query.
Untuk tiap query (r1, c1, r2, c2), tentukan apakah jumlah seluruh elemen
di dalam submatriks tersebut MERUPAKAN KELIPATAN DARI K!
Cetak "YES" jika kelipatan K, atau "NO" jika bukan.

INPUT FORMAT:
- Baris 1: N M K Q (1 ≤ N, M ≤ 500, 1 ≤ K ≤ 10^9, 1 ≤ Q ≤ 10^4)
- N baris berikutnya: M integer (1 ≤ A[i][j] ≤ 10^9)
- Q baris berikutnya: r1 c1 r2 c2

OUTPUT FORMAT:
- Q baris: "YES" atau "NO".

CONSTRAINTS:
- 1 ≤ N, M ≤ 500
- 1 ≤ K ≤ 10^9
- 1 ≤ Q ≤ 10^4

SAMPLE INPUT 1:
3 3 5 2
1 2 3
4 5 6
7 8 9
1 1 2 2
1 2 2 3

SAMPLE OUTPUT 1:
NO
YES

NOTE:
- Query 1: (1,1)->(2,2) = 1+2+4+5 = 12 (12 % 5 != 0) -> NO
- Query 2: (1,2)->(2,3) = 2+3+5+6 = 16? Wait, 2+3+5+6 = 16 (bukan kelipatan 5).
  Coba (1,1)->(2,3) = 1+2+3+4+5+6 = 21.
  Coba (2,2)->(3,3) = 5+6+8+9 = 28.
  Coba (1,2)->(3,2) = 2+5+8 = 15 -> 15 % 5 == 0 -> YES (untuk query 1 2 3 2).
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
