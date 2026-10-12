/*
============================================================
  Solution 6: Multi-format Graph Input
============================================================
Kompleksitas: O((V+E) log V)
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string format;
    cin >> format;

    int n = 0;
    vector<vector<pair<int,int>>> adj;

    if (format == "LIST") {
        int m; cin >> n >> m;
        adj.assign(n + 1, {});
        for (int i = 0; i < m; i++) {
            int u, v, w; cin >> u >> v >> w;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
    } else if (format == "MATRIX") {
        cin >> n;
        adj.assign(n + 1, {});
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                int w; cin >> w;
                if (w > 0 && i < j) {
                    adj[i].push_back({j, w});
                    adj[j].push_back({i, w});
                }
            }
    } else {  // EDGES
        int m; cin >> n >> m;
        adj.assign(n + 1, {});
        for (int i = 0; i < m; i++) {
            int u, v, w; cin >> u >> v >> w;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
    }

    int m = 0;
    for (int u = 1; u <= n; u++) {
        sort(adj[u].begin(), adj[u].end());
        m += adj[u].size();
    }
    m /= 2;

    cout << "Nodes: " << n << ", Edges: " << m << "\n";
    cout << "Adjacency List:\n";
    for (int u = 1; u <= n; u++) {
        cout << u << ":";
        for (auto [v, w] : adj[u]) cout << " (" << v << "," << w << ")";
        cout << "\n";
    }

    vector<int> ds;
    for (int u = 1; u <= n; u++) ds.push_back(adj[u].size());
    sort(ds.rbegin(), ds.rend());

    cout << "Degree sequence: [";
    for (int i = 0; i < (int)ds.size(); i++)
        cout << ds[i] << (i + 1 < (int)ds.size() ? ", " : "");
    cout << "]\n";
    return 0;
}
