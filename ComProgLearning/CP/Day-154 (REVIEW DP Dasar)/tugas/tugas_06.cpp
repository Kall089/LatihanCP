/*
============================================================
📋 TUGAS 06: Rute Grid Segi Empat dengan Langkah Diagonal
============================================================
Source: Classic Grid DP / King's Walk Grid
Difficulty: Medium
Topics: Grid DP, 3 Directions of Movement, Modulo 10^9+7

PROBLEM:
Diberikan papan catur berukuran R x C.
Sebuah bidak raja mulai dari pojok kiri atas (0, 0) dan ingin mencapai (R-1, C-1).
Dari sel (r, c), bidak hanya boleh bergerak ke salah satu dari 3 arah:
1. Kanan: (r, c + 1)
2. Bawah: (r + 1, c)
3. Diagonal kanan-bawah: (r + 1, c + 1)
Hitung banyak jalur berbeda yang dapat ditempuh raja, modulo 1.000.000.007!

INPUT FORMAT:
Satu baris berisi dua bilangan bulat R dan C.

OUTPUT FORMAT:
Satu baris berisi banyak jalur modulo 1.000.000.007.

CONSTRAINTS:
1 <= R, C <= 1.000

SAMPLE INPUT 1:
2 2

SAMPLE OUTPUT 1:
3
(Jalur: Kanan->Bawah, Bawah->Kanan, atau Diagonal langsung)

SAMPLE INPUT 2:
3 3

SAMPLE OUTPUT 2:
13
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

    // TODO: Selesaikan King Path DP modulo 10^9+7

    return 0;
}
