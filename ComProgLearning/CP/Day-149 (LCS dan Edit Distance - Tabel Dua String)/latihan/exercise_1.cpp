#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-149 (LCS dan Edit Distance - Tabel Dua String)
 * Latihan 1: Panjang LCS
 *
 * Diberi dua string A dan B (huruf kecil). Cetak panjang subsekuens bersama
 * terpanjang (tidak harus berdekatan).
 *
 * Batas: 1 <= |A|, |B| <= 3000
 *
// Test Case 1:
// Input:
// abcbdab
// bdcaba
// Output:
// 4
// (mis. bcba atau bdab)
//
// Test Case 2 (tidak ada huruf yang sama):
// Input:
// abc
// xyz
// Output:
// 0
//
// Test Case 3 (salah satu adalah subsekuens penuh dari yang lain):
// Input:
// ace
// abcde
// Output:
// 3
 */

void solve() {
    // TODO: Tulis implementasi di sini
    // Tabel (n+1) x (m+1). INGAT: huruf terakhir prefiks i adalah a[i-1].
    // cocok -> dp[i-1][j-1] + 1 ; beda -> max(dp[i-1][j], dp[i][j-1])
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
