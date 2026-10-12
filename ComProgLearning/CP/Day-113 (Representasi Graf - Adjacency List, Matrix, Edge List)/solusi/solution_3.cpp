/*
============================================================
  Solution 3: Degree Sequence & Properti Graph Dasar
============================================================
Kompleksitas: O(V + E)
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<int> deg(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        deg[u]++;
        deg[v]++;
    }

    vector<int> ds;
    for (int u = 1; u <= n; u++) ds.push_back(deg[u]);
    sort(ds.rbegin(), ds.rend());

    cout << "Degree sequence: [";
    for (int i = 0; i < (int)ds.size(); i++)
        cout << ds[i] << (i + 1 < (int)ds.size() ? ", " : "");
    cout << "]\n";

    int total = 0;
    for (int d : ds) total += d;
    cout << "Total edge: " << total / 2 << "\n";

    vector<int> isolated;
    for (int u = 1; u <= n; u++) if (deg[u] == 0) isolated.push_back(u);
    cout << "Node terisolasi: ";
    if (isolated.empty()) cout << "(tidak ada)\n";
    else { for (int x : isolated) cout << x << " "; cout << "\n"; }

    int odd_count = 0;
    for (int d : ds) if (d % 2 != 0) odd_count++;

    cout << "Euler Circuit: " << (odd_count == 0 ? "MUNGKIN ADA" : "TIDAK") << "\n";
    cout << "Euler Path: " << (odd_count == 2 ? "MUNGKIN ADA" : "TIDAK") << "\n";
    return 0;
}
