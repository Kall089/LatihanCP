/*
 * Day 39 — Priority Queue & Heap Applications
 * File  : solution_6.cpp
 * Topik : Dijkstra's Shortest Path (Priority Queue)
 * -----------------------------------------------
 * Temukan jarak terpendek dari node sumber ke semua node lain menggunakan Dijkstra dengan priority queue.
 *
 * Input format:
 * Baris 1: n m s (nodes, edges, source)
Baris berikutnya: m baris u v w (edge u→v berbobot w)
 *
 * Output format:
 * n baris: jarak dari s ke node 1..n (INF jika tidak terjangkau)
 *
 * Constraints:
 * 1 ≤ n ≤ 10^5, 1 ≤ m ≤ 3×10^5, 1 ≤ w ≤ 10^9
 *
 * Sample Input 1:
 * 5 6 1
 * 1 2 2
 * 1 3 4
 * 2 3 1
 * 2 4 7
 * 3 5 3
 * 4 5 1
 *
 * Sample Output 1:
 * 0
 * 2
 * 3
 * 9
 * 6
 *
 * Sample Input 2:
 * 3 2 1
 * 1 2 5
 * 2 3 3
 *
 * Sample Output 2:
 * 0
 * 5
 * 8
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

const ll INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, s;
    cin >> n >> m >> s;

    vector<vector<pair<int,int>>> adj(n+1);
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<ll> dist(n+1, INF);
    dist[s] = 0;

    // min-heap: (dist, node)
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue; // stale entry
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (dist[i] == INF) cout << "INF\n";
        else cout << dist[i] << "\n";
    }
    return 0;
}
