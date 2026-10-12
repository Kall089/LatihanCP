/*
 * Day 20 — Sliding Window
 * File  : tugas_02.cpp
 * Topik : Maximum Average Subarray of Size K
 * Tingkat: Easy ★☆☆☆☆
 * -----------------------------------------------
 * Diberikan array A berisi N bilangan dan integer K.
 * Cari subarray kontinu berukuran tepat K dengan AVERAGE TERTINGGI.
 * Outputkan average dengan presisi 6 angka di belakang koma.
 *
 * Tip: cari max sum saja (avg = sum / K), lalu print sebagai double.
 *
 * Input format  : Baris 1: N dan K
 *                 Baris 2: N bilangan bulat
 * Output format : 1 bilangan double dengan presisi 6
 * Constraints   : 1 ≤ K ≤ N ≤ 200.000
 *                 -10^4 ≤ A[i] ≤ 10^4
 *
 * Sample Input 1:        Sample Output 1:
 * 5 4                    12.750000
 * 1 12 -5 -6 50
 *
 * Sample Input 2:        Sample Output 2:
 * 1 1                    5.000000
 * 5
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: cari max sum, lalu output sum/K dengan setprecision(6)
    // Hint: cout << fixed << setprecision(6) << (double)max_sum / k;

    return 0;
}
