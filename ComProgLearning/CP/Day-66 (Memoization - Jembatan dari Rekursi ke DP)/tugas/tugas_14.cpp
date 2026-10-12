/*
============================================================
📋 TUGAS 14: Jalur Kotak Berbobot Minimum Top-Down (Minimum Path Sum)
============================================================
Source: LeetCode 64 / Classic Grid DP Top-Down
Difficulty: Medium
Topics: 2D Top-Down Memoization, Cost Minimization

PROBLEM:
Diberikan sebuah kisi berukuran R x C berisi bilangan bulat non-negatif grid[r][c].
Temukan sebuah jalur dari pojok kiri atas (0, 0) menuju pojok kanan bawah (R-1, C-1) yang
MEMINIMALKAN JUMLAH SEMUA BILANGAN di sepanjang jalur yang dilalui!
Kamu hanya boleh melangkah ke Bawah (r+1, c) atau ke Kanan (r, c+1).

Wajib diimplementasikan menggunakan REKURSIF DENGAN MEMOISASI (Top-Down)!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat R dan C.
R baris berikutnya masing-masing berisi C bilangan bulat non-negatif.

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: jumlah bobot minimum.

CONSTRAINTS:
1 <= R, C <= 500
0 <= grid[r][c] <= 1.000

SAMPLE INPUT 1:
3 3
1 3 1
1 5 1
4 2 1

SAMPLE OUTPUT 1:
7
(Jalur: 1 -> 3 -> 1 -> 1 -> 1, total 7)

SAMPLE INPUT 2:
2 3
1 2 3
4 5 6

SAMPLE OUTPUT 2:
12
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int r, c;
    if (!(cin >> r >> c)) return 0;

    // TODO: Selesaikan dengan 2D top-down memoization: solve(i, j)

    return 0;
}
