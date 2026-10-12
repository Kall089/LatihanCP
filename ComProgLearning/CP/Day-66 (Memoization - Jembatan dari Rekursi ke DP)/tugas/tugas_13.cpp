/*
============================================================
📋 TUGAS 13: Menghitung Kekacauan Susunan (Derangements / !N Top-Down)
============================================================
Source: Classic Combinatorics / Subfactorial
Difficulty: Easy-Medium
Topics: 1D Top-Down Memoization, Modulo 10^9+7

PROBLEM:
Sebuah permutasi dari himpunan {1, 2, ..., N} disebut sebagai kekacauan (*derangement*)
jika TIDAK ADA SATU PUN elemen yang menempati posisi aslinya
(artinya untuk setiap i dari 1 sampai N, p[i] != i).

Hitung BANYAK DERANGEMENT dari himpunan berukuran N, modulo 1.000.000.007!
Rumus rekursi derangement:
- !0 = 1
- !1 = 0
- !N = (N - 1) * (!(N - 1) + !(N - 2))

Wajib diimplementasikan menggunakan REKURSIF DENGAN MEMOISASI (Top-Down)!

INPUT FORMAT:
Satu baris berisi satu bilangan bulat N.

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: banyak derangement modulo 1.000.000.007.

CONSTRAINTS:
0 <= N <= 100.000

SAMPLE INPUT 1:
3

SAMPLE OUTPUT 1:
2
(Permutasi yang valid: (2, 3, 1) dan (3, 1, 2))

SAMPLE INPUT 2:
4

SAMPLE OUTPUT 2:
9
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // TODO: Selesaikan dengan top-down memoization

    return 0;
}
