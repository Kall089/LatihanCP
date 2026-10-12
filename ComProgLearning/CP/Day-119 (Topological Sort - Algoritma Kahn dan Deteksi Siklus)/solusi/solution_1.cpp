/*
============================================================
✅ Solution 1: Urutan Kuliah (Kahn Dasar)
============================================================
Approach: Kahn / BFS in-degree
Complexity: Time O(N + M) | Space O(N + M)
Key Insight: Simpul dengan in-degree 0 tidak punya prasyarat tersisa, jadi
             aman diambil kapan saja. Mengeluarkannya "membebaskan" tetangga.

📖 ALGORITMANYA:
   1. indeg[v] = banyak edge yang MASUK ke v
   2. antre semua v dengan indeg[v] == 0
   3. pop u -> tulis ke hasil -> untuk tiap tetangga v: --indeg[v],
      kalau jadi 0 push v
   4. ord.size() == n ? valid : IMPOSSIBLE

⚠️ SIMPUL TERISOLASI IKUT. Simpul tanpa edge sama sekali punya indeg 0, jadi
   ia otomatis masuk antrean di langkah 2. Sampel 3 (4 simpul, 0 edge) menguji
   ini: jawabannya 1 2 3 4, bukan baris kosong.

⚠️ ord.size() != n ADALAH SATU-SATUNYA CEK SIKLUS YANG DIBUTUHKAN.
   Jangan menulis DFS 3 warna terpisah. Kalau ada siklus, simpul-simpul di
   dalamnya saling menunggu dan indeg-nya tak pernah turun ke 0.

⚠️ ARAH EDGE. "u prasyarat v" -> g[u].push_back(v) dan indeg[v]++.
   Kalau terbalik, hasilnya persis kebalikan dari yang benar.

VERIFIKASI SAMPEL 1 (n=6, edge 1->3, 2->4, 2->6, 3->5, 4->5):
   indeg = [_,0,0,1,1,2,1]
   antre [1,2]
   pop 1 -> ord=[1], indeg[3]=0 push
   pop 2 -> ord=[1,2], indeg[4]=0 push, indeg[6]=0 push
   pop 3 -> ord=[1,2,3], indeg[5]=1  (belum!)
   pop 4 -> ord=[1,2,3,4], indeg[5]=0 push
   pop 6 -> ord=[1,2,3,4,6]
   pop 5 -> ord=[1,2,3,4,6,5]   size 6 == n  ✓

🔄 ALTERNATIVE APPROACHES:
- DFS post-order lalu reverse: O(N+M) juga, tapi rekursif -> risiko stack
  overflow pada rantai 2*10^5, dan butuh 3 warna untuk deteksi siklus.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main()
{
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);

   int n, m;
   cin >> n >> m;
   vector<vector<int>> g(n + 1);

   vector<int> indeg(n + 1, 0);

   for (int i = 0; i < m; i++)
   {
      int u, v;
      cin >> u >> v;
      g[u].push_back(v);
      indeg[v]++;
   }

   queue<int> q;
   for (int u = 1; u <= n; u++)
      if (indeg[u] == 0)
         q.push(u);

   vector<int> ord;
   ord.reserve(n);
   while (!q.empty())
   {
      int u = q.front();
      q.pop();
      ord.push_back(u);
      for (int v : g[u])
         if (--indeg[v] == 0)
            q.push(v);
   }

   if ((int)ord.size() != n)
   {
      cout << "IMPOSSIBLE\n";
      return 0;
   }
   for (int i = 0; i < n; i++)
      cout << ord[i] << " \n"[i + 1 == n];
   return 0;
}
