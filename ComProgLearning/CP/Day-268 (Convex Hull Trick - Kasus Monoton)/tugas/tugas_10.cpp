/*
============================================================
📋 TUGAS 10: Balap Sepeda dengan Efek Slipstream
============================================================
Source: Classic CHT DP
Difficulty: Hard
Topics: Convex Hull Trick, Monotone Deque

PROBLEM:
N pembalap sepeda berada dalam barisan dengan posisi kecepatan v[0] <= v[1] <= ... <= v[N-1].
Pembalap dapat membentuk kelompok peloton. Jika pembalap bergabung di belakang pembalap terdepan kelompoknya,
penghematan energi kelompok [j+1..i] memenuhi:
`Cost(j+1, i) = E_base + (v[i] - v[j+1])^2`.
Kita ingin meminimalkan total energi dari seluruh rombongan pembalap 1 sampai N.

Tentukan TOTAL ENERGI MINIMUM!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan E_base.
Baris kedua berisi N bilangan bulat v[0], ..., v[N-1] (terurut menaik).

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: total energi minimum.

CONSTRAINTS:
1 <= N <= 200.000
1 <= E_base <= 1.000.000.000
0 <= v[i] <= 1.000.000

SAMPLE INPUT 1:
3 20
2 5 10

SAMPLE OUTPUT 1:
38

SAMPLE INPUT 2:
1 10
5

SAMPLE OUTPUT 2:
10
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll e_base;
    if (!(cin >> n >> e_base)) return 0;

    // TODO: Selesaikan dengan CHT Deque

    return 0;
}
