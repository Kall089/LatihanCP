/*
============================================================
📋 TUGAS 07: BFS Shortest Path
============================================================
Source: Original
Difficulty: Medium
Topics: BFS, queue, shortest path

PROBLEM:
Diberikan graph tidak berarah tidak berbobot. Untuk setiap query (s, t),
temukan panjang path terpendek dari s ke t. Jika tidak ada, cetak -1.

INPUT FORMAT:
- Baris 1: dua integer n dan m
- m baris: dua integer u v (edge)
- Baris berikutnya: integer q
- q baris: dua integer s t

OUTPUT FORMAT:
- q baris: panjang path terpendek

CONSTRAINTS:
- 1 ≤ n ≤ 500, 1 ≤ m ≤ 5000
- 1 ≤ q ≤ 100

SAMPLE INPUT 1:
4 4
1 2
2 3
3 4
1 3
2
1 4
2 4

SAMPLE OUTPUT 1:
3
2

SAMPLE INPUT 2:
3 1
1 2
1
1 3

SAMPLE OUTPUT 2:
-1

NOTE: Jalankan BFS terpisah untuk setiap query. O(q × (V+E)).
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
