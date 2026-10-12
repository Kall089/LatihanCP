/*
 * Day 59 — DFS
 * File  : tugas_06.cpp
 * Topik : Bipartite Check (Pewarnaan 2 Warna)
 * Tingkat: Medium ★★★☆☆
 * -----------------------------------------------
 * Diberikan graph TAK BERARAH dengan N node dan M edge.
 * Tentukan apakah graph BIPARTITE — yaitu apakah semua node bisa diwarnai
 * dengan 2 warna sedemikian sehingga TIDAK ADA edge yang menghubungkan
 * dua node berwarna sama.
 * Cetak "YES" atau "NO".
 *
 * Idea — DFS COLORING:
 *   Beri node awal warna 0. Setiap tetangga harus berwarna kebalikannya (1).
 *   Kalau menemukan tetangga yang sudah berwarna SAMA dengan node sekarang
 *   → tidak bipartite.
 *
 *   bool dfs(int u, int c) {
 *       color[u] = c;
 *       for (int v : adj[u]) {
 *           if (color[v] == -1) { if (!dfs(v, 1 - c)) return false; }
 *           else if (color[v] == c) return false;      ← konflik
 *       }
 *       return true;
 *   }
 *
 * Teorema yang berguna: graph bipartite ⟺ tidak punya cycle berpanjang GANJIL.
 *
 * ⚠️ Graph bisa tidak terhubung — cek SEMUA komponen. Graph bipartite hanya
 *    jika SETIAP komponennya bipartite.
 *
 * Input format  : Baris 1: N dan M
 *                 M baris berikutnya: u dan v
 * Output format : "YES" atau "NO"
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 0 ≤ M ≤ 200.000
 *
 * Sample Input 1:        Sample Output 1:
 * 4 4                    YES
 * 1 2
 * 2 3
 * 3 4
 * 4 1
 *
 * Sample Input 2:        Sample Output 2:
 * 3 3                    NO
 * 1 2
 * 2 3
 * 3 1
 *
 * Sample Input 3:        Sample Output 3:
 * 5 3                    YES
 * 1 2
 * 3 4
 * 4 5
 *
 * NOTE Sample 1: cycle panjang 4 (genap) → bipartite. Warna: 1=A, 2=B,
 *                3=A, 4=B. Tidak ada edge A-A atau B-B.
 * NOTE Sample 2: segitiga = cycle panjang 3 (ganjil) → TIDAK bipartite.
 *                Coba warnai sendiri, pasti selalu konflik.
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int color[MAXN];        // -1 = belum diwarnai, 0 dan 1 = dua warna

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: kerjakan dengan DFS coloring, cek semua komponen

    return 0;
}
