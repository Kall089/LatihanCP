/*
============================================================
📋 TUGAS 13: Dijkstra di Grid Berbobot dengan Teleport
============================================================
Source: Varian kontes
Difficulty: Hard
Topics: model graf dari grid + edge khusus

PROBLEM:
Grid R x C. Setiap sel punya biaya masuk. Bergerak 4 arah membayar biaya sel
tujuan. Selain itu ada T pasang portal (r1,c1) <-> (r2,c2) yang bisa dilewati
dengan biaya P (dua arah). Cari biaya minimum dari (1,1) ke (R,C).
Biaya sel awal TIDAK dihitung.

INPUT FORMAT:
- Baris 1: R C T P
- R baris berisi C bilangan
- T baris: r1 c1 r2 c2

OUTPUT FORMAT:
- satu bilangan

CONSTRAINTS:
- 1 <= R, C <= 500; 0 <= T <= 10^5; biaya sel, P <= 10^9

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
2 2 0 0                3
0 1
2 2

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
2 2 1 0                0
0 100
100 100
1 1 2 2

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
1 3 0 0                5
0 2 3
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // id(r,c) = r*C + c. Portal = edge tambahan biasa, tidak perlu perlakuan
    // istimewa -- itulah gunanya memodelkan grid sebagai graf.
    return 0;
}
