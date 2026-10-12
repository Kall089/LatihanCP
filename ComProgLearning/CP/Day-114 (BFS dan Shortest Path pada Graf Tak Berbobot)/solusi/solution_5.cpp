/*
============================================================
  Solution 5: BFS Level-Order Tree Traversal
============================================================
Kompleksitas: O(V + E) = O(V) pada tree (E = V - 1)

Cara kerja:
- BFS dari root = 1
- Tiap iterasi luar: catat q.size() (jumlah node level ini)
- Proses tepat q.size() node → satu level selesai
- Semua node yang di-push dalam satu iterasi = level berikutnya
*/
#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> depth(n + 1, -1);
    vector<vector<int>> levels;
    queue<int> q;

    depth[1] = 0;
    q.push(1);

    while (!q.empty()) {
        int sz = q.size();
        vector<int> cur_level;

        for (int i = 0; i < sz; i++) {
            int u = q.front(); q.pop();
            cur_level.push_back(u);

            for (int v : adj[u]) {
                if (depth[v] == -1) {
                    depth[v] = depth[u] + 1;
                    q.push(v);
                }
            }
        }
        levels.push_back(cur_level);
    }

    cout << "=== Level-Order Traversal ===\n";
    for (int lv = 0; lv < (int)levels.size(); lv++) {
        cout << "Level " << lv << ": ";
        for (int i = 0; i < (int)levels[lv].size(); i++)
            cout << levels[lv][i] << (i + 1 < (int)levels[lv].size() ? " " : "\n");
    }

    cout << "=== Kedalaman Setiap Node ===\n";
    for (int u = 1; u <= n; u++)
        cout << "depth(" << u << ") = " << depth[u] << "\n";

    int maxDepth = 0, deepNode = 1;
    for (int u = 1; u <= n; u++)
        if (depth[u] > maxDepth) { maxDepth = depth[u]; deepNode = u; }

    cout << "Node terdalam: " << deepNode
         << " (depth=" << maxDepth << ")\n";

    return 0;
}
