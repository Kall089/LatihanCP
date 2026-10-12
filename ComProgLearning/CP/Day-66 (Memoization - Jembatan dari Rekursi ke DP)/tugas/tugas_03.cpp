/*
============================================================
📋 TUGAS 03: Pita Tanpa Tetangga (Binary Strings Without Consecutive 1s)
============================================================
Source: Classic Combinatorics / Top-Down Memoization
Difficulty: Easy-Medium
Topics: Top-Down Memoization, Fibonacci Relation, Modulo 10^9+7

PROBLEM:
Sebuah pita biner memiliki panjang N karakter (masing-masing karakter bernilai '0' atau '1').
Pita tersebut TIDAK BOLEH memiliki dua buah angka '1' yang bersebelahan (tidak boleh ada substring "11").
Hitung berapa banyak pita biner valid yang dapat dibentuk, modulo 1.000.000.007!
Catatan: Pita kosong (N = 0) dianggap valid dan dihitung sebagai 1 pita.

INPUT FORMAT:
Satu baris berisi satu bilangan bulat N.

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: banyak pita valid modulo 1.000.000.007.

CONSTRAINTS:
0 <= N <= 100.000

SAMPLE INPUT 1:
3

SAMPLE OUTPUT 1:
5
(Pita yang valid: "000", "001", "010", "100", "101")

SAMPLE INPUT 2:
0

SAMPLE OUTPUT 2:
1
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

    // TODO: Selesaikan dengan top-down memoization: f(i) = f(i-1) + f(i-2)

    return 0;
}
