/*
 * Day 59 — DFS (Depth-First Search)
 * File  : exercise_1.cpp
 * Topik : DFS Dasar — Urutan Kunjungan (Warm-up)
 * -----------------------------------------------
 * Diberikan graph TAK BERARAH dengan N node (bernomor 1..N) dan M edge.
 * Lakukan DFS mulai dari node 1, lalu cetak urutan node yang dikunjungi.
 *
 * Aturan: saat memilih tetangga mana yang dikunjungi lebih dulu, pilih
 * yang bernomor PALING KECIL. (Urutkan tiap adjacency list dulu.)
 *
 * Pola DFS standar:
 *   void dfs(int u) {
 *       visited[u] = true;              ← tandai DI AWAL
 *       cetak u
 *       for (int v : adj[u])
 *           if (!visited[v]) dfs(v);
 *   }
 *
 * Input format  : Baris 1: N dan M
 *                 M baris berikutnya: u dan v (ada edge u—v)
 * Output format : urutan node hasil DFS dari node 1, dipisah spasi
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 0 ≤ M ≤ 200.000
 *                 1 ≤ u, v ≤ N
 *                 Graph dijamin terhubung.
 *
 * Sample Input 1:        Sample Output 1:
 * 5 4                    1 2 4 5 3
 * 1 2
 * 1 3
 * 2 4
 * 4 5
 *
 * Sample Input 2:        Sample Output 2:
 * 6 5                    1 2 4 5 3 6
 * 1 2
 * 1 3
 * 2 4
 * 2 5
 * 3 6
 *
 * Sample Input 3:        Sample Output 3:
 * 1 0                    1
 *
 * NOTE Sample 1: dari 1 → 2 (tetangga terkecil) → 4 → 5 → buntu.
 *                Mundur sampai ke node 1, lalu lanjut ke tetangga 3.
 *                Perhatikan 3 dikunjungi TERAKHIR meski bertetangga langsung
 *                dengan node 1 — itulah ciri khas DFS (BFS akan mengunjungi
 *                3 di urutan kedua).
 * NOTE Sample 3: satu node tanpa edge — outputnya hanya node itu sendiri.
 *
 * HINT: adjacency list = vector<int> adj[MAXN].
 *       Untuk graph TAK BERARAH, push edge ke DUA arah.
 */

#include <bits/stdc++.h>
using namespace std;

void dfs(int u, vector<vector<int>> adj, vector<bool> &visited, vector<int> &order)
{
    visited[u] = true;

    order.push_back(u);

    for (int v : adj[u])
    {
        if (!visited[v])
        {
            dfs(v, adj, visited, order);
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    vector<bool> visited(n + 1, false);
    vector<int> order;

    while (m--)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            dfs(i, adj, visited, order);
        }
    }

    for (int x : order)
    {
        cout << x << " ";
    }
}