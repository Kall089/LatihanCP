/*
============================================================
📋 TUGAS 13: Submatrix Sum Maksimum Terdekat ≤ K
============================================================
Source: Original
Difficulty: Hard
Topics: Prefix Sum 2D + std::set / Binary Search

PROBLEM:
Diberikan matriks N × M dan sebuah target K.
Temukan JUMLAH SUBMATRIKS MAKSIMUM yang NILAINYA ≤ K!
(Setidaknya satu submatriks pasti memiliki sum ≤ K).

INPUT FORMAT:
- Baris 1: N M K (1 ≤ N, M ≤ 200, -10^5 ≤ K ≤ 10^5)
- N baris berikutnya: M integer (-1000 ≤ A[i][j] ≤ 1000)

OUTPUT FORMAT:
- Satu integer: jumlah submatriks terbesar yang tidak melebihi K.

CONSTRAINTS:
- 1 ≤ N, M ≤ 200

SAMPLE INPUT 1:
2 2 4
2 1
3 4

SAMPLE OUTPUT 1:
4

NOTE:
Submatriks yang sumnya <= 4:
- (1,1)->(1,1) = 2
- (1,2)->(1,2) = 1
- (2,1)->(2,1) = 3
- (2,2)->(2,2) = 4
- (1,1)->(1,2) = 3
Maksimum di antaranya yang <= 4 adalah 4.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Hint: Untuk pasangan (r1, r2), gunakan std::set<long long> untuk menyimpan prefix sum 1D dan lower_bound untuk mencari val >= pref - K!

    return 0;
}
