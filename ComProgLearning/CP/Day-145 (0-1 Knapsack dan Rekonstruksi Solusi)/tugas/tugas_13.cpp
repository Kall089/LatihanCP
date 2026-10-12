/*
============================================================
📋 TUGAS 13: Knapsack n <= 40
============================================================
Source: Original
Difficulty: Hard
Topics: meet in the middle

PROBLEM:
N barang dengan berat sampai 10^15 dan kapasitas sampai 10^15.
Maksimalkan nilai.

INPUT FORMAT:
- Baris pertama: N dan W
- N baris: w dan v

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 40
- 1 <= W, w <= 10^15
- 1 <= v <= 10^9

SAMPLE INPUT 1:
4 5
1 10
2 20
3 30
4 40

SAMPLE OUTPUT 1:
50
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // DP mustahil (W = 10^15). Ini soal Day 54: bagi dua paruh, urutkan berdasarkan berat, PREFIX MAKSIMUM atas nilai, lalu binary search.

    return 0;
}
