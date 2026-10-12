/*
============================================================
📋 TUGAS 04: Highest Set Bit Position
============================================================
Source: Original
Difficulty: Easy
Topics: bitmask, __builtin_clz, MSB

PROBLEM:
Diberikan T buah bilangan bulat positif N.
Untuk setiap N, cetak posisi (indeks 0-based, dihitung dari kanan)
dari bit tertinggi yang aktif (Most Significant Bit).

INPUT FORMAT:
- Baris 1: integer T
- T baris berikutnya: satu integer N per baris

OUTPUT FORMAT:
- T baris: posisi bit tertinggi untuk setiap N

CONSTRAINTS:
- 1 ≤ T ≤ 100000
- 1 ≤ N ≤ 10^9

SAMPLE INPUT 1:
3
1
8
100

SAMPLE OUTPUT 1:
0
3
6

SAMPLE INPUT 2:
4
2
15
64
1000

SAMPLE OUTPUT 2:
1
3
6
9

NOTE: 1=2^0 → bit 0. 8=2^3 → bit 3. 100=64+32+4=1100100b → bit 6.
      Gunakan: 31 - __builtin_clz(N) untuk N > 0.
      Atau iterasi: int pos=0; while(N>>=1) pos++;
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        // 31 - __builtin_clz(n) gives position of highest set bit (0-indexed)
        cout << (31 - __builtin_clz(n)) << '\n';
    }
    return 0;
}
