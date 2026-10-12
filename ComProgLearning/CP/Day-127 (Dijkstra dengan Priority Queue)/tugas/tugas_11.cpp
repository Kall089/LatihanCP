/*
============================================================
📋 TUGAS 11: Paths and Trees (Shortest Path Tree Termurah)
============================================================
Source: CF 545E
Difficulty: Hard
Topics: shortest path tree, tie-break bobot

PROBLEM:
Graf TAK BERARAH berbobot. Di antara semua shortest path tree berakar di
simpul S, cari yang TOTAL BOBOT EDGE-nya paling kecil. Cetak total bobotnya
lalu nomor-nomor edge yang dipakai (sesuai urutan input).

INPUT FORMAT:
- Baris 1: N M
- M baris: u v w
- Baris terakhir: S

OUTPUT FORMAT:
- Baris 1: total bobot (long long)
- Baris 2: N-1 nomor edge

CONSTRAINTS:
- 2 <= N <= 3*10^5, N-1 <= M <= 3*10^5, 1 <= w <= 10^9

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
3 3                    2
1 2 1                  1 2
2 3 1
1 3 2
1

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
4 4                    4
1 2 1                  1 2 3
2 3 1
3 4 2
1 4 4
1

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
2 1                    5
1 2 5                  1
1
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // Jalankan Dijkstra biasa. Untuk setiap v, di antara semua edge (u,v,w)
    // yang memenuhi dist[u] + w == dist[v], pilih yang w-nya TERKECIL.
    // Kenapa greedy per simpul ini optimal? Karena pilihan untuk satu simpul
    // tidak memengaruhi pilihan untuk simpul lain -- dist sudah tetap.
    return 0;
}
