/*
============================================================
📋 TUGAS 09: Perkalian Rantai Matriks (MCM) Rekonstruksi Kurung
============================================================
Source: Classic DP / Matrix Chain Multiplication Reconstruction
Difficulty: Medium-Hard
Topics: Range DP, Full Reconstruction

PROBLEM:
Diberikan rantai N buah matriks: M_1, M_2, ..., M_N.
Matriks M_i memiliki dimensi d[i-1] x d[i].
Hitung BIAYA MINIMUM (jumlah perkalian skalar) untuk mengalikan seluruh matriks,
DAN cetak BENTUK PENGURUNGAN OPTIMALNYA!
Format tanda kurung: matriks i ditulis sebagai `A{i}`, contoh `((A1(A2A3))A4)`.

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N + 1 bilangan bulat d[0], d[1], ..., d[N].

OUTPUT FORMAT:
Baris pertama berisi satu bilangan bulat: biaya perkalian minimum.
Baris kedua berisi string pengurungan optimal.

CONSTRAINTS:
1 <= N <= 100
1 <= d[i] <= 1.000

SAMPLE INPUT 1:
3
10 30 5 60

SAMPLE OUTPUT 1:
4500
((A1A2)A3)
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

    // TODO: Selesaikan MCM DP dan rekonstruksi rekursif kurung

    return 0;
}
