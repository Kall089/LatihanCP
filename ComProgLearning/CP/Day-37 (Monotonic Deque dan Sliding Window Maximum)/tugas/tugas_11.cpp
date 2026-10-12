/*
============================================================
📋 TUGAS 11: Deque untuk DP Optimization
============================================================
Source: Original
Difficulty: Hard
Topics: deque, DP, optimization

PROBLEM:
Diberikan array A. Temukan nilai minimum dari:
  min over 0<=i<j<=n: (j - i) * A[j] + A[i]
  di mana i < j.

INPUT FORMAT:
- Baris 1: integer n
- Baris 2: n integer (array A)

OUTPUT FORMAT:
- Satu baris: long long (nilai minimum)

CONSTRAINTS:
- 2 ≤ n ≤ 10^5
- 1 ≤ A[i] ≤ 10^9

SAMPLE INPUT 1:
4
1 3 2 4

SAMPLE OUTPUT 1:
3

SAMPLE INPUT 2:
3
5 1 3

SAMPLE OUTPUT 2:
3

NOTE: Brute force O(n^2). Coba optimasi dengan convex hull trick atau deque.
      Untuk tiap j, cari i yang meminimalkan A[i] - i*A[j] + j*A[j].
      Ini adalah linear optimization problem.
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
