/*
============================================================
📋 TUGAS 08: Sliding Window Maximum (Stack-based)
============================================================
Source: Original
Difficulty: Medium
Topics: stack, deque, sliding window

PROBLEM:
Diberikan array A dan integer k. Untuk setiap window berukuran k,
cetak elemen maksimum di window tersebut.

INPUT FORMAT:
- Baris 1: dua integer n dan k
- Baris 2: n integer (array A)

OUTPUT FORMAT:
- (n-k+1) integer (maksimum tiap window)

CONSTRAINTS:
- 1 ≤ k ≤ n ≤ 10^5
- 1 ≤ A[i] ≤ 10^9

SAMPLE INPUT 1:
8 3
1 3 -1 -3 5 3 6 7

SAMPLE OUTPUT 1:
3 3 5 5 6 7

SAMPLE INPUT 2:
5 2
4 3 1 2 5

SAMPLE OUTPUT 2:
4 3 2 5

NOTE: Gunakan deque (double-ended queue) untuk O(n) solution.
      Jaga deque dalam keadaan monotonic decreasing.
      Front deque selalu merupakan index maksimum window saat ini.
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
