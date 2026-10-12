/*
============================================================
📋 TUGAS 04: Partisi Segmen dengan Kuadrat Panjang dan Bobot
============================================================
Source: Classic D&C DP Optimization
Difficulty: Medium
Topics: Divide and Conquer DP Optimization, Monge Property

PROBLEM:
Diberikan array N bilangan non-negatif a[0], ..., a[N-1].
Bagi array menjadi TEPAT K segmen tak kosong.
Biaya satu segmen dari indeks l sampai r adalah:
`Cost(l, r) = (r - l + 1)^2 + (sum_{p=l}^r a[p])^2`.

Tentukan TOTAL BIAYA MINIMUM untuk mempartisi array menjadi tepat K segmen!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan K.
Baris kedua berisi N bilangan bulat a[0], ..., a[N-1].

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: total biaya minimum.

CONSTRAINTS:
1 <= K <= min(N, 30)
1 <= N <= 20.000
0 <= a[i] <= 10.000

SAMPLE INPUT 1:
4 2
1 2 3 4

SAMPLE OUTPUT 1:
66
(Bagi [1, 2] (len 2, sum 3 -> 4 + 9 = 13) dan [3, 4] (len 2, sum 7 -> 4 + 49 = 53). Total = 13 + 53 = 66)

SAMPLE INPUT 2:
2 1
5 5

SAMPLE OUTPUT 2:
104
(len 2, sum 10 -> 4 + 100 = 104)
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
