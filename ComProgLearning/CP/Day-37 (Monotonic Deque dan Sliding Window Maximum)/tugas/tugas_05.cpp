/*
============================================================
📋 TUGAS 05: Sliding Window Maximum dengan Queries
============================================================
Source: Original
Difficulty: Medium
Topics: deque, sliding window, offline

PROBLEM:
Diberikan array A dan q query. Setiap query: (l, r, k) → cari maximum
dalam setiap window berukuran k pada subarray A[l..r].

INPUT FORMAT:
- Baris 1: integer n
- Baris 2: n integer (array A)
- Baris 3: integer q
- q baris: tiga integer l, r, k

OUTPUT FORMAT:
- Untuk setiap query: (r-l+1-k+1) integer dipisah spasi

CONSTRAINTS:
- 1 ≤ n ≤ 10^4
- 1 ≤ q ≤ 100
- 1 ≤ l ≤ r ≤ n, 1 ≤ k ≤ r-l+1

SAMPLE INPUT 1:
8
1 3 -1 -3 5 3 6 7
2
1 8 3
3 6 2

SAMPLE OUTPUT 1:
3 3 5 5 6 7
-1 -3 5 5

SAMPLE INPUT 2:
5
4 3 1 2 5
1
1 5 2

SAMPLE OUTPUT 2:
4 3 2 5

NOTE: Untuk tiap query, jalankan sliding window max pada A[l-1..r-1].
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
