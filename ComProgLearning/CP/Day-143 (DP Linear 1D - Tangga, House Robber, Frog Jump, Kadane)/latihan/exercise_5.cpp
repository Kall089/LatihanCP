#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-143 (DP Linear 1D)
 * Latihan 5: Katak Melompat (Frog Jump)
 *
 * N batu dengan ketinggian h[0..N-1]. Katak mulai di batu 0 dan ingin sampai
 * di batu N-1. Dari batu i ia boleh melompat ke i+1 .. i+K, dengan biaya
 * |h[i] - h[j]|. Cetak total biaya minimum.
 *
 * Batas: 2 <= N <= 10^5, 1 <= K <= 100, 1 <= h[i] <= 10^4
 *
// Test Case 1 (K = 1, tidak ada pilihan):
// Input:
// 4 1
// 10 30 40 20
// Output:
// 50
// (|10-30| + |30-40| + |40-20| = 20 + 10 + 20 = 50)
//
// Test Case 2 (K = 2, greedy lokal menyesatkan):
// Input:
// 4 2
// 10 30 40 20
// Output:
// 30
// (0 -> 1 -> 3: 20 + 10 = 30)
//
// Test Case 3 (K besar, bisa langsung melompat):
// Input:
// 5 4
// 10 100 100 100 20
// Output:
// 10
 */

void solve() {
    // TODO: Tulis implementasi di sini
    // dp[i] = min over j=1..K of dp[i-j] + |h[i]-h[i-j]|, dp[0] = 0.
    // O(N*K). Untuk K sampai 10^5 pendekatan ini TLE -- butuh monotonic deque.
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
