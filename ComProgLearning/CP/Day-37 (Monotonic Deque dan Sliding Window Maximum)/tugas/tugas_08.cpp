/*
============================================================
📋 TUGAS 08: Level Order Zigzag
============================================================
Source: Original
Difficulty: Medium
Topics: BFS, queue, tree

PROBLEM:
Diberikan binary tree. Cetak node secara level order, tetapi alternating:
level genap dari kiri ke kanan, level ganjil dari kanan ke kiri.

INPUT FORMAT:
- Baris 1: integer n (jumlah node)
- Baris 2: n nilai node dalam level order (-1 = null)

OUTPUT FORMAT:
- Satu baris per level, nilai dipisah spasi

CONSTRAINTS:
- 1 ≤ n ≤ 1000

SAMPLE INPUT 1:
7
3 9 20 -1 -1 15 7

SAMPLE OUTPUT 1:
3
20 9
15 7

SAMPLE INPUT 2:
5
1 2 3 4 5

SAMPLE OUTPUT 2:
1
3 2
4 5

NOTE: Gunakan deque untuk BFS. Saat level ganjil, print secara terbalik.
      Atau gunakan deque: level genap → push_front, level ganjil → push_back.
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
