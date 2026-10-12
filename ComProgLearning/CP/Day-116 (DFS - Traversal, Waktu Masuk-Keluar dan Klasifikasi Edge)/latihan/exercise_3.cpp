/*
 * Day 59 — DFS (Depth-First Search)
 * File  : exercise_3.cpp
 * Topik : Deteksi Cycle pada Graph TAK BERARAH
 * -----------------------------------------------
 * Diberikan graph TAK BERARAH dengan N node dan M edge (bisa tidak terhubung).
 * Tentukan apakah graph mengandung CYCLE (siklus).
 * Cetak "YES" jika ada cycle, "NO" jika tidak ada.
 *
 * Idea — CEK PARENT:
 *   Saat DFS dari node u ke tetangga v:
 *     - Kalau v belum dikunjungi → rekursi biasa (tree edge)
 *     - Kalau v SUDAH dikunjungi DAN v bukan parent u → ada jalan lain
 *       menuju v → CYCLE!
 *
 *   bool dfs(int u, int parent) {
 *       visited[u] = true;
 *       for (int v : adj[u]) {
 *           if (!visited[v]) { if (dfs(v, u)) return true; }
 *           else if (v != parent) return true;      ← back edge
 *       }
 *       return false;
 *   }
 *
 * Mengapa perlu cek parent? Karena pada graph tak berarah, edge u—v tercatat
 * di kedua adjacency list. Saat memproses v, kita PASTI melihat u yang sudah
 * dikunjungi — tapi itu bukan cycle, itu hanya edge yang sama dilihat balik.
 *
 * ⚠️ Graph bisa punya beberapa komponen — cek SEMUA node sebagai start.
 *
 * Input format  : Baris 1: N dan M
 *                 M baris berikutnya: u dan v
 * Output format : "YES" atau "NO"
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 0 ≤ M ≤ 200.000
 *                 Tidak ada self-loop maupun multi-edge.
 *
 * Sample Input 1:        Sample Output 1:
 * 4 4                    YES
 * 1 2
 * 2 3
 * 3 4
 * 4 1
 *
 * Sample Input 2:        Sample Output 2:
 * 4 3                    NO
 * 1 2
 * 2 3
 * 3 4
 *
 * Sample Input 3:        Sample Output 3:
 * 6 4                    YES
 * 1 2
 * 4 5
 * 5 6
 * 6 4
 *
 * NOTE Sample 1: 1-2-3-4-1 membentuk siklus.
 * NOTE Sample 2: rantai lurus, tidak ada siklus (ini sebuah pohon).
 * NOTE Sample 3: siklus ada di komponen KEDUA {4,5,6} — kalau kamu hanya
 *                DFS dari node 1, kamu akan melewatkannya.
 *
 * HINT: Alternatif tanpa DFS — graph tak berarah punya cycle jika dan hanya
 *       jika M ≥ N − (jumlah komponen). Pakai itu untuk verifikasi silang.
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
bool visited[MAXN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
    }

    return 0;
}
