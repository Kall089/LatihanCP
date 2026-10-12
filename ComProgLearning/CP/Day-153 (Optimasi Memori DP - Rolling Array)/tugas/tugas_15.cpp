/*
============================================================
📋 TUGAS 15: Subarray Jumlah Terbesar Kadane O(1) Memori
============================================================
Source: LeetCode 53 (Maximum Subarray) / Kadane's Algorithm
Difficulty: Easy-Medium
Topics: 1D DP State Compression, Kadane's Algorithm, O(1) Memory

PROBLEM:
Diberikan sebuah array bilangan bulat berukuran N.
Cari sebuah SUBARRAY KONTIGU (setidaknya satu elemen) yang memiliki JUMLAH TERBESAR,
dan cetak nilai jumlah tersebut.
Program HARUS berjalan dalam O(1) memori tambahan tanpa menyimpan seluruh array.

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat a[0], ..., a[N-1].

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: jumlah subarray maksimum.

CONSTRAINTS:
1 <= N <= 1.000.000
-10^9 <= a[i] <= 10^9
Memori tambahan O(1)

SAMPLE INPUT 1:
9
-2 1 -3 4 -1 2 1 -5 4

SAMPLE OUTPUT 1:
6
(Subarray [4, -1, 2, 1] memiliki jumlah 6)

SAMPLE INPUT 2:
1
-5

SAMPLE OUTPUT 2:
-5
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // TODO: Selesaikan Maximum Subarray Sum dengan Kadane O(1) memori

    return 0;
}
