/*
============================================================
✅ Solution 3: Urutan Topologis Leksikografis Terkecil
============================================================
Approach: Kahn dengan min-heap menggantikan queue
Complexity: Time O((N + M) log N) | Space O(N + M)
Key Insight: Pada setiap langkah, HIMPUNAN simpul yang boleh diambil adalah
             semua yang indeg-nya 0. Greedy: ambil yang bernomor terkecil.
             Ini optimal karena memilih yang terkecil di posisi paling depan
             selalu memperbaiki (atau menyamai) urutan leksikografis, dan tidak
             pernah menutup pilihan -- simpul lain yang tadi siap TETAP siap.

⚠️ KESALAHAN NOMOR SATU: menjalankan Kahn biasa lalu sort(ord).
   Hasil sort BUKAN urutan topologis sama sekali. Contoh sampel 2:
   Kahn biasa bisa memberi [3,4,1,2]; men-sort-nya jadi [1,2,3,4] yang
   melanggar edge 4->1 dan 3->2. Pemilihan harus terjadi DI DALAM proses.

⚠️ priority_queue DEFAULT ADALAH MAX-HEAP.
   Wajib: priority_queue<int, vector<int>, greater<int>>.
   Lupa greater<int> memberi urutan leksikografis TERBESAR -- bug senyap.

⚠️ Cek siklus tetap sama: ord.size() != n -> IMPOSSIBLE.

VERIFIKASI SAMPEL 2 (n=4, edge 4->1, 3->2):
   indeg = [_,1,1,0,0]
   heap {3,4}
   top 3 -> ord=[3], indeg[2]=0 push -> heap {2,4}
   top 2 -> ord=[3,2]                 -> heap {4}
   top 4 -> ord=[3,2,4], indeg[1]=0   -> heap {1}
   top 1 -> ord=[3,2,4,1]  ✓
   Perhatikan 3 harus di depan karena 1 dan 2 masih terkunci.

🔄 ALTERNATIVE APPROACHES:
- Untuk leksikografis TERBESAR: pakai max-heap (priority_queue default).
- Untuk "urutan terkecil dari BELAKANG", balik semua edge, cari leksikografis
  terbesar, lalu reverse hasilnya -- ini soal yang berbeda dan sering tertukar.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    vector<int> indeg(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        indeg[v]++;
    }

    priority_queue<int, vector<int>, greater<int>> q;   // MIN-heap
    for (int u = 1; u <= n; u++) if (indeg[u] == 0) q.push(u);

    vector<int> ord;
    ord.reserve(n);
    while (!q.empty()) {
        int u = q.top(); q.pop();
        ord.push_back(u);
        for (int v : g[u]) if (--indeg[v] == 0) q.push(v);
    }

    if ((int)ord.size() != n) { cout << "IMPOSSIBLE\n"; return 0; }
    for (int i = 0; i < n; i++) cout << ord[i] << " \n"[i + 1 == n];
    return 0;
}
