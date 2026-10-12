/*
 * Day 11 — Recursion Dasar
 * File  : tugas_06.cpp
 * Topik : Binary to Decimal Rekursif
 * Kesulitan: Medium
 * -----------------------------------------------
 * Konversi bilangan biner (sebagai string) ke desimal menggunakan rekursi.
 *
 * Input format  : Satu string biner (hanya '0' dan '1')
 * Output format : Nilai desimal
 * Constraints   : 1 ≤ |s| ≤ 62 (nilai muat dalam long long)
 *
 * Sample Input 1:      Sample Output 1:
 * 1011                 11
 *
 * Sample Input 2:      Sample Output 2:
 * 0                    0
 *
 * Sample Input 3:      Sample Output 3:
 * 111111               63
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Implementasikan binToDec rekursif
    // Hint: Proses karakter dari kanan (LSB ke MSB)
    //       binToDec(s, idx, power) = (s[idx]-'0')*power + binToDec(s, idx-1, power*2)
    //       binToDec(s, -1, _)     = 0  (base case)

    return 0;
}
