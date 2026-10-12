/*
 * Day 22 — Aritmatika Modular
 * File  : exercise_6.cpp
 * Topik : Perkalian Modular dengan Modulus Besar (Overflow Prevention)
 * -----------------------------------------------
 * Diberikan T test case. Setiap test case berisi A, B, M dengan
 * M bisa mencapai 10^18 — artinya A × B bisa mencapai 10^36,
 * JAUH melebihi kapasitas long long (~9.2 × 10^18).
 *
 * Hitung (A × B) mod M tanpa overflow.
 *
 * Ada dua pendekatan:
 *   (1) __int128 — tipe 128-bit GCC/Clang:
 *         return (__int128)a * b % m;
 *   (2) Binary multiplication (mirip binary exponentiation, tapi pakai
 *       penjumlahan berulang) — O(log B), berguna kalau __int128 tidak ada:
 *         res = 0
 *         while (b > 0):
 *             if (b & 1) res = (res + a) % m
 *             a = (a + a) % m
 *             b >>= 1
 *
 * Implementasikan KEDUANYA dan pastikan hasilnya sama.
 *
 * Input format  : Baris 1: T
 *                 T baris berikutnya: A, B, M
 * Output format : T baris, masing-masing (A × B) mod M
 * Constraints   : 1 ≤ T ≤ 100.000
 *                 0 ≤ A, B < M
 *                 1 ≤ M ≤ 10^18
 *
 * Sample Input 1:                                 Sample Output 1:
 * 3                                               6
 * 2 3 1000000007                                  1
 * 999999999999999998 999999999999999998 999999999999999999
 * 0 12345 999999999999999999                      0
 *
 * Sample Input 2:                                 Sample Output 2:
 * 2                                               999999986000000049
 * 999999999 999999999 1000000000000000000         1
 * 5 5 8
 *
 * NOTE Test case 2 pada sample 1: A = B = M-1, maka
 *      (M-1)^2 mod M = (−1)^2 mod M = 1.
 *      Ini cara cepat memverifikasi implementasi tanpa kalkulator besar.
 *
 * HINT: __int128 tidak bisa langsung di-cout. Cast hasil akhir ke long long
 *       (aman karena hasil < M ≤ 10^18).
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// TODO: Implementasikan mulmod dengan __int128
// ll mulmod128(ll a, ll b, ll m) { ... }

// TODO: Implementasikan mulmod dengan binary multiplication (tanpa __int128)
// ll mulmodBinary(ll a, ll b, ll m) { ... }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca T, lalu untuk tiap test case cetak (A × B) mod M
    //       Opsional: assert kedua implementasi memberi hasil sama

    return 0;
}
