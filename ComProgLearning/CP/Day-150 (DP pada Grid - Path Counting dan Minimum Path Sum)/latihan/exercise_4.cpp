#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-150 (DP pada Grid - Path Counting dan Minimum Path Sum)
 * Latihan 4: Jalur Minimum + Rekonstruksi
 *
 * Sama seperti Latihan 3, tetapi cetak juga jalurnya: satu baris berisi
 * koordinat (baris kolom) 0-indexed, dipisah koma, dari awal ke tujuan.
 *
 * Batas: 1 <= R, C <= 1000
 *
// Test Case 1:
// Input:
// 3 3
// 1 3 1
// 1 5 1
// 4 2 1
// Output:
// 7
// (0,0) (0,1) (0,2) (1,2) (2,2)
// (jalur lain yang totalnya 7 juga diterima)
//
// Test Case 2 (satu sel):
// Input:
// 1 1
// 9
// Output:
// 9
// (0,0)
//
// Test Case 3 (satu baris):
// Input:
// 1 3
// 1 2 3
// Output:
// 6
// (0,0) (0,1) (0,2)
 */

void solve()
{
    // TODO: Tulis implementasi di sini
    // Telusuri balik dari (R-1, C-1). Loop memakai (i > 0 || j > 0), BUKAN &&.
    // Butuh tabel PENUH -- rolling array tidak bisa direkonstruksi.
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
