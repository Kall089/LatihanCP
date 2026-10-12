/*
============================================================
📋 TUGAS 03: Neighbor Lookup dengan Query
============================================================
Source: Original
Difficulty: Easy
Topics: adjacency list, unordered_set, O(1) query

PROBLEM:
Diberikan graph tidak berarah dengan n node dan m edge, lalu q query.
Tiap query berupa dua integer u v: apakah u dan v bertetangga
(ada edge langsung antara u dan v)?

INPUT FORMAT:
- Baris 1: tiga integer n, m, q
- m baris berikutnya: dua integer u v (edge)
- q baris berikutnya: dua integer u v (query)

OUTPUT FORMAT:
- q baris: "YES" atau "NO" untuk setiap query

CONSTRAINTS:
- 1 ≤ n, m ≤ 10^5
- 1 ≤ q ≤ 10^5
- 1 ≤ u, v ≤ n

SAMPLE INPUT 1:
4 4 3
1 2
2 3
3 4
1 4
1 3
2 4
1 2

SAMPLE OUTPUT 1:
NO
NO
YES

SAMPLE INPUT 2:
3 3 4
1 2
2 3
1 3
1 2
1 3
2 3
1 1

SAMPLE OUTPUT 2:
YES
YES
YES
NO

NOTE: Gunakan vector<unordered_set<int>> untuk O(1) average per query.
      Untuk undirected: simpan adj[u].insert(v) dan adj[v].insert(u).
      Query: cek adj[u].count(v) > 0.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, q;
    cin >> n >> m >> q;

    vector<unordered_set<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].insert(v);
        adj[v].insert(u);  // undirected
    }

    while (q--) {
        int u, v;
        cin >> u >> v;
        // O(1) average lookup
        cout << (adj[u].count(v) ? "YES" : "NO") << '\n';
    }
    return 0;
}
