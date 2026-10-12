/*
============================================================
✅ Solution 3: Membuktikan Dijkstra Gagal pada Bobot Negatif
============================================================
Approach: jalankan dua algoritma berdampingan dan bandingkan
Complexity: Dijkstra O(E log V) | Bellman-Ford O(V*E)
Key Insight: Kesalahan Dijkstra BUKAN karena tanda minus, melainkan karena
             asumsi "sekali final, selamanya final". Bobot negatif membuat
             sebuah jalur MEMENDEK setelah simpulnya terlanjur dikunci.

📖 DI MANA PERSIS BUKTINYA RUNTUH:
   Bukti kebenaran Dijkstra memakai satu baris:
       panjang PREFIKS jalur  <=  panjang SELURUH jalur
   Baris ini hanya benar kalau sisa jalur tidak negatif. Dengan edge negatif,
   prefiks justru bisa LEBIH PANJANG daripada keseluruhan, dan seluruh argumen
   "simpul terkecil pasti final" batal.

📖 TRACE SAMPEL 1 (1->2:1, 1->3:2, 2->4:5, 3->2:-4):
   Jawaban BENAR: 1-3-2-4 = 2 + (-4) + 5 = 3.

   Dijkstra versi KUNCI:
     pop 1 (d=0)  : dist[2]=1, dist[3]=2
     pop 2 (d=1)  : KUNCI simpul 2. dist[4] = 1 + 5 = 6
     pop 3 (d=2)  : relaksasi 3->2 memberi 2 + (-4) = -2 < 1,
                    TAPI simpul 2 sudah TERKUNCI -> diabaikan
     pop 4 (d=6)  : selesai
     hasil: 6   <-- SALAH

   Bellman-Ford: setelah N-1 putaran relaksasi semua edge,
     dist[3]=2, dist[2]=-2, dist[4]=3
     hasil: 3   <-- BENAR

⚠️ VERSI LAZY-DELETION BISA "KEBETULAN BENAR" -- DAN ITU BERBAHAYA.
   Implementasi C++ standar (tanpa array kunci) boleh memproses ulang simpul,
   jadi pada graf kecil ia sering memberi jawaban benar. Bug-nya lolos dari
   pengujianmu. Tapi jaminan kompleksitasnya HILANG: pada graf yang dirancang
   jahat, jumlah relaksasinya bisa EKSPONENSIAL -> TLE parah.
   Karena itu solusi ini sengaja memakai versi KUNCI: supaya kegagalannya
   terlihat, bukan tersembunyi.

⚠️ TRIK YANG TIDAK BERHASIL: menambahkan konstanta C ke semua bobot agar
   non-negatif. Jalur dengan lebih banyak edge mendapat tambahan lebih besar,
   jadi masalahnya berubah -- jalur terpendek yang baru belum tentu sama.

⚠️ SIKLUS NEGATIF. Soal ini menjamin tidak ada. Kalau ada, jarak terpendek
   TIDAK TERDEFINISI (bisa dibuat sekecil apa pun dengan memutari siklus).
   Bellman-Ford mendeteksinya: kalau putaran ke-N masih ada relaksasi berhasil,
   berarti ada siklus negatif. Itu materi Day 129.

🔄 ALTERNATIVE APPROACHES:
- Kalau grafnya DAG, DP topologis (Day 120) menyelesaikannya dalam O(V+E) --
  lebih cepat daripada Bellman-Ford DAN menerima bobot negatif.
- Johnson's algorithm: reweighting dengan potensial Bellman-Ford, lalu
  Dijkstra berkali-kali. Berguna untuk all-pairs pada graf jarang.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,int> pli;
const ll INF = LLONG_MAX / 4;

int n, m;
vector<array<ll,3>> edges;                  // {u, v, w}
vector<vector<pair<int,ll>>> g;

// Dijkstra versi "KUNCI": simpul yang sudah dipop tidak pernah diproses lagi.
// Inilah versi buku teks -- dan versi yang kegagalannya terlihat jelas.
ll dijkstraKunci() {
    vector<ll> dist(n + 1, INF);
    vector<char> kunci(n + 1, 0);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dist[1] = 0; pq.push({0, 1});
    while (!pq.empty()) {
        pli t = pq.top(); pq.pop();
        int u = t.second;
        if (kunci[u]) continue;
        kunci[u] = 1;                        // <-- FINAL, tidak boleh diubah lagi
        for (auto& e : g[u]) {
            int v = e.first; ll w = e.second;
            if (kunci[v]) continue;          // <-- di sinilah jawaban benar hilang
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist[n];
}

// Bellman-Ford: tidak punya asumsi "final", jadi bobot negatif tidak masalah.
ll bellmanFord() {
    vector<ll> dist(n + 1, INF);
    dist[1] = 0;
    for (int it = 0; it < n - 1; it++) {
        bool ubah = false;
        for (auto& e : edges) {
            int u = (int)e[0], v = (int)e[1]; ll w = e[2];
            if (dist[u] < INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                ubah = true;
            }
        }
        if (!ubah) break;
    }
    return dist[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    g.assign(n + 1, {});
    for (int i = 0; i < m; i++) {
        int u, v; ll w; cin >> u >> v >> w;
        g[u].push_back({v, w});
        edges.push_back({(ll)u, (ll)v, w});
    }

    ll a = dijkstraKunci();
    ll b = bellmanFord();
    cout << (a >= INF ? -1 : a) << ' ' << (b >= INF ? -1 : b) << '\n';
    return 0;
}
