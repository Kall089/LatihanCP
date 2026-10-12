/*
 * Day 59 — DFS
 * File  : tugas_13.cpp
 * Topik : Diameter Pohon dengan DFS
 * Tingkat: Hard ★★★★☆
 * -----------------------------------------------
 * Diberikan POHON dengan N node. DIAMETER pohon adalah panjang jalur
 * TERPANJANG antara dua node mana pun (diukur dalam jumlah edge).
 * Cetak diameternya.
 *
 * Idea — DOUBLE DFS (trik klasik):
 *   1. DFS dari node mana pun (misal node 1), cari node A yang PALING JAUH
 *   2. DFS lagi dari A, cari node B yang paling jauh dari A
 *   3. Jarak(A, B) = diameter
 *
 * Mengapa ini benar? Intuisi: node terjauh dari titik mana pun pasti
 * merupakan salah satu UJUNG dari diameter. Sekali kita memegang satu
 * ujung, mencari yang terjauh darinya memberi ujung yang lain.
 * (Bukti formalnya memakai argumen kontradiksi pada pohon — coba pikirkan.)
 *
 * ⚠️ Trik double-DFS ini HANYA berlaku pada POHON (dan graph berbobot
 *    non-negatif tanpa cycle). Pada graph umum bersiklus, tidak berlaku.
 *
 * Alternatif (satu kali DFS): untuk tiap node u, hitung dua kedalaman
 * anak terbesar; diameter = max(depth1[u] + depth2[u]). Pendekatan ini
 * adalah Tree DP dan akan didalami di Day 99.
 *
 * Input format  : Baris 1: N
 *                 N-1 baris berikutnya: u dan v
 * Output format : satu bilangan — diameter (jumlah edge)
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 Input dijamin membentuk pohon.
 *
 * Sample Input 1:        Sample Output 1:
 * 5                      3
 * 1 2
 * 1 3
 * 2 4
 * 2 5
 *
 * Sample Input 2:        Sample Output 2:
 * 1                      0
 *
 * Sample Input 3:        Sample Output 3:
 * 4                      3
 * 1 2
 * 2 3
 * 3 4
 *
 * NOTE Sample 1: struktur
 *            1
 *           / \
 *          2   3
 *         / \
 *        4   5
 *      Jalur terpanjang: 4 → 2 → 1 → 3 (3 edge), atau 5 → 2 → 1 → 3.
 *      Perhatikan diameter TIDAK harus melewati akar — di sini kebetulan iya.
 * NOTE Sample 2: satu node, tidak ada edge → diameter 0.
 * NOTE Sample 3: rantai lurus 4 node → 3 edge.
 *
 * HINT: Implementasikan satu fungsi dfs(u, parent, depth) yang mengembalikan
 *       node terjauh beserta jaraknya, lalu panggil dua kali.
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: DFS pertama dari node 1 → dapat node A terjauh
    // TODO: DFS kedua dari A → jarak terjauh = diameter

    return 0;
}
