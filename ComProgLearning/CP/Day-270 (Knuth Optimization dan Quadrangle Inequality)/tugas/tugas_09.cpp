/*
============================================================
📋 TUGAS 09: Penggabungan Gelang Energi Melingkar
============================================================
Source: Circular Merging Variant
Difficulty: Hard
Topics: Knuth Optimization, Circular Array Doubling

PROBLEM:
N kristal energi tersusun melingkar di reaktor fusi.
Kristal ke-i memiliki daya output e[i].
Dua kristal bertetangga di lingkaran dapat digabungkan menjadi satu kristal dengan biaya
sebesar total daya kedua kristal yang digabung DITAMBAH biaya stabilisasi cincin K:
`Cost(l, r) = sum_{t=l}^r e[t] + K`.
Proses diulang hingga tersisa satu super-kristal.

Tentukan TOTAL BIAYA STABILISASI MINIMUM untuk menggabungkan seluruh kristal!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan K.
Baris kedua berisi N bilangan bulat non-negatif e[0], ..., e[N-1] (mengikuti urutan lingkaran).

OUTPUT FORMAT:
Satu baris berisi biaya minimum.

CONSTRAINTS:
1 <= N <= 1000
0 <= K <= 1.000.000.000
0 <= e[i] <= 1.000.000.000

SAMPLE INPUT 1:
3 5
2 3 4

SAMPLE OUTPUT 1:
24
(2+3: 5+5 = 10. Lalu (5)+4: 9+5 = 14. Total = 10 + 14 = 24)

SAMPLE INPUT 2:
1 10
7

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
    ll k;
    if (!(cin >> n >> k)) return 0;

    // TODO: Selesaikan dengan Circular Knuth Optimization O(N^2)

    return 0;
}
