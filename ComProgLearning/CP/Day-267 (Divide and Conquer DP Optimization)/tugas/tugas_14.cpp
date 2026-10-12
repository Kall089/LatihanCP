/*
============================================================
📋 TUGAS 14: Penjadwalan Tugas dengan Biaya Waktu Kuadratik
============================================================
Source: Scheduling Theory / D&C DP Optimization
Difficulty: Hard
Topics: Divide and Conquer DP Optimization, Prefix Sums

PROBLEM:
Terdapat N tugas berurutan dengan durasi p[0], ..., p[N-1]. Tugas harus dikelompokkan ke dalam tepat K batch.
Batch ke-g memproses tugas-tugas di dalamnya secara berurutan.
Jika sebuah batch memproses tugas dari l sampai r, biaya pemrosesan batch adalah:
`Cost(l, r) = (r - l + 1) * sum_{i=l}^r p[i]`.

Tentukan TOTAL BIAYA PEMROSESAN MINIMUM untuk menjadwalkan seluruh N tugas ke dalam tepat K batch!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan K.
Baris kedua berisi N bilangan bulat positif p[0], ..., p[N-1].

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: biaya pemrosesan minimum.

CONSTRAINTS:
1 <= K <= min(N, 30)
1 <= N <= 20.000
1 <= p[i] <= 10.000

SAMPLE INPUT 1:
4 2
1 2 3 4

SAMPLE OUTPUT 1:
20
(Bagi [1, 2] (len 2 * 3 = 6) dan [3, 4] (len 2 * 7 = 14), total = 6 + 14 = 20)

SAMPLE INPUT 2:
2 1
3 5

SAMPLE OUTPUT 2:
16
(len 2 * 8 = 16)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    // TODO: Selesaikan dengan Divide & Conquer DP Optimization

    return 0;
}
