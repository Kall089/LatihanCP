/*
============================================================
📋 TUGAS 12: Pembagian Spektrum Frekuensi Radio
============================================================
Source: Spectrum Allocation DP
Difficulty: Hard
Topics: Knuth Optimization, Range DP

PROBLEM:
Otoritas telekomunikasi membagi spektrum frekuensi radio menjadi N kanal berurutan.
Kanal ke-i memiliki densitas interferensi i[0], ..., i[N-1].
Penggabungan dua blok kanal bersebelahan memerlukan filter sinyal berbiaya:
`Cost(l, r) = sum_{k=l}^r i[k]`.

Tentukan TOTAL BIAYA FILTER MINIMUM untuk menggabungkan seluruh kanal menjadi satu pita frekuensi!

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat non-negatif i[0], ..., i[N-1].

OUTPUT FORMAT:
Satu baris berisi biaya minimum.

CONSTRAINTS:
1 <= N <= 2000
0 <= i[k] <= 1.000.000.000

SAMPLE INPUT 1:
4
2 3 5 7

SAMPLE OUTPUT 1:
32
(2+3 = 5, lalu (5)+5 = 10, lalu (10)+7 = 17 -> 5 + 10 + 17 = 32?
Atau 5+7 = 12, 2+3 = 5, (5)+(12) = 17 -> 12 + 5 + 17 = 34.
Pilihan terbaik = 32.)

SAMPLE INPUT 2:
1
15

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

    // TODO: Selesaikan dengan Knuth Optimization O(N^2)

    return 0;
}
