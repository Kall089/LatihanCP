/*
============================================================
  Exercise 5 (Challenge): Edge List + Minimum Spanning Tree Preview
============================================================
Diberikan graph tidak berarah berbobot. Gunakan Edge List untuk:
1. Cetak semua edge diurutkan berdasarkan weight
2. Cari edge dengan weight minimum dan maksimum
3. Simulasi langkah-langkah Kruskal MST:
   - Tambahkan edge dengan weight terkecil yang tidak membentuk cycle
   - Gunakan Union-Find (DSU) sederhana untuk deteksi cycle
4. Cetak total cost MST dan edge-edge yang dipilih

📏 CONSTRAINTS:
  - 1 ≤ n ≤ 1000
  - 1 ≤ m ≤ 10^4
  - 1 ≤ weight ≤ 10^6

📎 SAMPLE INPUT:
  4 5
  1 2 4
  1 3 2
  2 3 1
  2 4 5
  3 4 3

📎 SAMPLE OUTPUT:
  === Edge List (sorted by weight) ===
  2 - 3 (w=1)
  1 - 3 (w=2)
  3 - 4 (w=3)
  1 - 2 (w=4)
  2 - 4 (w=5)

  Min weight edge: 2-3 (w=1)
  Max weight edge: 2-4 (w=5)

  === Kruskal MST ===
  Tambah edge 2-3 (w=1) ✓
  Tambah edge 1-3 (w=2) ✓
  Tambah edge 3-4 (w=3) ✓
  Skip edge 1-2 (w=4) — cycle!
  Skip edge 2-4 (w=5) — cycle!
  MST Cost: 6

💡 HINT — DSU (Union-Find) sederhana:
  vector<int> parent(n+1);
  iota(parent.begin(), parent.end(), 0);  // parent[i] = i

  function<int(int)> find = [&](int x) {
      return parent[x] == x ? x : parent[x] = find(parent[x]);
  };

  auto unite = [&](int u, int v) -> bool {
      u = find(u); v = find(v);
      if (u == v) return false;  // sudah sama komponen (cycle)
      parent[u] = v;
      return true;
  };

🎯 Learning Goals:
  Memahami Edge List dan penggunaannya dalam Kruskal MST.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    // TODO: baca edge ke dalam edge list {w, u, v}
    vector<tuple<int,int,int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        // TODO
    }

    // TODO: sort edge list by weight

    // TODO: cetak edge list sorted
    cout << "=== Edge List (sorted by weight) ===\n";

    // TODO: min dan max weight edge

    // TODO: Kruskal MST dengan DSU
    cout << "\n=== Kruskal MST ===\n";

    // DSU
    vector<int> parent(n + 1);
    iota(parent.begin(), parent.end(), 0);

    function<int(int)> find = [&](int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    };

    auto unite = [&](int u, int v) -> bool {
        u = find(u); v = find(v);
        if (u == v) return false;
        parent[u] = v;
        return true;
    };

    int mst_cost = 0;
    for (auto [w, u, v] : edges) {
        // TODO: coba tambah edge, cek cycle dengan DSU
    }

    // TODO: cetak MST Cost

    return 0;
}
