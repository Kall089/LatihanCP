/*
============================================================
📋 TUGAS 15: BFS — Jarak pada Papan Catur (Knight)
============================================================
Source: CSES Shortest Routes / Classic Chess BFS
Difficulty: Medium-Hard
Topics: BFS, implicit graph, 8-arah knight moves

PROBLEM:
Pada papan catur N×N (1-indexed), kuda (knight) berada di
posisi (r1, c1) dan ingin mencapai (r2, c2).
Kuda bergerak dalam pola "L": 8 kemungkinan gerakan.

Hitung jumlah langkah minimum kuda dari (r1,c1) ke (r2,c2).

Gerakan kuda dari (r,c):
  (r±1, c±2) dan (r±2, c±1) — total 8 arah

INPUT FORMAT:
- Baris 1: integer N (ukuran papan N×N)
- Baris 2: empat integer r1, c1, r2, c2 (1-indexed)

OUTPUT FORMAT:
- Satu integer: jumlah langkah minimum

CONSTRAINTS:
- 1 ≤ N ≤ 300
- 1 ≤ r1, c1, r2, c2 ≤ N

SAMPLE INPUT 1:
8
1 1 8 8

SAMPLE OUTPUT 1:
6

SAMPLE INPUT 2:
8
1 1 2 2

SAMPLE OUTPUT 2:
4

SAMPLE INPUT 3:
1
1 1 1 1

SAMPLE OUTPUT 3:
0

NOTE: BFS pada grid N×N dengan 8 gerakan kuda.
      Konversi ke 0-indexed agar lebih mudah, atau tetap 1-indexed
      dengan batas pengecekan 1..N.
      dist[r][c] diinisialisasi -1, dist[r1][c1] = 0.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO
    return 0;
}
