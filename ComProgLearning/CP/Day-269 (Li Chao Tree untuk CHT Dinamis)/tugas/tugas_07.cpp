/*
============================================================
📋 TUGAS 07: Penataan Kontainer Dermaga dengan Gravitasi Acak
============================================================
Source: Dynamic CHT DP
Difficulty: Hard
Topics: Li Chao Tree, Quadratic DP

PROBLEM:
Terdapat N kontainer dengan berat w[0], ..., w[N-1] (acak).
Kontainer dipindahkan secara berurutan. Posisi kontainer 0 memiliki biaya awal 0.
Biaya memindahkan crane dari tumpukan kontainer j ke i (j < i) adalah:
`Cost(j, i) = (w[i] - w[j])^2 + W_base`.

Tentukan TOTAL BIAYA MINIMUM untuk mencapai kontainer ke-N!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan W_base.
Baris kedua berisi N bilangan bulat berat w[0], ..., w[N-1].

OUTPUT FORMAT:
Satu baris berisi biaya minimum mencapai kontainer N.

CONSTRAINTS:
1 <= N <= 200.000
0 <= W_base <= 1.000.000.000
-1.000.000 <= w[i] <= 1.000.000

SAMPLE INPUT 1:
4 10
5 1 9 4

SAMPLE OUTPUT 1:
21
(0 -> 3 langsung: (4 - 5)^2 + 10 = 11?
Tunggu: (4 - 5)^2 + 10 = 11.
Lompat langsung: 1 + 10 = 11.)

SAMPLE INPUT 2:
1 5
100

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
    ll w_base;
    if (!(cin >> n >> w_base)) return 0;

    // TODO: Selesaikan dengan Li Chao Tree

    return 0;
}
