/*
 * Day 20 — Sliding Window
 * File  : tugas_06.cpp
 * Topik : Subarray with Exactly K Distinct Elements (Count)
 * Tingkat: Medium ★★★☆☆
 * -----------------------------------------------
 * Diberikan array A berisi N bilangan dan integer K.
 * Hitung BANYAK subarray kontinu yang mengandung TEPAT K bilangan berbeda.
 *
 * Trik klasik: exactly(K) = atMost(K) - atMost(K-1).
 *   atMost(K) = jumlah subarray dengan ≤ K distinct
 *   Untuk setiap R, jumlah subarray valid berakhiran R = R - L + 1.
 *
 * Input format  : Baris 1: N dan K
 *                 Baris 2: N bilangan
 * Output format : satu bilangan (long long)
 * Constraints   : 1 ≤ K ≤ N ≤ 200.000
 *                 1 ≤ A[i] ≤ N
 *
 * Sample Input 1:        Sample Output 1:
 * 6 2                    7
 * 1 2 1 2 3 4
 *
 * Sample Input 2:        Sample Output 2:
 * 5 1                    5
 * 1 1 1 1 1
 *
 * Sample Input 3:        Sample Output 3:
 * 4 3                    3
 * 1 2 1 3
 *
 * NOTE Sample 1: subarray dengan tepat 2 distinct:
 *   [1,2], [2,1], [1,2], [2,1,2], [1,2,1], [1,2,1,2], [2,1,2] = 7 subarray (sudah dihitung
 *   index unik). Memang lumayan tricky—itulah gunanya trik atMost.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: implementasi atMost(K) dengan sliding window + freq map
    // ll exactly = atMost(K) - atMost(K - 1);

    return 0;
}
