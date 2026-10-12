/*
============================================================
📋 TUGAS 12: Jalur Grid Dua Pemain Bersamaan (Cherry Pickup 2D)
============================================================
Source: LeetCode 741 / Classic Grid DP 3-Variable
Difficulty: Hard
Topics: Grid DP, 2 Agents Simultaneous Walk

PROBLEM:
Diberikan grid N x N berisi koin emas: grid[r][c].
Dua pemain (atau satu pemain pergi lalu kembali) mulai dari (0, 0) dan ingin mencapai (N-1, N-1).
Keduanya hanya boleh bergerak ke Kanan atau ke Bawah.
Jika kedua pemain menginjak sel yang sama pada saat bersamaan, koin emas pada sel tersebut
HANYA BOLEH DIAMBIL SATU KALI.
Tentukan JUMLAH KOIN EMAS MAKSIMUM yang dapat dikumpulkan oleh kedua pemain!

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
N baris berikutnya masing-masing berisi N bilangan bulat nonnegatif.

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: koin emas maksimum.

CONSTRAINTS:
1 <= N <= 100
0 <= grid[r][c] <= 1.000

SAMPLE INPUT 1:
3
1 2 3
4 5 6
7 8 9

SAMPLE OUTPUT 1:
46
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // TODO: Selesaikan 2-agent grid walking dengan state step k = r1 + c1 = r2 + c2

    return 0;
}
