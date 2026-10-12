#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-143 (DP Linear 1D)
 * Latihan 3: Perampok Rumah
 *
 * Deret N rumah dengan nilai a[0..N-1]. Tidak boleh merampok dua rumah yang
 * BERSEBELAHAN. Cetak total maksimum.
 *
 * Batas: 1 <= N <= 2*10^5, 0 <= a[i] <= 10^9
 *
// Test Case 1 (greedy selang-seling GAGAL di sini):
// Input:
// 4
// 2 1 1 2
// Output:
// 4
// (ambil rumah 0 dan 3; greedy genap/ganjil hanya memberi 3)
//
// Test Case 2:
// Input:
// 5
// 5 1 1 5 1
// Output:
// 10
// (rumah 0 dan 3: 5 + 5 = 10)
//
// Test Case 3 (satu rumah, uji base case):
// Input:
// 1
// 7
// Output:
// 7
 */

void solve() {
    // TODO: Tulis implementasi di sini
    // dp[i] = max(dp[i-1], dp[i-2] + a[i])
    // Pakai rolling variable; urutan penugasan p2 = p1; p1 = c; WAJIB begitu.
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
