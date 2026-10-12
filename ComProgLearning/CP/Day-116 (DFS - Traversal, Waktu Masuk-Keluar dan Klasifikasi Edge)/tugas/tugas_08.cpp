/*
 * Day 59 — DFS
 * File  : tugas_08.cpp
 * Topik : Course Schedule — Urutan Prasyarat Mata Kuliah
 * Tingkat: Medium ★★★☆☆
 * -----------------------------------------------
 * Ada N mata kuliah bernomor 1..N. Diberikan M pasangan (a, b) yang berarti
 * "mata kuliah a adalah PRASYARAT dari b" — a harus diambil sebelum b.
 *
 * Cetak satu urutan pengambilan mata kuliah yang valid.
 * Jika prasyaratnya melingkar (mustahil dipenuhi), cetak "IMPOSSIBLE".
 *
 * Ini adalah topological sort dalam balutan cerita — pola soal yang
 * SANGAT sering muncul di contest dan wawancara kerja.
 *
 * Langkah:
 *   1. Bangun graph berarah: edge a → b untuk tiap prasyarat
 *   2. Deteksi cycle dengan 3-color
 *   3. Kalau DAG, hasilkan post-order lalu balik
 *
 * Untuk hasil deterministik: sort tiap adjacency list menaik, dan proses
 * node start dari 1 sampai N.
 *
 * Input format  : Baris 1: N dan M
 *                 M baris berikutnya: a dan b (a prasyarat b)
 * Output format : N bilangan — urutan valid, atau "IMPOSSIBLE"
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 0 ≤ M ≤ 200.000
 *
 * Sample Input 1:        Sample Output 1:
 * 4 3                    1 2 3 4
 * 1 2
 * 2 3
 * 3 4
 *
 * Sample Input 2:        Sample Output 2:
 * 2 2                    IMPOSSIBLE
 * 1 2
 * 2 1
 *
 * Sample Input 3:        Sample Output 3:
 * 3 0                    3 2 1
 *
 * NOTE Sample 2: mata kuliah 1 butuh 2, dan 2 butuh 1 — mustahil.
 * NOTE Sample 3: tidak ada prasyarat, urutan apa pun valid. Output di atas
 *      adalah hasil metode post-order + reverse. Urutan lain yang valid
 *      juga diterima.
 *
 * HINT: Kalau kamu ingin urutan LEXICOGRAPHICALLY SMALLEST, DFS tidak bisa
 *       menjaminnya — gunakan Kahn's algorithm dengan priority_queue (Day 60).
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int color[MAXN];
vector<int> topo;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: kerjakan dengan DFS topological sort + deteksi cycle

    return 0;
}
