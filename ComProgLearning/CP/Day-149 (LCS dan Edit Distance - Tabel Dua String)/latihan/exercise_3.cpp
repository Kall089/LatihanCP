#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-149 (LCS dan Edit Distance - Tabel Dua String)
 * Latihan 3: Edit Distance (Levenshtein)
 *
 * Cetak jumlah MINIMUM operasi untuk mengubah A menjadi B. Operasi yang
 * diizinkan: sisip satu huruf, hapus satu huruf, ganti satu huruf.
 * Masing-masing berbiaya 1.
 *
 * Batas: 1 <= |A|, |B| <= 5000
 *
// Test Case 1 (contoh klasik):
// Input:
// kitten
// sitting
// Output:
// 3
// (k->s, e->i, sisipkan g)
//
// Test Case 2 (salah satu kosong setelah dihapus semua):
// Input:
// abcde
// a
// Output:
// 4
//
// Test Case 3 (identik):
// Input:
// halo
// halo
// Output:
// 0
 */

void solve() {
    // TODO: Tulis implementasi di sini
    // BASE CASE BUKAN NOL: dp[i][0] = i, dp[0][j] = j.
    // Test Case 2 langsung menangkap kesalahan ini.
    // beda -> 1 + min(diagonal=GANTI, atas=HAPUS, kiri=SISIP)
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
