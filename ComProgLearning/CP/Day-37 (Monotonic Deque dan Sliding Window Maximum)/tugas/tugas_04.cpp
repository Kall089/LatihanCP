/*
============================================================
📋 TUGAS 04: Antrian Bank dengan Prioritas
============================================================
Source: Original
Difficulty: Easy
Topics: queue, priority queue

PROBLEM:
Bank punya n nasabah dengan waktu kedatangan dan durasi layanan.
Proses nasabah yang sudah tiba (arrival <= waktu_sekarang) berdasarkan
durasi terpendek (Shortest Job First). Jika sama, urut arrival.
Hitung rata-rata waiting time.

INPUT FORMAT:
- Baris 1: integer n
- n baris: "arrival duration" per nasabah

OUTPUT FORMAT:
- Satu baris: rata-rata waiting time (2 desimal)

CONSTRAINTS:
- 1 ≤ n ≤ 100
- 0 ≤ arrival ≤ 1000, 1 ≤ duration ≤ 100

SAMPLE INPUT 1:
3
0 4
1 3
2 2

SAMPLE OUTPUT 1:
3.00

SAMPLE INPUT 2:
2
0 5
0 2

SAMPLE OUTPUT 2:
2.50

NOTE: Sort arrival, gunakan priority_queue<pair<int,int>, min-heap> untuk SJF.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO
    return 0;
}
