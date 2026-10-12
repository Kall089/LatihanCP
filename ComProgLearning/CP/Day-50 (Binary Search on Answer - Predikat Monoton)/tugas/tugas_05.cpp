/*
============================================================
📋 Tugas 05: Magnetic Force Between Two Balls (LeetCode 1552)
============================================================
Day: 50 | Difficulty: Medium
Topic: Binary Search on Answer (Maksimalkan Jarak Min)

PROBLEM STATEMENT:
Ada N keranjang pada posisi P[1..N]. Kamu harus menempatkan M buah bola ke dalam M keranjang berbeda.
Gaya magnet antara dua bola pada posisi x dan y adalah |x - y|.
Kamu ingin menempatkan M bola sedemikian hingga GAYA MAGNET MINIMUM antara dua bola mana pun bernilai MAKSIMUM.

INPUT FORMAT:
- Baris 1: N M
- Baris 2: N integer P[1..N]

OUTPUT FORMAT:
- Satu integer: gaya magnet minimum maksimum.

CONSTRAINTS:
- 2 ≤ N ≤ 100.000
- 2 ≤ M ≤ N
- 1 ≤ P[i] ≤ 10^9

SAMPLE INPUT 1:
5 3
1 2 3 4 7

SAMPLE OUTPUT 1:
3

PENJELASAN SAMPLE 1:
Pilih posisi keranjang 1, 4, dan 7.
Jarak antar bola: |1-4|=3, |4-7|=3, |1-7|=6. Jarak minimum adalah 3.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<long long> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];

    // TODO: Sort P dan lakukan Binary Search pada jarak minimum

    return 0;
}
