/*
 * Day 20 — Sliding Window
 * File  : tugas_05.cpp
 * Topik : Longest Subarray with Sum ≤ K
 * Tingkat: Easy ★★☆☆☆
 * -----------------------------------------------
 * Diberikan array A berisi N bilangan POSITIF dan target K.
 * Cari panjang subarray kontinu TERPANJANG dengan sum ≤ K.
 *
 * Pendekatan: variable-size sliding window (longest pattern):
 *   expand R, while sum > K → shrink L; update ans.
 *
 * Input format  : Baris 1: N dan K
 *                 Baris 2: N bilangan positif
 * Output format : panjang subarray terpanjang
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 1 ≤ A[i] ≤ 10^9
 *                 0 ≤ K ≤ 2 × 10^14
 *
 * Sample Input 1:        Sample Output 1:
 * 6 8                    3
 * 1 2 3 4 5 6
 *
 * Sample Input 2:        Sample Output 2:
 * 5 100                  5
 * 1 2 3 4 5
 *
 * Sample Input 3:        Sample Output 3:
 * 4 0                    0
 * 1 2 3 4
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: variable-size sliding window (longest)

    return 0;
}
