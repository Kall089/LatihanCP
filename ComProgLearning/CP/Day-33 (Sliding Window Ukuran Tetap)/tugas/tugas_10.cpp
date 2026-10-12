/*
 * Day 20 — Sliding Window
 * File  : tugas_10.cpp
 * Topik : Count Number of Nice Subarrays (Tepat K bilangan ganjil)
 * Tingkat: Medium ★★★☆☆
 * -----------------------------------------------
 * Diberikan array A berisi N bilangan positif dan integer K.
 * Subarray "nice" = subarray kontinu yang mengandung TEPAT K bilangan ganjil.
 * Hitung banyak subarray nice di A.
 *
 * Pendekatan: trik atMost — sama seperti tugas_06.
 *   exactly(K) = atMost(K) - atMost(K-1)
 *   atMost(K) = banyak subarray dengan ≤ K bilangan ganjil
 *
 * Untuk implementasi atMost: maintain count odd di window, shrink saat > K.
 *
 * Input format  : Baris 1: N dan K
 *                 Baris 2: N bilangan positif
 * Output format : banyak subarray nice (long long)
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 1 ≤ K ≤ N
 *                 1 ≤ A[i] ≤ 10^9
 *
 * Sample Input 1:        Sample Output 1:
 * 5 3                    2
 * 1 1 2 1 1
 *
 * Sample Input 2:        Sample Output 2:
 * 3 1                    0
 * 2 4 6
 *
 * Sample Input 3:        Sample Output 3:
 * 8 2                    16
 * 2 2 2 1 2 2 1 2
 *
 * NOTE Sample 1: [1,1,2,1] dan [1,2,1,1] = 2 subarray dengan tepat 3 ganjil.
 * NOTE Sample 2: tidak ada bilangan ganjil → 0.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: atMost(K) - atMost(K-1) dengan sliding window
    // Hint: atMost(K) hitung subarray dengan ≤ K ganjil

    return 0;
}
