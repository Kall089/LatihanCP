/*
============================================================
📋 Tugas 09: Find Minimum in Rotated Sorted Array (LeetCode 153)
============================================================
Day: 48 | Difficulty: Medium
Topic: Binary Search Rotated Array

PROBLEM STATEMENT:
Diberikan array A berukuran N terurut ascending tanpa duplikat, tetapi telah
di-rotate antara 1 hingga N kali.
Cari nilai ELEMEN MINIMUM dari array tersebut dalam O(log N).

INPUT FORMAT:
- Baris 1: N
- Baris 2: N integer A[i]

OUTPUT FORMAT:
- Satu integer: nilai minimum di A.

CONSTRAINTS:
- 1 ≤ N ≤ 100.000
- -10^9 ≤ A[i] ≤ 10^9

SAMPLE INPUT 1:
5
3 4 5 1 2

SAMPLE OUTPUT 1:
1

SAMPLE INPUT 2:
7
4 5 6 7 0 1 2

SAMPLE OUTPUT 2:
0

HINT:
Bandingkan A[mid] dengan A[high].
Jika A[mid] > A[high], elemen minimum pasti berada di sebelah kanan (low = mid + 1).
Jika A[mid] <= A[high], elemen minimum berada di mid atau sebelah kiri (high = mid).
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

    // TODO: Cari nilai minimum dengan Binary Search

    return 0;
}
