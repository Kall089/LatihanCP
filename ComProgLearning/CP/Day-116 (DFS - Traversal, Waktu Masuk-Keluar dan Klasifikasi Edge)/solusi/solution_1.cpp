/*
 * Day 59 — DFS (Depth-First Search)
 * File  : solution_1.cpp
 * Topik : DFS Dasar — Urutan Kunjungan — SOLUSI LENGKAP
 * -----------------------------------------------
 * Pendekatan: DFS rekursif standar dengan adjacency list
 *
 * Idea:
 *   1. Bangun adjacency list DUA ARAH (graph tak berarah)
 *   2. Sort tiap adjacency list agar tetangga terkecil dikunjungi lebih dulu
 *   3. dfs(1): tandai visited di AWAL, cetak, lalu rekursi ke tetangga
 *
 * Kenapa tandai di awal fungsi?
 *   Kalau ditandai setelah loop, node yang sama bisa masuk berkali-kali
 *   pada graph bersiklus → infinite recursion → stack overflow.
 *
 * Trace sample 1:
 *   adj[1]={2,3} adj[2]={1,4} adj[3]={1} adj[4]={2,5} adj[5]={4}
 *   dfs(1) cetak 1 → tetangga 2 belum → dfs(2) cetak 2
 *   → tetangga 1 sudah, 4 belum → dfs(4) cetak 4
 *   → tetangga 2 sudah, 5 belum → dfs(5) cetak 5 → buntu, mundur
 *   → mundur sampai node 1, tetangga 3 belum → dfs(3) cetak 3
 *   Output: 1 2 4 5 3 ✓
 *
 *   Perhatikan node 3 dikunjungi PALING AKHIR meski bertetangga langsung
 *   dengan node 1. DFS menuntaskan satu cabang penuh dulu sebelum pindah.
 *
 * Complexity: O(V + E) untuk DFS, plus O(E log E) untuk sorting adjacency list
 * Space: O(V + E) adjacency list + O(V) call stack
 *
 * Edge cases:
 *   - N=1, M=0 → output hanya "1"
 *   - Graph dijamin terhubung, jadi cukup satu panggilan dfs(1)
 *   - Kedalaman maksimal 2×10^5 → rekursi masih aman (~beberapa MB stack)
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
bool visited[MAXN];
vector<int> order_;

void dfs(int u) {
    visited[u] = true;          // TANDAI DI AWAL — krusial
    order_.push_back(u);

    for (int v : adj[u]) {
        if (!visited[v]) dfs(v);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    // Step 1: Bangun adjacency list DUA ARAH (undirected)
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Step 2: Sort agar tetangga bernomor kecil dikunjungi lebih dulu
    for (int i = 1; i <= n; i++) sort(adj[i].begin(), adj[i].end());

    // Step 3: DFS dari node 1
    dfs(1);

    for (int i = 0; i < (int)order_.size(); i++) {
        cout << order_[i] << " \n"[i + 1 == (int)order_.size()];
    }

    return 0;
}
