/*
 * Day 11 — Recursion Dasar
 * File  : tugas_07.cpp
 * Topik : Nested Braces Depth
 * Kesulitan: Medium
 * -----------------------------------------------
 * Hitung kedalaman nesting tanda kurung kurawal maksimal
 * dalam sebuah string yang valid.
 *
 * Contoh: "{{{}}{}" → depth maks = 3 (dari {{{}})
 *
 * Input format  : Satu string berisi karakter '{' dan '}'
 * Output format : Kedalaman nesting maksimal
 * Constraints   : 1 ≤ |s| ≤ 10^5, string selalu valid
 *
 * Sample Input 1:      Sample Output 1:
 * {{{}}}               3
 *
 * Sample Input 2:      Sample Output 2:
 * {}{}                 1
 *
 * Sample Input 3:      Sample Output 3:
 * {{}{{}}}             3
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Implementasikan dengan rekursi
    // Hint: Bisa gunakan counter (bukan rekursi murni) atau
    //       rekursi dengan parameter index dan current depth
    //       depth(s, i, curDepth) → track maxDepth secara global

    return 0;
}
