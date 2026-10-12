/*
============================================================
📋 TUGAS 06: Maximum Submatrix Sum 2 × 2
============================================================
Source: Original
Difficulty: Medium
Topics: Prefix Sum 2D, Fixed Window

PROBLEM:
Diberikan matriks N × M. Cari submatriks berukuran tepat 2 × 2
yang memiliki jumlah elemen terbesar! Cetak jumlah maksimumnya beserta
koordinat pojok kiri-atasnya (r, c) (jika ada lebih dari satu, pilih (r, c) terleksikografis terkecil).

INPUT FORMAT:
- Baris 1: N M (2 ≤ N, M ≤ 1000)
- N baris berikutnya: M integer (-10^6 ≤ A[i][j] ≤ 10^6)

OUTPUT FORMAT:
- Baris 1: Satu integer (jumlah maksimum submatriks 2×2)
- Baris 2: Dua integer r c (koordinat pojok kiri-atas submatriks tersebut, 1-indexed)

CONSTRAINTS:
- 2 ≤ N, M ≤ 1000

SAMPLE INPUT 1:
3 3
1 2 3
4 5 6
7 8 9

SAMPLE OUTPUT 1:
28
2 2

NOTE:
Submatriks (2,2) ke (3,3): [5 6 / 8 9] -> 5+6+8+9 = 28.
Pojok kiri-atas berada di (2, 2).
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
