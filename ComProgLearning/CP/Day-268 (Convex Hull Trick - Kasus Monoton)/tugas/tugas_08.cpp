/*
============================================================
📋 TUGAS 08: Pemasangan Pipa Air dengan Sambungan Kuadratik
============================================================
Source: Classic Quadratic DP CHT
Difficulty: Hard
Topics: Convex Hull Trick, Deque

PROBLEM:
Terdapat N desa di sepanjang sungai dengan koordinat posisi x[0] <= x[1] <= ... <= x[N-1].
Pipa induk harus dipasang menghubungkan desa 1 hingga desa N.
Pipa dapat dibagi menjadi beberapa segmen pipa baja. Setiap segmen pipa yang membentang dari
desa j+1 ke desa i memerlukan sambungan las berkekuatan tinggi dengan biaya:
`Cost(j+1, i) = K + (x[i] - x[j+1])^2 + W * (x[i] - x[j+1])`.

Tentukan TOTAL BIAYA MINIMUM untuk memasang pipa dari desa 1 sampai desa N!

INPUT FORMAT:
Baris pertama berisi tiga bilangan bulat N, K, dan W.
Baris kedua berisi N bilangan bulat x[0], ..., x[N-1] (terurut menaik).

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: total biaya minimum.

CONSTRAINTS:
1 <= N <= 200.000
1 <= K <= 1.000.000.000
0 <= W <= 10.000
0 <= x[i] <= 1.000.000

SAMPLE INPUT 1:
3 10 2
1 3 6

SAMPLE OUTPUT 1:
28

SAMPLE INPUT 2:
1 5 0
10

SAMPLE OUTPUT 2:
5
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll k, w;
    if (!(cin >> n >> k >> w)) return 0;

    // TODO: Selesaikan dengan CHT Deque

    return 0;
}
