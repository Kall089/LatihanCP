/*
 * Day 59 — DFS (Depth-First Search)
 * File  : solution_3.cpp
 * Topik : Deteksi Cycle Graph TAK BERARAH — SOLUSI LENGKAP
 * -----------------------------------------------
 * Pendekatan: DFS dengan pelacakan parent
 *
 * Idea:
 *   Pada graph tak berarah, edge u—v tercatat di adjacency list KEDUANYA.
 *   Saat DFS berada di v (datang dari u), kita pasti melihat u sudah
 *   dikunjungi — tapi itu bukan cycle, hanya edge yang sama dilihat balik.
 *
 *   Cycle yang sebenarnya = menemukan node terkunjungi yang BUKAN parent,
 *   artinya ada jalur ALTERNATIF menuju node tersebut.
 *
 *   bool dfs(u, parent):
 *       visited[u] = true
 *       for v in adj[u]:
 *           if !visited[v]:  if dfs(v, u) return true      ← tree edge
 *           else if v != parent: return true               ← back edge = CYCLE
 *       return false
 *
 * Trace sample 1 (1-2, 2-3, 3-4, 4-1):
 *   dfs(1,0) → dfs(2,1) → dfs(3,2) → dfs(4,3)
 *   di node 4: tetangga {3, 1}. 3 == parent, lewati. 1 sudah dikunjungi
 *   dan 1 != 3 (parent) → CYCLE terdeteksi → YES ✓
 *
 * Trace sample 2 (1-2, 2-3, 3-4 — rantai lurus):
 *   dfs(1,0)→dfs(2,1)→dfs(3,2)→dfs(4,3): di tiap node, satu-satunya
 *   tetangga terkunjungi adalah parent → tidak ada cycle → NO ✓
 *
 * Trace sample 3 (1-2, 4-5, 5-6, 6-4):
 *   Komponen 1 {1,2}: tidak ada cycle.
 *   Komponen 2 {4,5,6}: 4→5→6→4, di node 6 tetangga 4 terkunjungi & bukan
 *   parent(5) → CYCLE → YES ✓
 *   Ini menunjukkan pentingnya loop SEMUA node, bukan hanya dfs(1).
 *
 * Complexity: O(V + E) time, O(V + E) space
 *
 * Edge cases:
 *   - Graph tidak terhubung → wajib loop semua node sebagai start
 *   - N=1, M=0 → tidak ada cycle → NO
 *   - Pohon (M = N-1 dan terhubung) → tidak pernah ada cycle
 *   - Multi-edge (u—v dua kali): cek parent GAGAL mendeteksinya.
 *     Soal ini menjamin tidak ada multi-edge. Kalau ada, lacak edge id.
 *   - Self-loop (u—u): juga lolos cek parent; soal menjamin tidak ada.
 *
 * Alternative approaches:
 *   - Hitung komponen C, lalu cycle ada ⟺ M > N − C. O(V+E) juga,
 *     dan kebal terhadap masalah multi-edge.
 *   - DSU: saat menyatukan dua node yang sudah satu grup → cycle.
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
bool visited[MAXN];

bool dfs(int u, int parent) {
    visited[u] = true;

    for (int v : adj[u]) {
        if (!visited[v]) {
            if (dfs(v, u)) return true;     // cycle ditemukan di subtree
        }
        else if (v != parent) {
            return true;                     // back edge → CYCLE
        }
    }
    return false;
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

    bool hasCycle = false;
    for (int i = 1; i <= n && !hasCycle; i++) {
        if (!visited[i]) {
            if (dfs(i, 0)) hasCycle = true;  // parent 0 = tidak ada parent
        }
    }

    cout << (hasCycle ? "YES" : "NO") << "\n";
    return 0;
}
