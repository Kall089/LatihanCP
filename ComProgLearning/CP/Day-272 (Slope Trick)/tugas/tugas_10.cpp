/*
============================================================
📋 TUGAS 10: Perdagangan Saham Berulang dengan Komisi Nol
============================================================
Source: Stock Market Arbitrage
Difficulty: Medium
Topics: Slope Trick, Min-Heap, Regret Greedy

PROBLEM:
Diberikan riwayat harga saham harian P[0], ..., P[N-1].
Kamu dapat melakukan pembelian dan penjualan saham sebanyak mungkin tanpa biaya komisi.
Setiap hari kamu dapat membeli 1 saham, menjual 1 saham, atau tidak bertransaksi.
Maksimumkan total keuntungan!

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat positif P[0], ..., P[N-1].

OUTPUT FORMAT:
Satu baris berisi keuntungan maksimum.

CONSTRAINTS:
1 <= N <= 300.000
1 <= P[i] <= 1.000.000.000

SAMPLE INPUT 1:
5
7 1 5 3 6 4

SAMPLE OUTPUT 1:
7
(Beli 1 jual 5 -> untung 4. Beli 3 jual 6 -> untung 3. Total untung = 4 + 3 = 7)

SAMPLE INPUT 2:
5
7 6 4 3 1

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
