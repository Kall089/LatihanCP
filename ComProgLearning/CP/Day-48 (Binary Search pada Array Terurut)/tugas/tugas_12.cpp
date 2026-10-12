/*
============================================================
📋 Tugas 12: Peak Index in a Mountain Array (LeetCode 852)
============================================================
Day: 48 | Difficulty: Medium
Topic: Ternary / Binary Search Peak

PROBLEM STATEMENT:
Diberikan array gunung A berukuran N (N >= 3) di mana elemen naik dari awal
hingga suatu puncak di indeks P, lalu turun dari P hingga akhir.
Cari indeks puncak P dalam O(log N).

INPUT FORMAT:
- Baris 1: N
- Baris 2: N integer A[i]

OUTPUT FORMAT:
- Satu integer: indeks puncak P.

CONSTRAINTS:
- 3 ≤ N ≤ 100.000
- 0 ≤ A[i] ≤ 10^9

SAMPLE INPUT 1:
4
0 2 1 0

SAMPLE OUTPUT 1:
1

SAMPLE INPUT 2:
5
0 10 5 2 0

SAMPLE OUTPUT 2:
1

HINT:
Jika A[mid] < A[mid + 1], puncak berada di sebelah kanan (low = mid + 1).
Jika A[mid] > A[mid + 1], puncak berada di mid atau sebelah kiri (high = mid).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // TODO: Cari indeks puncak dengan Binary Search

    return 0;
}
