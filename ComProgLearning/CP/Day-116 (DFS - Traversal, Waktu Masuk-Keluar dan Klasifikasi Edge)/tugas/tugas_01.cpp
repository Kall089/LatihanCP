/*
 * Day 59 — DFS
 * File  : tugas_01.cpp
 * Topik : Cek Keterhubungan Dua Node
 * Tingkat: Easy ★☆☆☆☆
 * -----------------------------------------------
 * Diberikan graph TAK BERARAH dengan N node dan M edge, serta dua node S dan T.
 * Tentukan apakah ada jalur dari S ke T.
 * Cetak "YES" jika ada, "NO" jika tidak.
 *
 * DFS dari S, lalu cukup periksa apakah visited[T] bernilai true.
 * Perhatikan: kita TIDAK butuh jarak, hanya butuh tahu terjangkau atau tidak —
 * jadi DFS sudah cukup, tidak perlu BFS.
 *
 * Input format  : Baris 1: N, M, S, T
 *                 M baris berikutnya: u dan v
 * Output format : "YES" atau "NO"
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 0 ≤ M ≤ 200.000
 *                 1 ≤ S, T ≤ N
 *
 * Sample Input 1:        Sample Output 1:
 * 5 3 1 3               YES
 * 1 2
 * 2 3
 * 4 5
 *
 * Sample Input 2:        Sample Output 2:
 * 5 3 1 4               NO
 * 1 2
 * 2 3
 * 4 5
 *
 * Sample Input 3:        Sample Output 3:
 * 3 0 2 2               YES
 *
 * NOTE Sample 3: S == T. Sebuah node selalu terjangkau dari dirinya sendiri,
 *                walaupun tidak punya edge sama sekali.
 */

#include <bits/stdc++.h>
using namespace std;

void dfs(int u, const vector<vector<int>> &adj, vector<bool> &visited)
{
    visited[u] = true;

    for (int v : adj[u])
    {
        if (!visited[v])
        {
            dfs(v, adj, visited);
        }
    }
}

int main()
{
    int n, m, s, t;
    cin >> n >> m >> s >> t;

    vector<vector<int>> adj(n + 1);
    vector<bool> visited(n + 1, false);

    while (m--)
    {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(s, adj, visited);

    if (visited[t])
    {
        cout << "YES";
    }
    else
    {
        cout << "NO";
    }
}