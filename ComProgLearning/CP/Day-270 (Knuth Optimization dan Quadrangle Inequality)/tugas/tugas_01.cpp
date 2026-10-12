/*
============================================================
📋 TUGAS 01: Biaya Alat Tetap (Fixed Overhead Sequential Merge)
============================================================
Source: Classic Knuth DP Variant
Difficulty: Medium
Topics: Knuth Optimization, Range DP

PROBLEM:
Terdapat N peti barang berjejer dari 1 sampai N dengan bobot a[0], ..., a[N-1].
Peti digabungkan secara berurutan dengan memilih dua kelompok peti bersebelahan.
Setiap satu kali operasi penggabungan, selain membayar total bobot kedua kelompok,
juga dikenakan biaya sewa alat tetap sebesar F:
`Cost(l, r) = sum_{k=l}^r a[k] + F`.

Tentukan TOTAL BIAYA MINIMUM untuk menggabungkan seluruh N peti menjadi satu!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan F.
Baris kedua berisi N bilangan bulat non-negatif a[0], ..., a[N-1].

OUTPUT FORMAT:
Satu baris berisi total biaya minimum.

CONSTRAINTS:
1 <= N <= 2000
0 <= a[i], F <= 1.000.000.000

SAMPLE INPUT 1:
3 5
1 2 3

SAMPLE OUTPUT 1:
19
(1+2: 3 + 5 = 8; lalu (3)+3: 6 + 5 = 11 -> total = 8 + 11 = 19)

SAMPLE INPUT 2:
1 99
8

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
    ll f;
    if (!(cin >> n >> f)) return 0;

    // TODO: Selesaikan dengan Knuth Optimization O(N^2)

    return 0;
}
