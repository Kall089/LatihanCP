/*
============================================================
📋 TUGAS 12: Count Submatrices dengan Jumlah Genap
============================================================
Source: Original
Difficulty: Hard
Topics: Prefix Sum 2D + Parity Counting

PROBLEM:
Diberikan matriks N × M.
Hitung berapa banyak submatriks (r1, c1, r2, c2) sedemikian rupa sehingga
JUMLAH ELEMEN di dalam submatriks tersebut adalah GENAP (even sum)!

INPUT FORMAT:
- Baris 1: N M (1 ≤ N, M ≤ 300)
- N baris berikutnya: M integer (1 ≤ A[i][j] ≤ 10^9)

OUTPUT FORMAT:
- Satu integer: banyaknya submatriks dengan jumlah genap.

CONSTRAINTS:
- 1 ≤ N, M ≤ 300

SAMPLE INPUT 1:
2 2
1 2
3 4

SAMPLE OUTPUT 1:
4

NOTE:
- Total submatriks = 9.
- Submatriks dengan jumlah genap:
  1. (1,2)->(1,2) = 2 (genap)
  2. (2,2)->(2,2) = 4 (genap)
  3. (1,1)->(2,2) = 1+2+3+4 = 10 (genap)
  4. (1,1)->(2,1) = 1+3 = 4 (genap)
Total = 4.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Hint: Kompresi baris r1..r2, lalu hitung subarray sum genap 1D dengan menghitung frekuensi genap/ganjil pada prefix sum!

    return 0;
}
