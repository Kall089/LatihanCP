/*
============================================================
  Day 58 — BFS: Solusi Lengkap Exercise 1 s/d 6
============================================================
Kompilasi satu solusi yang diinginkan dengan mengubah #define
EXERCISE ke nomor yang sesuai, atau uncomment bagian main().

Kompleksitas:
  Exercise 1: O(V + E)
  Exercise 2: O(V + E)
  Exercise 3: O(R × C)
  Exercise 4: O(R × C)
  Exercise 5: O(V + E)  [tree]
  Exercise 6: O(R × C)  [0-1 BFS]
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════
// SOLUTION 1: BFS Dasar — Kunjungi Semua Node dari Source
// ═══════════════════════════════════════════════════════════
/*
  Cara kerja:
  - Inisialisasi dist[s] = 0, push s ke queue
  - Tiap iterasi: ambil u dari depan queue
  - Untuk tiap tetangga v yang belum dikunjungi (dist == -1):
      set dist[v] = dist[u] + 1, push v ke queue
  - Simpan urutan kunjungan di vector 'order'
*/
void solve_1() {
    int n, m, s;
    cin >> n >> m >> s;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> dist(n + 1, -1);
    vector<int> order;
    queue<int> q;

    dist[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);

        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    cout << "=== Urutan BFS ===\n";
    for (int i = 0; i < (int)order.size(); i++)
        cout << order[i] << (i+1 < (int)order.size() ? " " : "\n");

    cout << "=== Jarak dari node " << s << " ===\n";
    for (int u = 1; u <= n; u++)
        cout << "dist(" << u << ") = " << dist[u] << "\n";

    cout << "=== Node Tidak Terjangkau ===\n";
    bool ada = false;
    for (int u = 1; u <= n; u++)
        if (dist[u] == -1) { cout << u << "\n"; ada = true; }
    if (!ada) cout << "Semua node terjangkau\n";
}

// ═══════════════════════════════════════════════════════════
// SOLUTION 2: BFS Shortest Path Unweighted
// ═══════════════════════════════════════════════════════════
/*
  Cara kerja:
  - BFS dari S sambil simpan prev[v] = u (parent v dalam BFS tree)
  - Setelah BFS, rekonstruksi path dari T dengan mengikuti prev[]
  - Balik path karena kita trace dari T ke S
*/
void solve_2() {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int S, T; cin >> S >> T;

    vector<int> dist(n + 1, -1), prev(n + 1, -1);
    queue<int> q;
    dist[S] = 0;
    q.push(S);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == T) break;  // early termination
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                prev[v] = u;  // simpan parent
                q.push(v);
            }
        }
    }

    if (dist[T] == -1) {
        cout << "TIDAK ADA PATH\n";
        return;
    }

    cout << "Panjang path terpendek: " << dist[T] << "\n";

    // Rekonstruksi path dari T ke S lewat prev[]
    vector<int> path;
    for (int v = T; v != -1; v = prev[v])
        path.push_back(v);
    reverse(path.begin(), path.end());

    cout << "Path: ";
    for (int i = 0; i < (int)path.size(); i++)
        cout << path[i] << (i+1 < (int)path.size() ? " -> " : "\n");
}

// ═══════════════════════════════════════════════════════════
// SOLUTION 3: BFS pada Grid
// ═══════════════════════════════════════════════════════════
/*
  Cara kerja:
  - Cari posisi 'S' dan 'T' di grid
  - BFS dari 'S', bergerak 4 arah
  - Abaikan '#' (tembok) dan sel yang sudah dikunjungi
  - Output dist[er][ec], atau -1 jika tidak terjangkau
*/
void solve_3() {
    int R, C; cin >> R >> C;
    vector<string> grid(R);
    for (int i = 0; i < R; i++) cin >> grid[i];

    int sr = -1, sc = -1, er = -1, ec = -1;
    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++) {
            if (grid[r][c] == 'S') { sr = r; sc = c; }
            if (grid[r][c] == 'T') { er = r; ec = c; }
        }

    int dx[] = {-1, 1,  0, 0};
    int dy[] = { 0, 0, -1, 1};

    vector<vector<int>> dist(R, vector<int>(C, -1));
    queue<pair<int,int>> q;
    dist[sr][sc] = 0;
    q.push({sr, sc});

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + dx[d], nc = c + dy[d];
            // Cek batas, bukan tembok, belum dikunjungi
            if (nr >= 0 && nr < R && nc >= 0 && nc < C
                && grid[nr][nc] != '#' && dist[nr][nc] == -1) {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }

    cout << dist[er][ec] << "\n";
}

