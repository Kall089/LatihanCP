/*
============================================================
📋 TUGAS 14: Minimum Spanning Tree (Kruskal)
============================================================
Source: Original
Difficulty: Hard
Topics: edge list, Kruskal, Disjoint Set Union (DSU), MST

PROBLEM:
Diberikan n kota dan m rencana jalan dengan biaya masing-masing.
Cari biaya minimum untuk menghubungkan semua kota (Minimum Spanning Tree).
Jika tidak mungkin (graph tidak connected), cetak -1.
Cetak juga edge-edge yang terpilih.

INPUT FORMAT:
- Baris 1: dua integer n dan m
- m baris berikutnya: tiga integer u v w (jalan u-v berbiaya w)

OUTPUT FORMAT:
- "MST Cost: C" (atau -1 jika tidak connected)
- "Edge yang dipakai:" lalu setiap edge dalam format "U-V (w=W)" (sorted by weight)

CONSTRAINTS:
- 1 ≤ n ≤ 10^5
- 1 ≤ m ≤ 2×10^5
- 1 ≤ w ≤ 10^9

SAMPLE INPUT 1:
4 5
1 2 4
1 3 2
2 3 1
2 4 5
3 4 3

SAMPLE OUTPUT 1:
MST Cost: 6
Edge yang dipakai:
2-3 (w=1)
1-3 (w=2)
3-4 (w=3)

SAMPLE INPUT 2:
3 1
1 2 5

SAMPLE OUTPUT 2:
-1

NOTE: Kruskal: sort edges by weight, lalu iterate menggunakan DSU.
      Tambahkan edge jika kedua endpoint berada di komponen berbeda.
      MST valid jika tepat n-1 edge terpilih.
      DSU: path compression + union by rank untuk O(α(n)) per operasi.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kruskal MST dengan edge list + DSU
    return 0;
}
