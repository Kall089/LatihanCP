/*
============================================================
📋 TUGAS 08: Pembagian Gerbong Kereta dengan Biaya Pasangan Selisih Absolut
============================================================
Source: Classic D&C DP / Array Partitioning
Difficulty: Hard
Topics: Divide and Conquer DP Optimization, Prefix Sums

PROBLEM:
Diberikan barisan N penumpang dengan tingkat kenyamanan a[0] <= a[1] <= ... <= a[N-1] (terurut menaik).
Bagi penumpang ke dalam tepat K gerbong berurutan tak kosong.
Biaya suatu gerbong [l..r] adalah JUMLAH SELISIH KENYAMANAN ANTARA SELURUH PASANGAN PENUMPANG di gerbong tersebut:
`Cost(l, r) = sum_{l <= i < j <= r} (a[j] - a[i])`.

Secara matematis, untuk elemen yang terurut, rumus ini dapat dihitung dalam O(1):
`Cost(l, r) = sum_{i=l}^r (2*i - l - r) * a[i]`.

Tentukan TOTAL BIAYA MINIMUM untuk mempartisi barisan menjadi tepat K gerbong!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan K.
Baris kedua berisi N bilangan bulat non-negatif a[0], ..., a[N-1] (terurut menaik).

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: total biaya minimum.

CONSTRAINTS:
1 <= K <= min(N, 30)
1 <= N <= 20.000
0 <= a[i] <= 1.000.000

SAMPLE INPUT 1:
4 2
1 2 5 6

SAMPLE OUTPUT 1:
2
(Bagi [1, 2] [selisih = 1] dan [5, 6] [selisih = 1], total = 1 + 1 = 2)

SAMPLE INPUT 2:
3 1
1 3 6

SAMPLE OUTPUT 2:
7
((3-1) + (6-1) + (6-3) = 2 + 5 + 3 = 10? Cek: (3-1)=2, (6-1)=5, (6-3)=3 -> total = 10)
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

    // TODO: Selesaikan dengan D&C DP menggunakan prefix sum dan prefix (i * a[i])

    return 0;
}
