/*
============================================================
📋 TUGAS 13: Pembagian Beban GPU dengan Latensi Kuadratik
============================================================
Source: Distributed GPU Computing
Difficulty: Hard
Topics: Li Chao Tree, Quadratic DP

PROBLEM:
Sebuah kluster GPU memproses N kernel grafis bernomor 1 sampai N dengan beban clock c[0], ..., c[N-1] (acak).
Sinkronisasi antar-kernel j dan i (j < i) memerlukan latensi:
`Cost(j, i) = (c[i] - c[j])^2 + Overhead`.

Tentukan TOTAL LATENSI MINIMUM dari kernel 1 sampai kernel N!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan Overhead.
Baris kedua berisi N bilangan bulat c[0], ..., c[N-1].

OUTPUT FORMAT:
Satu baris berisi latensi minimum mencapai kernel N.

CONSTRAINTS:
1 <= N <= 200.000
0 <= Overhead <= 1.000.000.000
-1.000.000 <= c[i] <= 1.000.000

SAMPLE INPUT 1:
3 15
100 200 120

SAMPLE OUTPUT 1:
415
(1 -> 3: (120 - 100)^2 + 15 = 400 + 15 = 415)

SAMPLE INPUT 2:
1 1000
50

SAMPLE OUTPUT 2:
0
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll overhead;
    if (!(cin >> n >> overhead)) return 0;

    // TODO: Selesaikan dengan Li Chao Tree

    return 0;
}
