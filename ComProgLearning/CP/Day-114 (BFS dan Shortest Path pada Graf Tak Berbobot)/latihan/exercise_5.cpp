/*
============================================================
  Exercise 5: BFS Level-Order Tree Traversal
============================================================
Diberikan sebuah tree berakar di node 1 dengan n node.
Input berupa daftar edge (tidak berarah, node 1-indexed).
Lakukan BFS level-order traversal dari root (node 1) dan:
1. Cetak semua node yang ada di setiap level
2. Cetak kedalaman (depth) dari setiap node
3. Cetak node yang berada paling dalam (depth terbesar)

📏 CONSTRAINTS:
  - 1 ≤ n ≤ 10^5
  - Dijamin input adalah tree (connected, n-1 edge, tanpa cycle)
  - Root = node 1

📎 SAMPLE INPUT:
  7
  1 2
  1 3
  2 4
  2 5
  3 6
  3 7

📎 SAMPLE OUTPUT:
  === Level-Order Traversal ===
  Level 0: 1
  Level 1: 2 3
  Level 2: 4 5 6 7
  === Kedalaman Setiap Node ===
  depth(1) = 0
  depth(2) = 1
  depth(3) = 1
  depth(4) = 2
  depth(5) = 2
  depth(6) = 2
  depth(7) = 2
  Node terdalam: 4 (depth=2)

💡 HINT:
  - Untuk level-order: catat q.size() sebelum loop dalam
  - Proses q.size() node sekaligus → satu level selesai
  - dist[] berfungsi sebagai depth[]
  - Node terdalam = node dengan dist[] maksimum

🎯 Learning Goals:
  BFS secara natural menghasilkan level-order traversal.
  Teknik "catat ukuran queue" memisahkan level dengan bersih.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    // TODO: deklarasi adjacency list
    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        // TODO: tambah edge undirected
    }

    // TODO: BFS level-order dari root = 1
    vector<int> depth(n + 1, -1);
    vector<vector<int>> levels;  // levels[i] = daftar node di level i
    queue<int> q;

    // TODO: inisialisasi BFS

    // TODO: loop BFS dengan pemisahan level
    // while (!q.empty()) {
    //     int sz = q.size();  // jumlah node di level ini
    //     vector<int> cur_level;
    //     for (int i = 0; i < sz; i++) {
    //         // proses node, tambah ke cur_level
    //     }
    //     levels.push_back(cur_level);
    // }

    // Cetak level-order
    cout << "=== Level-Order Traversal ===\n";
    // TODO: cetak tiap level

    // Cetak kedalaman
    cout << "=== Kedalaman Setiap Node ===\n";
    // TODO: cetak depth[1..n]

    // Cetak node terdalam
    // TODO: cari node dengan depth maksimum
    // cetak: "Node terdalam: X (depth=D)"

    return 0;
}
