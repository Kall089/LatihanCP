/*
============================================================
  Solution 2: BFS Shortest Path Unweighted
============================================================
Kompleksitas: O(V + E)

Cara kerja:
- BFS dari S sambil simpan prev[v] = u (parent v dalam BFS tree)
- Setelah BFS, rekonstruksi path dari T dengan mengikuti prev[]
- Balik path karena kita trace dari T ke S
*/
#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int S, T; cin >> S >> T;

    vector<int> dist(n + 1, -1), prev(n + 1, -1);
    queue<int> q;
    dist[S] = 0;
    q.push(S);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == T) break;
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                prev[v] = u;
                q.push(v);
            }
        }
    }

    if (dist[T] == -1) {
        cout << "TIDAK ADA PATH\n";
        return 0;
    }

    cout << "Panjang path terpendek: " << dist[T] << "\n";

    vector<int> path;
    for (int v = T; v != -1; v = prev[v])
        path.push_back(v);
    reverse(path.begin(), path.end());

    cout << "Path: ";
    for (int i = 0; i < (int)path.size(); i++)
        cout << path[i] << (i + 1 < (int)path.size() ? " -> " : "\n");

    return 0;
}
