/*
============================================================
  Exercise 2: Konversi Antar Representasi Graph
============================================================
Diberikan graph berarah berbobot dengan n node dan m edge.
Lakukan konversi dari Adjacency List ke:
  a) Adjacency Matrix
  b) Edge List (diurutkan berdasarkan weight, lalu u, lalu v)

Untuk setiap representasi, cetak hasilnya.

📏 CONSTRAINTS:
  - 1 ≤ n ≤ 500  (karena adjacency matrix O(n²))
  - 0 ≤ m ≤ 10^4
  - 1 ≤ weight ≤ 10^6

📎 SAMPLE INPUT:
  4 5
  1 2 3
  1 3 7
  2 4 2
  3 2 1
  3 4 5

📎 SAMPLE OUTPUT:
  === Adjacency Matrix ===
  0 3 7 0
  0 0 0 2
  0 1 0 5
  0 0 0 0

  === Edge List (sorted) ===
  3 4 (w=2)
  3 2 (w=1)
  1 2 (w=3)
  3 4 (w=5)
  1 3 (w=7)

  (Sebenarnya sort berdasarkan weight: 1,2,3,5,7)
  Edge (3,2,w=1), (2,4,w=2), (1,2,w=3), (3,4,w=5), (1,3,w=7)

💡 HINT:
  - Adj list → matrix: untuk tiap edge (u,v,w) set mat[u][v] = w
  - Adj list → edge list: kumpulkan {w,u,v} lalu sort
  - Untuk matrix: 0 berarti tidak ada edge (graph unweighted pakai 0/1)
  - Untuk directed graph, JANGAN tambah sisi balik

🎯 Learning Goals:
  Memahami konversi antar 3 representasi graph.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    // Baca ke adjacency list dulu
    vector<vector<pair<int,int>>> adj(n + 1);  // adj[u] = {(v, w)}
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        // TODO: tambah ke adj list (directed)
    }

    // ── Konversi ke Adjacency Matrix ───────────────────────────
    cout << "=== Adjacency Matrix ===\n";
    vector<vector<int>> mat(n + 1, vector<int>(n + 1, 0));

    // TODO: isi matrix dari adj list

    // TODO: cetak matrix (baris 1..n, kolom 1..n)

    cout << "\n";

    // ── Konversi ke Edge List ───────────────────────────────────
    cout << "=== Edge List (sorted by weight) ===\n";
    vector<tuple<int,int,int>> edges;  // {w, u, v}

    // TODO: kumpulkan semua edge dari adj list ke edge list
    // TODO: sort berdasarkan weight
    // TODO: cetak dalam format "u v (w=X)"

    return 0;
}
