/*
============================================================
📋 TUGAS 09: BFS Grid — Hitung Luas Ruangan
============================================================
Source: CSES-inspired (Counting Rooms)
Difficulty: Medium
Topics: BFS grid, connected components, flood fill

PROBLEM:
Diberikan grid R×C:
  '.' = lantai (bisa dilewati)
  '#' = tembok

Setiap kumpulan sel lantai yang terhubung (4-arah)
membentuk sebuah "ruangan".
Hitung:
1. Jumlah ruangan
2. Luas (jumlah sel) ruangan terbesar
3. Luas (jumlah sel) ruangan terkecil

INPUT FORMAT:
- Baris 1: dua integer R, C
- R baris berikutnya: string grid

OUTPUT FORMAT:
- Baris 1: "Jumlah ruangan: K"
- Baris 2: "Terbesar: X"
- Baris 3: "Terkecil: Y"

CONSTRAINTS:
- 1 ≤ R, C ≤ 1000
- Dijamin ada setidaknya satu '.'

SAMPLE INPUT 1:
5 8
########
#..#...#
####.###
#.......
########

SAMPLE OUTPUT 1:
Jumlah ruangan: 3
Terbesar: 5
Terkecil: 2

SAMPLE INPUT 2:
3 3
...
...
...

SAMPLE OUTPUT 2:
Jumlah ruangan: 1
Terbesar: 9
Terkecil: 9

NOTE: BFS/DFS dari setiap sel '.' yang belum dikunjungi.
      Hitung berapa sel yang dikunjungi tiap BFS = luas ruangan.
      Ini disebut "Flood Fill".
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
