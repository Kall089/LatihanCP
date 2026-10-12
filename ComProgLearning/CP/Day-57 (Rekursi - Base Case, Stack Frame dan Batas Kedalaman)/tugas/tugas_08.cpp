/*
 * Day 11 — Recursion Dasar
 * File  : tugas_08.cpp
 * Topik : Ackermann Function dengan Memoization
 * Kesulitan: Medium
 * -----------------------------------------------
 * Hitung fungsi Ackermann A(m, n).
 * Definisi:
 *   A(0, n) = n + 1
 *   A(m, 0) = A(m-1, 1)        untuk m > 0
 *   A(m, n) = A(m-1, A(m, n-1)) untuk m > 0, n > 0
 *
 * Fungsi ini tumbuh SANGAT cepat. A(4,0) = 13, A(4,1) = 65533!
 *
 * Input format  : m n (dalam satu baris)
 * Output format : Nilai A(m, n)
 * Constraints   : 0 ≤ m ≤ 3, 0 ≤ n ≤ 10
 *
 * Sample Input 1:      Sample Output 1:
 * 2 3                  9
 *
 * Sample Input 2:      Sample Output 2:
 * 3 3                  61
 *
 * Sample Input 3:      Sample Output 3:
 * 0 5                  6
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Implementasikan Ackermann dengan memoization
    // Hint: Gunakan map<pair<int,int>, long long> untuk memo
    //       Karena domain m,n tidak terbatas secara pasti

    return 0;
}
