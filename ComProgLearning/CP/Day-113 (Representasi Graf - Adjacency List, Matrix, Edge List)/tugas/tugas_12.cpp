/*
============================================================
📋 TUGAS 12: Bellman-Ford Shortest Path
============================================================
Source: Original
Difficulty: Medium
Topics: edge list, Bellman-Ford, negative cycle detection

PROBLEM:
Diberikan graph berarah berbobot (bobot bisa negatif) dengan n node
dan m edge. Implementasikan Bellman-Ford untuk mencari shortest path
dari source s ke semua node lain. Deteksi negative cycle yang reachable
dari s (jika ada, cetak "Negative cycle: ADA").

INPUT FORMAT:
- Baris 1: tiga integer n, m, dan s (source)
- m baris berikutnya: tiga integer u v w (edge u→v berbobot w)

OUTPUT FORMAT:
- n baris: "X: D" (jarak dari s ke X) atau "X: INF" jika tidak reachable
- Satu baris: "Negative cycle: ADA" atau "Negative cycle: TIDAK"

CONSTRAINTS:
- 1 ≤ n ≤ 1000
- 1 ≤ m ≤ 5000
- -10^4 ≤ w ≤ 10^4

SAMPLE INPUT 1:
5 6 1
1 2 -1
1 3 4
2 3 3
2 4 2
2 5 2
4 2 1

SAMPLE OUTPUT 1:
1: 0
2: -1
3: 2
4: 1
5: 1
Negative cycle: TIDAK

SAMPLE INPUT 2:
3 3 1
1 2 1
2 3 -3
3 1 1

SAMPLE OUTPUT 2:
1: 0
2: 1
3: -2
Negative cycle: ADA

NOTE: Bellman-Ford: inisialisasi dist[s]=0, lainnya=INF.
      Ulangi V-1 kali: for each edge (u,v,w): relax(v, dist[u]+w).
      Iterasi ke-V: jika masih ada relaksasi → ada negative cycle.
      Untuk sample 2: 1→2→3→1 membentuk siklus dengan total bobot -1 < 0.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
const long long INF = 1e18;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO
    return 0;
}
