/*
============================================================
📋 Tugas 11: Search in 2D Matrix II (LeetCode 240)
============================================================
Day: 48 | Difficulty: Medium
Topic: Staircase Search / Binary Search Variant

PROBLEM STATEMENT:
Diberikan matriks M berukuran R x C dengan sifat:
- Setiap baris terurut dari kiri ke kanan (ascending).
- Setiap kolom terurut dari atas ke bawah (ascending).
Cari apakah nilai X ada di dalam matriks ini dalam O(R + C).

INPUT FORMAT:
- Baris 1: R C X
- R baris berikutnya: C integer per baris

OUTPUT FORMAT:
- Cetak "ADA" atau "TIDAK".

CONSTRAINTS:
- 1 ≤ R, C ≤ 1.000
- -10^9 ≤ M[i][j], X ≤ 10^9

SAMPLE INPUT 1:
5 5 5
1   4  7 11 15
2   5  8 12 19
3   6  9 16 22
10 13 14 17 24
18 21 23 26 30

SAMPLE OUTPUT 1:
ADA

HINT:
Mulai pencarian dari sudut kanan atas (row = 0, col = C - 1).
Jika M[row][col] == X -> ADA.
Jika M[row][col] > X -> col-- (pindah ke kiri).
Jika M[row][col] < X -> row++ (pindah ke bawah).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int r, c;
    long long x;
    if (!(cin >> r >> c >> x)) return 0;

    vector<vector<long long>> m(r, vector<long long>(c));
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) cin >> m[i][j];
    }

    // TODO: Staircase search dari kanan atas

    return 0;
}
