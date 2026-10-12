/*
============================================================
📋 TUGAS 14: Penataan Ketinggian Pematang Sawah Bertingkat
============================================================
Source: Terrace Step Level Smoothing
Difficulty: Medium
Topics: Slope Trick, Min-Heap, Suffix Minimum

PROBLEM:
Sawah bertingkat memiliki N terasering dari atas ke bawah dengan elevasi tanah saat ini z[0], ..., z[N-1].
Untuk mengalirkan air irigasi secara alami dari puncak ke lembah, elevasi terasering harus
terurut tidak menaik:
z'[0] >= z'[1] >= ... >= z'[N-1].
Biaya perataan adalah |z[i] - z'[i]|.

Tentukan TOTAL BIAYA PERATAAN MINIMUM!

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat z[0], ..., z[N-1].

OUTPUT FORMAT:
Satu baris berisi total biaya minimum.

CONSTRAINTS:
1 <= N <= 200.000
1 <= z[i] <= 1.000.000.000

SAMPLE INPUT 1:
4
1 3 2 4

SAMPLE OUTPUT 1:
4
(z' = [3, 3, 2, 2]: |1-3| + |3-3| + |2-2| + |4-2| = 2 + 0 + 0 + 2 = 4)

SAMPLE INPUT 2:
2
10 5

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
