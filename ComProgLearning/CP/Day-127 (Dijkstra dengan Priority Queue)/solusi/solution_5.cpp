/*
============================================================
✅ Solution 5: Minimax — Edge Termahal Seminimal Mungkin
============================================================
Approach: Dijkstra dengan operator gabung diganti
Complexity: Time O(E log V) | Space O(V + E)
Key Insight: Dijkstra tidak khusus untuk PENJUMLAHAN. Ia bekerja untuk operator
             gabung APA PUN yang MONOTON, yaitu tidak pernah membuat nilai
             mengecil: gabung(a, w) >= a. Untuk penjumlahan, itu berarti
             w >= 0. Untuk max, max(a, w) >= a SELALU benar -- tanpa syarat
             apa pun pada w.

📖 SATU-SATUNYA PERUBAHAN:
       nd = dist[u] + w        ->        nd = max(dist[u], w)
   Sisanya identik. Bukti kebenarannya juga identik: prefiks jalur tidak
   pernah punya nilai lebih besar daripada seluruh jalur, karena max hanya
   bisa naik.

⚠️ dist[1] = 0, BUKAN INF DAN BUKAN bobot apa pun.
   Artinya "jalur kosong punya edge termahal 0". Kalau bobot boleh negatif,
   inisialisasinya harus -INF, bukan 0.

⚠️ JANGAN TERJEBAK MENJUMLAHKAN. Soal semacam ini ("ketinggian maksimum",
   "beban jembatan terberat", "usaha terbesar") sering terbaca seperti soal
   jarak biasa. Baca ulang definisi BIAYA JALUR-nya.

VERIFIKASI SAMPEL 1 (tak berarah: 1-2:10, 2-4:10, 1-3:3, 3-4:8):
   pop (0,1) : dist[2]=max(0,10)=10 ; dist[3]=max(0,3)=3
   pop (3,3) : dist[4]=max(3,8)=8   ; dist[1] tidak membaik
   pop (8,4) : dist[2]=min(10, max(8,10))=10, tidak membaik
   pop (10,2): selesai
   dist[4] = 8  ✓  (lewat 1-3-4; jalur 1-2-4 memberi 10)

🔄 ALTERNATIVE APPROACHES:
- BINARY SEARCH ON ANSWER (Day 50): tebak ambang X, buang semua edge > X,
  cek konektivitas dengan BFS/DFS. O((V+E) log maxW). Sering lebih mudah
  dipikirkan, dan berguna kalau bentuk soalnya "apakah mungkin dengan
  ambang X".
- MINIMUM SPANNING TREE (Day 135-137): jalur minimax antara dua simpul mana
  pun pada graf TAK BERARAH selalu terletak di dalam MST. Bangun MST dengan
  Kruskal, lalu jalannya tinggal ditelusuri. Ini fakta yang sangat berguna.
- DSU dengan menambahkan edge dari yang terkecil sampai 1 dan N terhubung --
  jawabannya adalah bobot edge terakhir yang ditambahkan. O(E log E).

VARIAN KEBALIKAN (MAXIMIN / bottleneck terlebar):
  pakai MAX-heap dan nd = min(dist[u], w). Contohnya "kapasitas truk terbesar
  yang bisa lewat".
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
        int u, v; ll h; cin >> u >> v >> h;
        g[u].push_back({v, h});
        g[v].push_back({u, h});            // TAK BERARAH
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
            ll nd = max(d, w);                    // <-- satu-satunya perubahan
            if (nd < dist[v]) {
                dist[v] = nd;
                pq.push({nd, v});
            }
        }
    }

    cout << (dist[n] >= INF ? -1 : dist[n]) << '\n';
    return 0;
}
