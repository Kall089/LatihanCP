/*
============================================================
📋 TUGAS 15: Champion Subset Drill
============================================================
Source: Custom contest drill
Difficulty: Hard
Topics: subset sum, counting, queries

PROBLEM:
Diberikan N bilangan non-negatif dan Q query. Setiap query berisi target T.
Untuk setiap T, cetak dua informasi:
1. apakah ada subset dengan jumlah T
2. banyak subset dengan jumlah T modulo 1.000.000.007

INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan A[i]
- Q baris berikutnya: satu target T

OUTPUT FORMAT:
- Untuk setiap query, cetak:
  YES ways
  atau
  NO 0

CONSTRAINTS:
- 1 <= N <= 200
- 1 <= Q <= 100000
- 0 <= A[i] <= 1000
- 0 <= T <= 100000

SAMPLE INPUT 1:
4 4
1 2 3 2
5
4
0
9

SAMPLE OUTPUT 1:
YES 3
YES 2
YES 1
NO 0

HINT:
Counting DP sudah cukup untuk menjawab reachability juga: reachable jika
ways[T] > 0. Hati-hati jika ada banyak elemen 0.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Precompute ways[0..100000], lalu jawab semua query O(1).

    return 0;
}
