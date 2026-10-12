/*
============================================================
  Day 58 — BFS (Breadth-First Search) | CP Template
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;

const int INF = 1e9;
const ll LLINF = 1e18;

// ─── BFS PADA GRAPH ──────────────────────────────────────

// Adjacency list (unweighted)
// adj[u] = daftar tetangga u
vector<int> adj[100005];

// BFS dari source s, kembalikan array jarak
// dist[v] = -1 berarti v tidak terjangkau dari s
vector<int> bfs(int s, int n) {
    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}

// BFS dengan rekonstruksi path (simpan prev[v] = parent v)
vector<int> bfs_path(int s, int t, int n) {
    vector<int> dist(n + 1, -1), prev(n + 1, -1);
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == t) break;  // early exit jika sudah ketemu tujuan
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                prev[v] = u;
                q.push(v);
            }
        }
    }
    if (dist[t] == -1) return {};  // tidak terjangkau
    // Rekonstruksi path dari t ke s, lalu balik
    vector<int> path;
    for (int v = t; v != -1; v = prev[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

// ─── MULTI-SOURCE BFS ────────────────────────────────────

// BFS dari banyak source sekaligus
// sources = kumpulan node awal
vector<int> multi_source_bfs(vector<int>& sources, int n) {
    vector<int> dist(n + 1, -1);
    queue<int> q;
    for (int s : sources) {
        dist[s] = 0;
        q.push(s);
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}

// ─── BFS PADA GRID ───────────────────────────────────────

// 4-arah: atas, bawah, kiri, kanan
int dx4[] = {0, 0,  1, -1};
int dy4[] = {1, -1, 0,  0};

// 8-arah (termasuk diagonal)
int dx8[] = {0, 0,  1, -1, 1,  1, -1, -1};
int dy8[] = {1, -1, 0,  0, 1, -1,  1, -1};

// BFS pada grid R×C dari (sr,sc) ke (er,ec)
// '#' = tembok, '.' = bisa dilalui
int bfs_grid(vector<string>& grid, int sr, int sc, int er, int ec) {
    int R = grid.size(), C = grid[0].size();
    vector<vector<int>> dist(R, vector<int>(C, -1));
    queue<pii> q;
    dist[sr][sc] = 0;
    q.push({sr, sc});
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        if (r == er && c == ec) return dist[r][c];
        for (int d = 0; d < 4; d++) {
            int nr = r + dx4[d], nc = c + dy4[d];
            if (nr >= 0 && nr < R && nc >= 0 && nc < C
                && grid[nr][nc] != '#' && dist[nr][nc] == -1) {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
    return -1;  // tidak terjangkau
}

// ─── 0-1 BFS ─────────────────────────────────────────────

// 0-1 BFS: edge weight 0 atau 1 — gunakan deque
// - edge weight 0: push_front (seperti tidak pindah level)
// - edge weight 1: push_back (level bertambah)
// adj01[u] = {(v, w)} dengan w ∈ {0, 1}
vector<pii> adj01[100005];

vector<int> bfs_01(int s, int n) {
    vector<int> dist(n + 1, INF);
    deque<int> dq;
    dist[s] = 0;
    dq.push_front(s);
    while (!dq.empty()) {
        int u = dq.front(); dq.pop_front();
        for (auto [v, w] : adj01[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (w == 0) dq.push_front(v);
                else        dq.push_back(v);
            }
        }
    }
    return dist;
}

// ─── SHORTHAND ────────────────────────────────────────────

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

    // Baca graph unweighted undirected
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);  // hapus untuk directed
    }

    int src;
    cin >> src;

    // Jalankan BFS
    vector<int> dist = bfs(src, n);

    // Cetak jarak dari source
    for (int u = 1; u <= n; u++) {
        if (dist[u] == -1)
            cout << "Node " << u << ": tidak terjangkau\n";
        else
            cout << "Node " << u << ": jarak " << dist[u] << "\n";
    }

    // TODO: tambahkan solusi di sini

    return 0;
}
