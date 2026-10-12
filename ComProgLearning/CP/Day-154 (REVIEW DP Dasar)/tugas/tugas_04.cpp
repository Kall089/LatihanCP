/*
============================================================
📋 TUGAS 04: Subsekuens Naik Terpanjang dan Banyak Cara (LIS + Counting)
============================================================
Source: LeetCode 673 (Number of Longest Increasing Subsequences)
Difficulty: Medium
Topics: LIS DP, Optimization + Counting

PROBLEM:
Diberikan array N bilangan bulat a[0], ..., a[N-1].
Hitung:
1. Panjang dari Subsekuens Naik Terpanjang (LIS).
2. Banyak subsekuens berbeda yang mencapai panjang LIS tersebut, modulo 1.000.000.007.

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat a[0], ..., a[N-1].

OUTPUT FORMAT:
Satu baris berisi dua bilangan bulat:
[panjang LIS] [banyak LIS modulo 1.000.000.007].

CONSTRAINTS:
1 <= N <= 2.000
-10^9 <= a[i] <= 10^9

SAMPLE INPUT 1:
5
1 3 5 4 7

SAMPLE OUTPUT 1:
4 2
(LIS panjang 4: [1, 3, 5, 7] dan [1, 3, 4, 7])

SAMPLE INPUT 2:
5
2 2 2 2 2

SAMPLE OUTPUT 2:
1 5
(LIS panjang 1: setiap elemen sendiri-sendiri, total 5 subsekuens)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // TODO: Selesaikan LIS Length + Way Counting

    return 0;
}
