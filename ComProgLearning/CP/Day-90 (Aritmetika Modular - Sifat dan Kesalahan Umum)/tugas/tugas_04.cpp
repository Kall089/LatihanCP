/*
 * Day 22 — Aritmatika Modular
 * File  : tugas_04.cpp
 * Topik : Jam Melingkar (Modulo sebagai Siklus)
 * Tingkat: Easy ★☆☆☆☆
 * -----------------------------------------------
 * Sebuah jam menunjukkan pukul H (format 24 jam, 0 ≤ H ≤ 23).
 * Diberikan Q query, masing-masing berisi bilangan bulat X yang
 * BISA NEGATIF (X < 0 berarti mundur ke masa lalu).
 *
 * Untuk setiap query, cetak jam yang ditunjukkan setelah X jam berlalu,
 * dalam format 24 jam (0..23).
 *
 * Ini adalah aplikasi langsung modulo sebagai sistem melingkar.
 * Karena X bisa negatif, kamu WAJIB memakai normalisasi:
 *     ((H + X) % 24 + 24) % 24
 *
 * Input format  : Baris 1: H dan Q
 *                 Q baris berikutnya: satu bilangan X
 * Output format : Q baris, masing-masing jam hasil (0..23)
 * Constraints   : 0 ≤ H ≤ 23
 *                 1 ≤ Q ≤ 100.000
 *                 -10^18 ≤ X ≤ 10^18
 *
 * Sample Input 1:        Sample Output 1:
 * 10 5                   15
 * 5                      2
 * 16                     8
 * -2                     10
 * 24                     22
 * -1000000000000000000
 *
 * NOTE: 10 + 5 = 15.
 *       10 + 16 = 26 → 26 % 24 = 2.
 *       10 - 2 = 8.
 *       10 + 24 = 34 → 34 % 24 = 10 (satu putaran penuh, kembali).
 *       Query terakhir: verifikasi bahwa hasilmu berada di [0,23]
 *       dan tidak negatif.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: kerjakan dengan normalisasi modulo 24

    return 0;
}
