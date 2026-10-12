/*
============================================================
📋 TUGAS 06: BFS Grid — Jarak Terpendek di Labirin
============================================================
Source: Original
Difficulty: Medium
Topics: BFS grid, 4-arah, shortest path

PROBLEM:
Diberikan grid R×C yang merepresentasikan labirin:
  '.' = bisa dilalui
  '#' = tembok
  'S' = posisi awal (tepat 1)
  'T' = posisi tujuan (tepat 1)

Gerak: 4 arah (atas, bawah, kiri, kanan).
Cetak jumlah langkah minimum dari S ke T.
Jika tidak ada jalur, cetak -1.

INPUT FORMAT:
- Baris 1: dua integer R, C
- R baris berikutnya: string panjang C (grid)

OUTPUT FORMAT:
- Satu integer: jumlah langkah minimum, atau -1

CONSTRAINTS:
- 1 ≤ R, C ≤ 1000
- Dijamin ada tepat satu 'S' dan satu 'T'

SAMPLE INPUT 1:
5 9
#########
#S.....T#
#.#####.#
#.......#
#########

SAMPLE OUTPUT 1:
6

SAMPLE INPUT 2:
3 5
S####
#####
####T

SAMPLE OUTPUT 2:
-1

NOTE: BFS pada grid identik dengan BFS pada graph.
      Setiap sel = node, setiap langkah = edge berbobot 1.
      Cek batas dan tembok sebelum push ke queue.
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
