/*
 * Day 11 — Recursion Dasar
 * File  : tugas_13.cpp
 * Topik : Josephus Problem
 * Kesulitan: Hard
 * -----------------------------------------------
 * n orang berdiri melingkar (0, 1, ..., n-1).
 * Dimulai dari orang ke-0, eliminasi setiap orang ke-k.
 * Temukan posisi (0-indexed) orang yang selamat terakhir.
 *
 * Formula rekursif:
 *   J(1, k) = 0
 *   J(n, k) = (J(n-1, k) + k) % n
 *
 * Input format  : n k
 * Output format : Posisi pemenang (0-indexed)
 * Constraints   : 1 ≤ n ≤ 10^5, 1 ≤ k ≤ 10^5
 *
 * Sample Input 1:      Sample Output 1:
 * 5 2                  2
 *
 * Sample Input 2:      Sample Output 2:
 * 7 3                  3
 *
 * Sample Input 3:      Sample Output 3:
 * 1 100                0
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Implementasikan Josephus(n, k) rekursif
    // J(1, k) = 0
    // J(n, k) = (J(n-1, k) + k) % n
    // PERINGATAN: n bisa besar (10^5) — rekursi depth = n
    // Untuk n besar, konversi ke iteratif!
    // int j = 0;
    // for (int i = 2; i <= n; i++) j = (j + k) % i;
    // return j;

    return 0;
}
