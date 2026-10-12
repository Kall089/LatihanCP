/*
============================================================
📋 TUGAS 14: Minimum Vertex Cover (Bitmask)
============================================================
Source: Original
Difficulty: Hard
Topics: bitmask enumeration, vertex cover, graph theory

PROBLEM:
Diberikan graph tidak berarah dengan n node (0-indexed) dan m edge.
Cari ukuran MINIMUM Vertex Cover: himpunan node terkecil sedemikian
sehingga setiap edge memiliki setidaknya satu endpoint di dalam himpunan.
Cetak ukurannya.

INPUT FORMAT:
- Baris 1: dua integer n dan m
- m baris berikutnya: dua integer u v (edge antara u dan v)

OUTPUT FORMAT:
- Satu integer: ukuran minimum vertex cover

CONSTRAINTS:
- 1 ≤ n ≤ 20
- 0 ≤ m ≤ n*(n-1)/2

SAMPLE INPUT 1:
4 4
0 1
0 2
1 3
2 3

SAMPLE OUTPUT 1:
2

SAMPLE INPUT 2:
5 5
0 1
1 2
2 3
3 4
4 0

SAMPLE OUTPUT 2:
3

NOTE: Untuk sample 1, vertex cover minimum: {0,3} atau {1,2} (keduanya size 2).
      Untuk sample 2 (siklus genap C5 tidak, ini C5): min cover = 3.
      
      Hint: Iterasi semua 2^n subset sebagai kandidat vertex cover.
      Untuk setiap subset, cek apakah setiap edge ter-cover
      (setidaknya satu endpoint ada di subset). Ambil yang terkecil.
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
