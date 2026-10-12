/*
 * Day 22 — Aritmatika Modular
 * File  : tugas_06.cpp
 * Topik : Fibonacci ke-N Modulo 10^9+7 (Iteratif)
 * Tingkat: Medium ★★★☆☆
 * -----------------------------------------------
 * Definisi: F(0) = 0, F(1) = 1, F(n) = F(n-1) + F(n-2).
 * Diberikan N, hitung F(N) mod 10^9+7.
 *
 * F(N) tumbuh eksponensial — F(100) saja sudah 21 digit, jauh melebihi
 * long long. Kuncinya: ambil mod di SETIAP langkah penjumlahan.
 * Karena F(n) = F(n-1) + F(n-2) hanya melibatkan penjumlahan, properti
 * distributif modulo menjamin hasilnya tetap benar.
 *
 * Gunakan iterasi dengan dua variabel (rolling), bukan array —
 * hemat memori O(1).
 *
 * Input format  : Baris 1: N
 * Output format : F(N) mod 10^9+7
 * Constraints   : 0 ≤ N ≤ 10^7
 *
 * Sample Input 1:  0        Sample Output 1:  0
 * Sample Input 2:  1        Sample Output 2:  1
 * Sample Input 3:  10       Sample Output 3:  55
 * Sample Input 4:  50       Sample Output 4:  586268941
 * Sample Input 5:  1000     Sample Output 5:  517691607
 * Sample Input 6:  1000000  Sample Output 6:  918091266
 *
 * NOTE: F(50) = 12586269025, dan 12586269025 % (10^9+7) = 586268941.
 *       Ini bukti bahwa mod-tiap-langkah memberi hasil yang sama dengan
 *       menghitung nilai penuh lalu mod di akhir.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: kerjakan dengan iterasi rolling + mod tiap langkah

    return 0;
}
