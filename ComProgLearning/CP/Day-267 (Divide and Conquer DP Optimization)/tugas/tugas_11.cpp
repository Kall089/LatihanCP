/*
============================================================
📋 TUGAS 11: Partisi Pasangan Inversi Elemen Terbalik
============================================================
Source: Classic Two-Pointer D&C DP
Difficulty: Hard
Topics: Divide and Conquer DP Optimization, Inversion Counting, Fenwick Tree

PROBLEM:
Diberikan array N bilangan bulat a[0], ..., a[N-1].
Bagi array menjadi TEPAT K segmen berurutan tak kosong.
Biaya suatu segmen [l..r] adalah BANYAKNYA PASANGAN INVERSI di dalamnya:
`Cost(l, r) = sum_{l <= i < j <= r} [a[i] > a[j]]`.

Tentukan TOTAL BIAYA MINIMUM untuk membagi seluruh array menjadi tepat K segmen!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan K.
Baris kedua berisi N bilangan bulat a[0], ..., a[N-1].

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: total pasangan inversi minimum.

CONSTRAINTS:
1 <= K <= min(N, 20)
1 <= N <= 10.000
1 <= a[i] <= N

SAMPLE INPUT 1:
5 2
5 4 3 2 1

SAMPLE OUTPUT 1:
4
(Bagi [5, 4] (1 inversi) dan [3, 2, 1] (3 inversi), total = 1 + 3 = 4)

SAMPLE INPUT 2:
4 4
4 3 2 1

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

    // TODO: Selesaikan dengan D&C DP + Sliding Fenwick Tree

    return 0;
}
