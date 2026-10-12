/*
============================================================
  Solution 1: BFS Dasar — Kunjungi Semua Node dari Source
============================================================
Kompleksitas: O(V + E)

Cara kerja:
- Inisialisasi dist[s] = 0, push s ke queue
- Tiap iterasi: ambil u dari depan queue
- Untuk tiap tetangga v yang belum dikunjungi (dist == -1):
    set dist[v] = dist[u] + 1, push v ke queue
- Simpan urutan kunjungan di vector 'order'
*/
#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, s;
    cin >> n >> m >> s;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> dist(n + 1, -1);
    vector<int> order;
    queue<int> q;

    dist[s] = 0;
    q.push(s);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        order.push_back(u);

        for (int v : adj[u])
        {
            if (dist[v] == -1)
            {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    cout << "=== Urutan BFS ===\n";
    for (int i = 0; i < (int)order.size(); i++)
        cout << order[i] << (i + 1 < (int)order.size() ? " " : "\n");

    cout << "=== Jarak dari node " << s << " ===\n";
    for (int u = 1; u <= n; u++)
        cout << "dist(" << u << ") = " << dist[u] << "\n";

    cout << "=== Node Tidak Terjangkau ===\n";
    bool ada = false;
    for (int u = 1; u <= n; u++)
        if (dist[u] == -1)
        {
            cout << u << "\n";
            ada = true;
        }
    if (!ada)
        cout << "Semua node terjangkau\n";

    return 0;
}
