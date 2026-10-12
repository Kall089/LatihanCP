/*
============================================================
📋 TUGAS 05: Perjalanan Benteng Papan Catur 2D (Grid Paths with Free Steps)
============================================================
Source: Classic Grid DP / Top-Down Memoization
Difficulty: Medium
Topics: 2D Top-Down Memoization, Modulo Arithmetic

PROBLEM:
Diberikan papan catur berukuran R x C.
Sebuah bidak mulai dari pojok kiri atas (0, 0) dan ingin mencapai (R-1, C-1).
Dari sel (r, c), bidak dapat melangkah:
1. Satu petak ke kanan: (r, c + 1)
2. Dua petak ke kanan: (r, c + 2)
3. Satu petak ke bawah: (r + 1, c)
4. Dua petak ke bawah: (r + 2, c)

Hitung berapa banyak jalur berbeda untuk mencapai (R-1, C-1), modulo 1.000.000.007!

INPUT FORMAT:
Satu baris berisi dua bilangan bulat R dan C.

OUTPUT FORMAT:
Satu baris berisi banyak jalur modulo 1.000.000.007.

CONSTRAINTS:
1 <= R, C <= 500

SAMPLE INPUT 1:
2 2

SAMPLE OUTPUT 1:
2
(Jalur: (0,0)->(0,1)->(1,1) atau (0,0)->(1,0)->(1,1))

SAMPLE INPUT 2:
3 3

SAMPLE OUTPUT 2:
22
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int r, c;
    if (!(cin >> r >> c)) return 0;

    // TODO: Selesaikan dengan 2D top-down memoization

    return 0;
}
