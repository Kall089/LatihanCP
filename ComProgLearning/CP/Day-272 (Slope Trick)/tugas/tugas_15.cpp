/*
============================================================
📋 TUGAS 15: Optimasi Transaksi Kripto Dinamis
============================================================
Source: Cryptocurrency Dynamic Arbitrage
Difficulty: Menantang
Topics: Slope Trick, Min-Heap, Regret Greedy

PROBLEM:
Diberikan harga koin kripto selama N jam: C[0], ..., C[N-1].
Pada setiap jam, kamu dapat membeli 1 unit koin, menjual 1 unit koin, atau tidak melakukan apa-apa.
Maksimumkan total keuntungan bersih yang dapat diperoleh!

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat positif C[0], ..., C[N-1].

OUTPUT FORMAT:
Satu baris berisi keuntungan maksimum.

CONSTRAINTS:
1 <= N <= 300.000
1 <= C[i] <= 1.000.000.000

SAMPLE INPUT 1:
6
10 20 30 5 15 25

SAMPLE OUTPUT 1:
40
(Beli 10 jual 30 -> untung 20. Beli 5 jual 25 -> untung 20. Total = 40)

SAMPLE INPUT 2:
3
50 50 50

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
