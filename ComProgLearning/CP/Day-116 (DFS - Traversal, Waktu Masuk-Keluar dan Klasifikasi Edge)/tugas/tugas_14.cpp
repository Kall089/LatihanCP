/*
 * Day 59 — DFS
 * File  : tugas_14.cpp
 * Topik : Menambah Edge Minimum agar Graph Terhubung
 * Tingkat: Hard ★★★★☆
 * -----------------------------------------------
 * Diberikan graph TAK BERARAH dengan N node dan M edge.
 * Tentukan jumlah edge MINIMUM yang perlu ditambahkan agar seluruh graph
 * menjadi terhubung, lalu cetak juga edge-edge yang ditambahkan.
 *
 * Baris pertama output: K (jumlah edge yang ditambahkan)
 * K baris berikutnya: sepasang node yang dihubungkan
 *
 * Idea:
 *   Hitung jumlah connected component C dengan DFS.
 *   Untuk menyatukan C komponen menjadi satu, dibutuhkan tepat C − 1 edge.
 *
 *   Cara paling sederhana: simpan satu node PERWAKILAN dari tiap komponen,
 *   lalu hubungkan perwakilan komponen 1 dengan komponen 2, komponen 1
 *   dengan komponen 3, dan seterusnya.
 *
 * Mengapa C − 1 adalah minimum? Setiap edge baru paling banyak mengurangi
 * jumlah komponen sebanyak 1 (karena satu edge hanya bisa menyatukan
 * dua komponen). Dari C komponen menuju 1 komponen, minimal butuh C−1 edge.
 *
 * Input format  : Baris 1: N dan M
 *                 M baris berikutnya: u dan v
 * Output format : Baris 1: K
 *                 K baris berikutnya: pasangan node yang dihubungkan
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 0 ≤ M ≤ 200.000
 *
 * Sample Input 1:        Sample Output 1:
 * 5 2                    2
 * 1 2                    1 3
 * 4 5                    1 4
 *
 * Sample Input 2:        Sample Output 2:
 * 3 0                    2
 *                        1 2
 *                        1 3
 *
 * Sample Input 3:        Sample Output 3:
 * 3 2                    0
 * 1 2
 * 2 3
 *
 * NOTE Sample 1: komponen {1,2}, {3}, {4,5} → 3 komponen → butuh 2 edge.
 *      Jawaban lain juga diterima, misalnya "2 3" dan "3 4", asalkan
 *      hasil akhirnya terhubung dan jumlah edge-nya tepat 2.
 * NOTE Sample 3: sudah terhubung → K = 0, tidak ada baris tambahan.
 *
 * HINT: Soal ini setara dengan CSES 1666 "Building Roads".
 *       Bisa juga diselesaikan dengan DSU (Day 52).
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
bool visited[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: DFS untuk mencari perwakilan tiap komponen,
    //       lalu cetak C-1 edge penghubung

    return 0;
}
