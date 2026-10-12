/*
============================================================
TEMPLATE Day 119 — Topological Sort (Kahn & DFS)
============================================================
Salin bagian yang dibutuhkan. Semua versi 1-INDEXED.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// ------------------------------------------------------------------
// 1. KAHN DASAR — mengembalikan urutan topologis.
//    Jika ord.size() < n  =>  graf punya SIKLUS.
// ------------------------------------------------------------------
vector<int> kahn(int n, const vector<vector<int>>& g) {
    vector<int> indeg(n + 1, 0), ord;
    for (int u = 1; u <= n; u++)
        for (int v : g[u]) indeg[v]++;

    queue<int> q;
    for (int u = 1; u <= n; u++)
        if (indeg[u] == 0) q.push(u);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        ord.push_back(u);
        for (int v : g[u])
            if (--indeg[v] == 0) q.push(v);
    }
    return ord;
}

// ------------------------------------------------------------------
// 2. DETEKSI SIKLUS pada graf BERARAH (satu baris efektif)
// ------------------------------------------------------------------
bool adaSiklus(int n, const vector<vector<int>>& g) {
    return (int)kahn(n, g).size() != n;
}

// ------------------------------------------------------------------
// 3. KAHN LEKSIKOGRAFIS TERKECIL — O((V+E) log V)
// ------------------------------------------------------------------
vector<int> kahnLex(int n, const vector<vector<int>>& g) {
    vector<int> indeg(n + 1, 0), ord;
    for (int u = 1; u <= n; u++)
        for (int v : g[u]) indeg[v]++;

    priority_queue<int, vector<int>, greater<int>> q;
    for (int u = 1; u <= n; u++)
        if (indeg[u] == 0) q.push(u);

    while (!q.empty()) {
        int u = q.top(); q.pop();
        ord.push_back(u);
        for (int v : g[u])
            if (--indeg[v] == 0) q.push(v);
    }
    return ord;
}

// ------------------------------------------------------------------
// 4. KAHN + CEK KEUNIKAN + LEVEL (rantai prasyarat terpanjang)
//    unik  : true jika hanya ada SATU urutan topologis
//    lvl[v]: panjang rantai terpanjang yang berakhir di v (0-based)
// ------------------------------------------------------------------
struct TopoInfo {
    vector<int> ord;
    vector<int> lvl;
    bool unik = true;
    bool dag  = true;
};

TopoInfo kahnFull(int n, const vector<vector<int>>& g) {
    TopoInfo r;
    r.lvl.assign(n + 1, 0);
    vector<int> indeg(n + 1, 0);
    for (int u = 1; u <= n; u++)
        for (int v : g[u]) indeg[v]++;

    queue<int> q;
    for (int u = 1; u <= n; u++)
        if (indeg[u] == 0) q.push(u);

    while (!q.empty()) {
        if (q.size() > 1) r.unik = false;   // ada >1 pilihan sah
        int u = q.front(); q.pop();
        r.ord.push_back(u);
        for (int v : g[u]) {
            r.lvl[v] = max(r.lvl[v], r.lvl[u] + 1);
            if (--indeg[v] == 0) q.push(v);
        }
    }
    r.dag = ((int)r.ord.size() == n);
    if (!r.dag) r.unik = false;
    return r;
}

// ------------------------------------------------------------------
// 5. VERSI DFS — post-order + reverse, dengan 3 warna
//    warna: 0 belum, 1 sedang di stack, 2 selesai
// ------------------------------------------------------------------
struct TopoDFS {
    int n;
    const vector<vector<int>>* g;
    vector<int> warna, ord;
    bool siklus = false;

    TopoDFS(int n_, const vector<vector<int>>& g_) : n(n_), g(&g_) {
        warna.assign(n + 1, 0);
    }
    void dfs(int u) {
        warna[u] = 1;
        for (int v : (*g)[u]) {
            if (warna[v] == 1) { siklus = true; return; }  // back edge
            if (warna[v] == 0) { dfs(v); if (siklus) return; }
        }
        warna[u] = 2;
        ord.push_back(u);
    }
    vector<int> run() {
        for (int u = 1; u <= n && !siklus; u++)
            if (warna[u] == 0) dfs(u);
        if (siklus) return {};
        reverse(ord.begin(), ord.end());
        return ord;
    }
};

// ------------------------------------------------------------------
// 6. KERANGKA PEMBACAAN INPUT STANDAR
//    n m, lalu m baris "u v" berarti u HARUS SEBELUM v
// ------------------------------------------------------------------
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);           // u sebelum v
    }

    vector<int> ord = kahn(n, g);
    if ((int)ord.size() != n) { cout << "IMPOSSIBLE\n"; return 0; }
    for (int i = 0; i < n; i++) cout << ord[i] << " \n"[i + 1 == n];
    return 0;
}
