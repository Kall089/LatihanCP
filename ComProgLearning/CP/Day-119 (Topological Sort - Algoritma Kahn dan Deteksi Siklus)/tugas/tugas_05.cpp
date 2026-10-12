/*
============================================================
📋 TUGAS 05: Topological Sort dengan DFS
============================================================
Source: Latihan implementasi
Difficulty: Easy
Topics: DFS post-order, 3 warna

PROBLEM:
Kerjakan Tugas 03 TANPA memakai Kahn. Gunakan DFS post-order + reverse, dan
deteksi siklus dengan sistem 3 warna.

INPUT FORMAT / OUTPUT FORMAT:
- sama dengan Tugas 03

CONSTRAINTS:
- 1 <= N <= 10^5  (waspadai kedalaman rekursi!)

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
4 3                    1 2 3 4
1 2
2 3
3 4

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
3 3                    IMPOSSIBLE
1 2
2 3
3 1

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
5 2                    (mis.) 5 4 3 1 2
1 2
3 4
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // warna: 0 belum, 1 di stack, 2 selesai. Ketemu warna 1 -> siklus.
    return 0;
}
