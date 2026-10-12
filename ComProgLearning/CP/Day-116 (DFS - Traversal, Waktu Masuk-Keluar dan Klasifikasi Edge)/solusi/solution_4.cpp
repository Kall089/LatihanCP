/*
 * Day 59 — DFS (Depth-First Search)
 * File  : solution_4.cpp
 * Topik : Deteksi Cycle Graph BERARAH (3-Color) — SOLUSI LENGKAP
 * -----------------------------------------------
 * Pendekatan: DFS dengan pewarnaan 3 status (recursion stack tracking)
 *
 * Idea:
 *   Pada graph BERARAH, "sudah dikunjungi" TIDAK sama dengan "cycle".
 *   Yang menandakan cycle adalah BACK EDGE — edge menuju node yang masih
 *   berada di recursion stack saat ini.
 *
 *   WHITE (0) : belum tersentuh
 *   GRAY  (1) : sedang diproses, ADA DI RECURSION STACK
 *   BLACK (2) : selesai total, beserta seluruh keturunannya
 *
 *   Menemukan tetangga GRAY = kita menemukan jalan kembali ke leluhur
 *   yang masih dalam proses = CYCLE.
 *
 *   Menemukan tetangga BLACK = cabang itu sudah tuntas dijelajahi dan
 *   terbukti tidak menuju balik ke kita = AMAN.
 *
 * Trace sample 1 (1→2, 2→3, 3→1):
 *   color[1]=GRAY → color[2]=GRAY → color[3]=GRAY
 *   dari 3, tetangga 1 berwarna GRAY → CYCLE → YES ✓
 *
 * Trace sample 2 (1→2, 1→3, 2→3) — KASUS PEMBEDA:
 *   color[1]=GRAY → color[2]=GRAY → color[3]=GRAY
 *   3 tidak punya tetangga → color[3]=BLACK
 *   2 selesai → color[2]=BLACK
 *   kembali ke 1, tetangga berikutnya = 3, color[3]==BLACK → AMAN, lewati
 *   color[1]=BLACK → tidak ada cycle → NO ✓
 *
 *   Kalau kita hanya memakai array visited biasa, langkah terakhir akan
 *   dikira cycle → jawaban salah. Inilah alasan 3-color diperlukan.
 *
 * Trace sample 3 (1→2, 2→3, 4→5, 5→4, 3→1):
 *   Dari node 1: 1→2→3→1, saat di 3 tetangga 1 masih GRAY → CYCLE → YES ✓
 *
 * Complexity: O(V + E) time, O(V + E) space
 *
 * Edge cases:
 *   - Self-loop u→u: color[u]==GRAY saat memeriksa dirinya sendiri → cycle ✓
 *   - Graph tidak terhubung → loop semua node WHITE sebagai start
 *   - M=0 → tidak ada cycle
 *   - DAG apapun → NO
 *
 * Alternative approaches:
 *   - Kahn's algorithm (Day 60): hitung in-degree, kalau node yang berhasil
 *     dikeluarkan < N maka ada cycle. Berbasis BFS, tidak ada risiko
 *     stack overflow.
 *   - Boolean array inStack[] terpisah dari visited[] — setara dengan 3-color.
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int color[MAXN];        // 0 = WHITE, 1 = GRAY, 2 = BLACK

bool dfs(int u) {
    color[u] = 1;                       // GRAY — masuk recursion stack

    for (int v : adj[u]) {
        if (color[v] == 1) return true;                 // back edge → CYCLE
        if (color[v] == 0 && dfs(v)) return true;       // rekursi ke WHITE
        // color[v] == 2 (BLACK) → cabang tuntas & aman, lewati
    }

    color[u] = 2;                       // BLACK — keluar recursion stack
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    // Graph BERARAH — push SATU arah saja
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    bool hasCycle = false;
    for (int i = 1; i <= n && !hasCycle; i++) {
        if (color[i] == 0) {
            if (dfs(i)) hasCycle = true;
        }
    }

    cout << (hasCycle ? "YES" : "NO") << "\n";
    return 0;
}
