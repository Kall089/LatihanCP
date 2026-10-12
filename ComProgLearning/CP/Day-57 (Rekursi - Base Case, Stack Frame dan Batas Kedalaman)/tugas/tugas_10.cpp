/*
 * Day 11 — Recursion Dasar
 * File  : tugas_10.cpp
 * Topik : Hitung 2^n Tanpa pow()
 * Kesulitan: Medium
 * -----------------------------------------------
 * Hitung 2^n menggunakan rekursi tanpa menggunakan fungsi pow() bawaan.
 * Gunakan binary splitting untuk efisiensi O(log n).
 *
 * Input format  : Satu bilangan n
 * Output format : 2^n mod 10^9+7
 * Constraints   : 0 ≤ n ≤ 10^18
 *
 * Sample Input 1:      Sample Output 1:
 * 10                   1024
 *
 * Sample Input 2:      Sample Output 2:
 * 0                    1
 *
 * Sample Input 3:      Sample Output 3:
 * 62                   611973901
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Implementasikan power2(n) rekursif O(log n)
    // Hint: Gunakan binary splitting
    //   power2(0) = 1
    //   power2(n) = (power2(n/2))^2          jika n genap
    //   power2(n) = 2 * (power2(n/2))^2      jika n ganjil
    // Semua operasi mod MOD

    return 0;
}
