/*
============================================================
📋 TUGAS 03: Biaya Relai pada Seluruh Pos
============================================================
Source: Classic CHT Variant
Difficulty: Medium
Topics: Convex Hull Trick, All States Output

PROBLEM:
Terdapat N pos relai pengiriman di sepanjang garis pantai (pos 1 sampai N).
Pos 1 sudah aktif sejak awal dengan biaya 0.
Untuk mengaktifkan pos i (i > 1), kamu memilih pos j yang sudah aktif sebelumnya (j < i)
dengan biaya:
`dp[i] = min_{j < i} (dp[j] + b[j] * a[i])`.
Array a tidak pernah menurun (a[0] <= a[1] <= ... <= a[N-1]).
Array b tidak pernah menaik (b[0] >= b[1] >= ... >= b[N-1]).

Cetak BIAYA MINIMUM AKTIVASI UNTUK SELURUH POS: dp[1], dp[2], ..., dp[N]!

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat a[0], ..., a[N-1].
Baris ketiga berisi N bilangan bulat b[0], ..., b[N-1].

OUTPUT FORMAT:
Satu baris berisi N bilangan bulat dipisahkan spasi: dp[1], dp[2], ..., dp[N].

CONSTRAINTS:
1 <= N <= 200.000
0 <= a[i], b[i] <= 1.000.000

SAMPLE INPUT 1:
3
1 2 3
5 3 1

SAMPLE OUTPUT 1:
0 10 15

SAMPLE INPUT 2:
2
0 1
0 0

SAMPLE OUTPUT 2:
0 0
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

    // TODO: Selesaikan dengan CHT Deque dan cetak seluruh dp[i]

    return 0;
}
