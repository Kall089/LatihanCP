/*
============================================================
📋 TUGAS 15: Submatrix Sum pada Grid Papan Catur (Alternating Signs)
============================================================
Source: Original
Difficulty: Hard
Topics: Prefix Sum 2D Transformation, Chessboard Pattern

PROBLEM:
Diberikan matriks N × M.
Definisikan "Alternating Submatrix Sum" dari (r1, c1) ke (r2, c2) sebagai:
∑ (-1)^(i + j) × A[i][j] untuk semua r1 ≤ i ≤ r2 dan c1 ≤ j ≤ c2.

Diberikan Q query (r1, c1, r2, c2), hitunglah nilai Alternating Submatrix Sum tersebut!

INPUT FORMAT:
- Baris 1: N M Q (1 ≤ N, M ≤ 500, 1 ≤ Q ≤ 10^4)
- N baris berikutnya: M integer (-10^6 ≤ A[i][j] ≤ 10^6)
- Q baris berikutnya: r1 c1 r2 c2

OUTPUT FORMAT:
- Q baris: hasil Alternating Submatrix Sum untuk setiap query.

CONSTRAINTS:
- 1 ≤ N, M ≤ 500
- 1 ≤ Q ≤ 10^4

SAMPLE INPUT 1:
2 2 1
5 3
2 4
1 1 2 2

SAMPLE OUTPUT 1:
4

NOTE:
i+j untuk sel:
(1,1): 1+1=2 (genap) -> +1 * 5 = +5
(1,2): 1+2=3 (ganjil) -> -1 * 3 = -3
(2,1): 2+1=3 (ganjil) -> -1 * 2 = -2
(2,2): 2+2=4 (genap) -> +1 * 4 = +4
Total = 5 - 3 - 2 + 4 = 4.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Hint: Transformasi matriks A menjadi B[i][j] = ((i+j)%2 == 0 ? A[i][j] : -A[i][j]), lalu bangun Prefix Sum 2D biasa pada B!

    return 0;
}
