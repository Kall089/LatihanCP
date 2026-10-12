/*
 * Day 59 — DFS (Depth-First Search)
 * File  : exercise_4.cpp
 * Topik : Deteksi Cycle pada Graph BERARAH (3-Color)
 * -----------------------------------------------
 * Diberikan graph BERARAH dengan N node dan M edge berarah (u → v).
 * Tentukan apakah graph mengandung CYCLE berarah.
 * Cetak "YES" jika ada cycle, "NO" jika tidak (berarti graph adalah DAG).
 *
 * ⚠️ Cek parent seperti exercise_3 TIDAK BEKERJA di sini!
 *    Contoh: 1→2, 1→3, 2→3. Node 3 dikunjungi dua kali, tapi TIDAK ada cycle.
 *
 * Idea — 3-COLOR (recursion stack):
 *   color[u] = 0 (WHITE) : belum dikunjungi
 *   color[u] = 1 (GRAY)  : sedang diproses, ADA DI RECURSION STACK
 *   color[u] = 2 (BLACK) : selesai total (semua turunannya juga selesai)
 *
 *   bool dfs(int u) {
 *       color[u] = 1;                              ← masuk stack
 *       for (int v : adj[u]) {
 *           if (color[v] == 1) return true;        ← BACK EDGE = CYCLE
 *           if (color[v] == 0 && dfs(v)) return true;
 *           // color[v] == 2 → aman, lewati
 *       }
 *       color[u] = 2;                              ← keluar stack
 *       return false;
 *   }
 *
 * Kenapa BLACK aman? Karena kalau v sudah selesai sepenuhnya, semua node yang
 * bisa dicapai dari v juga sudah selesai — tidak mungkin ada jalur balik ke u.
 *
 * Input format  : Baris 1: N dan M
 *                 M baris berikutnya: u dan v (edge berarah u → v)
 * Output format : "YES" atau "NO"
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 0 ≤ M ≤ 200.000
 *
 * Sample Input 1:        Sample Output 1:
 * 3 3                    YES
 * 1 2
 * 2 3
 * 3 1
 *
 * Sample Input 2:        Sample Output 2:
 * 3 3                    NO
 * 1 2
 * 1 3
 * 2 3
 *
 * Sample Input 3:        Sample Output 3:
 * 5 5                    YES
 * 1 2
 * 2 3
 * 4 5
 * 5 4
 * 3 1
 *
 * NOTE Sample 2: INI KASUS PENTING. Node 3 dikunjungi dari dua jalur berbeda,
 *      tapi tidak ada cycle. Kalau solusimu output YES di sini, berarti kamu
 *      salah memakai cek "sudah dikunjungi" alih-alih cek GRAY.
 *
 * HINT: Untuk graph BERARAH, push edge hanya SATU arah (u → v saja).
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int color[MAXN];    // 0 = WHITE, 1 = GRAY, 2 = BLACK

// TODO: Implementasikan dfs dengan 3-color
// bool dfs(int u) { ... }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca input, bangun adjacency list SATU arah

    // TODO: Loop semua node berwarna WHITE, cek cycle

    return 0;
}
