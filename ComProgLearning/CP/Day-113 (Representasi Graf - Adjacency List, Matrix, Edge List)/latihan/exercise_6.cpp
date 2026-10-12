/*
============================================================
  Exercise 6 (Contest-level): Multi-format Graph Input
============================================================
Program ini harus bisa membaca graph dalam 3 format berbeda,
kemudian untuk setiap format cetak informasi yang sama:
- Jumlah node, jumlah edge
- Adjacency list (sorted)
- Degree sequence

Format input ditentukan oleh baris pertama:
  "LIST"   → n m, lalu m baris "u v w"
  "MATRIX" → n, lalu n baris berisi n angka (adjacency matrix)
  "EDGES"  → n m, lalu m baris "u v w"

Setelah membaca, konversi semua ke adjacency list dan cetak output standar.

📏 CONSTRAINTS:
  - n ≤ 500 (untuk MATRIX format)
  - m ≤ 10^4
  - weight: 1..10^6

📎 SAMPLE INPUT 1 (LIST format):
  LIST
  4 4
  1 2 3
  1 3 5
  2 4 2
  3 4 1

📎 SAMPLE INPUT 2 (MATRIX format):
  MATRIX
  3
  0 5 0
  5 0 3
  0 3 0

📎 SAMPLE OUTPUT (untuk keduanya, format sama):
  Nodes: 4, Edges: 4
  Adjacency List:
  1: (2,3) (3,5)
  2: (1,3) (4,2)
  3: (1,5) (4,1)
  4: (2,2) (3,1)
  Degree sequence: [2, 2, 2, 2]

💡 HINT:
  - Baca format sebagai string, lalu pilih cara parsing yang sesuai
  - Untuk MATRIX: mat[i][j] > 0 berarti ada edge dengan weight mat[i][j]
  - Setelah parsing, semua dikonversi ke adjacency list yang sama
  - Undirected: tambah dua arah

🎯 Learning Goals:
  Bisa handle berbagai format input graph yang sering muncul di soal CP.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string format;
    cin >> format;

    int n = 0, m = 0;
    vector<vector<pair<int,int>>> adj;  // adj[u] = {(v, w)}

    if (format == "LIST") {
        cin >> n >> m;
        adj.assign(n + 1, {});
        for (int i = 0; i < m; i++) {
            int u, v, w; cin >> u >> v >> w;
            // TODO: tambah edge undirected
        }
        // TODO: hitung m dari adj list

    } else if (format == "MATRIX") {
        cin >> n;
        adj.assign(n + 1, {});
        // TODO: baca n×n matrix, tambahkan edge ke adj list (undirected)
        // jika mat[i][j] > 0 dan i < j (untuk undirected tanpa duplikat)

    } else if (format == "EDGES") {
        cin >> n >> m;
        adj.assign(n + 1, {});
        // TODO: sama seperti LIST
    }

    // Sort tiap adj[u] dan hitung m
    m = 0;
    for (int u = 1; u <= n; u++) {
        sort(adj[u].begin(), adj[u].end());
        m += adj[u].size();
    }
    m /= 2;  // setiap edge dihitung 2x untuk undirected

    // TODO: cetak output standar
    cout << "Nodes: " << n << ", Edges: " << m << "\n";
    cout << "Adjacency List:\n";
    // TODO

    cout << "Degree sequence: [";
    // TODO: cetak degree sequence descending
    cout << "]\n";

    return 0;
}
