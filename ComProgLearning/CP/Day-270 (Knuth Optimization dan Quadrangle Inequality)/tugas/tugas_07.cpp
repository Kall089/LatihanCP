/*
============================================================
📋 TUGAS 07: Rantai Kompresi Citra Satelit
============================================================
Source: Satellite Tile Stitching DP
Difficulty: Hard
Topics: Knuth Optimization, Range DP

PROBLEM:
Terdapat N potongan citra satelit yang diambil secara berjejer dari utara ke selatan dengan resolusi piksel r[0], ..., r[N-1].
Citra harus digabungkan bertahap menjadi satu peta mosaik raksasa.
Biaya menggabungkan dua segmen citra bersebelahan [l..k] dan [k+1..r] adalah:
`Cost(l, r) = sum_{t=l}^r r[t] + C_stitch`.

Tentukan TOTAL BIAYA JAHIT MINIMUM untuk menggabungkan seluruh potongan citra!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan C_stitch.
Baris kedua berisi N bilangan bulat non-negatif r[0], ..., r[N-1].

OUTPUT FORMAT:
Satu baris berisi biaya jahit minimum.

CONSTRAINTS:
1 <= N <= 2000
0 <= C_stitch <= 1.000.000.000
0 <= r[i] <= 1.000.000.000

SAMPLE INPUT 1:
3 2
3 4 5

SAMPLE OUTPUT 1:
23
(3+4: 7 + 2 = 9; lalu (7)+5: 12 + 2 = 14 -> 9 + 14 = 23)

SAMPLE INPUT 2:
1 10
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
    ll c_stitch;
    if (!(cin >> n >> c_stitch)) return 0;

    // TODO: Selesaikan dengan Knuth Optimization O(N^2)

    return 0;
}
