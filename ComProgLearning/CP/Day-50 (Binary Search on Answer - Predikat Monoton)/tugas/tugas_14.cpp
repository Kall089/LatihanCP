/*
============================================================
📋 Tugas 14: Kth Smallest Pair Distance (LeetCode 719)
============================================================
Day: 50 | Difficulty: Hard
Topic: Binary Search + Two Pointers

PROBLEM STATEMENT:
Jarak antara dua elemen A[i] dan A[j] didefinisikan sebagai |A[i] - A[j]|.
Diberikan array A berukuran N dan integer K.
Cari JARAK KETIGA TERKECIL (K-th smallest distance) di antara semua pasangan (i, j) dengan i < j.

INPUT FORMAT:
- Baris 1: N K
- Baris 2: N integer A[1..N]

OUTPUT FORMAT:
- Satu integer: jarak pasangan ke-K terkecil.

CONSTRAINTS:
- 2 ≤ N ≤ 10.000
- 1 ≤ K ≤ N*(N-1)/2
- 0 ≤ A[i] ≤ 10^6

SAMPLE INPUT 1:
3 1
1 3 1

SAMPLE OUTPUT 1:
0

PENJELASAN SAMPLE 1:
Semua pasangan jarak: |1-3|=2, |1-1|=0, |3-1|=2.
Diurutkan: [0, 2, 2]. Pasangan ke-1 terkecil = 0.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long k;
    if (!(cin >> n >> k)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // TODO: Sort A, binary search pada jarak mid, gunakan Two Pointers di check(mid)

    return 0;
}
