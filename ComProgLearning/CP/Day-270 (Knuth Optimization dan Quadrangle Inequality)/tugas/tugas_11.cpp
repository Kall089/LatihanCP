/*
============================================================
📋 TUGAS 11: Partisi Antrean Dokumen Cetak Prioritas
============================================================
Source: Print Job Batch Merge
Difficulty: Hard
Topics: Knuth Optimization, Range DP

PROBLEM:
Terdapat N berkas dokumen berurutan yang harus dicetak dengan jumlah halaman p[0], ..., p[N-1].
Printer industri hanya dapat menggabungkan dua tumpukan dokumen yang bersebelahan.
Setiap penggabungan dua tumpukan dokumen membayar waktu proses yang sebanding dengan jumlah halaman
ditambah waktu pendinginan laser C:
`Cost(l, r) = sum_{k=l}^r p[k] + C`.

Tentukan TOTAL WAKTU MINIMUM untuk menggabungkan seluruh dokumen menjadi satu berkas cetak!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan C.
Baris kedua berisi N bilangan bulat non-negatif p[0], ..., p[N-1].

OUTPUT FORMAT:
Satu baris berisi total waktu minimum.

CONSTRAINTS:
1 <= N <= 2000
0 <= C <= 1.000.000.000
0 <= p[i] <= 1.000.000.000

SAMPLE INPUT 1:
3 4
10 20 30

SAMPLE OUTPUT 1:
98
(10+20: 30+4 = 34. Lalu (30)+30: 60+4 = 64. Total = 34 + 64 = 98)

SAMPLE INPUT 2:
1 10
5

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
    ll c;
    if (!(cin >> n >> c)) return 0;

    // TODO: Selesaikan dengan Knuth Optimization O(N^2)

    return 0;
}
