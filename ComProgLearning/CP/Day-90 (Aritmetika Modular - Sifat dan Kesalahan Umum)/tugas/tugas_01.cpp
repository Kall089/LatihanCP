/*
 * Day 22 — Aritmatika Modular
 * File  : tugas_01.cpp
 * Topik : Digit Terakhir dari A^B
 * Tingkat: Easy ★☆☆☆☆
 * -----------------------------------------------
 * Diberikan T test case berisi A dan B. Untuk setiap test case,
 * cetak DIGIT TERAKHIR dari A^B (dalam basis 10).
 *
 * Digit terakhir sebuah bilangan = bilangan itu mod 10.
 * Jadi jawabannya adalah (A^B) mod 10 — gunakan binary exponentiation.
 *
 * Input format  : Baris 1: T
 *                 T baris berikutnya: A dan B
 * Output format : T baris, masing-masing satu digit
 * Constraints   : 1 ≤ T ≤ 100.000
 *                 0 ≤ A ≤ 10^9
 *                 0 ≤ B ≤ 10^18
 *                 (definisi: A^0 = 1 untuk semua A, termasuk A = 0)
 *
 * Sample Input 1:                Sample Output 1:
 * 5                              4
 * 2 10                           1
 * 3 0                            3
 * 7 7                            0
 * 10 5                           1
 * 999999999 1000000000
 *
 * NOTE: 2^10 = 1024 → digit terakhir 4.
 *       7^7 = 823543 → digit terakhir 3.
 *       10^5 = 100000 → digit terakhir 0.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: kerjakan dengan binary exponentiation modulo 10

    return 0;
}
