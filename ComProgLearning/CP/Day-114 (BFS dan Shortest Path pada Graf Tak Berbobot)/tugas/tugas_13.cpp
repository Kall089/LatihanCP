/*
============================================================
📋 TUGAS 13: 0-1 BFS — Biaya Minimum di Grid
============================================================
Source: Original (0-1 BFS pattern)
Difficulty: Medium-Hard
Topics: 0-1 BFS, deque, minimum cost

PROBLEM:
Diberikan grid R×C. Setiap sel berisi karakter:
  'A' atau 'B' (dua jenis lantai)

Bergerak dari (0,0) ke (R-1,C-1) dengan 4 arah.
Biaya pindah:
  - Ke sel tipe SAMA: 0
  - Ke sel tipe BERBEDA: 1

Cari biaya minimum untuk mencapai (R-1,C-1) dari (0,0).

INPUT FORMAT:
- Baris 1: dua integer R, C
- R baris berikutnya: string grid

OUTPUT FORMAT:
- Satu integer: biaya minimum

CONSTRAINTS:
- 1 ≤ R, C ≤ 500
- Grid hanya berisi 'A' dan 'B'

SAMPLE INPUT 1:
3 4
AABA
BBAA
ABBA

SAMPLE OUTPUT 1:
1

SAMPLE INPUT 2:
2 2
AB
BA

SAMPLE OUTPUT 2:
1

NOTE: Gunakan deque (0-1 BFS):
  - Biaya 0: push_front
  - Biaya 1: push_back
  Inisialisasi dist semua INF, dist[0][0] = 0.
  Cek: if (dist[r][c] + cost < dist[nr][nc]) update dan push.
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
