/*
 * Day 11 — Recursion Dasar
 * File  : tugas_15.cpp
 * Topik : Climb Stairs dengan Memoization
 * Kesulitan: Hard
 * -----------------------------------------------
 * Kamu berada di tangga dengan n anak tangga.
 * Setiap langkah, kamu bisa naik 1 atau 2 anak tangga.
 * Hitung jumlah cara untuk mencapai anak tangga ke-n.
 *
 * Ini adalah Fibonacci yang disamarkan! ways(n) = ways(n-1) + ways(n-2).
 *
 * Variasi: Jika kamu juga bisa naik 3 anak tangga sekaligus,
 *          rumus menjadi ways(n) = ways(n-1) + ways(n-2) + ways(n-3).
 *
 * Tugas ini menggabungkan KEDUANYA:
 * Baris 1 input: n dan k (max langkah per sekali naik)
 * Hitung cara untuk naik n anak tangga dengan langkah 1..k.
 *
 * ways(0) = 1  (sudah di tujuan — 1 cara: tidak melakukan apa-apa)
 * ways(i) = sum(ways(i-j)) untuk j=1..min(k,i)
 *
 * Input format  : n k (n anak tangga, max langkah k per sekali)
 * Output format : Jumlah cara mod 10^9+7
 * Constraints   : 1 ≤ n ≤ 10^4, 1 ≤ k ≤ min(n, 10)
 *
 * Sample Input 1:      Sample Output 1:
 * 5 2                  8
 *
 * Sample Input 2:      Sample Output 2:
 * 4 3                  7
 *
 * Sample Input 3:      Sample Output 3:
 * 10 1                 1
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Implementasikan climbStairs(n, k) dengan memoization
    // ways(0) = 1
    // ways(i) = sum_{j=1}^{min(k,i)} ways(i-j)   mod MOD
    // Gunakan array memo[n+1]

    return 0;
}
