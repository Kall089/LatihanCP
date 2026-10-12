/*
 * Day 11 — Recursion Dasar
 * File  : tugas_09.cpp
 * Topik : Catalan Number dengan Memoization
 * Kesulitan: Medium
 * -----------------------------------------------
 * Hitung bilangan Catalan ke-n (C_n).
 * Rumus:
 *   C_0 = 1
 *   C_n = sum(C_i * C_(n-1-i)) untuk i = 0..n-1
 *
 * Bilangan Catalan muncul dalam banyak masalah kombinatorik:
 * - Jumlah cara bracket valid panjang 2n
 * - Jumlah binary tree dengan n node
 * - Jumlah triangulasi polygon (n+2) sisi
 *
 * Input format  : Satu bilangan n
 * Output format : C_n
 * Constraints   : 0 ≤ n ≤ 15
 *
 * Sample Input 1:      Sample Output 1:
 * 5                    42
 *
 * Sample Input 2:      Sample Output 2:
 * 0                    1
 *
 * Sample Input 3:      Sample Output 3:
 * 10                   16796
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Implementasikan catalan(n) dengan memoization
    // catalan[0] = 1
    // catalan[n] = sum_{i=0}^{n-1} catalan[i] * catalan[n-1-i]

    return 0;
}
