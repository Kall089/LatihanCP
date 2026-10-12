/*
============================================================
📋 TUGAS 14: Sliding Window Median
============================================================
Source: Original
Difficulty: Hard
Topics: deque, two heaps, sliding window

PROBLEM:
Diberikan array A dan window size k. Untuk setiap window berukuran k,
cetak median. Jika k genap, median = rata-rata dua elemen tengah.

INPUT FORMAT:
- Baris 1: dua integer n dan k
- Baris 2: n integer

OUTPUT FORMAT:
- (n-k+1) nilai median, format: integer jika bulat, "x.5" jika setengah

CONSTRAINTS:
- 1 ≤ k ≤ n ≤ 10^4
- 1 ≤ A[i] ≤ 10^9

SAMPLE INPUT 1:
7 3
1 3 -1 -3 5 3 6

SAMPLE OUTPUT 1:
1 -1 -1 3 5

SAMPLE INPUT 2:
6 2
1 2 3 4 5 6

SAMPLE OUTPUT 2:
1.5 2.5 3.5 4.5 5.5

NOTE: Gunakan dua priority queue (max-heap untuk bawah, min-heap untuk atas).
      Untuk remove elemen keluar window: gunakan lazy deletion.
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
