/*
============================================================
📋 TUGAS 07: Hitung Jumlah Frame/Bingkai Submatriks
============================================================
Source: Original
Difficulty: Medium
Topics: Prefix Sum 2D, Geometry / Inclusion-Exclusion

PROBLEM:
Diberikan matriks N × M dan Q buah query.
Setiap query berupa submatriks (r1, c1) hingga (r2, c2) dengan syarat r2 - r1 >= 2 dan c2 - c1 >= 2.
Hitunglah JUMLAH HANYA ELEMEN PINGGIR/BINGKAI (border/frame) dari submatriks tersebut!
Yaitu elemen-elemen di baris r1, baris r2, kolom c1, dan kolom c2, tanpa menghitung bagian dalam!

INPUT FORMAT:
- Baris 1: N M Q (3 ≤ N, M ≤ 500, 1 ≤ Q ≤ 10^4)
- N baris berikutnya: M integer (1 ≤ A[i][j] ≤ 10^6)
- Q baris berikutnya: r1 c1 r2 c2 (r2 - r1 >= 2, c2 - c1 >= 2)

OUTPUT FORMAT:
- Q baris: jumlah elemen bingkai submatriks.

CONSTRAINTS:
- 3 ≤ N, M ≤ 500
- 1 ≤ Q ≤ 10^4

SAMPLE INPUT 1:
3 3 1
1 2 3
4 5 6
7 8 9
1 1 3 3

SAMPLE OUTPUT 1:
40

NOTE:
Seluruh matriks berukuran 3x3.
Bagian bingkai adalah semua sel kecuali sel tengah (2,2) yang bernilai 5.
Jumlah seluruh matriks = 45.
Jumlah bagian dalam (2,2)..(2,2) = 5.
Jumlah bingkai = 45 - 5 = 40.
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
