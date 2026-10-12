/*
 * Day 59 — DFS
 * File  : tugas_03.cpp
 * Topik : Menghitung Pulau di Grid (Flood Fill 4-arah)
 * Tingkat: Easy ★★☆☆☆
 * -----------------------------------------------
 * Diberikan grid berukuran R × C berisi karakter '.' (air) dan '#' (daratan).
 * Hitung banyaknya PULAU — kelompok sel '#' yang saling terhubung
 * secara horizontal atau vertikal (4-arah, DIAGONAL TIDAK dihitung).
 *
 * Ini adalah connected components pada graph implisit: setiap sel adalah
 * node, tetangganya adalah 4 sel di sekelilingnya.
 *
 *   for tiap sel (r,c):
 *       if grid[r][c] == '#' && !visited[r][c]:
 *           islands++
 *           dfs(r, c)      ← menandai seluruh pulau itu
 *
 * Arah gerak: int dr[] = {-1,1,0,0}, dc[] = {0,0,-1,1};
 *
 * ⚠️ Selalu cek batas grid SEBELUM mengakses grid[r][c].
 *
 * Input format  : Baris 1: R dan C
 *                 R baris berikutnya: string sepanjang C
 * Output format : satu bilangan — jumlah pulau
 * Constraints   : 1 ≤ R, C ≤ 1000
 *                 Grid hanya berisi '.' dan '#'
 *
 * Sample Input 1:        Sample Output 1:
 * 4 5                    3
 * #..#.
 * #..#.
 * ...#.
 * ##...
 *
 * Sample Input 2:        Sample Output 2:
 * 3 3                    0
 * ...
 * ...
 * ...
 *
 * Sample Input 3:        Sample Output 3:
 * 2 2                    1
 * ##
 * ##
 *
 * NOTE Sample 1: pulau 1 = dua '#' di kolom 0 baris 0-1;
 *                pulau 2 = tiga '#' di kolom 3 baris 0-2;
 *                pulau 3 = dua '#' di baris 3 kolom 0-1.
 *                Perhatikan pulau 1 dan pulau 3 TIDAK terhubung
 *                (baris 2 kolom 0 adalah '.').
 *
 * HINT: Grid 1000×1000 semuanya '#' → kedalaman rekursi bisa 10^6.
 *       Kalau crash, ganti ke versi iteratif atau BFS.
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
}