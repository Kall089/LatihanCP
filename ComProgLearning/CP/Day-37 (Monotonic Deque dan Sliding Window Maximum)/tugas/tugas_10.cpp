/*
============================================================
📋 TUGAS 10: Reconstruct Queue by Height
============================================================
Source: Original
Difficulty: Hard
Topics: queue, greedy, sorting

PROBLEM:
Diberikan n orang dalam queue, masing-masing dengan (h, k):
h = tinggi badan, k = jumlah orang yang lebih tinggi di depan mereka.
Rekonstruksi urutan queue yang valid.

INPUT FORMAT:
- Baris 1: integer n
- n baris: dua integer h dan k

OUTPUT FORMAT:
- n baris: h dan k dalam urutan queue yang benar

CONSTRAINTS:
- 1 ≤ n ≤ 1000

SAMPLE INPUT 1:
6
7 0
4 4
7 1
5 0
6 1
5 2

SAMPLE OUTPUT 1:
5 0
7 0
5 2
6 1
4 4
7 1

SAMPLE INPUT 2:
3
5 0
7 0
5 2

SAMPLE OUTPUT 2:
5 0
7 0
5 2

NOTE: Sort descending by h, lalu by k ascending jika h sama.
      Insert ke index k: list.insert(it + k, person).
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
