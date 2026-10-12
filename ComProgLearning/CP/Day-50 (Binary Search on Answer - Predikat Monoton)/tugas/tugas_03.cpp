/*
============================================================
📋 Tugas 03: Minimum Limit of Balls in Bag (LeetCode 1760)
============================================================
Day: 50 | Difficulty: Medium
Topic: Binary Search on Answer (Minimalkan Maksimum)

PROBLEM STATEMENT:
Diberikan N kantong bola di mana kantong ke-i berisi NUMS[i] bola.
Kamu diberikan batas maksimal MAX_OPS operasi. Dalam satu operasi, kamu bisa membagi
sebuah kantong berisi B bola menjadi 2 kantong baru (x dan y) di mana x + y = B (x, y > 0).

Tujuanmu adalah MEMINIMALKAN jumlah bola MAKSIMUM yang ada di dalam satu kantong setelah
melakukan maksimal MAX_OPS operasi.

INPUT FORMAT:
- Baris 1: N MAX_OPS
- Baris 2: N integer NUMS[1..N]

OUTPUT FORMAT:
- Satu integer: skor minimum (jumlah bola maksimum pada satu kantong).

CONSTRAINTS:
- 1 ≤ N ≤ 100.000
- 1 ≤ MAX_OPS ≤ 10^9
- 1 ≤ NUMS[i] ≤ 10^9

SAMPLE INPUT 1:
1 2
9

SAMPLE OUTPUT 1:
3

PENJELASAN SAMPLE 1:
- Bagi 9 menjadi 6 dan 3 (ops 1) -> [6, 3]
- Bagi 6 menjadi 3 dan 3 (ops 2) -> [3, 3, 3]
Kapasitas maksimum kantong menjadi 3.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long max_ops;
    if (!(cin >> n >> max_ops)) return 0;

    vector<long long> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    // TODO: Binary search pada skor maksimum per kantong

    return 0;
}
