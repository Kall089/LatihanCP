/*
 * Day 22 — Aritmatika Modular
 * File  : exercise_4.cpp
 * Topik : Modulo Bilangan Raksasa (Horner's Rule)
 * -----------------------------------------------
 * Diberikan sebuah bilangan bulat non-negatif N yang SANGAT besar —
 * sampai 100.000 digit, sehingga tidak muat di tipe data apapun.
 * N diberikan sebagai STRING. Hitung N mod M.
 *
 * Gunakan HORNER'S RULE — proses digit dari kiri ke kanan:
 *
 *   N = d0*10^(k-1) + d1*10^(k-2) + ... + d(k-1)
 *     = (((d0*10 + d1)*10 + d2)*10 + ...)
 *
 *   res = 0
 *   for each digit d:
 *       res = (res * 10 + d) % M
 *
 * Karena res selalu < M ≤ 10^9, maka res*10 + 9 < 10^10 → aman di long long.
 *
 * Input format  : Baris 1: string N (tanpa leading zero berlebih)
 *                 Baris 2: M
 * Output format : satu bilangan — N mod M
 * Constraints   : 1 ≤ panjang(N) ≤ 100.000
 *                 1 ≤ M ≤ 10^9
 *
 * Sample Input 1:        Sample Output 1:
 * 12345                  4
 * 7
 *
 * Sample Input 2:        Sample Output 2:
 * 100000000000000000000  4900
 * 1000000007
 *
 * Sample Input 3:        Sample Output 3:
 * 987654321987654321     74074116
 * 1000000007
 *
 * NOTE Sample 1: 12345 = 1763×7 + 4 → hasil 4.
 * NOTE Sample 2: 10^20 = (10^9)^2 × 100. Karena 10^9 ≡ -7 (mod 10^9+7),
 *                hasilnya ≡ 49 × 100 = 4900.
 *
 * HINT: Baca N sebagai std::string, iterasi karakter, konversi dengan (c - '0').
 *       Jangan mencoba stoll() — angkanya terlalu besar.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca string N dan modulus M

    // TODO: Terapkan Horner's rule, ambil mod tiap digit

    // TODO: Cetak hasil

    return 0;
}
