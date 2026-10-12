/*
============================================================
📋 Tugas 04: Search Insert Position (LeetCode 35)
============================================================
Day: 48 | Difficulty: Easy
Topic: Binary Search / Lower Bound

PROBLEM STATEMENT:
Diberikan array A terurut tanpa duplikat dan nilai target X.
Cari indeks tempat X berada. Jika X tidak ditemukan, kembalikan indeks
tempat X seharusnya disisipkan agar array tetap terurut.

INPUT FORMAT:
- Baris 1: N X
- Baris 2: N integer terurut A[i]

OUTPUT FORMAT:
- Cetak satu integer: indeks tempat X ditemukan / disisipkan.

CONSTRAINTS:
- 1 ≤ N ≤ 100.000
- -10^9 ≤ A[i], X ≤ 10^9

SAMPLE INPUT 1:
4 5
1 3 5 6

SAMPLE OUTPUT 1:
2

SAMPLE INPUT 2:
4 2
1 3 5 6

SAMPLE OUTPUT 2:
1

SAMPLE INPUT 3:
4 7
1 3 5 6

SAMPLE OUTPUT 3:
4

HINT:
Indeks penyisipan sama persis dengan definisi Lower Bound!
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long x;
    if (!(cin >> n >> x)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // TODO: Cari posisi penyisipan menggunakan Lower Bound

    return 0;
}
