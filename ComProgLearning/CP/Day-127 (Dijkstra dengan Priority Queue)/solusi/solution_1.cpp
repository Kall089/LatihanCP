/*
============================================================
✅ Solution 1: Jarak Terpendek dari Simpul 1
============================================================
Approach: Dijkstra dengan min-heap + lazy deletion
Complexity: Time O(E log V) | Space O(V + E)
Key Insight: Simpul dengan jarak sementara terkecil sudah pasti final --
             karena bobot non-negatif berarti jalur mana pun yang keluar dari
             himpunan final harus melewati simpul lain yang jaraknya lebih
             kecil, dan simpul itu akan dipop lebih dulu.

📖 ALGORITMANYA:
   dist[1] = 0, sisanya INF; push (0,1)
   while heap: pop (d,u)
       if (d > dist[u]) continue;          <- entri usang, buang
       for (v,w) in g[u]:
           if (d + w < dist[v]) { dist[v] = d + w; push (dist[v], v); }

⚠️ long long WAJIB. Sampel 3 menguji ini: 2 * 10^9 sudah melewati int.
   Pada graf sungguhan, 2*10^5 edge * 10^9 = 2*10^14.

⚠️ INF = LLONG_MAX / 4, BUKAN LLONG_MAX.
   Kalau INF = LLONG_MAX, ekspresi d + w akan OVERFLOW (undefined behavior).
   Membaginya 4 memberi ruang yang cukup untuk penjumlahan apa pun.

⚠️ priority_queue DEFAULT ADALAH MAX-HEAP.
   Wajib: priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>>.
   Lupa greater<> menghasilkan angka yang sekilas masuk akal tapi salah.

⚠️ "if (d > dist[u]) continue;" -- LAZY DELETION.
   std::priority_queue tidak punya decrease-key, jadi kita push entri baru dan
   membiarkan yang lama jadi sampah. Menghapus baris ini TIDAK membuat jawaban
   salah, tapi membuat simpul diproses berulang kali -> TLE pada graf besar.

⚠️ URUTAN PASANGAN: (jarak, simpul), bukan (simpul, jarak). Perbandingan
   default pair mengurutkan berdasarkan elemen pertama.

VERIFIKASI SAMPEL 1 (1->2:6, 1->3:2, 3->2:3, 2->4:1, 3->4:5):
   pop (0,1): dist[2]=6, dist[3]=2
   pop (2,3): dist[2]=min(6, 2+3)=5 push; dist[4]=2+5=7 push
   pop (5,2): dist[4]=min(7, 5+1)=6 push
   pop (6,4): tidak ada tetangga
   pop (7,4): 7 > dist[4]=6 -> SKIP
   hasil 0 5 2 6  ✓

🔄 ALTERNATIVE APPROACHES:
- Dijkstra O(V^2) tanpa heap: lebih baik kalau E ~ V^2 (graf sangat padat).
- set<pair<ll,int>> dengan erase manual: mensimulasikan decrease-key, heap
  tetap berukuran O(V), tapi konstantanya lebih besar.
- Bobot hanya 0/1 -> BFS 0-1 dengan deque, O(V+E), jauh lebih cepat.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,int> pli;
const ll INF = LLONG_MAX / 4;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,ll>>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v; ll w; cin >> u >> v >> w;
        g[u].push_back({v, w});
    }

    vector<ll> dist(n + 1, INF);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dist[1] = 0; pq.push({0, 1});
    while (!pq.empty()) {
        pli t = pq.top(); pq.pop();
        ll d = t.first; int u = t.second;
        if (d > dist[u]) continue;
        for (auto& e : g[u]) {
            int v = e.first; ll w = e.second;
            if (d + w < dist[v]) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }

    for (int v = 1; v <= n; v++)
        cout << (dist[v] >= INF ? -1 : dist[v]) << " \n"[v == n];
    return 0;
}
