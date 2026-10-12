/*
============================================================
📋 TUGAS 08: LIS sebagai Jalur Terpanjang di DAG
============================================================
Source: Latihan sintesis (jembatan ke Day 148)
Difficulty: Medium
Topics: DAG tersembunyi

PROBLEM:
Diberi array a berukuran N (N <= 2000). Bangun DAG dengan edge i -> j bila
i < j dan a[i] < a[j], lalu cari jalur TERPANJANG (banyak simpul) di DAG itu.
Cetak panjangnya. Itu adalah LIS dari array.

INPUT FORMAT:
- Baris 1: N
- Baris 2: N bilangan

OUTPUT FORMAT:
- satu bilangan

CONSTRAINTS:
- 1 <= N <= 2000, |a[i]| <= 10^9

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
6                      4
1 3 2 5 4 6

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
5                      1
5 4 3 2 1

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
4                      4
1 2 3 4
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // DAG-nya punya O(N^2) edge -- itu sebabnya pendekatan ini hanya untuk
    // N kecil. Day 148 menunjukkan cara O(N log N)-nya.
    return 0;
}
