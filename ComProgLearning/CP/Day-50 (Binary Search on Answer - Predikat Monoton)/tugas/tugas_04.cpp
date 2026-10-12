/*
============================================================
📋 Tugas 04: Smallest Divisor Given a Threshold (LeetCode 1283)
============================================================
Day: 50 | Difficulty: Medium
Topic: Binary Search on Answer (Pembagi Terkecil)

PROBLEM STATEMENT:
Diberikan array A berukuran N dan integer THRESHOLD.
Tentukan sebuah pembagi bulat D (D > 0) MINIMUM sedemikian hingga jumlah dari ceil(A[i] / D)
untuk seluruh i tidak melebihi THRESHOLD.

INPUT FORMAT:
- Baris 1: N THRESHOLD
- Baris 2: N integer A[i]

OUTPUT FORMAT:
- Satu integer: nilai pembagi D terkecil.

CONSTRAINTS:
- 1 ≤ N ≤ 100.000
- N ≤ THRESHOLD ≤ 10^6
- 1 ≤ A[i] ≤ 10^6

SAMPLE INPUT 1:
4 6
1 2 5 9

SAMPLE OUTPUT 1:
5

PENJELASAN SAMPLE 1:
Dengan D = 5:
ceil(1/5) + ceil(2/5) + ceil(5/5) + ceil(9/5) = 1 + 1 + 1 + 2 = 5 (<= 6).
Jika D = 4, hasilnya 1 + 1 + 2 + 3 = 7 (> 6, tidak valid).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long threshold;
    if (!(cin >> n >> threshold)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // TODO: Binary search pada pembagi D

    return 0;
}
