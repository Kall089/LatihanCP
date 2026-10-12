/*
============================================================
📋 TUGAS 08: Multi-source BFS — Api Menyebar
============================================================
Source: Original
Difficulty: Medium
Topics: multi-source BFS, grid, simulation

PROBLEM:
Diberikan grid R×C:
  '.' = tanah kosong
  '#' = tembok (tidak bisa dilewati api)
  'F' = api (bisa ada lebih dari 1)

Api menyebar 4 arah setiap menit. Tembok tidak bisa dibakar.
Untuk setiap sel kosong ('.'), cetak berapa menit sampai
sel tersebut terbakar. Jika tidak terjangkau (karena tembok),
cetak -1.

Cetak seluruh grid dengan nilai waktu (atau -1 atau '#').

INPUT FORMAT:
- Baris 1: dua integer R, C
- R baris berikutnya: string grid

OUTPUT FORMAT:
- R baris, C nilai per baris, dipisah spasi
  Nilai: waktu terbakar (>= 0), atau -1 (tidak terbakar), atau '#'

CONSTRAINTS:
- 1 ≤ R, C ≤ 500
- Setidaknya ada satu 'F'

SAMPLE INPUT 1:
4 5
..F..
.....
..#..
.....

SAMPLE OUTPUT 1:
2 1 0 1 2
3 2 1 2 3
4 3 # 3 4
5 4 3 4 5

SAMPLE INPUT 2:
2 3
F#F
...

SAMPLE OUTPUT 2:
0 # 0
1 -1 1

NOTE: Multi-source BFS: masukkan SEMUA sel 'F' ke queue awal.
      Sel '#' tidak pernah dimasukkan ke queue.
      Jawaban untuk '#' adalah '#', bukan angka.
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
