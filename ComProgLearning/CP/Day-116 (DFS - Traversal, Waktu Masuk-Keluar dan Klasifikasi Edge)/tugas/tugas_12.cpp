/*
 * Day 59 — DFS
 * File  : tugas_12.cpp
 * Topik : Jalur Terpanjang pada DAG (DP on DAG)
 * Tingkat: Hard ★★★★☆
 * -----------------------------------------------
 * Diberikan DAG (graph berarah tanpa cycle) dengan N node dan M edge.
 * Cari panjang JALUR TERPANJANG dalam graph tersebut, diukur dalam
 * jumlah EDGE yang dilalui.
 *
 * Jalur boleh dimulai dan diakhiri di node mana pun.
 *
 * Idea — DFS + MEMOISASI:
 *   dp[u] = panjang jalur terpanjang yang DIMULAI dari node u
 *
 *   dp[u] = 0                                jika u tidak punya keluar
 *   dp[u] = 1 + max(dp[v]) untuk semua v ∈ adj[u]
 *
 *   int dfs(int u) {
 *       if (dp[u] != -1) return dp[u];       ← memo, jangan hitung ulang
 *       dp[u] = 0;
 *       for (int v : adj[u]) dp[u] = max(dp[u], 1 + dfs(v));
 *       return dp[u];
 *   }
 *
 *   Jawaban = max(dp[u]) untuk semua u.
 *
 * Tanpa memoisasi, kompleksitasnya eksponensial. Dengan memoisasi,
 * setiap node dihitung tepat sekali → O(V + E).
 *
 * Ini adalah jembatan menuju Bulan 4 (Dynamic Programming) — DAG adalah
 * struktur di mana DP bekerja secara alami, karena tidak ada
 * ketergantungan melingkar.
 *
 * ⚠️ Catatan: pada graph BERSIKLUS, "jalur terpanjang" adalah masalah
 *    NP-hard. Sifat DAG-lah yang membuat soal ini bisa diselesaikan
 *    dalam waktu linear.
 *
 * Input format  : Baris 1: N dan M
 *                 M baris berikutnya: u dan v (edge berarah u → v)
 * Output format : satu bilangan — panjang jalur terpanjang (jumlah edge)
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 0 ≤ M ≤ 200.000
 *                 Input dijamin DAG (tidak ada cycle).
 *
 * Sample Input 1:        Sample Output 1:
 * 4 3                    3
 * 1 2
 * 2 3
 * 3 4
 *
 * Sample Input 2:        Sample Output 2:
 * 5 4                    2
 * 1 2
 * 1 3
 * 2 4
 * 3 5
 *
 * Sample Input 3:        Sample Output 3:
 * 3 0                    0
 *
 * NOTE Sample 1: rantai 1→2→3→4 melewati 3 edge.
 * NOTE Sample 2: jalur terpanjang misalnya 1→2→4 = 2 edge.
 * NOTE Sample 3: tidak ada edge → jalur terpanjang 0 edge (satu node saja).
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int dp[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: DFS dengan memoisasi, jawaban = max dp[u]

    return 0;
}
