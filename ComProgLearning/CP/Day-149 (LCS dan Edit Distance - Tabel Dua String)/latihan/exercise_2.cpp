#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-149 (LCS dan Edit Distance - Tabel Dua String)
 * Latihan 2: LCS + Rekonstruksi
 *
 * Cetak panjang LCS pada baris pertama, lalu SALAH SATU LCS yang sah pada
 * baris kedua. Kalau panjangnya 0, cetak baris kosong.
 *
 * Batas: 1 <= |A|, |B| <= 3000
 *
// Test Case 1:
// Input:
// abcbdab
// bdcaba
// Output:
// 4
// bcba
// (jawaban lain yang panjangnya 4 juga diterima)
//
// Test Case 2:
// Input:
// axbycz
// abc
// Output:
// 3
// abc
//
// Test Case 3 (tidak ada kesamaan):
// Input:
// qq
// ww
// Output:
// 0
// (baris kosong)
 */

void solve() {
    // TODO: Tulis implementasi di sini
    // Telusuri balik dari dp[n][m]:
    //   huruf cocok -> ambil, i--, j--
    //   selain itu  -> pindah ke tetangga yang nilainya SAMA dengan dp[i][j]
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
