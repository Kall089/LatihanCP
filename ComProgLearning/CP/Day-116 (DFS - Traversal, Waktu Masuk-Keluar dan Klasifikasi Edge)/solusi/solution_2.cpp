/*
 * Day 59 — DFS (Depth-First Search)
 * File  : solution_2.cpp
 * Topik : Connected Components — SOLUSI LENGKAP
 * -----------------------------------------------
 * Pendekatan: DFS dari setiap node yang belum dikunjungi
 *
 * Idea:
 *   Kunci teoritisnya: satu panggilan dfs(i) akan menandai SELURUH node yang
 *   terhubung dengan i. Jadi kalau setelah itu masih ada node yang belum
 *   ditandai, node tersebut PASTI berada di komponen yang berbeda.
 *
 *   for (int i = 1; i <= n; i++)
 *       if (!visited[i]) { components++; maxSize = max(maxSize, dfs(i)); }
 *
 *   dfs mengembalikan jumlah node yang ditandainya = ukuran komponen.
 *
 * Trace sample 1 (N=6, edge: 1-2, 2-3, 4-5):
 *   i=1 belum → comp=1, dfs(1) tandai {1,2,3} → size 3, maxSize=3
 *   i=2,3 sudah → skip
 *   i=4 belum → comp=2, dfs(4) tandai {4,5} → size 2, maxSize tetap 3
 *   i=5 sudah → skip
 *   i=6 belum → comp=3, dfs(6) tandai {6} → size 1
 *   Output: 3 3 ✓
 *
 * Trace sample 2 (N=4, M=0):
 *   Tiap node terisolasi → 4 komponen, tiap ukuran 1 → "4 1" ✓
 *
 * Complexity: O(V + E) — loop luar O(V), total kerja DFS O(V+E)
 * Space: O(V + E)
 *
 * Edge cases:
 *   - M = 0 → jawaban selalu "N 1"
 *   - Graph terhubung penuh → jawaban "1 N"
 *   - Node terisolasi tetap dihitung sebagai satu komponen
 *
 * Alternative approaches:
 *   - BFS: sama persis O(V+E), tinggal ganti stack jadi queue
 *   - DSU (Day 52): O(V + E·α), lebih cocok kalau edge datang online
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
bool visited[MAXN];

// Mengembalikan jumlah node dalam komponen yang memuat u
int dfs(int u) {
    visited[u] = true;
    int size = 1;                       // hitung diri sendiri
    for (int v : adj[u]) {
        if (!visited[v]) size += dfs(v);
    }
    return size;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int components = 0;
    int maxSize = 0;

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            components++;               // node belum terjamah = komponen baru
            maxSize = max(maxSize, dfs(i));
        }
    }

    cout << components << " " << maxSize << "\n";
    return 0;
}
