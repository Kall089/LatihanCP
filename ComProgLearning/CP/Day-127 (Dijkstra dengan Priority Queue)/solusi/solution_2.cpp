/*
============================================================
✅ Solution 2: Rekonstruksi Rute Terpendek
============================================================
Approach: Dijkstra + array parent, telusuri balik
Complexity: Time O(E log V) | Space O(V + E)
Key Insight: Dijkstra menghitung NILAI; par[] menyimpan KEPUTUSAN. Setiap kali
             dist[v] benar-benar membaik, edge penyebabnya adalah edge terakhir
             pada jalur terpendek ke v saat ini. Kumpulan seluruh edge par[v]->v
             membentuk SHORTEST PATH TREE.

📖 ALGORITMANYA:
   if (d + w < dist[v]) { dist[v] = d + w; par[v] = u; push; }
   lalu: v = N; while (v) { path.push(v); if (v==1) break; v = par[v]; } reverse.

⚠️ GRAF TAK BERARAH -> PUSH KEDUA ARAH saat membaca input.
   Ini kesalahan yang sangat sering terjadi dan gejalanya "jawaban -1 padahal
   jelas ada jalur".

⚠️ par[v] HARUS DI DALAM if. Kalau di luar, ia menyimpan pengirim terakhir yang
   DILIHAT, bukan yang TERBAIK -- jaraknya benar tapi jalurnya salah.

⚠️ CEK dist[N] SEBELUM MENELUSURI. Kalau masih INF, par[N] = 0 dan loop
   penelusuran menghasilkan sampah atau berputar.

⚠️ SERI DIPERBOLEHKAN. Kalau ada dua jalur terpendek yang sama panjang, jalur
   mana pun benar. Jangan membandingkan output dengan satu string tetap.

VERIFIKASI SAMPEL 1 (tak berarah):
   pop (0,1): dist[2]=2 par=1 ; dist[4]=1 par=1
   pop (1,4): dist[3]=1+3=4 par=4
   pop (2,2): dist[3]=min(4, 2+4)=4 tidak membaik ; dist[5]=2+5=7 par=2
   pop (4,3): dist[5]=min(7, 4+1)=5 par=3
   pop (5,5): selesai
   telusuri 5 -> 3 -> 4 -> 1  =>  1 4 3 5, jarak 5  ✓

🔄 ALTERNATIVE APPROACHES:
- Tanpa par[]: telusuri balik dari N mencari tetangga u dengan
  dist[u] + w == dist[N]. Butuh graf terbalik pada graf berarah.
- Kalau soal minta jalur LEKSIKOGRAFIS TERKECIL di antara yang terpendek:
  saat seri, pilih par yang bernomor lebih kecil -- tapi hati-hati, itu
  tidak selalu memberi jalur leksikografis terkecil secara global.
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
        g[v].push_back({u, w});            // TAK BERARAH
    }

    vector<ll> dist(n + 1, INF);
    vector<int> par(n + 1, 0);
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
                par[v] = u;                // DI DALAM if
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[n] >= INF) { cout << -1 << '\n'; return 0; }

    vector<int> path;
    for (int v = n; v; v = par[v]) { path.push_back(v); if (v == 1) break; }
    reverse(path.begin(), path.end());

    cout << dist[n] << '\n';
    for (size_t i = 0; i < path.size(); i++)
        cout << path[i] << " \n"[i + 1 == path.size()];
    return 0;
}
