/*
 * Day 22 — Aritmatika Modular
 * File  : tugas_08.cpp
 * Topik : Deret Geometri Modular Tanpa Pembagian
 * Tingkat: Medium ★★★★☆
 * -----------------------------------------------
 * Hitung S = 1 + A + A^2 + A^3 + ... + A^(N-1)  (mod M).
 *
 * Rumus tertutup S = (A^N − 1)/(A − 1) melibatkan PEMBAGIAN modular —
 * tidak valid tanpa modular inverse, dan inverse belum tentu ada
 * (M tidak dijamin prima, A−1 bisa tidak koprima dengan M).
 *
 * Gunakan DIVIDE & CONQUER O(log N):
 *
 *   S(n) = 1 + A + ... + A^(n-1)
 *
 *   jika n genap:  S(n) = S(n/2) × (1 + A^(n/2))
 *   jika n ganjil: S(n) = S(n-1) + A^(n-1)
 *   basis:         S(0) = 0
 *
 * Intuisi n genap: bagi deret jadi dua paruh — paruh kedua adalah
 * paruh pertama dikalikan A^(n/2).
 *   contoh n=4: (1 + A) + A²(1 + A) = (1+A)(1 + A²)  ✓
 *
 * Input format  : Baris 1: T
 *                 T baris berikutnya: A, N, M
 * Output format : T baris, masing-masing S mod M
 * Constraints   : 1 ≤ T ≤ 10.000
 *                 0 ≤ A ≤ 10^9
 *                 0 ≤ N ≤ 10^18
 *                 1 ≤ M ≤ 10^9
 *
 * Sample Input 1:            Sample Output 1:
 * 4                          15
 * 2 4 1000000007             6
 * 3 3 7                      5
 * 1 5 100                    1
 * 5 1 13
 *
 * NOTE: A=2, N=4 → 1+2+4+8 = 15.
 *       A=3, N=3 → 1+3+9 = 13 → 13 % 7 = 6.
 *       A=1, N=5 → 1+1+1+1+1 = 5 (perhatikan: rumus tertutup akan
 *                  membagi nol di sini — bukti pembagian itu berbahaya).
 *       A=5, N=1 → hanya suku pertama = 1.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: kerjakan dengan divide & conquer + modpow

    return 0;
}
