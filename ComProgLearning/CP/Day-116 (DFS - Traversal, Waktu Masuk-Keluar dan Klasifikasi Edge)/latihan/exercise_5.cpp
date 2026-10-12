/*
 * Day 59 — DFS (Depth-First Search)
 * File  : exercise_5.cpp
 * Topik : Topological Sort dengan DFS Post-Order
 * -----------------------------------------------
 * Diberikan graph BERARAH dengan N node dan M edge (u → v berarti
 * "u harus dikerjakan sebelum v"). Hasilkan satu urutan valid yang
 * memenuhi semua kendala tersebut — TOPOLOGICAL SORT.
 *
 * Jika graph mengandung cycle (tidak mungkin ada urutan valid),
 * cetak "IMPOSSIBLE".
 *
 * Idea — DFS POST-ORDER:
 *   void dfs(int u) {
 *       visited[u] = true;
 *       for (int v : adj[u]) if (!visited[v]) dfs(v);
 *       topo.push_back(u);           ← POST-ORDER: setelah semua turunan
 *   }
 *   ... loop semua node ...
 *   reverse(topo.begin(), topo.end());     ← WAJIB dibalik!
 *
 * Mengapa post-order lalu dibalik?
 *   Node u baru masuk list SETELAH semua node yang bisa dicapai darinya
 *   sudah masuk. Jadi di list, u berada SESUDAH semua turunannya.
 *   Dibalik → u berada SEBELUM semuanya. Persis yang kita inginkan.
 *
 * Untuk deteksi cycle, gabungkan dengan 3-color dari exercise_4.
 *
 * Aturan tie-break: jika ada beberapa jawaban valid, cetak yang mana saja —
 * checker hanya memverifikasi bahwa semua edge terpenuhi. Untuk exercise ini,
 * proses node start dalam urutan menaik (1, 2, 3, ...) dan sort tiap
 * adjacency list agar hasilnya deterministik & cocok dengan sample.
 *
 * Input format  : Baris 1: N dan M
 *                 M baris berikutnya: u dan v (u harus sebelum v)
 * Output format : N bilangan dipisah spasi (urutan topologis),
 *                 atau "IMPOSSIBLE" jika ada cycle
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 0 ≤ M ≤ 200.000
 *
 * Sample Input 1:        Sample Output 1:
 * 6 6                    1 5 3 2 4 6
 * 1 2
 * 1 3
 * 2 4
 * 3 4
 * 4 6
 * 1 5
 *
 * Sample Input 2:        Sample Output 2:
 * 3 3                    IMPOSSIBLE
 * 1 2
 * 2 3
 * 3 1
 *
 * Sample Input 3:        Sample Output 3:
 * 4 0                    4 3 2 1
 *
 * NOTE Sample 1: verifikasi — 1 sebelum 2 ✓, 1 sebelum 3 ✓, 2 sebelum 4 ✓,
 *      3 sebelum 4 ✓, 4 sebelum 6 ✓, 1 sebelum 5 ✓. Semua terpenuhi.
 * NOTE Sample 3: tanpa edge, urutan apa pun valid. Sample output di atas
 *      adalah hasil dari metode post-order + reverse (node terakhir yang
 *      diproses berada di depan). Kalau urutanmu berbeda tapi semua edge
 *      terpenuhi, jawabanmu tetap BENAR — topological sort tidak unik.
 *
 * HINT: Deteksi cycle DULU, baru bangun topological order — atau gabungkan
 *       keduanya dalam satu DFS dengan 3-color.
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int color[MAXN];
vector<int> topo;

// TODO: Implementasikan dfs yang sekaligus deteksi cycle & bangun post-order
// bool dfs(int u) { ... }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca input, bangun adjacency list satu arah, sort tiap list

    // TODO: DFS semua node; jika ketemu cycle cetak IMPOSSIBLE

    // TODO: Balik topo dan cetak

    return 0;
}
