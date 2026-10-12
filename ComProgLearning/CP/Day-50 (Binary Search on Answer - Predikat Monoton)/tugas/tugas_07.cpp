/*
============================================================
📋 Tugas 07: Minimum Days to Make m Bouquets (LeetCode 1482)
============================================================
Day: 50 | Difficulty: Medium
Topic: Binary Search on Answer (Kondisi Kontigu)

PROBLEM STATEMENT:
Ada N bunga di mana bunga ke-i akan mekar pada hari B[i].
Kamu ingin membuat M buah buket bunga. Setiap buket membutuhkan K bunga yang mekar dan BERDAMPINGAN (kontigu).
Cari hari MINIMUM yang dibutuhkan untuk membuat M buket. Jika tidak mungkin, cetak -1.

INPUT FORMAT:
- Baris 1: N M K
- Baris 2: N integer B[1..N]

OUTPUT FORMAT:
- Satu integer: hari minimum, atau -1 jika tidak mungkin.

CONSTRAINTS:
- 1 ≤ N ≤ 100.000
- 1 ≤ M, K ≤ 100.000
- 1 ≤ B[i] ≤ 10^9

SAMPLE INPUT 1:
5 3 1
1 10 3 10 2

SAMPLE OUTPUT 1:
3

PENJELASAN SAMPLE 1:
Pada hari 3: bunga mekar pada indeks [1, 3, 5] (mekar: [✓, ✗, ✓, ✗, ✓]).
Dapat membuat 3 buket yang masing-masing butuh 1 bunga.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long m, k;
    if (!(cin >> n >> m >> k)) return 0;

    vector<long long> b(n);
    for (int i = 0; i < n; i++) cin >> b[i];

    // TODO: Binary search pada hari

    return 0;
}
