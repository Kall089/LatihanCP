/*
 * Day 59 — DFS
 * File  : tugas_02.cpp
 * Topik : Ukuran Setiap Connected Component
 * Tingkat: Easy ★☆☆☆☆
 * -----------------------------------------------
 * Diberikan graph TAK BERARAH dengan N node dan M edge.
 * Cetak ukuran SETIAP connected component, diurutkan MENAIK,
 * dipisah spasi.
 *
 * Loop semua node; setiap node yang belum dikunjungi menandai awal
 * komponen baru. DFS dari sana sambil menghitung node yang ditandai.
 * Kumpulkan semua ukuran ke dalam vector, lalu sort.
 *
 * Input format  : Baris 1: N dan M
 *                 M baris berikutnya: u dan v
 * Output format : ukuran tiap komponen, terurut menaik, dipisah spasi
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 0 ≤ M ≤ 200.000
 *
 * Sample Input 1:        Sample Output 1:
 * 7 4                    1 1 2 3
 * 1 2
 * 2 3
 * 3 1
 * 4 5
 *
 * Sample Input 2:        Sample Output 2:
 * 3 0                    1 1 1
 *
 * Sample Input 3:        Sample Output 3:
 * 4 3                    4
 * 1 2
 * 2 3
 * 3 4
 *
 * NOTE Sample 1: N=7. Edge membentuk segitiga 1-2-3 dan pasangan 4-5.
 *      Node 6 dan 7 terisolasi.
 *      Komponen: {1,2,3} ukuran 3, {4,5} ukuran 2, {6} ukuran 1, {7} ukuran 1.
 *      Terurut menaik → 1 1 2 3.
 *      Perhatikan: node terisolasi TETAP dihitung sebagai komponen sendiri.
 */

#include <bits/stdc++.h>
using namespace std;

void dfs(int u, const vector<vector<int>> &adj, vector<bool> &visited, int &x)
{
    visited[u] = true;

    for (int v : adj[u])
    {
        if (!visited[v])
        {
            x++;
            dfs(v, adj, visited, x);
        }
    }
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

    vector<bool> visited(n + 1, false);
    vector<int> node_count;

    for (int i = 1; i <= n; i++)
    {
        int x = 1;
        if (!visited[i])
        {
            dfs(i, adj, visited, x);
            node_count.push_back(x);
        }
    }

    sort(node_count.begin(), node_count.end());

    for (int z : node_count)
    {
        cout << z << " ";
    }
}
