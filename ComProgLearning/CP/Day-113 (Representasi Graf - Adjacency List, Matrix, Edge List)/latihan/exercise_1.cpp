/*
============================================================
  Exercise 1: Baca & Print Adjacency List
============================================================
Diberikan graph tidak berarah dan tidak berbobot dengan n node
dan m edge. Bangun adjacency list lalu cetak:
1. Daftar tetangga setiap node (diurutkan ascending)
2. Degree setiap node
3. Node dengan degree tertinggi
4. Jumlah total edge

📏 CONSTRAINTS:
  - 1 ≤ n ≤ 10^5
  - 0 ≤ m ≤ 2×10^5
  - Node 1-indexed

📎 SAMPLE INPUT:
  5 6
  1 2
  1 3
  2 3
  2 4
  3 5
  4 5

📎 SAMPLE OUTPUT:
  === Adjacency List ===
  1: 2 3
  2: 1 3 4
  3: 1 2 5
  4: 2 5
  5: 3 4
  === Degree ===
  deg(1) = 2
  deg(2) = 3
  deg(3) = 3
  deg(4) = 2
  deg(5) = 2
  Node dengan degree tertinggi: 2 (deg=3)
  Total edge: 6

💡 HINT:
  - Setelah baca semua edge, sort tiap adj[u] agar output terurut
  - Degree(u) = adj[u].size()
  - Total edge = sum degree / 2 (karena tiap edge dihitung 2x)

🎯 Learning Goals:
  Bisa baca input graph dan bangun adjacency list dengan benar.
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

  for (int i = 1; i <= n; i++)
  {
    sort(adj[i].begin(), adj[i].end());
  }

  for (int i = 1; i <= n; i++)
  {
    cout << i << ": ";
    for (int v : adj[i])
    {
      cout << v << " ";
    }
    cout << endl;
  }

  return 0;
}
