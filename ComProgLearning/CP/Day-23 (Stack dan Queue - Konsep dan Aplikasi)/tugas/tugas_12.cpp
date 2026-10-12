/*
============================================================
📋 TUGAS 12: Priority Queue — Room Allocation
============================================================
Source: CSES-style
Difficulty: Hard
Topics: priority_queue, greedy, sorting

PROBLEM:
Ada N tamu hotel, masing-masing punya waktu check-in dan check-out.
Berapa jumlah MINIMUM kamar yang dibutuhkan agar semua tamu bisa
ditampung? (Tamu dengan check-out = x dan check-in = x BISA pakai
kamar yang sama, karena checkout dulu baru checkin)

INPUT:
- Baris pertama: integer N
- N baris berikutnya: dua integer arrive_i dan depart_i

OUTPUT:
- Satu integer: jumlah minimum kamar

CONSTRAINTS:
- 1 ≤ N ≤ 200,000
- 1 ≤ arrive < depart ≤ 1,000,000,000

SAMPLE INPUT:
3
1 5
2 4
6 8

SAMPLE OUTPUT:
2

SAMPLE INPUT 2:
4
1 3
2 5
4 7
6 8

SAMPLE OUTPUT 2:
2
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Hint: Sort by arrival. Min heap stores departure times of active rooms.
    //       For each guest: if min_departure <= arrival → reuse room (pop, push new departure)
    //       Else: allocate new room (push departure). Answer = max heap size ever.

    return 0;
}
