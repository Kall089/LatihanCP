/*
 * Day 11 — Recursion Dasar
 * File  : tugas_12.cpp
 * Topik : Recursive Flood Fill
 * Kesulitan: Hard
 * -----------------------------------------------
 * Pada grid n×m berisi '.' (kosong) dan '#' (dinding),
 * ganti semua sel yang terhubung dengan sel (r, c) dari '.'
 * menjadi '*'.
 *
 * Dua sel dianggap terhubung jika berbagi sisi (4-arah: U/D/L/R).
 *
 * Input format  : Baris 1: n m r c (grid size dan titik awal)
 *                 Baris 2..n+1: baris grid
 * Output format : Grid setelah flood fill
 * Constraints   : 1 ≤ n,m ≤ 100, 0 ≤ r < n, 0 ≤ c < m
 *
 * Sample Input 1:      Sample Output 1:
 * 4 5 1 1              .....
 * .....                .***.
 * .....                .***.
 * ..##.                ..##.
 * .....                .....
 *
 * (hanya sel yang terhubung ke (1,1) dari (1,0) diisi — cek koneksi!)
 *
 * Catatan: Sample di atas: flood dari (1,1) mengisi semua '.'
 * yang terhubung ke (1,1). Grid (3,0)..(3,4) terputus oleh '#'.
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Implementasikan floodFill(grid, r, c, n, m) rekursif
    // - Jika (r,c) di luar batas atau bukan '.' → return
    // - Set grid[r][c] = '*'
    // - Rekursi ke 4 tetangga (atas, bawah, kiri, kanan)

    return 0;
}
