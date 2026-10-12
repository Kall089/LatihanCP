/*
============================================================
TEMPLATE Day 127 — Dijkstra dengan Priority Queue
============================================================
Semua versi 1-INDEXED. SYARAT: semua bobot >= 0.
Ada bobot negatif -> Bellman-Ford (Day 129) atau DP-DAG (Day 120).
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,int> pli;

const ll INF = LLONG_MAX / 4;      // BUKAN LLONG_MAX: dist[u]+w harus aman
const ll MOD = 1000000007LL;

// ------------------------------------------------------------------
// 1. DIJKSTRA DASAR — O(E log V), lazy deletion
// ------------------------------------------------------------------
vector<ll> dijkstra(int n, const vector<vector<pair<int,ll>>>& g, int s) {
    vector<ll> dist(n + 1, INF);
    priority_queue<pli, vector<pli>, greater<pli>> pq;   // MIN-heap
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        pli top = pq.top(); pq.pop();
        ll d = top.first; int u = top.second;
        if (d > dist[u]) continue;                       // entri USANG
        for (auto& e : g[u]) {
            int v = e.first; ll w = e.second;
            if (d + w < dist[v]) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

// ------------------------------------------------------------------
// 2. DIJKSTRA + PARENT (rekonstruksi jalur)
// ------------------------------------------------------------------
vector<ll> dijkstraPar(int n, const vector<vector<pair<int,ll>>>& g, int s,
                       vector<int>& par) {
    vector<ll> dist(n + 1, INF);
    par.assign(n + 1, 0);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dist[s] = 0; pq.push({0, s});
    while (!pq.empty()) {
        pli top = pq.top(); pq.pop();
        ll d = top.first; int u = top.second;
        if (d > dist[u]) continue;
        for (auto& e : g[u]) {
            int v = e.first; ll w = e.second;
            if (d + w < dist[v]) {
                dist[v] = d + w;
                par[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

vector<int> buildPath(int s, int t, const vector<ll>& dist, const vector<int>& par) {
    if (dist[t] >= INF) return {};
    vector<int> path;
    for (int v = t; v; v = par[v]) { path.push_back(v); if (v == s) break; }
    reverse(path.begin(), path.end());
    return path;
}

// ------------------------------------------------------------------
// 3. DIJKSTRA + MENGHITUNG JALUR TERPENDEK
// ------------------------------------------------------------------
void dijkstraCount(int n, const vector<vector<pair<int,ll>>>& g, int s,
                   vector<ll>& dist, vector<ll>& cnt) {
    dist.assign(n + 1, INF);
    cnt.assign(n + 1, 0);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dist[s] = 0; cnt[s] = 1; pq.push({0, s});
    while (!pq.empty()) {
        pli top = pq.top(); pq.pop();
        ll d = top.first; int u = top.second;
        if (d > dist[u]) continue;
        for (auto& e : g[u]) {
            int v = e.first; ll w = e.second;
            if (d + w < dist[v]) {
                dist[v] = d + w;
                cnt[v] = cnt[u];
                pq.push({dist[v], v});
            } else if (d + w == dist[v]) {
                cnt[v] = (cnt[v] + cnt[u]) % MOD;
            }
        }
    }
}

// ------------------------------------------------------------------
// 4. MINIMAX — minimalkan EDGE TERBESAR di sepanjang jalur
//    (LC 1631 Path With Minimum Effort)
// ------------------------------------------------------------------
vector<ll> minimax(int n, const vector<vector<pair<int,ll>>>& g, int s) {
    vector<ll> dist(n + 1, INF);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dist[s] = 0; pq.push({0, s});
    while (!pq.empty()) {
        pli top = pq.top(); pq.pop();
        ll d = top.first; int u = top.second;
        if (d > dist[u]) continue;
        for (auto& e : g[u]) {
            int v = e.first; ll w = e.second;
            ll nd = max(d, w);                 // <-- satu-satunya perubahan
            if (nd < dist[v]) { dist[v] = nd; pq.push({nd, v}); }
        }
    }
    return dist;
}

// ------------------------------------------------------------------
// 5. MAXIMIN — maksimalkan KAPASITAS TERKECIL (bottleneck terlebar)
// ------------------------------------------------------------------
vector<ll> maximin(int n, const vector<vector<pair<int,ll>>>& g, int s) {
    vector<ll> dist(n + 1, -1);
    priority_queue<pli> pq;                    // MAX-heap
    dist[s] = INF; pq.push({INF, s});
    while (!pq.empty()) {
        pli top = pq.top(); pq.pop();
        ll d = top.first; int u = top.second;
        if (d < dist[u]) continue;
        for (auto& e : g[u]) {
            int v = e.first; ll w = e.second;
            ll nd = min(d, w);
            if (nd > dist[v]) { dist[v] = nd; pq.push({nd, v}); }
        }
    }
    return dist;
}

// ------------------------------------------------------------------
// 6. DIJKSTRA BERLAPIS — dist[v][k], k = kupon/gratis yang sudah dipakai
// ------------------------------------------------------------------
vector<vector<ll>> dijkstraLayered(int n, int K,
        const vector<vector<pair<int,ll>>>& g, int s) {
    vector<vector<ll>> dist(n + 1, vector<ll>(K + 1, INF));
    // heap: (jarak, simpul*(K+1)+k) supaya tetap pakai pair
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dist[s][0] = 0;
    pq.push({0, s * (K + 1) + 0});
    while (!pq.empty()) {
        pli top = pq.top(); pq.pop();
        ll d = top.first;
        int u = top.second / (K + 1), k = top.second % (K + 1);
        if (d > dist[u][k]) continue;
        for (auto& e : g[u]) {
            int v = e.first; ll w = e.second;
            if (d + w < dist[v][k]) {                 // bayar penuh
                dist[v][k] = d + w;
                pq.push({dist[v][k], v * (K + 1) + k});
            }
            if (k < K && d < dist[v][k + 1]) {        // pakai satu kupon
                dist[v][k + 1] = d;
                pq.push({dist[v][k + 1], v * (K + 1) + k + 1});
            }
        }
    }
    return dist;
}

// ------------------------------------------------------------------
// 7. KERANGKA MAIN
//    n m, lalu m baris "u v w" (graf berarah; tambahkan arah balik bila perlu)
// ------------------------------------------------------------------
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<vector<pair<int,ll>>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v; ll w; cin >> u >> v >> w;
        g[u].push_back({v, w});
        // g[v].push_back({u, w});      // aktifkan kalau TAK BERARAH
    }

    vector<ll> dist = dijkstra(n, g, 1);
    for (int v = 1; v <= n; v++)
        cout << (dist[v] >= INF ? -1 : dist[v]) << " \n"[v == n];
    return 0;
}
