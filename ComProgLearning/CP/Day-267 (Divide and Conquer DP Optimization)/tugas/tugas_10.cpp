/*
============================================================
📋 TUGAS 10: Partisi Barisan dengan Penalti Tambahan Konveks
============================================================
Source: Classic D&C DP Variation
Difficulty: Hard
Topics: Divide and Conquer DP Optimization, Convex Penalties

PROBLEM:
Diberikan array N bilangan non-negatif a[0], ..., a[N-1].
Bagi array menjadi TEPAT K segmen tak kosong.
Biaya suatu segmen dari l sampai r adalah:
`Cost(l, r) = (sum_{p=l}^r a[p])^2 + C * (r - l + 1)^3`, di mana C adalah konstanta penalti panjang.

Tentukan TOTAL BIAYA MINIMUM untuk membagi seluruh array menjadi tepat K segmen!

INPUT FORMAT:
Baris pertama berisi tiga bilangan bulat N, K, dan C.
Baris kedua berisi N bilangan bulat non-negatif a[0], ..., a[N-1].

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: total biaya minimum.

CONSTRAINTS:
1 <= K <= min(N, 20)
1 <= N <= 10.000
0 <= C <= 100
0 <= a[i] <= 1.000

SAMPLE INPUT 1:
4 2 1
1 2 3 4

SAMPLE OUTPUT 1:
82
(Bagi [1, 2] (cost = 3^2 + 1*2^3 = 9 + 8 = 17) dan [3, 4] (cost = 7^2 + 1*2^3 = 49 + 8 = 57)? Tunggu: 17 + 57 = 74.
Cek jika bagi [1, 2, 3] dan [4]: (36 + 27) + (16 + 1) = 63 + 17 = 80.
Bagi [1] dan [2, 3, 4]: (1 + 1) + (81 + 27) = 110.
Minimum = 74.)

SAMPLE INPUT 2:
1 1 5
2

SAMPLE OUTPUT 2:
9
(2^2 + 5 * 1^3 = 4 + 5 = 9)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    ll c;
    if (!(cin >> n >> k >> c)) return 0;

    // TODO: Selesaikan dengan Divide & Conquer DP Optimization

    return 0;
}
