/*
 * Day 22 — Aritmatika Modular
 * File  : tugas_10.cpp
 * Topik : Menara Pangkat A^(B^C) mod P (Fermat's Little Theorem)
 * Tingkat: Medium ★★★★☆
 * -----------------------------------------------
 * Diberikan A, B, C dan bilangan PRIMA P = 10^9+7.
 * Hitung A^(B^C) mod P.
 *
 * Masalahnya: B^C sendiri bisa astronomis (misal 10^9 pangkat 10^9),
 * tidak muat di variabel apapun. Kita tidak bisa menghitung eksponennya
 * lebih dulu lalu memanggil modpow.
 *
 * SOLUSI — Fermat's Little Theorem (preview Day 27):
 *   Jika P prima dan gcd(A, P) = 1, maka  A^(P-1) ≡ 1 (mod P).
 *   Konsekuensinya, eksponen boleh direduksi modulo (P-1):
 *
 *       A^E mod P  =  A^(E mod (P-1)) mod P
 *
 *   Jadi: hitung E = B^C mod (P-1) dengan modpow,
 *         lalu jawaban = modpow(A, E, P).
 *
 * ⚠️ Perhatikan DUA modulus berbeda:
 *      basis  → mod P
 *      eksponen → mod (P-1)
 *    Tertukar = jawaban salah.
 *
 * ⚠️ Kasus A ≡ 0 (mod P) harus ditangani terpisah — Fermat tidak berlaku
 *    karena gcd(A,P) ≠ 1. Jika A mod P == 0, jawabannya 0 (untuk eksponen > 0).
 *
 * Input format  : Baris 1: T
 *                 T baris berikutnya: A, B, C
 * Output format : T baris, masing-masing A^(B^C) mod (10^9+7)
 * Constraints   : 1 ≤ T ≤ 100.000
 *                 1 ≤ A, B, C ≤ 10^9
 *
 * Sample Input 1:        Sample Output 1:
 * 3                      512
 * 2 3 2                  390625
 * 5 2 3                  7
 * 7 1 1
 *
 * NOTE: 2^(3^2) = 2^9 = 512.
 *       5^(2^3) = 5^8 = 390625.
 *       7^(1^1) = 7^1 = 7.
 *       Sample sengaja kecil agar bisa diverifikasi manual — tapi
 *       solusimu harus tetap benar untuk A=B=C=10^9.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: reduksi eksponen mod (MOD-1), lalu modpow dengan mod MOD

    return 0;
}
