/*
============================================================
  Solution 2: Konversi Antar Representasi Graph
============================================================
Kompleksitas: O(V² + E log E)
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int,int>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w});  // directed
    }

    // Adjacency Matrix
    cout << "=== Adjacency Matrix ===\n";
    vector<vector<int>> mat(n + 1, vector<int>(n + 1, 0));
    for (int u = 1; u <= n; u++)
        for (auto [v, w] : adj[u])
            mat[u][v] = w;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            cout << mat[i][j] << (j < n ? " " : "\n");
    }

    // Edge List
    cout << "\n=== Edge List (sorted by weight) ===\n";
    vector<tuple<int,int,int>> edges;
    for (int u = 1; u <= n; u++)
        for (auto [v, w] : adj[u])
            edges.push_back({w, u, v});

    sort(edges.begin(), edges.end());
    for (auto [w, u, v] : edges)
        cout << u << " " << v << " (w=" << w << ")\n";

    return 0;
}
