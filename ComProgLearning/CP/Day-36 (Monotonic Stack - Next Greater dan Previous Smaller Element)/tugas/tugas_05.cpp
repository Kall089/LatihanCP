/*
============================================================
📋 TUGAS 05: Next Greater Element Circular
============================================================
Source: Original
Difficulty: Medium
Topics: stack, next greater element, circular array

PROBLEM:
Diberikan array A berbentuk CIRCULAR (A[n-1] diikuti A[0]).
Untuk setiap elemen, temukan Next Greater Element (elemen pertama
yang lebih besar dalam arah searah jarum jam). Jika tidak ada, output -1.

INPUT FORMAT:
- Baris 1: integer n
- Baris 2: n integer (array A)

OUTPUT FORMAT:
- n integer (NGE untuk setiap posisi)

CONSTRAINTS:
- 1 ≤ n ≤ 10^4
- 1 ≤ A[i] ≤ 10^9

SAMPLE INPUT 1:
5
1 2 1 4 3

SAMPLE OUTPUT 1:
2 4 4 -1 4

SAMPLE INPUT 2:
3
3 3 3

SAMPLE OUTPUT 2:
-1 -1 -1

NOTE: Iterasi array dua kali (index 0 hingga 2n-1) menggunakan i % n.
      Stack menyimpan index. Hanya set answer saat pertama kali ditemukan.
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
