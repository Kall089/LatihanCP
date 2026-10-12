/*
 * Day 59 — DFS
 * File  : tugas_09.cpp
 * Topik : Area Terbesar di Grid (Flood Fill + Akumulasi)
 * Tingkat: Medium ★★★☆☆
 * -----------------------------------------------
 * Diberikan grid R × C berisi '.' (kosong) dan '#' (terisi).
 * Cari LUAS (jumlah sel) dari kelompok '#' terbesar yang saling terhubung
 * secara 4-arah.
 *
 * Jika tidak ada '#' sama sekali, cetak 0.
 *
 * Perbedaan dengan tugas_03: di sini DFS harus MENGEMBALIKAN jumlah sel
 * yang ditandainya, bukan sekadar menandai.
 *
 *   int dfs(int r, int c) {
 *       if (di luar grid || vis[r][c] || grid[r][c] == '.') return 0;
 *       vis[r][c] = true;
 *       int area = 1;
 *       for tiap 4 arah: area += dfs(nr, nc);
 *       return area;
 *   }
 *
 * Input format  : Baris 1: R dan C
 *                 R baris berikutnya: string sepanjang C
 * Output format : satu bilangan — luas area terbesar
 * Constraints   : 1 ≤ R, C ≤ 1000
 *
 * Sample Input 1:        Sample Output 1:
 * 4 5                    4
 * ##...
 * ##...
 * ...#.
 * ...##
 *
 * Sample Input 2:        Sample Output 2:
 * 2 2                    0
 * ..
 * ..
 *
 * Sample Input 3:        Sample Output 3:
 * 3 3                    9
 * ###
 * ###
 * ###
 *
 * NOTE Sample 1: kelompok kiri-atas berukuran 4 (blok 2×2);
 *      kelompok kanan-bawah berukuran 3. Terbesar = 4.
 * NOTE Sample 3: semua sel terhubung → 3×3 = 9.
 *
 * HINT: Grid 1000×1000 penuh '#' → rekursi sedalam 10^6 bisa crash.
 *       Kalau itu terjadi, konversi ke versi iteratif dengan stack.
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: kerjakan dengan flood fill yang mengembalikan luas area

    return 0;
}
