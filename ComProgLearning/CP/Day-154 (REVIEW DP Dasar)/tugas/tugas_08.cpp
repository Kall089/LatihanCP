/*
============================================================
📋 TUGAS 08: Jumlah Subarray Bernilai Kelipatan K
============================================================
Source: LeetCode 974 (Subarray Sums Divisible by K)
Difficulty: Medium
Topics: Prefix Sums, Modulo Arithmetic, Counting DP

PROBLEM:
Diberikan sebuah array bilangan bulat berukuran N dan sebuah bilangan bulat K.
Hitung berapa banyak subarray kontigu (tidak kosong) yang JUMLAH ELEMENNYA HABIS DIBAGI K
(artinya sum(subarray) % K == 0)!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan K.
Baris kedua berisi N bilangan bulat a[0], ..., a[N-1].

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: banyak subarray kelipatan K.

CONSTRAINTS:
1 <= N <= 100.000
2 <= K <= 10.000
-10.000 <= a[i] <= 10.000

SAMPLE INPUT 1:
6 5
4 5 0 -2 -3 1

SAMPLE OUTPUT 1:
7
(Subarray: [5], [5, 0], [0], [0, -2, -3], [-2, -3], [5, 0, -2, -3], [4, 5, 0, -2, -3, 1])
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    // TODO: Selesaikan Subarray Sums Divisible by K dengan prefix mod freq

    return 0;
}
