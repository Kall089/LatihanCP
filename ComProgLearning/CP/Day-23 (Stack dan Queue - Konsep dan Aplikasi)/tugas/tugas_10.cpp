/*
============================================================
📋 TUGAS 10: Sliding Window Minimum (Deque)
============================================================
Source: Classic
Difficulty: Medium
Topics: deque, monotonic deque

PROBLEM:
Diberikan array N bilangan dan integer K. Untuk setiap window
berukuran K, cetak elemen TERKECIL di window tersebut.

(Kebalikan dari exercise 5 yang cari maximum)

INPUT:
- Baris pertama: dua integer N dan K
- Baris kedua: N integer

OUTPUT:
- (N-K+1) integer: minimum per window

CONSTRAINTS:
- 1 ≤ K ≤ N ≤ 200,000
- -1,000,000,000 ≤ a[i] ≤ 1,000,000,000

SAMPLE INPUT:
8 3
1 3 -1 -3 5 3 6 7

SAMPLE OUTPUT:
-1 -3 -3 -3 3 3
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Hint: Sama seperti sliding window max, tapi maintain INCREASING deque

    return 0;
}
