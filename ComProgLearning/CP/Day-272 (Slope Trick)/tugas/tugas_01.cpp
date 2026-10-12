/*
============================================================
📋 TUGAS 01: Pengurutan Ketinggian Menara Sinyal
============================================================
Source: Classic Elevation Smoothing
Difficulty: Medium
Topics: Slope Trick, Max-Heap

PROBLEM:
Terdapat N menara sinyal berurutan dengan tinggi awal h[0], ..., h[N-1].
Untuk memperlancar perambatan sinyal gelombang mikro, tinggi menara harus terurut tidak menurun:
h'[0] <= h'[1] <= ... <= h'[N-1].
Biaya pemotongan atau peninggian menara ke-i adalah |h[i] - h'[i]|.

Tentukan TOTAL BIAYA MINIMUM untuk menata seluruh menara!

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat h[0], ..., h[N-1].

OUTPUT FORMAT:
Satu baris berisi total biaya minimum.

CONSTRAINTS:
1 <= N <= 200.000
1 <= h[i] <= 1.000.000.000

SAMPLE INPUT 1:
3
10 5 2

SAMPLE OUTPUT 1:
8
(Ubah menjadi [5, 5, 5]: |10-5| + |5-5| + |2-5| = 5 + 0 + 3 = 8)

SAMPLE INPUT 2:
3
1 2 3

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
