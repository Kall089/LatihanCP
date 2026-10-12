/*
============================================================
📋 TUGAS 15: Investigation (min + count + panjang)
============================================================
Source: CSES 1202 (versi DAG)
Difficulty: Hard
Topics: tiga DP bersamaan

PROBLEM:
DAG berbobot non-negatif. Cetak empat bilangan pada satu baris:
  biaya minimum 1 -> N,
  banyak jalur berbiaya minimum (mod 10^9+7),
  jumlah edge PALING SEDIKIT di antara jalur berbiaya minimum,
  jumlah edge PALING BANYAK di antara jalur berbiaya minimum.

INPUT FORMAT:
- Baris 1: N M
- M baris: u v w

OUTPUT FORMAT:
- empat bilangan

CONSTRAINTS:
- 1 <= N <= 10^5, 1 <= M <= 2*10^5, 1 <= w <= 10^9

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
4 5                    3 2 1 2
1 4 3
1 2 1
2 4 2
1 3 1
3 4 2

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
3 2                    3 1 2 2
1 2 1
2 3 2

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
2 2                    1 1 1 1
1 2 1
1 2 5
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // Empat array: dist, cnt, minE, maxE. Saat baru < dist[v] -> SALIN semua.
    // Saat baru == dist[v] -> GABUNGKAN (cnt +=, minE = min, maxE = max).
    // Perhatikan sampel 1: dua jalur berbiaya 3, satu lewat 1 edge, satu 2 edge.
    return 0;
}
