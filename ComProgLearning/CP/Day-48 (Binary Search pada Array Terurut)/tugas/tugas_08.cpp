/*
============================================================
📋 Tugas 08: Single Element in a Sorted Array (LeetCode 540)
============================================================
Day: 48 | Difficulty: Medium
Topic: Binary Search Parity Check

PROBLEM STATEMENT:
Diberikan array A terurut berukuran N (N selalu ganjil). Setiap elemen di A
muncul tepat 2 kali, KECUALI 1 elemen yang muncul tepat 1 kali.
Cari elemen tunggal tersebut dalam O(log N).

INPUT FORMAT:
- Baris 1: N
- Baris 2: N integer terurut

OUTPUT FORMAT:
- Cetak nilai elemen tunggal tersebut.

CONSTRAINTS:
- 1 ≤ N ≤ 100.000 (N selalu ganjil)
- -10^9 ≤ A[i] ≤ 10^9

SAMPLE INPUT 1:
7
1 1 2 3 3 4 4

SAMPLE OUTPUT 1:
2

SAMPLE INPUT 2:
9
3 3 7 7 10 11 11 12 12

SAMPLE OUTPUT 2:
10

HINT:
Sebelum elemen tunggal, pasangan angka selalu mulai di indeks genap (0, 2, 4...).
Setelah elemen tunggal, pasangan angka mulai di indeks ganjil.
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

    // TODO: Cari single element dengan Binary Search O(log N)

    return 0;
}
