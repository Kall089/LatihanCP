/*
 * Day 22 — Aritmatika Modular
 * File  : tugas_14.cpp
 * Topik : Jumlah Pangkat — ∑ i^K mod P
 * Tingkat: Hard ★★★★☆
 * -----------------------------------------------
 * Diberikan N dan K. Hitung:
 *
 *     S = 1^K + 2^K + 3^K + ... + N^K   (mod 10^9+7)
 *
 * K bisa sampai 10^18, jadi tiap suku WAJIB dihitung dengan binary
 * exponentiation, bukan perkalian berulang.
 *
 * Kompleksitas target: O(N log K).
 *
 * Definisi khusus: i^0 = 1 untuk semua i ≥ 1.
 *
 * Bonus (opsional, untuk yang mau menantang diri):
 *   Jika K kecil (misal K ≤ 100) tapi N sampai 10^18, ada solusi
 *   O(K² log P) memakai interpolasi Lagrange — di luar cakupan hari ini,
 *   tapi bagus untuk diketahui bahwa solusi itu ada.
 *
 * Input format  : Baris 1: N dan K
 * Output format : satu bilangan — S mod 10^9+7
 * Constraints   : 1 ≤ N ≤ 1.000.000
 *                 0 ≤ K ≤ 10^18
 *
 * Sample Input 1:        Sample Output 1:
 * 3 2                    14
 *
 * Sample Input 2:        Sample Output 2:
 * 5 1                    15
 *
 * Sample Input 3:        Sample Output 3:
 * 4 0                    4
 *
 * Sample Input 4:                    Sample Output 4:
 * 10 1000000000000000000             289342769
 *
 * NOTE Sample 1: 1² + 2² + 3² = 1 + 4 + 9 = 14.
 * NOTE Sample 2: 1 + 2 + 3 + 4 + 5 = 15.
 * NOTE Sample 3: setiap i^0 = 1, ada 4 suku → 4.
 * NOTE Sample 4: eksponen raksasa — hanya bisa dengan modpow.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: kerjakan — loop i dari 1..N, akumulasi modpow(i, K, MOD)

    return 0;
}
