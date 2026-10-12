/*
============================================================
📋 TUGAS 06: All-Pairs Shortest Path (Floyd-Warshall)
============================================================
Source: Original
Difficulty: Medium
Topics: adjacency matrix, Floyd-Warshall, all-pairs shortest path

PROBLEM:
Diberikan graph berarah berbobot dengan n node dan m edge
(bobot bisa negatif). Hitung shortest path untuk semua pasangan (i,j).
Cetak matrix jarak; jika tidak ada path cetak "INF".
Deteksi juga apakah ada negative cycle.

INPUT FORMAT:
- Baris 1: dua integer n dan m
- m baris berikutnya: tiga integer u v w (edge u→v berbobot w)

OUTPUT FORMAT:
- Matriks n×n: baris i kolom j = jarak terpendek dari i ke j, atau "INF"
- Satu baris: "Negative cycle: ADA" atau "Negative cycle: TIDAK"

CONSTRAINTS:
- 1 ≤ n ≤ 200
- 1 ≤ m ≤ n*n
- -10^4 ≤ w ≤ 10^4

SAMPLE INPUT 1:
3 4
1 2 3
1 3 7
2 3 2
3 1 1

SAMPLE OUTPUT 1:
0 3 5
3 0 2
1 4 0
Negative cycle: TIDAK

SAMPLE INPUT 2:
3 3
1 2 1
2 3 -2
3 1 -1

SAMPLE OUTPUT 2:
0 1 -1
INF 0 -2
INF INF 0
Negative cycle: ADA

NOTE: Inisialisasi dist[i][i]=0, dist[i][j]=INF, lalu set edge weights.
      Floyd-Warshall: for k: for i: for j: dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j])
      Negative cycle: setelah algoritma, cek apakah ada dist[i][i] < 0.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
const long long INF = 1e18;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;

    const long long INF = 1e18;
    vector<vector<long long>> dist(n + 1, vector<long long>(n + 1, INF));
    for (int i = 1; i <= n; i++) dist[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], (long long)w);
    }

    // Floyd-Warshall
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (dist[i][k] != INF && dist[k][j] != INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    // Print distance matrix
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j > 1) cout << ' ';
            if (dist[i][j] == INF) cout << "INF";
            else cout << dist[i][j];
        }
        cout << '\n';
    }

    // Detect negative cycle: dist[i][i] < 0 for any i
    bool negCycle = false;
    for (int i = 1; i <= n; i++)
        if (dist[i][i] < 0) { negCycle = true; break; }
    cout << "Negative cycle: " << (negCycle ? "ADA" : "TIDAK") << '\n';
    return 0;
}
