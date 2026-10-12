/*
============================================================
📋 TUGAS 11: Maksimalisasi Daya Pancar Radar
============================================================
Source: Classic Upper CHT
Difficulty: Hard
Topics: Upper Convex Hull Trick, Monotone Deque

PROBLEM:
Terdapat N radar dengan kapasitas penguatan g[0] <= g[1] <= ... <= g[N-1] (terurut menaik).
Setiap radar memiliki daya cadangan awal b[i].
Daya jangkauan radar pada frekuensi f diberikan oleh rumus linear:
`Power_i(f) = g[i] * f + b[i]`.

Terdapat Q kueri frekuensi f[0] <= f[1] <= ... <= f[Q-1] (terurut menaik).
Untuk setiap frekuensi, tentukan DAYA MAKSIMUM yang dapat dicapai!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan Q.
N baris berikutnya berisi g[i] dan b[i].
Baris terakhir berisi Q bilangan bulat f[0], ..., f[Q-1].

OUTPUT FORMAT:
Cetak Q baris, masing-masing berisi daya maksimum.

CONSTRAINTS:
1 <= N, Q <= 200.000
-1.000.000 <= g[i], f[q] <= 1.000.000
-1.000.000.000.000 <= b[i] <= 1.000.000.000.000
g tidak menurun, f tidak menurun

SAMPLE INPUT 1:
3 3
1 5
3 2
5 0
1 2 5

SAMPLE OUTPUT 1:
6
10
25

SAMPLE INPUT 2:
1 1
2 3
4

SAMPLE OUTPUT 2:
11
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    // TODO: Selesaikan dengan Upper Convex Hull Trick Deque

    return 0;
}
