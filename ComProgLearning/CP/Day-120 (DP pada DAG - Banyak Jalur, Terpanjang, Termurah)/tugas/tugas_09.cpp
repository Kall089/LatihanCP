/*
============================================================
📋 TUGAS 09: Jalur Terpanjang dengan Dua Kriteria
============================================================
Source: Varian kontes
Difficulty: Medium
Topics: DP tuple, tie-break

PROBLEM:
DAG berbobot. Cari jalur 1 -> N dengan total bobot MAKSIMUM; jika seri, pilih
yang jumlah EDGE-nya paling SEDIKIT. Cetak "bobot jumlahEdge", atau -1.

INPUT FORMAT:
- Baris 1: N M
- M baris: u v w

OUTPUT FORMAT:
- dua bilangan, atau -1

CONSTRAINTS:
- 1 <= N <= 10^5, 1 <= M <= 2*10^5, 1 <= w <= 10^9

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
5 6                    9 2
1 2 3
1 3 2
2 4 4
3 4 1
3 5 7
4 5 2

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
3 3                    5 1
1 2 2
2 3 3
1 3 5

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
3 1                    -1
1 2 4
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // Bandingkan pair(bobot, -jumlahEdge) dengan max. Rapi dan bebas bug.
    return 0;
}
