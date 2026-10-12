/*
============================================================
  Exercise 4 (Challenge): Adjacency Matrix Operations
============================================================
Diberikan graph berarah melalui adjacency matrix n×n.
Lakukan operasi berikut:

1. Hitung in-degree dan out-degree tiap node
2. Cari node "source" (in-degree = 0) dan "sink" (out-degree = 0)
3. Cetak transitive closure: apakah ada path dari u ke v
   (gunakan Floyd-Warshall yang dimodifikasi)
4. Hitung jumlah path panjang tepat 2 dari u ke v
   (menggunakan perkalian matriks)

📏 CONSTRAINTS:
  - 1 ≤ n ≤ 100 (matrix operation!)
  - Nilai matrix: 0 (tidak ada edge) atau 1 (ada edge, unweighted)

📎 SAMPLE INPUT:
  4
  0 1 1 0
  0 0 0 1
  0 1 0 1
  0 0 0 0

📎 SAMPLE OUTPUT:
  === In-degree / Out-degree ===
  Node 1: in=0, out=2  [SOURCE]
  Node 2: in=2, out=1
  Node 3: in=1, out=2
  Node 4: in=2, out=0  [SINK]

  === Transitive Closure (reachable[u][v]=1 jika ada path u→v) ===
  0 1 1 1
  0 0 0 1
  0 1 0 1
  0 0 0 0

  === Path panjang tepat 2 (mat²[u][v]) ===
  0 1 0 2
  0 0 0 0
  0 0 0 1
  0 0 0 0

💡 HINT Transitive Closure:
  - Inisialisasi reach[u][v] = mat[u][v]
  - Floyd-Warshall: reach[i][j] |= (reach[i][k] & reach[k][j])

💡 HINT Path panjang 2:
  - mat²[u][v] = Σ mat[u][k] * mat[k][v] untuk k=1..n
  - Ini adalah perkalian matriks biasa

🎯 Learning Goals:
  Manipulasi adjacency matrix untuk analisis graph lanjutan.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<vector<int>> mat(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> mat[i][j];

    // TODO: hitung in-degree dan out-degree
    // TODO: cetak in/out degree dan tandai source/sink

    cout << "=== In-degree / Out-degree ===\n";

    // TODO: Transitive Closure dengan Floyd-Warshall
    cout << "\n=== Transitive Closure ===\n";

    // TODO: Path panjang tepat 2 (perkalian matriks)
    cout << "\n=== Path panjang tepat 2 ===\n";

    return 0;
}