// ═══════════════════════════════════════════════════════════
// SOLUTION 4: Multi-source BFS
// ═══════════════════════════════════════════════════════════
/*
  Cara kerja:
  - Masukkan SEMUA sel daratan ('1') ke queue awal dengan dist = 0
  - BFS menyebar dari semua daratan sekaligus
  - Setiap sel lautan ('0') mendapat dist = jarak ke daratan terdekat
  - Jawaban = max(dist) dari semua sel lautan
*/
void solve_4() {
    int R, C; cin >> R >> C;
    vector<string> grid(R);
    for (int i = 0; i < R; i++) cin >> grid[i];

    bool hasDaratan = false, hasLautan = false;
    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++) {
            if (grid[r][c] == '1') hasDaratan = true;
            if (grid[r][c] == '0') hasLautan = true;
        }

    if (!hasDaratan || !hasLautan) {
        cout << -1 << "\n";
        return;
    }

    int dx[] = {-1, 1,  0, 0};
    int dy[] = { 0, 0, -1, 1};

    vector<vector<int>> dist(R, vector<int>(C, -1));
    queue<pair<int,int>> q;

    // Masukkan semua daratan ke queue dengan dist = 0
    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++)
            if (grid[r][c] == '1') {
                dist[r][c] = 0;
                q.push({r, c});
            }

    // BFS multi-source
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + dx[d], nc = c + dy[d];
            if (nr >= 0 && nr < R && nc >= 0 && nc < C
                && dist[nr][nc] == -1) {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }

    // Cari jarak maksimum dari semua sel lautan
    int ans = 0;
    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++)
            if (grid[r][c] == '0')
                ans = max(ans, dist[r][c]);

    cout << ans << "\n";
}

// ═══════════════════════════════════════════════════════════
// SOLUTION 5: BFS Level-Order Tree Traversal
// ═══════════════════════════════════════════════════════════
/*
  Cara kerja:
  - BFS dari root = 1
  - Tiap iterasi luar: catat q.size() (jumlah node level ini)
  - Proses tepat q.size() node → satu level selesai
  - Semua node yang di-push dalam satu iterasi = level berikutnya
*/
void solve_5() {
    int n; cin >> n;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> depth(n + 1, -1);
    vector<vector<int>> levels;
    queue<int> q;

    depth[1] = 0;
    q.push(1);

    while (!q.empty()) {
        int sz = q.size();  // jumlah node di level ini
        vector<int> cur_level;

        for (int i = 0; i < sz; i++) {
            int u = q.front(); q.pop();
            cur_level.push_back(u);

            for (int v : adj[u]) {
                if (depth[v] == -1) {  // belum dikunjungi
                    depth[v] = depth[u] + 1;
                    q.push(v);
                }
            }
        }
        levels.push_back(cur_level);
    }

    // Cetak level-order
    cout << "=== Level-Order Traversal ===\n";
    for (int lv = 0; lv < (int)levels.size(); lv++) {
        cout << "Level " << lv << ": ";
        for (int i = 0; i < (int)levels[lv].size(); i++)
            cout << levels[lv][i] << (i+1 < (int)levels[lv].size() ? " " : "\n");
    }

    // Cetak kedalaman
    cout << "=== Kedalaman Setiap Node ===\n";
    for (int u = 1; u <= n; u++)
        cout << "depth(" << u << ") = " << depth[u] << "\n";

    // Cari node terdalam (node dengan depth terbesar, pilih terkecil jika seri)
    int maxDepth = 0, deepNode = 1;
    for (int u = 1; u <= n; u++)
        if (depth[u] > maxDepth) { maxDepth = depth[u]; deepNode = u; }

    cout << "Node terdalam: " << deepNode
         << " (depth=" << maxDepth << ")\n";
}

// ═══════════════════════════════════════════════════════════
// SOLUTION 6: 0-1 BFS dengan Deque
// ═══════════════════════════════════════════════════════════
/*
  Cara kerja:
  - Gunakan deque<pair<int,int>> sebagai pengganti queue
  - Edge weight = 0 (nilai sama): push_front → tidak tambah jarak
  - Edge weight = 1 (nilai beda): push_back → tambah jarak 1
  - Penting: cek dist[r][c] + cost < dist[nr][nc] (bukan == -1)
    karena node bisa diproses ulang jika ditemukan jarak lebih kecil
*/
void solve_6() {
    int R, C; cin >> R >> C;
    vector<string> grid(R);
    for (int i = 0; i < R; i++) cin >> grid[i];

    const int INF = 1e9;
    int dx[] = {-1, 1,  0, 0};
    int dy[] = { 0, 0, -1, 1};

    vector<vector<int>> dist(R, vector<int>(C, INF));
    deque<pair<int,int>> dq;

    dist[0][0] = 0;
    dq.push_front({0, 0});

    while (!dq.empty()) {
        auto [r, c] = dq.front(); dq.pop_front();

        for (int d = 0; d < 4; d++) {
            int nr = r + dx[d], nc = c + dy[d];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;

            // Biaya: 0 jika nilai sama, 1 jika berbeda
            int cost = (grid[nr][nc] != grid[r][c]) ? 1 : 0;

            if (dist[r][c] + cost < dist[nr][nc]) {
                dist[nr][nc] = dist[r][c] + cost;
                if (cost == 0) dq.push_front({nr, nc});  // gratis
                else           dq.push_back({nr, nc});   // bayar 1
            }
        }
    }

    cout << dist[R-1][C-1] << "\n";
}

// ═══════════════════════════════════════════════════════════
// MAIN — Uncomment solusi yang ingin dijalankan
// ═══════════════════════════════════════════════════════════
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Uncomment salah satu:
    solve_1();
    // solve_2();
    // solve_3();
    // solve_4();
    // solve_5();
    // solve_6();

    return 0;
}
