/*
 * Day 59 — DFS
 * File  : tugas_10.cpp
 * Topik : Discovery & Finish Time — Cek Ancestor dalam O(1)
 * Tingkat: Medium ★★★★☆
 * -----------------------------------------------
 * Diberikan POHON dengan N node berakar di node 1, dan Q query.
 * Setiap query berisi dua node u dan v.
 * Untuk setiap query, cetak "YES" jika u adalah ANCESTOR dari v
 * (v berada di dalam subtree u), "NO" jika bukan.
 *
 * Catatan: sebuah node dianggap ancestor dari dirinya sendiri.
 *
 * Cara naif (telusuri parent dari v sampai akar) = O(N) per query → TLE.
 *
 * Idea — DISCOVERY & FINISH TIME:
 *   Saat DFS, catat waktu masuk tin[u] dan waktu keluar tout[u]:
 *
 *   void dfs(int u, int p) {
 *       tin[u] = timer++;
 *       for (int v : adj[u]) if (v != p) dfs(v, u);
 *       tout[u] = timer++;
 *   }
 *
 *   Properti kunci — interval [tin[u], tout[u]] dari sebuah node selalu
 *   MEMUAT PENUH interval semua turunannya (nested interval):
 *
 *       u ancestor dari v  ⟺  tin[u] ≤ tin[v] && tout[v] ≤ tout[u]
 *
 *   Sekali DFS O(N), lalu tiap query O(1). Total O(N + Q).
 *
 * Teknik ini adalah fondasi Euler Tour (Day 48), LCA (Day 47),
 * dan HLD (Day 125).
 *
 * Input format  : Baris 1: N dan Q
 *                 N-1 baris berikutnya: u dan v (edge pohon)
 *                 Q baris berikutnya: u dan v (query)
 * Output format : Q baris berisi "YES" atau "NO"
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 1 ≤ Q ≤ 200.000
 *                 Input dijamin membentuk pohon berakar di 1.
 *
 * Sample Input 1:        Sample Output 1:
 * 5 4                    YES
 * 1 2                    YES
 * 1 3                    NO
 * 2 4                    YES
 * 2 5
 * 1 4
 * 2 5
 * 3 4
 * 2 2
 *
 * NOTE Struktur pohon sample:
 *            1
 *           / \
 *          2   3
 *         / \
 *        4   5
 *   query (1,4): 1 adalah akar → ancestor semua node → YES
 *   query (2,5): 5 ada di subtree 2 → YES
 *   query (3,4): 4 TIDAK ada di subtree 3 → NO
 *   query (2,2): node adalah ancestor dirinya sendiri → YES
 *
 * HINT: Kedalaman pohon bisa 2×10^5 (rantai). Rekursi masih aman,
 *       tapi kalau ragu, tulis versi iteratif.
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int tin[MAXN], tout_[MAXN];
int timer_ = 0;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: DFS untuk mengisi tin[] dan tout[], lalu jawab query O(1)

    return 0;
}
