/*
 * Day 22 — Aritmatika Modular
 * File  : exercise_3.cpp
 * Topik : Binary Exponentiation (Modular Power)
 * -----------------------------------------------
 * Diberikan T test case. Setiap test case berisi tiga bilangan A, B, M.
 * Hitung (A^B) mod M.
 *
 * Karena B bisa sampai 10^18, pendekatan naif (kalikan B kali) akan TLE.
 * Gunakan BINARY EXPONENTIATION:
 *
 *   A^13 = A^(1101 biner) = A^8 × A^4 × A^1
 *
 *   result = 1
 *   while (exp > 0):
 *       if (exp & 1) result = result * base % m
 *       base = base * base % m
 *       exp >>= 1
 *
 * Kompleksitas: O(log B) per query.
 *
 * Input format  : Baris 1: T
 *                 T baris berikutnya: A, B, M
 * Output format : T baris, masing-masing (A^B) mod M
 * Constraints   : 1 ≤ T ≤ 100.000
 *                 0 ≤ A ≤ 10^9
 *                 0 ≤ B ≤ 10^18
 *                 1 ≤ M ≤ 10^9
 *
 * Sample Input 1:            Sample Output 1:
 * 4                          323
 * 3 13 1000                  1
 * 5 0 1000000007             0
 * 2 10 1024                  1
 * 7 100 1
 *
 * Sample Input 2:            Sample Output 2:
 * 3                          976371285
 * 2 100 1000000007           49
 * 10 18 1000000007           64
 * 999999999 2 1000000007
 *
 * NOTE: 3^13 = 1594323 → mod 1000 = 323.
 *       Kasus B=0 harus menghasilkan 1 (konvensi: A^0 = 1).
 *       Kasus M=1 harus menghasilkan 0 (semua bilangan mod 1 = 0).
 *
 * HINT: Jangan pakai pow() dari <cmath> — itu double dan kehilangan presisi.
 *       Perhatikan urutan edge case M=1 vs B=0.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// TODO: Implementasikan fungsi modpow
// ll modpow(ll base, ll exp, ll m) { ... }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca T

    // TODO: Untuk tiap test case, baca A, B, M dan cetak modpow(A, B, M)

    return 0;
}
