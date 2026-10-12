/*
============================================================
📋 TUGAS 07: Dijkstra Banyak Sumber
============================================================
Source: Klasik
Difficulty: Medium
Topics: multi-source

PROBLEM:
N kota, M jalan tak berarah. Ada K kota yang punya rumah sakit. Untuk setiap
kota, cetak jarak ke rumah sakit TERDEKAT.

INPUT FORMAT:
- Baris 1: N M K
- Baris 2: K nomor kota berumah sakit
- M baris: a b w

OUTPUT FORMAT:
- N bilangan (-1 jika tak terjangkau)

CONSTRAINTS:
- 1 <= N <= 10^5, 1 <= M <= 2*10^5, 1 <= K <= N

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
4 3 2                  0 2 0 3
1 3
1 2 2
2 3 5
3 4 3

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
3 1 1                  0 4 -1
1
1 2 4

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
3 2 3                  0 0 0
1 2 3
1 2 7
2 3 7
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // Push SEMUA sumber di awal dengan dist = 0. Tidak butuh super-source.
    return 0;
}
