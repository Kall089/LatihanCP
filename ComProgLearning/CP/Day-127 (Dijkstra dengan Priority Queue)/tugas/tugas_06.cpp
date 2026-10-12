/*
============================================================
📋 TUGAS 06: Investigation
============================================================
Source: CSES 1202
Difficulty: Medium
Topics: dist + count + minEdge + maxEdge

PROBLEM:
Graf berarah berbobot positif. Cetak empat bilangan: biaya minimum 1 -> N,
banyak jalur berbiaya minimum (mod 10^9+7), jumlah edge paling sedikit di
antara jalur minimum, jumlah edge paling banyak di antaranya.

INPUT FORMAT:
- Baris 1: N M
- M baris: a b c

OUTPUT FORMAT:
- empat bilangan

CONSTRAINTS:
- 1 <= N <= 10^5, 1 <= M <= 2*10^5, 1 <= c <= 10^9

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
4 5                    3 2 1 2
1 4 3
1 2 1
2 4 2
1 3 1
3 4 2

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
2 1                    5 1 1 1
1 2 5

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
3 3                    4 2 1 2
1 3 4
1 2 2
2 3 2
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // baru <  dist[v] -> SALIN semua (cnt, minE = minE[u]+1, maxE = maxE[u]+1)
    // baru == dist[v] -> GABUNG   (cnt +=, minE = min, maxE = max)
    return 0;
}
