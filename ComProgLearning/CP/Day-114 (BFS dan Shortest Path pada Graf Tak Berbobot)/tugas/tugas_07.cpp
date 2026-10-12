/*
============================================================
📋 TUGAS 07: Hitung Jumlah Komponen Terhubung
============================================================
Source: Original
Difficulty: Medium
Topics: BFS, connected components, graph traversal

PROBLEM:
Diberikan graph tidak berarah tidak berbobot dengan n node
dan m edge (graph bisa tidak connected).
Hitung jumlah komponen terhubung (connected components).
Untuk setiap komponen, cetak ukurannya (jumlah node).
Urutkan ukuran komponen dari terbesar ke terkecil.

INPUT FORMAT:
- Baris 1: dua integer n, m
- m baris berikutnya: dua integer u v

OUTPUT FORMAT:
- Baris 1: "Jumlah komponen: K"
- K baris berikutnya: ukuran tiap komponen (descending)

CONSTRAINTS:
- 1 ≤ n ≤ 10^5
- 0 ≤ m ≤ 2×10^5

SAMPLE INPUT 1:
7 4
1 2
2 3
4 5
6 7

SAMPLE OUTPUT 1:
Jumlah komponen: 3
3
2
2

SAMPLE INPUT 2:
5 0

SAMPLE OUTPUT 2:
Jumlah komponen: 5
1
1
1
1
1

NOTE: Lakukan BFS dari setiap node yang belum dikunjungi.
      Setiap BFS yang baru dimulai = komponen baru.
      Hitung berapa node yang dikunjungi tiap BFS.
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
