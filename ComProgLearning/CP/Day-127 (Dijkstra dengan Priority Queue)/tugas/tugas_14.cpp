/*
============================================================
📋 TUGAS 14: Dijkstra dengan Waktu Tunggu (Jadwal Kereta)
============================================================
Source: Varian kontes
Difficulty: Hard
Topics: bobot yang bergantung waktu kedatangan

PROBLEM:
N stasiun, M rute. Rute i berangkat dari u pada waktu t, t+p, t+2p, ...
dan memakan waktu d untuk sampai di v. Kamu berada di stasiun 1 pada waktu 0.
Cari waktu paling awal untuk sampai di stasiun N. Cetak -1 jika tidak bisa.

INPUT FORMAT:
- Baris 1: N M
- M baris: u v t p d

OUTPUT FORMAT:
- satu bilangan

CONSTRAINTS:
- 1 <= N <= 10^5, 1 <= M <= 2*10^5, 0 <= t, p, d <= 10^9

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
2 1                    15
1 2 5 10 10

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
2 1                    10
1 2 0 10 10

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
3 1                    -1
1 2 0 1 1
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // Bobot bergantung waktu: keberangkatan paling awal >= dist[u] adalah
    //     t + ceil(max(0, dist[u]-t) / p) * p
    // Dijkstra tetap benar karena fungsi kedatangan MONOTON dan tidak pernah
    // mengurangi waktu (tiba >= berangkat >= dist[u]) -- ini syarat yang sama
    // dengan "bobot non-negatif", hanya dinyatakan lebih umum.
    // Hati-hati p = 0 (hanya ada satu keberangkatan).
    return 0;
}
