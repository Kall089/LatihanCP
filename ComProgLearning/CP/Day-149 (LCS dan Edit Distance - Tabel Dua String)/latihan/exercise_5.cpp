#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-149 (LCS dan Edit Distance - Tabel Dua String)
 * Latihan 5: Substring Bersama Terpanjang
 *
 * Perhatikan: SUBSTRING, bukan subsekuens — hurufnya harus BERDEKATAN.
 * Cetak panjangnya, lalu salah satu substring-nya. Cetak "0" dan baris kosong
 * jika tidak ada.
 *
 * Batas: 1 <= |A|, |B| <= 3000
 *
// Test Case 1:
// Input:
// abcdxyz
// xyzabcd
// Output:
// 4
// abcd
//
// Test Case 2 (bandingkan dengan LCS!):
// Input:
// abcbdab
// bdcaba
// Output:
// 2
// ab
// (LCS-nya 4, tapi substring bersama terpanjang hanya 2 — inilah bedanya)
//
// Test Case 3 (tidak ada huruf yang sama):
// Input:
// aaa
// bbb
// Output:
// 0
// (baris kosong)
 */

void solve() {
    // TODO: Tulis implementasi di sini
    // beda -> dp[i][j] = 0 (RESET, bukan max)
    // jawaban = MAX atas SELURUH tabel, bukan dp[n][m]
    // Simpan indeks akhir agar bisa memotong substring-nya.
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
