/*
 * Day 59 — DFS
 * File  : tugas_04.cpp
 * Topik : Apakah Graph Ini Sebuah Pohon?
 * Tingkat: Easy ★★☆☆☆
 * -----------------------------------------------
 * Diberikan graph TAK BERARAH dengan N node dan M edge.
 * Tentukan apakah graph tersebut adalah sebuah POHON (tree).
 * Cetak "YES" atau "NO".
 *
 * Sebuah graph adalah pohon jika dan hanya jika memenuhi KETIGA syarat:
 *   1. TERHUBUNG (semua node saling terjangkau)
 *   2. TIDAK ADA CYCLE
 *   3. M == N − 1
 *
 * Fakta menarik: syarat (3) plus salah satu dari (1) atau (2) sudah cukup —
 * dua syarat mana pun mengimplikasikan yang ketiga. Tapi untuk latihan,
 * cek ketiganya secara eksplisit dengan DFS.
 *
 * Input format  : Baris 1: N dan M
 *                 M baris berikutnya: u dan v
 * Output format : "YES" atau "NO"
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 0 ≤ M ≤ 200.000
 *                 Tidak ada self-loop atau multi-edge.
 *
 * Sample Input 1:        Sample Output 1:
 * 4 3                    YES
 * 1 2
 * 1 3
 * 3 4
 *
 * Sample Input 2:        Sample Output 2:
 * 4 4                    NO
 * 1 2
 * 2 3
 * 3 4
 * 4 1
 *
 * Sample Input 3:        Sample Output 3:
 * 4 2                    NO
 * 1 2
 * 3 4
 *
 * Sample Input 4:        Sample Output 4:
 * 1 0                    YES
 *
 * NOTE Sample 2: M = N = 4, ada cycle → bukan pohon.
 * NOTE Sample 3: tidak ada cycle, tapi TIDAK TERHUBUNG (dua komponen)
 *                → bukan pohon, ini "forest".
 * NOTE Sample 4: satu node tanpa edge adalah pohon yang sah (M = 0 = N−1).
 */

#include <bits/stdc++.h>
using namespace std;

void dfs(int u, const vector<vector<int>> &adj, vector<bool> visited)
{
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}