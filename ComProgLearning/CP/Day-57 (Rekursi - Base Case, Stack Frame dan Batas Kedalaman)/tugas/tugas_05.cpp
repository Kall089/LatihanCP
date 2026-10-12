/*
 * Day 11 — Recursion Dasar
 * File  : tugas_05.cpp
 * Topik : Reverse Number Rekursif
 * Kesulitan: Easy
 * -----------------------------------------------
 * Balik digit-digit dari bilangan bulat positif n menggunakan rekursi.
 * (Abaikan leading zero pada hasil — misal 1200 dibalik menjadi 21)
 *
 * Input format  : Satu bilangan n
 * Output format : Bilangan dengan digit dibalik
 * Constraints   : 1 ≤ n ≤ 10^9
 *
 * Sample Input 1:      Sample Output 1:
 * 12345                54321
 *
 * Sample Input 2:      Sample Output 2:
 * 100                  1
 *
 * Sample Input 3:      Sample Output 3:
 * 9                    9
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Implementasikan reverseNum rekursif
    // Hint: Konversi ke string dulu, lalu balik string rekursif
    //       ATAU: gunakan helper revHelper(n, result)
    //       revHelper(n, r) = revHelper(n/10, r*10 + n%10)
    //       revHelper(0, r) = r  (base case)

    return 0;
}
