/*
 * Day 59 — DFS
 * File  : tugas_05.cpp
 * Topik : Ukuran Subtree Setiap Node
 * Tingkat: Easy ★★☆☆☆
 * -----------------------------------------------
 * Diberikan POHON dengan N node berakar di node 1. Untuk setiap node u,
 * hitung ukuran subtree yang berakar di u (termasuk u sendiri).
 *
 * Cetak N bilangan: size[1], size[2], ..., size[N], dipisah spasi.
 *
 * Ini adalah pola DFS POST-ORDER yang paling fundamental:
 *
 *   void dfs(int u, int parent) {
 *       size[u] = 1;                      ← hitung diri sendiri
 *       for (int v : adj[u])
 *           if (v != parent) {
 *               dfs(v, u);
 *               size[u] += size[v];       ← akumulasi SETELAH anak selesai
 *           }
 *   }
 *
 * Pada pohon, kita tidak perlu array visited — cukup hindari kembali ke
 * parent. (Kalau grafnya bukan pohon, cara ini tidak aman.)
 *
 * Pola ini adalah fondasi Tree DP (Day 99) — kuasai betul.
 *
 * Input format  : Baris 1: N
 *                 N-1 baris berikutnya: u dan v (edge pohon)
 * Output format : N bilangan dipisah spasi
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 Input dijamin membentuk pohon.
 *
 * Sample Input 1:        Sample Output 1:
 * 5                      5 3 1 1 1
 * 1 2
 * 1 3
 * 2 4
 * 2 5
 *
 * Sample Input 2:        Sample Output 2:
 * 1                      1
 *
 * Sample Input 3:        Sample Output 3:
 * 4                      4 3 2 1
 * 1 2
 * 2 3
 * 3 4
 *
 * NOTE Sample 1: struktur pohonnya
 *            1
 *           / \
 *          2   3
 *         / \
 *        4   5
 *      size[1]=5 (semua), size[2]=3 ({2,4,5}), size[3]=size[4]=size[5]=1
 * NOTE Sample 3: rantai lurus — tiap node punya subtree seukuran sisa rantai.
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int subtreeSize[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: kerjakan dengan DFS post-order, akumulasi ukuran dari anak

    return 0;
}
