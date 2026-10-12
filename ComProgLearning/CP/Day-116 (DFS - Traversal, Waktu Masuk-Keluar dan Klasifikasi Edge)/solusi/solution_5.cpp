/*
 * Day 59 — DFS (Depth-First Search)
 * File  : solution_5.cpp
 * Topik : Topological Sort (DFS Post-Order) — SOLUSI LENGKAP
 * -----------------------------------------------
 * Pendekatan: DFS post-order + reverse, digabung dengan deteksi cycle 3-color
 *
 * Idea:
 *   Node u dimasukkan ke list SETELAH semua node yang bisa dicapai dari u
 *   selesai diproses. Artinya, dalam list post-order, u selalu muncul
 *   SESUDAH seluruh turunannya.
 *
 *   Untuk topological sort kita ingin sebaliknya (u SEBELUM turunannya),
 *   maka cukup BALIK listnya.
 *
 *   Bukti singkat: untuk setiap edge u→v,
 *     - kalau v WHITE saat kita di u → dfs(v) selesai dulu → v masuk list
 *       lebih dulu → setelah reverse, u sebelum v ✓
 *     - kalau v BLACK → v sudah di list → setelah reverse, u sebelum v ✓
 *     - kalau v GRAY → itu cycle, dan kita sudah menolaknya
 *
 * Deteksi cycle memakai 3-color yang sama persis dengan solution_4 —
 * karena topological sort HANYA terdefinisi pada DAG.
 *
 * Trace sample 1 (1→2, 1→3, 2→4, 3→4, 4→6, 1→5):
 *   adj[1]={2,3,5} adj[2]={4} adj[3]={4} adj[4]={6}
 *   dfs(1): GRAY
 *     dfs(2): GRAY → dfs(4): GRAY → dfs(6): BLACK, push 6
 *                    4 BLACK, push 4
 *             2 BLACK, push 2
 *     dfs(3): GRAY → tetangga 4 BLACK, lewati → push 3
 *     dfs(5): push 5
 *     1 BLACK, push 1
 *   topo (post-order) = [6, 4, 2, 3, 5, 1]
 *   reverse            = [1, 5, 3, 2, 4, 6]
 *
 *   Verifikasi semua edge: 1<2 ✓ 1<3 ✓ 2<4 ✓ 3<4 ✓ 4<6 ✓ 1<5 ✓  VALID
 *
 *   Catatan: topological sort TIDAK UNIK. "1 2 3 5 4 6" juga jawaban valid
 *   untuk input yang sama. Checker harus memverifikasi semua edge terpenuhi,
 *   bukan mencocokkan string persis.
 *
 * Trace sample 2 (1→2, 2→3, 3→1): cycle terdeteksi → IMPOSSIBLE ✓
 * Trace sample 3 (M=0): tidak ada edge, post-order = [1,2,3,4],
 *   dibalik → 4 3 2 1. Valid (tidak ada kendala yang dilanggar). ✓
 *
 * Complexity: O(V + E) time (plus O(E log E) untuk sort adjacency list)
 * Space: O(V + E)
 *
 * Edge cases:
 *   - M = 0 → output 1..N berurutan
 *   - Ada cycle → IMPOSSIBLE
 *   - Graph tidak terhubung → tetap valid, loop semua node
 *   - N = 1 → output "1"
 *
 * Alternative approaches:
 *   - Kahn's algorithm (Day 60): BFS + in-degree. Menghasilkan urutan
 *     lexicographically smallest jika memakai priority_queue.
 *   - Kahn juga mendeteksi cycle secara alami (kalau node terproses < N).
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int color[MAXN];            // 0 = WHITE, 1 = GRAY, 2 = BLACK
vector<int> topo;

bool dfs(int u) {
    color[u] = 1;                       // GRAY

    for (int v : adj[u]) {
        if (color[v] == 1) return true;                 // cycle
        if (color[v] == 0 && dfs(v)) return true;
    }

    color[u] = 2;                       // BLACK
    topo.push_back(u);                  // POST-ORDER
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
        adj[u].push_back(v);            // BERARAH — satu arah saja
    }

    for (int i = 1; i <= n; i++) sort(adj[i].begin(), adj[i].end());

    // Step 1: DFS semua node, sekaligus deteksi cycle
    for (int i = 1; i <= n; i++) {
        if (color[i] == 0) {
            if (dfs(i)) {
                cout << "IMPOSSIBLE\n";
                return 0;
            }
        }
    }

    // Step 2: post-order harus DIBALIK
    reverse(topo.begin(), topo.end());

    for (int i = 0; i < (int)topo.size(); i++) {
        cout << topo[i] << " \n"[i + 1 == (int)topo.size()];
    }

    return 0;
}
