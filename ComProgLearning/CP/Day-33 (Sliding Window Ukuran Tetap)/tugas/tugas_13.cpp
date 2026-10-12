/*
 * Day 20 — Sliding Window
 * File  : tugas_13.cpp
 * Topik : Subarrays with K Different Integers (LeetCode 992)
 * Tingkat: Hard ★★★★☆
 * -----------------------------------------------
 * Diberikan array A berisi N bilangan dan integer K.
 * Hitung BANYAK subarray kontinu yang mengandung TEPAT K bilangan berbeda
 * (distinct).
 *
 * Sama seperti tugas_06 tapi dengan constraint lebih besar dan
 * benar-benar fokus pada trik atMost.
 *
 * Trik:
 *   exactly(K) = atMost(K) - atMost(K-1)
 *
 * Untuk atMost(K): sliding window + freq map.
 *   Saat freq.size() > K, shrink L sampai valid.
 *   Untuk tiap R, jumlah subarray valid berakhiran R = R - L + 1.
 *   Total = sum dari (R - L + 1).
 *
 * Input format  : Baris 1: N dan K
 *                 Baris 2: N bilangan
 * Output format : banyak subarray (long long)
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 1 ≤ K ≤ N
 *                 1 ≤ A[i] ≤ N
 *
 * Sample Input 1:        Sample Output 1:
 * 5 2                    7
 * 1 2 1 2 3
 *
 * Sample Input 2:        Sample Output 2:
 * 6 3                    3
 * 1 2 1 3 4 4
 *
 * NOTE Sample 1: subarray dengan tepat 2 distinct:
 *   [1,2], [2,1], [1,2], [2,1,2], [1,2,1], [1,2,1,2], [2,1,2] → 7
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: implement atMost dengan sliding window, lalu hitung diff

    return 0;
}
