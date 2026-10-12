/*
 * Day 22 — Aritmatika Modular
 * File  : exercise_5.cpp
 * Topik : Prefix Sum Modular + Range Query (Pengurangan Modular)
 * -----------------------------------------------
 * Diberikan array A berisi N bilangan bulat (BOLEH NEGATIF) dan Q query.
 * Setiap query berisi L dan R (1-indexed, inklusif).
 * Untuk setiap query, cetak (A[L] + A[L+1] + ... + A[R]) mod 10^9+7,
 * dengan hasil dinormalisasi ke rentang [0, MOD-1].
 *
 * Gunakan PREFIX SUM MODULAR:
 *   pre[i] = (pre[i-1] + A[i]) mod MOD      (normalisasi karena A[i] bisa negatif)
 *   jawab  = (pre[R] - pre[L-1] + MOD) mod MOD
 *                      └──────┬──┘
 *                 WAJIB +MOD — pre[R] bisa lebih kecil dari pre[L-1]!
 *
 * Ini adalah pitfall paling sering muncul di contest: lupa +MOD pada
 * pengurangan → hasil negatif → Wrong Answer.
 *
 * Input format  : Baris 1: N dan Q
 *                 Baris 2: N bilangan A[i]
 *                 Q baris berikutnya: L dan R
 * Output format : Q baris, masing-masing hasil range sum mod 10^9+7
 * Constraints   : 1 ≤ N, Q ≤ 200.000
 *                 -10^9 ≤ A[i] ≤ 10^9
 *                 1 ≤ L ≤ R ≤ N
 *
 * Sample Input 1:        Sample Output 1:
 * 5 3                    6
 * 1 2 3 4 5              9
 * 1 3                    15
 * 2 4
 * 1 5
 *
 * Sample Input 2:        Sample Output 2:
 * 4 3                    1000000005
 * -5 3 -2 10             6
 * 1 2                    11
 * 1 4
 * 2 4
 *
 * NOTE Sample 2 query 1: -5 + 3 = -2 → (-2) mod (10^9+7) = 10^9+5 = 1000000005.
 *      Query 2: -5+3-2+10 = 6. Query 3: 3-2+10 = 11.
 *      Jika hasilmu keluar angka negatif, berarti lupa +MOD.
 *
 * HINT: Simpan prefix sebagai long long yang SUDAH dinormalisasi ke [0, MOD).
 *       Baru selisihnya dinormalisasi lagi.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca N dan Q

    // TODO: Bangun prefix sum modular (1-indexed), normalisasi tiap langkah

    // TODO: Jawab tiap query dengan (pre[R] - pre[L-1] + MOD) % MOD

    return 0;
}
