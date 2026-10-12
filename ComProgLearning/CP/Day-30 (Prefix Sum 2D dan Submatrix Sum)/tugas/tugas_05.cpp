/*
============================================================
📋 TUGAS 05: Hitung Karakter Spesifik pada Peta 2D
============================================================
Source: Original
Difficulty: Easy
Topics: Prefix Sum 2D, Grid Karakter

PROBLEM:
Diberikan grid N × M karakter. Karakter yang tersedia adalah 'A', 'B', dan 'C'.
Untuk Q buah query, kamu diberikan karakter X dan koordinat subgrid (r1, c1) ke (r2, c2).
Hitung berapa banyak karakter X yang ada di dalam subgrid tersebut!

INPUT FORMAT:
- Baris 1: N M Q (1 ≤ N, M ≤ 500, 1 ≤ Q ≤ 10^4)
- N baris berikutnya: string M karakter ('A', 'B', atau 'C')
- Q baris berikutnya: char X dan 4 integer r1 c1 r2 c2

OUTPUT FORMAT:
- Q baris: jumlah kemunculan karakter X di subgrid.

CONSTRAINTS:
- 1 ≤ N, M ≤ 500
- 1 ≤ Q ≤ 10^4

SAMPLE INPUT 1:
3 3 2
ABC
BCA
CAB
A 1 1 3 3
B 1 1 2 2

SAMPLE OUTPUT 1:
3
2

NOTE:
- Peta berisi 3 'A', 3 'B', 3 'C'.
- Subgrid (1,1) ke (2,2) ber-isi [A, B], [B, C] -> 'B' muncul 2 kali.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini

    return 0;
}
