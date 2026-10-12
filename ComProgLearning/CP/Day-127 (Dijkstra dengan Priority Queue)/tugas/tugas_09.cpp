/*
============================================================
📋 TUGAS 09: Cheapest Flights Within K Stops
============================================================
Source: LC 787
Difficulty: Medium
Topics: batas hop, Bellman-Ford berlapis

PROBLEM:
N kota, penerbangan berbiaya. Cari biaya termurah dari src ke dst dengan
paling banyak K transit (yaitu paling banyak K+1 penerbangan). Cetak -1 jika
tidak mungkin.

INPUT FORMAT:
- Baris 1: N M src dst K
- M baris: u v w

OUTPUT FORMAT:
- satu bilangan

CONSTRAINTS:
- 1 <= N <= 100, 0 <= M <= N*(N-1), 0 <= K < N

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
4 4 1 4 1              700
1 2 100
2 4 600
1 3 200
3 4 200

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
4 4 1 4 2              400
1 2 100
2 4 600
1 3 200
3 4 200

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
3 1 1 3 5              -1
1 2 100
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // Bellman-Ford dengan TEPAT K+1 putaran, memakai salinan dist tiap putaran
    // (kalau tidak, satu putaran bisa memakai hasil putaran yang sama).
    // Bandingkan sampel 1 dan 2: batas transit mengubah jawabannya.
    return 0;
}
