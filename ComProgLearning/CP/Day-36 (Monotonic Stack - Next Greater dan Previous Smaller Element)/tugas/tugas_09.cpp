/*
============================================================
📋 TUGAS 09: 132 Pattern
============================================================
Source: Original
Difficulty: Medium
Topics: stack, monotonic stack

PROBLEM:
Diberikan array A. Tentukan apakah ada triplet i < j < k sehingga
A[i] < A[k] < A[j] (pola 1-3-2).

INPUT FORMAT:
- Baris 1: integer n
- Baris 2: n integer (array A)

OUTPUT FORMAT:
- "YES" jika pola 132 ada, "NO" jika tidak

CONSTRAINTS:
- 1 ≤ n ≤ 2×10^5
- -10^9 ≤ A[i] ≤ 10^9

SAMPLE INPUT 1:
4
3 1 4 2

SAMPLE OUTPUT 1:
YES

SAMPLE INPUT 2:
3
1 2 3

SAMPLE OUTPUT 2:
NO

NOTE: Iterasi dari kanan ke kiri. Gunakan stack dan track nilai 'k' (third element).
      Saat melihat elemen < k → pola ditemukan.
      Saat elemen > stack.top() → pop dan update k = popped value.
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
