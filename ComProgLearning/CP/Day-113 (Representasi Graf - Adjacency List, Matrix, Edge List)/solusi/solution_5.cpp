/*
============================================================
  Solution 5: Edge List + Kruskal MST Preview
============================================================
Kompleksitas: O(E log E) sort + O(E α(V)) DSU operations.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<tuple<int,int,int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        edges.push_back({w, u, v});
    }
    sort(edges.begin(), edges.end());

    cout << "=== Edge List (sorted by weight) ===\n";
    for (auto [w, u, v] : edges)
        cout << u << " - " << v << " (w=" << w << ")\n";

    auto [wmin, umin, vmin] = edges.front();
    auto [wmax, umax, vmax] = edges.back();
    cout << "\nMin weight edge: " << umin << "-" << vmin << " (w=" << wmin << ")\n";
    cout << "Max weight edge: " << umax << "-" << vmax << " (w=" << wmax << ")\n";

    cout << "\n=== Kruskal MST ===\n";
    vector<int> parent(n + 1);
    iota(parent.begin(), parent.end(), 0);

    function<int(int)> find = [&](int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    };
    auto unite = [&](int u, int v) -> bool {
        u = find(u); v = find(v);
        if (u == v) return false;
        parent[u] = v;
        return true;
    };

    int mst_cost = 0, cnt = 0;
    for (auto [w, u, v] : edges) {
        if (unite(u, v)) {
            cout << "Tambah edge " << u << "-" << v << " (w=" << w << ") ✓\n";
            mst_cost += w;
            if (++cnt == n - 1) break;
        } else {
            cout << "Skip edge " << u << "-" << v << " (w=" << w << ") — cycle!\n";
        }
    }
    cout << "MST Cost: " << mst_cost << "\n";
    return 0;
}
