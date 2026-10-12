#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-149 (LCS dan Edit Distance - Tabel Dua String)
 * Latihan 6: Supersequence Bersama Terpendek
 *
 * Cari string TERPENDEK yang memuat A DAN B sebagai subsekuens.
 * Cetak panjangnya, lalu salah satu string-nya.
 *
 * Batas: 1 <= |A|, |B| <= 1000
 *
// Test Case 1:
// Input:
// abac
// cab
// Output:
// 5
// cabac
//
// Test Case 2 (tidak ada huruf yang sama - tinggal disambung):
// Input:
// ab
// cd
// Output:
// 4
// abcd
// (urutan lain yang sah juga diterima)
//
// Test Case 3 (salah satu subsekuens dari yang lain):
// Input:
// abcde
// ace
// Output:
// 5
// abcde
 */

void solve() {
    // TODO: Tulis implementasi di sini
    // panjang SCS = |A| + |B| - LCS(A, B).
    // Untuk stringnya: telusuri balik tabel LCS, dan saat huruf TIDAK cocok
    // tuliskan huruf dari sisi yang kamu lewati. Jangan lupa menghabiskan
    // sisa string yang belum selesai setelah loop.
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
