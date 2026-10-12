/*
 * Day 59 — DFS (Depth-First Search)
 * Template C++ berisi seluruh pola DFS yang dipakai hari ini.
 *
 * Pilih pola yang sesuai, hapus yang tidak diperlukan.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 200005;

vector<int> adj[MAXN];
bool visited[MAXN];

// ──────────────────────────────────────────────────────────────────
// 0. MEMBACA GRAPH
// ──────────────────────────────────────────────────────────────────
//
// int n, m; cin >> n >> m;
// for (int i = 0; i < m; i++) {
//     int u, v; cin >> u >> v;
//     adj[u].push_back(v);
//     adj[v].push_back(u);      // HAPUS baris ini kalau graph BERARAH
// }

// ──────────────────────────────────────────────────────────────────
// 1. DFS DASAR (rekursif)
// Tandai visited DI AWAL fungsi — kalau tidak, infinite loop
// ──────────────────────────────────────────────────────────────────

void dfs(int u) {
    visited[u] = true;
    // ... proses u (pre-order) ...
    for (int v : adj[u]) {
        if (!visited[v]) dfs(v);
    }
    // ... proses u (post-order) ...
}

// ──────────────────────────────────────────────────────────────────
// 2. DFS ITERATIF (untuk graph dalam, hindari stack overflow)
// Cek visited SAAT POP — node bisa masuk stack lebih dari sekali
// ──────────────────────────────────────────────────────────────────

void dfsIterative(int start) {
    stack<int> st;
    st.push(start);
    while (!st.empty()) {
        int u = st.top(); st.pop();
        if (visited[u]) continue;       // WAJIB
        visited[u] = true;
        // ... proses u ...
        for (int i = (int)adj[u].size() - 1; i >= 0; i--) {
            if (!visited[adj[u][i]]) st.push(adj[u][i]);
        }
    }
}

// ──────────────────────────────────────────────────────────────────
// 3. CONNECTED COMPONENTS + UKURANNYA
// ──────────────────────────────────────────────────────────────────

int dfsSize(int u) {
    visited[u] = true;
    int sz = 1;
    for (int v : adj[u]) if (!visited[v]) sz += dfsSize(v);
    return sz;
}

// int components = 0, maxSize = 0;
// for (int i = 1; i <= n; i++)
//     if (!visited[i]) { components++; maxSize = max(maxSize, dfsSize(i)); }

// ──────────────────────────────────────────────────────────────────
// 4. CYCLE DETECTION — GRAPH TAK BERARAH (cek parent)
// ──────────────────────────────────────────────────────────────────

bool dfsCycleUndirected(int u, int parent) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            if (dfsCycleUndirected(v, u)) return true;
        }
        else if (v != parent) return true;      // back edge → CYCLE
    }
    return false;
}
// Panggil: for (i=1..n) if (!visited[i]) if (dfsCycleUndirected(i, 0)) ...
// ⚠️ Gagal pada multi-edge & self-loop. Alternatif: cycle ada ⟺ M > N - C

// ──────────────────────────────────────────────────────────────────
// 5. CYCLE DETECTION — GRAPH BERARAH (3-color)
// Cek parent TIDAK cukup di sini!
// ──────────────────────────────────────────────────────────────────

int color[MAXN];        // 0 = WHITE, 1 = GRAY (di recursion stack), 2 = BLACK

bool dfsCycleDirected(int u) {
    color[u] = 1;                                       // GRAY
    for (int v : adj[u]) {
        if (color[v] == 1) return true;                 // back edge → CYCLE
        if (color[v] == 0 && dfsCycleDirected(v)) return true;
        // BLACK → aman, lewati
    }
    color[u] = 2;                                       // BLACK
    return false;
}

// ──────────────────────────────────────────────────────────────────
// 6. TOPOLOGICAL SORT (DFS post-order + reverse)
// Hanya valid pada DAG — deteksi cycle dulu!
// ──────────────────────────────────────────────────────────────────

vector<int> topo;

bool dfsTopo(int u) {                   // return true jika ada cycle
    color[u] = 1;
    for (int v : adj[u]) {
        if (color[v] == 1) return true;
        if (color[v] == 0 && dfsTopo(v)) return true;
    }
    color[u] = 2;
    topo.push_back(u);                  // POST-ORDER
    return false;
}
// for (i=1..n) if (color[i]==0) if (dfsTopo(i)) { cout << "IMPOSSIBLE"; return 0; }
// reverse(topo.begin(), topo.end());   ← WAJIB DIBALIK

// ──────────────────────────────────────────────────────────────────
// 7. DISCOVERY & FINISH TIME (fondasi bridges, SCC, Euler tour)
// ──────────────────────────────────────────────────────────────────

int timer_ = 0;
int tin[MAXN], tout_[MAXN];

void dfsTime(int u, int parent) {
    tin[u] = timer_++;
    for (int v : adj[u]) if (v != parent) dfsTime(v, u);
    tout_[u] = timer_++;
}

// u ancestor dari v  ⟺  tin[u] <= tin[v] && tout_[v] <= tout_[u]   → O(1)
bool isAncestor(int u, int v) {
    return tin[u] <= tin[v] && tout_[v] <= tout_[u];
}

// ──────────────────────────────────────────────────────────────────
// 8. UKURAN SUBTREE (DFS post-order pada POHON)
// Pada pohon tidak butuh visited — cukup hindari parent
// ──────────────────────────────────────────────────────────────────

int subSize[MAXN];

void dfsSubtree(int u, int parent) {
    subSize[u] = 1;
    for (int v : adj[u]) {
        if (v == parent) continue;
        dfsSubtree(v, u);
        subSize[u] += subSize[v];       // akumulasi SETELAH anak selesai
    }
}

// ──────────────────────────────────────────────────────────────────
// 9. BIPARTITE CHECK (DFS 2-coloring)
// ──────────────────────────────────────────────────────────────────

int col2[MAXN];         // -1 = belum, 0 dan 1 = dua warna

bool dfsBipartite(int u, int c) {
    col2[u] = c;
    for (int v : adj[u]) {
        if (col2[v] == -1) { if (!dfsBipartite(v, 1 - c)) return false; }
        else if (col2[v] == c) return false;        // konflik
    }
    return true;
}
// memset(col2, -1, sizeof(col2));
// for (i=1..n) if (col2[i]==-1) if (!dfsBipartite(i, 0)) → NOT bipartite

// ──────────────────────────────────────────────────────────────────
// 10. DFS PADA GRID (flood fill 4-arah)
// ──────────────────────────────────────────────────────────────────

const int dr[] = {-1, 1, 0, 0};         // atas, bawah, kiri, kanan
const int dc[] = {0, 0, -1, 1};
// const int dr8[] = {-1,-1,-1,0,0,1,1,1};    // versi 8-arah
// const int dc8[] = {-1,0,1,-1,1,-1,0,1};

// int R, C;
// vector<string> grid;
// vector<vector<bool>> vis;
//
// int dfsGrid(int r, int c) {                  // return luas area
//     if (r < 0 || r >= R || c < 0 || c >= C) return 0;
//     if (vis[r][c] || grid[r][c] == '.') return 0;
//     vis[r][c] = true;
//     int area = 1;
//     for (int d = 0; d < 4; d++) area += dfsGrid(r + dr[d], c + dc[d]);
//     return area;
// }
// ⚠️ Grid 1000×1000 penuh → depth 10^6 → pakai versi iteratif atau BFS

// ──────────────────────────────────────────────────────────────────
// 11. DP ON DAG (longest path, jumlah jalur) — DFS + memoisasi
// ──────────────────────────────────────────────────────────────────

int dp[MAXN];

int dfsLongest(int u) {
    if (dp[u] != -1) return dp[u];
    dp[u] = 0;
    for (int v : adj[u]) dp[u] = max(dp[u], 1 + dfsLongest(v));
    return dp[u];
}
// memset(dp, -1, sizeof(dp)); lalu ambil max dfsLongest(i) untuk semua i

// ──────────────────────────────────────────────────────────────────
// CHECKLIST SEBELUM SUBMIT SOAL DFS
//   [ ] visited ditandai di AWAL fungsi?
//   [ ] Loop SEMUA node sebagai start (graph bisa tidak terhubung)?
//   [ ] Undirected: edge di-push ke DUA arah?
//   [ ] Directed: pakai 3-color, bukan cek parent?
//   [ ] Topological sort: hasil sudah di-reverse?
//   [ ] Kedalaman maksimal aman untuk rekursi (< ~10^6)?
//   [ ] Multi test case: visited/color sudah di-reset?
//   [ ] Node 1-indexed atau 0-indexed — konsisten?
//   [ ] Soal minta "terpendek"? → seharusnya BFS, bukan DFS!
// ──────────────────────────────────────────────────────────────────

void solve() {
    // Solusi untuk satu test case
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    // cin >> t;   // Uncomment jika multi test case
    while (t--) solve();

    return 0;
}
