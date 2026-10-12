/*
============================================================
📋 TUGAS 12: Kombinasi Koin Cara Berbeda Top-Down (Coin Change II)
============================================================
Source: LeetCode 518 / Classic Unbounded Knapsack Counting
Difficulty: Medium
Topics: 2D Top-Down Memoization, Unbounded Coin Change

PROBLEM:
Terdapat N jenis pecahan koin berbeda: c[0], ..., c[N-1].
Persediaan setiap jenis koin tidak terbatas.
Hitung BANYAK KOMBINASI BERBEDA untuk membentuk total nominal persis X, modulo 1.000.000.007!
(Urutan koin yang diambil tidak berpengaruh; misalnya [1, 2] dan [2, 1] dianggap kombinasi yang sama).

Wajib diimplementasikan menggunakan REKURSIF DENGAN MEMOISASI (Top-Down)!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan X.
Baris kedua berisi N bilangan bulat c[0], ..., c[N-1].

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: banyak kombinasi modulo 1.000.000.007.

CONSTRAINTS:
1 <= N <= 300
0 <= X <= 5.000
1 <= c[i] <= 5.000

SAMPLE INPUT 1:
3 5
1 2 5

SAMPLE OUTPUT 1:
4
(Kombinasi: 5=5, 5=2+2+1, 5=2+1+1+1, 5=1+1+1+1+1)

SAMPLE INPUT 2:
3 3
2 4 6

SAMPLE OUTPUT 2:
0
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

    vector<int> c(n);
    for (int i = 0; i < n; i++) cin >> c[i];

    // TODO: Selesaikan dengan 2D top-down memoization: solve(i, rem)

    return 0;
}
