/*
============================================================
📋 Tugas 06: Integer Square Root (LeetCode 69)
============================================================
Day: 48 | Difficulty: Easy
Topic: Binary Search on Range [0, N]

PROBLEM STATEMENT:
Diberikan sebuah integer non-negatif N. Hitung nilai floor(sqrt(N))
menggunakan Binary Search tanpa menggunakan fungsi bawaan sqrt() atau pow().

INPUT FORMAT:
- Satu baris berisi integer N.

OUTPUT FORMAT:
- Satu baris berisi floor(sqrt(N)).

CONSTRAINTS:
- 0 ≤ N ≤ 2^31 - 1

SAMPLE INPUT 1:
4

SAMPLE OUTPUT 1:
2

SAMPLE INPUT 2:
8

SAMPLE OUTPUT 2:
2

PENJELASAN SAMPLE 2:
sqrt(8) = 2.82842... floor-nya adalah 2.

HINT:
Binary search pada range low = 0, high = N.
Gunakan (long long) mid * mid <= N untuk menghindari overflow.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n;
    if (!(cin >> n)) return 0;

    // TODO: Hitung floor(sqrt(N)) dengan Binary Search

    return 0;
}
