/*
 * Day 59 — DFS
 * File  : tugas_07.cpp
 * Topik : Rekonstruksi Jalur dengan DFS
 * Tingkat: Medium ★★★☆☆
 * -----------------------------------------------
 * Diberikan graph TAK BERARAH dengan N node dan M edge, serta node S dan T.
 * Cetak SATU jalur dari S ke T (tidak harus terpendek), sebagai urutan node
 * dipisah spasi. Jika tidak ada jalur, cetak "IMPOSSIBLE".
 *
 * Idea — simpan PARENT saat DFS:
 *   Saat dfs masuk dari u ke v, catat par[v] = u.
 *   Setelah DFS selesai, telusuri mundur dari T:
 *       T → par[T] → par[par[T]] → ... → S
 *   lalu balik hasilnya.
 *
 * ⚠️ DFS TIDAK menjamin jalur terpendek. Kalau soal minta jalur TERPENDEK,
 *    kamu harus pakai BFS (Day 58). Soal ini sengaja hanya minta jalur
 *    apa saja, agar kamu merasakan perbedaannya.
 *
 * Aturan tie-break agar deterministik: sort tiap adjacency list menaik.
 *
 * Input format  : Baris 1: N, M, S, T
 *                 M baris berikutnya: u dan v
 * Output format : urutan node dari S ke T, atau "IMPOSSIBLE"
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 0 ≤ M ≤ 200.000
 *
 * Sample Input 1:        Sample Output 1:
 * 5 4 1 5                1 2 3 4 5
 * 1 2
 * 2 3
 * 3 4
 * 4 5
 *
 * Sample Input 2:        Sample Output 2:
 * 4 2 1 4                IMPOSSIBLE
 * 1 2
 * 3 4
 *
 * Sample Input 3:        Sample Output 3:
 * 3 0 2 2                2
 *
 * NOTE Sample 3: S == T, jalurnya hanya berisi satu node.
 * NOTE Sample 1: rantai lurus, jalur unik.
 *
 * HINT: Untuk graph yang punya banyak jalur, jawabanmu bisa berbeda dari
 *       jalur terpendek — itu tetap diterima selama jalurnya valid
 *       (setiap pasangan berurutan benar-benar terhubung edge).
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
bool visited[MAXN];
int par[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: DFS dari S sambil mencatat parent, lalu rekonstruksi mundur dari T

    return 0;
}
