/*
============================================================
📋 TUGAS 10: Sparse Table Dua Dimensi
============================================================
Source: Original
Difficulty: Medium
Topics: sparse table 2D

PROBLEM:
Diberikan matriks R x C statis dan Q query berupa submatriks
(r1, c1, r2, c2). Cetak nilai minimum di dalam submatriks itu.

INPUT FORMAT:
- Baris pertama: R, C, Q
- R baris berisi C bilangan
- Q baris: r1 c1 r2 c2

OUTPUT FORMAT:
- Q baris

CONSTRAINTS:
- 1 <= R, C <= 300
- 1 <= Q <= 10^5

SAMPLE INPUT 1:
2 2 1
1 5
3 2
1 1 2 2

SAMPLE OUTPUT 1:
1
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Perluas idenya: sp[kr][kc][i][j]. Query memakai EMPAT blok tumpang tindih. Hitung memorinya sebelum menulis.

    return 0;
}
