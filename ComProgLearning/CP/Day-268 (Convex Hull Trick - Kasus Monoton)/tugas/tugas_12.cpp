/*
============================================================
📋 TUGAS 12: Pengelompokan Pelanggan dengan Biaya Pengiriman
============================================================
Source: Classic CHT Optimization
Difficulty: Hard
Topics: Convex Hull Trick, Monotone Deque

PROBLEM:
N pelanggan berada pada koordinat x[0] <= x[1] <= ... <= x[N-1] di sepanjang jalan raya.
Kurir dapat membagi pengiriman menjadi beberapa kloter.
Satu kloter dari pelanggan j+1 sampai pelanggan i memiliki biaya bensin dan operasional:
`Cost(j+1, i) = F + (x[i] - x[j+1])^2`.

Tentukan TOTAL BIAYA PENGIRIMAN MINIMUM untuk melayani seluruh N pelanggan!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan F.
Baris kedua berisi N bilangan bulat x[0], ..., x[N-1] (terurut menaik).

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: total biaya minimum.

CONSTRAINTS:
1 <= N <= 200.000
1 <= F <= 1.000.000.000
0 <= x[i] <= 1.000.000.000

SAMPLE INPUT 1:
4 50
1 4 8 10

SAMPLE OUTPUT 1:
90

SAMPLE INPUT 2:
2 100
0 10

SAMPLE OUTPUT 2:
100
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll f;
    if (!(cin >> n >> f)) return 0;

    // TODO: Selesaikan dengan CHT Deque

    return 0;
}
