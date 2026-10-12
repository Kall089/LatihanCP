/*
============================================================
📋 TUGAS 11: Fast Target Queries
============================================================
Source: Practice
Difficulty: Medium-Hard
Topics: bitset, subset sum queries

PROBLEM:
Diberikan N bilangan non-negatif dan Q query target. Untuk setiap target,
jawab apakah target tersebut bisa dibentuk oleh suatu subset. Array sama untuk
semua query, jadi preprocessing harus dilakukan sekali.

INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan A[i]
- Baris ketiga sampai Q baris berikutnya: satu target T

OUTPUT FORMAT:
- Q baris, masing-masing YES atau NO

CONSTRAINTS:
- 1 <= N <= 200
- 1 <= Q <= 200000
- 0 <= A[i] <= 1000
- 0 <= T <= 200000
- Total A[i] <= 200000

SAMPLE INPUT 1:
4 4
4 2 5 2
7
3
13
14

SAMPLE OUTPUT 1:
YES
NO
YES
NO
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Precompute bitset reachable, lalu jawab tiap query O(1).

    return 0;
}
