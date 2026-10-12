/*
 * Day 22 — Aritmatika Modular
 * File  : tugas_02.cpp
 * Topik : Jumlah 1..N Modulo M (Jebakan Pembagian)
 * Tingkat: Easy ★☆☆☆☆
 * -----------------------------------------------
 * Diberikan N dan M. Hitung (1 + 2 + 3 + ... + N) mod M.
 *
 * Rumusnya S = N(N+1)/2. Tapi HATI-HATI:
 *   - N sampai 10^18, jadi N × (N+1) langsung akan OVERFLOW long long
 *   - Pembagian TIDAK boleh dilakukan setelah mod!
 *     ((N%M) * ((N+1)%M) / 2) % M  ← ❌ SALAH TOTAL
 *
 * TRIK: Antara N dan N+1, pasti tepat SATU yang genap.
 * Bagi 2 pada yang genap DULU (sebelum mod), baru kalikan modular.
 *
 *   if (N % 2 == 0) a = N/2, b = N+1;
 *   else            a = N,   b = (N+1)/2;
 *   jawab = (a % M) * (b % M) % M;
 *
 * Input format  : Baris 1: T
 *                 T baris berikutnya: N dan M
 * Output format : T baris, masing-masing hasil mod M
 * Constraints   : 1 ≤ T ≤ 100.000
 *                 1 ≤ N ≤ 10^18
 *                 1 ≤ M ≤ 10^9
 *
 * Sample Input 1:                    Sample Output 1:
 * 4                                  15
 * 5 1000000007                       6
 * 10 7                               1225
 * 1000000000000000000 1000000007     1
 * 1 5
 *
 * NOTE: 1+..+5 = 15. 1+..+10 = 55 → 55 % 7 = 6.
 *       N=10^18 → jawaban 1225 (verifikasi dengan program kamu).
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: kerjakan — bagi 2 SEBELUM mengambil mod

    return 0;
}
