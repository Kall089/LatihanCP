/*
============================================================
📋 Tugas 07: Search in 2D Matrix (LeetCode 74)
============================================================
Day: 48 | Difficulty: Medium
Topic: Binary Search 2D -> 1D Mapping

PROBLEM STATEMENT:
Diberikan matriks M berukuran R x C di mana:
1. Setiap baris terurut dari kiri ke kanan.
2. Elemen pertama setiap baris lebih besar dari elemen terakhir baris sebelumnya.
Tentukan apakah target X ada di dalam matriks M.

INPUT FORMAT:
- Baris 1: R C X
- R baris berikutnya: Masing-masing berisi C integer

OUTPUT FORMAT:
- Cetak "ADA" jika X ditemukan, atau "TIDAK" jika tidak.

CONSTRAINTS:
- 1 ≤ R, C ≤ 500
- -10^9 ≤ M[i][j], X ≤ 10^9

SAMPLE INPUT 1:
3 4 3
1 3 5 7
10 11 16 20
23 30 34 60

SAMPLE OUTPUT 1:
ADA

SAMPLE INPUT 2:
3 4 13
1 3 5 7
10 11 16 20
23 30 34 60

SAMPLE OUTPUT 2:
TIDAK

HINT:
Matriks ini pada dasarnya adalah 1D array terurut berukuran R * C.
Indeks 1D idx dipetakan ke 2D: row = idx / C, col = idx % C.
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

    vector<vector<long long>> mat(r, vector<long long>(c));
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> mat[i][j];
        }
    }

    // TODO: Lakukan Binary Search 1D pada rentang [0, R*C - 1]

    return 0;
}
