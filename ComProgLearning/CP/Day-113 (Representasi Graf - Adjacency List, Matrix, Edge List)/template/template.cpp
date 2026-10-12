/*
============================================================
  Day 57 — Graph Representation | CP Template
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<int,ll> pil;
typedef vector<int> vi;
typedef vector<pii> vpii;

const int INF = 1e9;
const ll LLINF = 1e18;

// ─── REPRESENTASI GRAPH ──────────────────────────────────

// 1. Adjacency List (paling umum di CP)
//    adj[u] = list of {v, weight} (untuk weighted graph)
//    adj[u] = list of v           (untuk unweighted graph)
vector<pii> adj[100005];   // adj[u] = {(v, w), ...}
// atau: vector<vector<pii>> adj(n+1);

// 2. Adjacency Matrix (untuk n kecil, n <= 1000)
//    mat[u][v] = weight, 0 atau INF jika tidak ada edge
int mat[1005][1005];

// 3. Edge List (untuk Kruskal, dll)
//    edges = {(w, u, v), ...} — mudah di-sort
vector<tuple<int,int,int>> edges;  // {weight, u, v}

// ─── HELPER ──────────────────────────────────────────────

// Tambah edge (undirected, weighted)
void addEdge(vector<pii> adj[], int u, int v, int w = 1) {
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
}

// Tambah edge directed
void addEdgeDir(vector<pii> adj[], int u, int v, int w = 1) {
    adj[u].push_back({v, w});
}

// Shorthand
#define all(x)  (x).begin(), (x).end()
#define sz(x)   (int)(x).size()
#define pb      push_back
#define mp      make_pair

#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << "\n"
#else
#define dbg(x)
#endif

int main() {
    FASTIO;

    int n, m;
    cin >> n >> m;

    // Baca graph (pilih representasi yang sesuai)
    vector<vector<pii>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});  // hapus untuk directed
    }

    // TODO: write solution here

    return 0;
}
