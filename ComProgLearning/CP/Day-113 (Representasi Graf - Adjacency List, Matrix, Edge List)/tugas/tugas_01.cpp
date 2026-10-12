/*
============================================================
📋 TUGAS 01: Bangun Adjacency List & Analisis Degree
============================================================
Source: Original
Difficulty: Easy
Topics: adjacency list, degree, undirected graph

PROBLEM:
Diberikan sebuah graph tidak berarah (undirected) dengan n node
dan m edge. Bangun adjacency list-nya, kemudian cetak:
1. Adjacency list setiap node (tetangga diurutkan menaik)
2. Degree (jumlah tetangga) setiap node
3. Node dengan degree terbesar (jika seri, cetak yang terkecil)

INPUT FORMAT:
- Baris 1: dua integer n dan m
- m baris berikutnya: dua integer u dan v (edge u-v, undirected)

OUTPUT FORMAT:
- n baris adjacency list: "u: v1 v2 ..."
- n baris degree: "degree(u) = d"
- Satu baris: "Max degree: node u dengan degree d"

CONSTRAINTS:
- 1 ≤ n ≤ 10^5
- 0 ≤ m ≤ 2×10^5
- 1 ≤ u, v ≤ n, u ≠ v
- Tidak ada self-loop, bisa ada multiple edge

SAMPLE INPUT 1:
5 6
1 2
1 3
2 4
2 5
3 4
4 5

SAMPLE OUTPUT 1:
1: 2 3
2: 1 4 5
3: 1 4
4: 2 3 5
5: 2 4
degree(1) = 2
degree(2) = 3
degree(3) = 2
degree(4) = 3
degree(5) = 2
Max degree: node 2 dengan degree 3

SAMPLE INPUT 2:
4 0

SAMPLE OUTPUT 2:
1:
2:
3:
4:
degree(1) = 0
degree(2) = 0
degree(3) = 0
degree(4) = 0
Max degree: node 1 dengan degree 0

NOTE: Graph dengan 0 edge tetap valid.
      Jika ada multiple edge antara u dan v, keduanya dihitung.
      Adjacency list diurutkan menaik agar output deterministik.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Sort each adjacency list
    for (int i = 1; i <= n; i++) sort(adj[i].begin(), adj[i].end());

    // Print adjacency list
    for (int i = 1; i <= n; i++) {
        cout << i << ":";
        for (int v : adj[i]) cout << ' ' << v;
        cout << '\n';
    }

    // Print degree per node
    int maxDeg = 0, maxNode = 1;
    for (int i = 1; i <= n; i++) {
        int deg = (int)adj[i].size();
        cout << "degree(" << i << ") = " << deg << '\n';
        if (deg > maxDeg) { maxDeg = deg; maxNode = i; }
    }

    cout << "Max degree: node " << maxNode << " dengan degree " << maxDeg << '\n';
    return 0;
}
