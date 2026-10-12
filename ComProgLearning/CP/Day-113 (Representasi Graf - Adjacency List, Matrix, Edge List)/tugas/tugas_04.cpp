/*
============================================================
📋 TUGAS 04: Graph Complement
============================================================
Source: Original
Difficulty: Easy
Topics: adjacency matrix, complement graph, set operations

PROBLEM:
Diberikan simple graph tidak berarah dengan n node dan m edge.
Cetak adjacency list dari graph komplemen-nya: graph yang memiliki edge
(u,v) jika dan hanya jika edge (u,v) TIDAK ADA di graph asal (u ≠ v).

INPUT FORMAT:
- Baris 1: dua integer n dan m
- m baris berikutnya: dua integer u v (edge, 1-indexed)

OUTPUT FORMAT:
- n baris: "X: a b c ..." (tetangga di komplemen, sorted ascending)
  Jika tidak ada tetangga, cetak "X: (kosong)"

CONSTRAINTS:
- 2 ≤ n ≤ 1000
- 0 ≤ m ≤ n*(n-1)/2

SAMPLE INPUT 1:
4 3
1 2
2 3
3 4

SAMPLE OUTPUT 1:
1: 3 4
2: 4
3: 1
4: 1 2

SAMPLE INPUT 2:
3 3
1 2
2 3
1 3

SAMPLE OUTPUT 2:
1: (kosong)
2: (kosong)
3: (kosong)

NOTE: Sample 2 adalah complete graph K3 → komplementnya kosong.
      Cara: gunakan adjacency matrix (bool adj[n+1][n+1]).
      Untuk tiap pasang (u,v) dengan u≠v, edge di komplemen jika !adj[u][v].
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;

    // Adjacency matrix for small n (n <= 1000)
    vector<vector<bool>> adj(n + 1, vector<bool>(n + 1, false));
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u][v] = adj[v][u] = true;
    }

    // Build complement adjacency list
    for (int u = 1; u <= n; u++) {
        vector<int> comp_neighbors;
        for (int v = 1; v <= n; v++) {
            if (v != u && !adj[u][v]) comp_neighbors.push_back(v);
        }
        cout << u << ": ";
        if (comp_neighbors.empty()) cout << "(kosong)";
        else for (int i = 0; i < (int)comp_neighbors.size(); i++) {
            if (i) cout << ' ';
            cout << comp_neighbors[i];
        }
        cout << '\n';
    }
    return 0;
}
