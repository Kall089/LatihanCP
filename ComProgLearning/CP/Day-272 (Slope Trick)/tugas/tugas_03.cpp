/*
============================================================
📋 TUGAS 03: Perataan Kemiringan Saluran Irigasi Menurun
============================================================
Source: Irrigation Flow Gradient Smoothing
Difficulty: Medium
Topics: Slope Trick, Min-Heap, Suffix Minimum

PROBLEM:
Saluran irigasi sepanjang N stasiun memiliki elevasi tanah awal e[0], ..., e[N-1].
Agar air mengalir secara gravitasi tanpa terbendung, elevasi baru e'[i] harus tidak menaik:
e'[0] >= e'[1] >= ... >= e'[N-1].
Biaya galian atau timbunan pada stasiun i adalah |e[i] - e'[i]|.

Tentukan TOTAL BIAYA PENGGALIAN/PENIMBUNAN MINIMUM!

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat e[0], ..., e[N-1].

OUTPUT FORMAT:
Satu baris berisi total biaya minimum.

CONSTRAINTS:
1 <= N <= 200.000
1 <= e[i] <= 1.000.000.000

SAMPLE INPUT 1:
3
2 5 10

SAMPLE OUTPUT 1:
8
(Ubah menjadi [5, 5, 5]: |2-5| + |5-5| + |10-5| = 3 + 0 + 5 = 8)

SAMPLE INPUT 2:
3
10 5 2

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

    // TODO: Selesaikan dengan Slope Trick (Min-Heap) O(N log N)

    return 0;
}
