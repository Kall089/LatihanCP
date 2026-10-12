/*
============================================================
📋 TUGAS 05: Penukaran Koin Kombinasi Cara (Coin Change II 1D Forward)
============================================================
Source: LeetCode 518 / CSES Coin Combinations II
Difficulty: Medium
Topics: Unbounded Knapsack, Forward Loop DP, Modulo Arithmetic

PROBLEM:
Tersedia N jenis koin dengan nilai c[0], ..., c[N-1] dengan persediaan tak terbatas.
Hitung BANYAK KOMBINASI berbeda untuk membentuk nominal tepat X, modulo 1.000.000.007!
Urutan koin tidak mempengaruhi kombinasi (misal 1+2 sama dengan 2+1).
Selesaikan dengan 1 baris array DP berukuran O(X) menggunakan loop MAJU.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan X.
Baris kedua berisi N bilangan bulat c[0], ..., c[N-1].

OUTPUT FORMAT:
Satu baris berisi banyak kombinasi modulo 1.000.000.007.

CONSTRAINTS:
1 <= N <= 100
0 <= X <= 1.000.000
1 <= c[i] <= 1.000.000

SAMPLE INPUT 1:
3 9
2 3 5

SAMPLE OUTPUT 1:
3
(Kombinasi yang valid: {2, 2, 5}, {3, 3, 3}, {2, 2, 2, 3})
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    if (!(cin >> n >> x)) return 0;

    // TODO: Selesaikan Coin Combinations II dengan 1D DP loop maju

    return 0;
}
