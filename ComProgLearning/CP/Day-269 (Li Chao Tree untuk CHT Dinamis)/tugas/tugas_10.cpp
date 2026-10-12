/*
============================================================
📋 TUGAS 10: Penyewaan Kendaraan Lintas Provinsi
============================================================
Source: Rental Selection CHT
Difficulty: Hard
Topics: Li Chao Tree, Dynamic Lines

PROBLEM:
Terdapat N agen rental kendaraan. Agen ke-i menawarkan biaya sewa harian m[i] dan biaya asuransi awal b[i].
`Sewa_i(d) = m[i] * d + b[i]`.
Urutan kedatangan agen tidak teratur.
Terdapat Q kueri jumlah hari sewa d[0], ..., d[Q-1].
Untuk setiap kueri, cari BIAYA SEWA TERMURAH di antara seluruh agen rental.

INPUT FORMAT:
Baris pertama berisi N dan Q.
N baris berikutnya berisi m[i] dan b[i].
Baris terakhir berisi Q bilangan bulat d[0], ..., d[Q-1].

OUTPUT FORMAT:
Cetak Q baris, masing-masing berisi biaya sewa termurah.

CONSTRAINTS:
1 <= N, Q <= 200.000
-1.000.000 <= m[i], d[q] <= 1.000.000
-1.000.000.000.000 <= b[i] <= 1.000.000.000.000

SAMPLE INPUT 1:
3 3
10 50
5 100
20 10
2 10 20

SAMPLE OUTPUT 1:
50
140
200

SAMPLE INPUT 2:
1 1
0 5
100

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

    int n, q;
    if (!(cin >> n >> q)) return 0;

    // TODO: Selesaikan dengan Li Chao Tree

    return 0;
}
