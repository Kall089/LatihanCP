/*
============================================================
📋 TUGAS 12: BFS — Pesan Terkirim (Message Route)
============================================================
Source: CSES Problem Set - Message Route (inspired)
Difficulty: Medium
Topics: BFS, shortest path, path reconstruction

PROBLEM:
Udin ingin mengirim pesan dari node 1 ke node n dalam jaringan
komputer. Jaringan memiliki n komputer dan m koneksi (undirected).
Temukan rute terpendek (dalam jumlah komputer yang dikunjungi)
dari komputer 1 ke komputer n.

Cetak jumlah komputer dalam rute tersebut, lalu cetak node-nodenya.
Jika tidak ada rute, cetak "IMPOSSIBLE".

INPUT FORMAT:
- Baris 1: dua integer n, m
- m baris berikutnya: dua integer u v (koneksi)

OUTPUT FORMAT:
- Jika ada path: baris 1 = panjang rute (jumlah komputer),
  baris 2 = node-node dari 1 ke n dipisah spasi
- Jika tidak ada: "IMPOSSIBLE"

CONSTRAINTS:
- 2 ≤ n ≤ 10^5
- 1 ≤ m ≤ 2×10^5

SAMPLE INPUT 1:
5 5
1 2
1 3
2 4
3 4
4 5

SAMPLE OUTPUT 1:
4
1 2 4 5

SAMPLE INPUT 2:
4 2
1 2
3 4

SAMPLE OUTPUT 2:
IMPOSSIBLE

NOTE: Ini mirip CSES Message Route.
      Panjang rute = dist[n] + 1 (jumlah node, bukan edge).
      Rekonstruksi dengan prev[].
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
