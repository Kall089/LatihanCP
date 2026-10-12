/*
============================================================
📋 TUGAS 11: Same Differences
============================================================
Source: Codeforces 1520D-style
Difficulty: Hard
Topics: map, math transformation

PROBLEM:
Diberikan array A dengan N elemen. Hitung berapa banyak pasangan
(i, j) dengan i < j dimana A[j] - A[i] == j - i.

Dengan kata lain: A[j] - j == A[i] - i.

INPUT:
- Baris pertama: integer N
- Baris kedua: N buah integer

OUTPUT:
- Satu integer: jumlah pasangan valid

CONSTRAINTS:
- 2 ≤ N ≤ 200,000
- 1 ≤ A[i] ≤ 1,000,000,000

SAMPLE INPUT:
5
1 2 3 4 5

SAMPLE OUTPUT:
10

SAMPLE INPUT 2:
4
4 3 2 1

SAMPLE OUTPUT 2:
0

NOTE: Sample 1: semua pasangan valid karena A[i]-i = 0 untuk semua i.
      C(5,2) = 10 pasangan.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Hint: Transform B[i] = A[i] - i. Hitung pasangan (i,j) dimana B[i]==B[j].
    //       Gunakan map<long long, long long> freq.
    //       Untuk setiap B[i], tambahkan freq[B[i]] ke answer, lalu freq[B[i]]++.

    return 0;
}
