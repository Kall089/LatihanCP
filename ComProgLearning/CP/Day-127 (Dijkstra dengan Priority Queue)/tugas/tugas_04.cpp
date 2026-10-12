/*
============================================================
📋 TUGAS 04: Path With Minimum Effort
============================================================
Source: LC 1631
Difficulty: Medium
Topics: minimax di grid

PROBLEM:
Grid R x C berisi ketinggian. Dari (1,1) ke (R,C), bergerak 4 arah. "Usaha"
sebuah jalur adalah SELISIH ketinggian terbesar antara dua sel bersebelahan
di sepanjang jalur. Cari usaha minimum.

INPUT FORMAT:
- Baris 1: R C
- R baris berisi C bilangan

OUTPUT FORMAT:
- satu bilangan

CONSTRAINTS:
- 1 <= R, C <= 100, 0 <= tinggi <= 10^6

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
3 3                    2
1 2 2
3 8 2
5 3 5

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
1 3                    2
1 2 3

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
2 2                    0
5 5
5 5
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // nd = max(dist[u], |h[u]-h[v]|). Simpul = sel, id = r*C + c.
    // Bandingkan juga dengan pendekatan binary search + BFS.
    return 0;
}
