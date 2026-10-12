/*
============================================================
  Solution 1: Baca & Print Adjacency List
============================================================
Kompleksitas: O((V + E) log V) — sort tetangga tiap node.
*/
#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

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

    for (int u = 1; u <= n; u++)
        sort(adj[u].begin(), adj[u].end());

    cout << "=== Adjacency List ===\n";
    for (int u = 1; u <= n; u++)
    {
        cout << u << ":";
        for (int v : adj[u])
            cout << " " << v;
        cout << "\n";
    }

    cout << "=== Degree ===\n";
    int maxDeg = 0, maxNode = 1;
    for (int u = 1; u <= n; u++)
    {
        int d = adj[u].size();
        cout << "deg(" << u << ") = " << d << "\n";
        if (d > maxDeg)
        {
            maxDeg = d;
            maxNode = u;
        }
    }

    cout << "Node dengan degree tertinggi: " << maxNode << " (deg=" << maxDeg << ")\n";
    cout << "Total edge: " << m << "\n";
    return 0;
}
