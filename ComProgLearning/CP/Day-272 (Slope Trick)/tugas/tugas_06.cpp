/*
============================================================
📋 TUGAS 06: Perdagangan Emas Batangan Terbuka
============================================================
Source: Gold Trading with Regret Slope Trick
Difficulty: Medium
Topics: Slope Trick, Priority Queue, Regret Greedy

PROBLEM:
Diberikan harga 1 gram emas selama N hari: g[0], ..., g[N-1].
Setiap hari kamu dapat membeli 1 gram emas, menjual 1 gram emas (jika memegang setidaknya 1 gram),
atau tidak melakukan apa-apa.
Maksimumkan total keuntungan bersih!

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat positif g[0], ..., g[N-1].

OUTPUT FORMAT:
Satu baris berisi keuntungan maksimum.

CONSTRAINTS:
1 <= N <= 200.000
1 <= g[i] <= 1.000.000.000

SAMPLE INPUT 1:
3
3 1 4

SAMPLE OUTPUT 1:
3
(Beli di harga 1 hari kedua, jual di harga 4 hari ketiga -> untung 3)

SAMPLE INPUT 2:
3
5 3 1

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
    if (!(cin >> n)) return 0;

    // TODO: Selesaikan dengan Slope Trick O(N log N)

    return 0;
}
