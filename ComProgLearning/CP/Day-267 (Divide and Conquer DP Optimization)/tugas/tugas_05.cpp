/*
============================================================
📋 TUGAS 05: Partisi dengan Biaya Varians Minimum Mandiri
============================================================
Source: Classic D&C DP
Difficulty: Hard
Topics: Divide and Conquer DP Optimization, Variance Minimization

PROBLEM:
Diberikan barisan N bilangan terurut x[0] <= x[1] <= ... <= x[N-1].
Bagi barisan menjadi TEPAT K segmen tak kosong.
Biaya suatu segmen [l..r] adalah:
`Cost(l, r) = (r - l + 1) * sum_{i=l}^r x[i]^2 - (sum_{i=l}^r x[i])^2`.

Tentukan TOTAL BIAYA MINIMUM untuk mempartisi array menjadi tepat K segmen!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan K.
Baris kedua berisi N bilangan bulat x[0], ..., x[N-1].

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: biaya minimum.

CONSTRAINTS:
1 <= K <= min(N, 30)
1 <= N <= 20.000
0 <= x[i] <= 10.000

SAMPLE INPUT 1:
4 2
2 4 8 10

SAMPLE OUTPUT 1:
8
(Bagi [2, 4] -> len 2 * 20 - 36 = 4. Bagi [8, 10] -> len 2 * 164 - 324 = 4. Total = 8)

SAMPLE INPUT 2:
3 3
1 2 3

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
