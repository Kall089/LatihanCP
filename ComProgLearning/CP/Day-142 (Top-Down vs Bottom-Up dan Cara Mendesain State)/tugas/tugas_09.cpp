/*
============================================================
📋 TUGAS 09: Barisan Biner Tanpa Tiga Angka 1 Berturut-turut
============================================================
Source: Classic Counting DP
Difficulty: Medium
Topics: State Design with Consecutive Run-Length

PROBLEM:
Sebuah string biner sepanjang N hanya terdiri dari karakter '0' dan '1'.
Kamu ingin menghitung banyaknya string biner berbeda sepanjang N yang TIDAK mengandung
substring "111" (artinya tidak boleh ada 3 atau lebih angka '1' yang muncul berurutan).
Keluarkan jawaban modulo 1.000.000.007.
Untuk N = 0, jawabannya adalah 1 (string kosong).

INPUT FORMAT:
Satu baris berisi bilangan bulat N.

OUTPUT FORMAT:
Satu bilangan bulat: banyak string biner valid modulo 1.000.000.007.

CONSTRAINTS:
0 <= N <= 100.000

SAMPLE INPUT 1:
1

SAMPLE OUTPUT 1:
2
(Penjelasan: "0" dan "1")

SAMPLE INPUT 2:
3

SAMPLE OUTPUT 2:
7
(Penjelasan: Dari 8 string biner panjang 3, hanya "111" yang dilarang. 8 - 1 = 7.)

SAMPLE INPUT 3:
4

SAMPLE OUTPUT 3:
13
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // TODO: Definisikan state:
    // dp[i][0]: berakhir di '0'
    // dp[i][1]: berakhir di tepat satu '1' (yaitu "...01")
    // dp[i][2]: berakhir di dua '1' (yaitu "...011")
    // Transisi:
    // Menambah '0': semua state di i-1 boleh ditambah '0' -> dp[i][0] = dp[i-1][0] + dp[i-1][1] + dp[i-1][2]
    // Menambah '1': dp[i][1] = dp[i-1][0], dp[i][2] = dp[i-1][1]

    return 0;
}
