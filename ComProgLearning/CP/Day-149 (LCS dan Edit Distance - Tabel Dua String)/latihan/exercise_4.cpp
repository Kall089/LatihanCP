#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-149 (LCS dan Edit Distance - Tabel Dua String)
 * Latihan 4: Edit Distance + Daftar Operasinya
 *
 * Cetak jumlah operasi minimum, lalu satu baris per operasi dalam urutan
 * dari kiri ke kanan, dengan format:
 *   GANTI x -> y
 *   HAPUS x
 *   SISIP y
 *
 * Batas: 1 <= |A|, |B| <= 1000
 *
// Test Case 1:
// Input:
// kitten
// sitting
// Output:
// 3
// GANTI k -> s
// GANTI e -> i
// SISIP g
// (urutan/pilihan lain yang jumlahnya 3 juga diterima)
//
// Test Case 2 (hanya penghapusan):
// Input:
// abc
// a
// Output:
// 2
// HAPUS b
// HAPUS c
//
// Test Case 3 (identik - tidak ada operasi):
// Input:
// aa
// aa
// Output:
// 0
 */

void solve() {
    // TODO: Tulis implementasi di sini
    // Loop rekonstruksi memakai (i > 0 || j > 0), BUKAN &&.
    // Periksa kasus "cocok" LEBIH DULU, supaya tidak melaporkan GANTI a -> a.
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
