/*
 * Day 22 — Aritmatika Modular
 * File  : tugas_07.cpp
 * Topik : Faktorial Modulo dengan Precompute
 * Tingkat: Medium ★★★☆☆
 * -----------------------------------------------
 * Diberikan Q query, masing-masing berisi satu bilangan N.
 * Untuk setiap query, cetak N! mod 10^9+7.
 *
 * Menghitung ulang faktorial tiap query = O(Q × N) → TLE.
 * PRECOMPUTE array fact[0..MAXN] sekali di awal:
 *     fact[0] = 1
 *     fact[i] = fact[i-1] * i % MOD
 * Lalu tiap query hanya O(1) lookup.
 *
 * Ini adalah persiapan langsung untuk Day 26 (kombinatorika nCr)
 * dan Day 27 (modular inverse).
 *
 * Input format  : Baris 1: Q
 *                 Q baris berikutnya: satu bilangan N
 * Output format : Q baris, masing-masing N! mod 10^9+7
 * Constraints   : 1 ≤ Q ≤ 200.000
 *                 0 ≤ N ≤ 1.000.000
 *                 (definisi: 0! = 1)
 *
 * Sample Input 1:        Sample Output 1:
 * 6                      1
 * 0                      1
 * 1                      120
 * 5                      3628800
 * 10                     146326063
 * 20                     641102369
 * 1000000
 *
 * NOTE: 20! = 2432902008176640000 (masih muat long long)
 *       → 2432902008176640000 % (10^9+7) = 146326063.
 *       21! sudah overflow long long — inilah kenapa mod tiap langkah wajib.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;
const int MAXN = 1000005;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: precompute array fact[], lalu jawab tiap query O(1)

    return 0;
}
