/*
============================================================
📋 TUGAS 11: BFS — Deteksi Cycle di Graph Tidak Berarah
============================================================
Source: Original
Difficulty: Medium
Topics: BFS, cycle detection, undirected graph

PROBLEM:
Diberikan graph tidak berarah tidak berbobot dengan n node
dan m edge.
Tentukan apakah graph tersebut mengandung CYCLE atau tidak.

Gunakan BFS: ketika memproses node u dari parent p,
jika ada tetangga v yang sudah dikunjungi dan v != p,
maka ada cycle.

INPUT FORMAT:
- Baris 1: dua integer n, m
- m baris berikutnya: dua integer u v

OUTPUT FORMAT:
- "ADA CYCLE" atau "TIDAK ADA CYCLE"

CONSTRAINTS:
- 1 ≤ n ≤ 10^5
- 0 ≤ m ≤ 2×10^5
- Graph tidak memiliki self-loop

SAMPLE INPUT 1:
4 4
1 2
2 3
3 4
4 2

SAMPLE OUTPUT 1:
ADA CYCLE

SAMPLE INPUT 2:
4 3
1 2
2 3
3 4

SAMPLE OUTPUT 2:
TIDAK ADA CYCLE

NOTE: Untuk graph tidak connected, jalankan BFS dari setiap
      komponen. Simpan parent tiap node saat BFS.
      Jika tetangga v sudah dikunjungi dan v != parent[u] → cycle.
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
