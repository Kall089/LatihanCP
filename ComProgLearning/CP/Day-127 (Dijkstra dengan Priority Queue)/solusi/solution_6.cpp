/*
============================================================
✅ Solution 6: Tiket Diskon (Dijkstra Berlapis)
============================================================
Approach: Dijkstra pada graf berlapis dist[v][k]
Complexity: Time O(K * E * log(K*V)) | Space O(K * V)
Key Insight: Jangan menambal Dijkstra. Bangun graf BARU yang punya K+1 salinan
             dari graf asli ("lapisan"), dengan edge biasa di dalam lapisan dan
             edge gratis yang melompat satu lapisan ke atas. Lalu jalankan
             Dijkstra biasa di graf itu. Kebenarannya langsung mengikuti, tanpa
             perlu argumen baru.

📖 DUA JENIS RELAKSASI per edge (u -> v, bobot w), dari state (u, k):
   BAYAR  : dist[v][k]   <- dist[u][k] + w        (tetap di lapisan k)
   KUPON  : dist[v][k+1] <- dist[u][k] + 0        (naik ke lapisan k+1)
   Jawaban: min atas k dari dist[N][k].

⚠️ JAWABANNYA min ATAS SEMUA k, bukan dist[N][K].
   Kupon tidak wajib dipakai habis. Sampel 3 menguji ini secara terbalik:
   K=5 padahal hanya ada 2 edge -- program harus tetap benar (jawaban 0).

⚠️ SEMUA BOBOT TETAP NON-NEGATIF. Edge kupon berbobot 0, jadi syarat Dijkstra
   masih terpenuhi dan jaminan kebenarannya utuh. Kalau kuponnya "mengurangi
   biaya sebanyak X" dan bisa membuat bobot negatif, Dijkstra tidak berlaku.

⚠️ ENCODING STATE. Di C++ paling praktis memakai pair<ll,int> dengan
   int = u*(K+1) + k, atau tuple<ll,int,int>. Yang penting jarak tetap menjadi
   elemen pembanding pertama.

⚠️ MEMORI. dist berukuran (N+1) x (K+1). Dengan N=10^5 dan K=10 itu ~1.1 juta
   long long = ~9 MB. Aman, tapi K besar akan meledak -- kalau K bisa sampai
   10^5, pendekatannya harus lain.

VERIFIKASI SAMPEL 1 (K=1; 1->2:3, 2->4:10, 1->3:5, 3->4:5):
   dist[2][0]=3, dist[3][0]=5
   dist[2][1]=0  (kupon di edge 1->2)
   dari (2,0): dist[4][0]=13 ; dist[4][1]=3    <- kupon di edge 2->4
   dari (3,0): dist[4][0]=min(13,10)=10 ; dist[4][1]=min(3,5)=3
   min(dist[4][0], dist[4][1]) = min(10, 3) = 3  ✓

VERIFIKASI SAMPEL 2 (K=0): tidak ada lapisan tambahan -> Dijkstra biasa.
   1-2-4 = 13, 1-3-4 = 10  ->  10  ✓

🔄 ALTERNATIVE APPROACHES:
- Kalau grafnya DAG: DP dp[v][k] dalam urutan topologis, O((V+E)*K), tanpa heap.
- Kalau K = 1 saja: dua Dijkstra (dari 1 di graf asli, dari N di graf terbalik)
  lalu untuk setiap edge (u,v,w) hitung distDepan[u] + 0 + distBelakang[v].
  O(E log V), lebih cepat, dan pola "dua arah" ini sering muncul.
- LC 787 (Cheapest Flights Within K Stops) memakai state yang mirip tetapi
  membatasi JUMLAH HOP, bukan kupon -- di sana Bellman-Ford berlapis K justru
  lebih alami.
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

    int n, m, K;
    cin >> n >> m >> K;
    vector<vector<pair<int,ll>>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v; ll w; cin >> u >> v >> w;
        g[u].push_back({v, w});
    }

    int L = K + 1;
    vector<vector<ll>> dist(n + 1, vector<ll>(L, INF));
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dist[1][0] = 0;
    pq.push({0, 1 * L + 0});

    while (!pq.empty()) {
        pli t = pq.top(); pq.pop();
        ll d = t.first;
        int u = t.second / L, k = t.second % L;
        if (d > dist[u][k]) continue;
        for (auto& e : g[u]) {
            int v = e.first; ll w = e.second;
            if (d + w < dist[v][k]) {                 // BAYAR
                dist[v][k] = d + w;
                pq.push({dist[v][k], v * L + k});
            }
            if (k + 1 < L && d < dist[v][k + 1]) {    // PAKAI KUPON
                dist[v][k + 1] = d;
                pq.push({dist[v][k + 1], v * L + k + 1});
            }
        }
    }

    ll best = INF;
    for (int k = 0; k < L; k++) best = min(best, dist[n][k]);
    cout << (best >= INF ? -1 : best) << '\n';
    return 0;
}
