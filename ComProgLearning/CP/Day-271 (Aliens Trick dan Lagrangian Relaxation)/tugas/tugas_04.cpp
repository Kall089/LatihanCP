/*
============================================================
📋 TUGAS 04: Menutupi Titik dengan K Foto Berbiaya Keliling
============================================================
Source: Perimeter Coverage Variant
Difficulty: Hard
Topics: Aliens Trick, CHT

PROBLEM:
Terdapat N titik pada garis bilangan: x[0] < x[1] < ... < x[N-1].
Kita ingin menutupi seluruh N titik dengan PALING BANYAK K buah foto interval.
Biaya sebuah foto yang menutupi titik-titik dari x[j] sampai x[i] adalah:
`Cost = (x[i] - x[j] + 1)^2 + B`.
di mana B adalah biaya bingkai per foto.

Tentukan TOTAL BIAYA MINIMUM untuk menutupi seluruh titik dengan paling banyak K foto!

INPUT FORMAT:
Baris pertama berisi tiga bilangan bulat N, K, dan B.
Baris kedua berisi N bilangan bulat x[0], ..., x[N-1] (terurut menaik).

OUTPUT FORMAT:
Satu baris berisi total biaya minimum.

CONSTRAINTS:
1 <= K <= N <= 100.000
0 <= B <= 1.000.000.000
1 <= x[0] < ... < x[N-1] <= 1.000.000.000

SAMPLE INPUT 1:
3 3 5
1 4 7

SAMPLE OUTPUT 1:
18
(3 foto 1x1: luas 1+1+1 = 3, biaya bingkai 3 * 5 = 15 -> total = 18)

SAMPLE INPUT 2:
3 1 5
1 4 7

SAMPLE OUTPUT 2:
54
(1 foto 1..7: luas 49 + bingkai 5 = 54)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    ll b;
    if (!(cin >> n >> k >> b)) return 0;

    // TODO: Selesaikan dengan Aliens Trick + CHT O(N log(MaxCost))

    return 0;
}
