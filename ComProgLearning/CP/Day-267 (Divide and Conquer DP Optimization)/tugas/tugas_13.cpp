/*
============================================================
📋 TUGAS 13: Partisi Rentang Nilai dengan Selisih Ekstrem
============================================================
Source: Classic D&C DP Variation
Difficulty: Hard
Topics: Divide and Conquer DP Optimization, Monge Property

PROBLEM:
Diberikan barisan N bilangan terurut a[0] <= a[1] <= ... <= a[N-1].
Bagi barisan menjadi TEPAT K segmen tak kosong.
Biaya suatu segmen [l..r] adalah KUADRAT SELISIH ELEMEN TERBESAR DAN TERKECIL:
`Cost(l, r) = (a[r] - a[l])^2`.

Tentukan TOTAL BIAYA MINIMUM untuk mempartisi barisan menjadi tepat K segmen!

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
1 2 10 11

SAMPLE OUTPUT 1:
2
(Bagi [1, 2] -> (2-1)^2 = 1 dan [10, 11] -> (11-10)^2 = 1. Total = 1 + 1 = 2)

SAMPLE INPUT 2:
3 3
1 5 10

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

    int n, k;
    if (!(cin >> n >> k)) return 0;

    // TODO: Selesaikan dengan Divide & Conquer DP Optimization

    return 0;
}
