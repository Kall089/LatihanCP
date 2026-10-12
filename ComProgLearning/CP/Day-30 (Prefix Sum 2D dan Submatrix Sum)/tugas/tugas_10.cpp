/*
============================================================
📋 TUGAS 10: Rata-Rata Submatrix K × K Melebihi Threshold
============================================================
Source: Original
Difficulty: Medium
Topics: Prefix Sum 2D, Fixed Window, Floating Point / Threshold

PROBLEM:
Diberikan matriks N × M, integer K, dan threshold T (double).
Hitung ada berapa banyak submatriks berukuran K × K yang RATA-RATANYA ≥ T!

INPUT FORMAT:
- Baris 1: N M K T (1 ≤ K ≤ N, M ≤ 1000, T adalah double)
- N baris berikutnya: M integer (0 ≤ A[i][j] ≤ 10^6)

OUTPUT FORMAT:
- Satu integer: banyaknya submatriks K × K yang rata-ratanya ≥ T.

CONSTRAINTS:
- 1 ≤ K ≤ N, M ≤ 1000
- 0 ≤ T ≤ 10^6

SAMPLE INPUT 1:
3 3 2 5.0
1 2 3
4 5 6
7 8 9

SAMPLE OUTPUT 1:
3

NOTE:
Submatriks 2x2 yang ada:
1. (1,1)->(2,2): sum = 12, avg = 3.0 (< 5.0)
2. (1,2)->(2,3): sum = 16, avg = 4.0 (< 5.0)
3. (2,1)->(3,2): sum = 24, avg = 6.0 (≥ 5.0) -> Ya
4. (2,2)->(3,3): sum = 28, avg = 7.0 (≥ 5.0) -> Ya
Total = 2 (atau 3 jika ada tambahan). Cek: sum ≥ T * K * K.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Hint: avg >= T ekivalen dengan sum >= T * K * K (hindari precision issue!)

    return 0;
}
