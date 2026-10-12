/*
============================================================
📋 TUGAS 02: Katak Berpajak Acak
============================================================
Source: Frog 3 Variant (Arbitrary Heights + Taxes)
Difficulty: Hard
Topics: Li Chao Tree, Dynamic DP

PROBLEM:
Terdapat N batu berurutan dari 1 sampai N dengan ketinggian h[0], ..., h[N-1] (ketinggian acak).
Seekor katak berada di batu 1 dengan biaya 0.
Untuk melompat dari batu j ke batu i (j < i), biaya lompatannya adalah:
`Cost(j, i) = (h[i] - h[j])^2 + p[i]`.
Di mana p[i] adalah pajak pendaratan di batu i.

Tentukan BIAYA MINIMUM untuk mencapai batu N!

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat h[0], ..., h[N-1].
Baris ketiga berisi N bilangan bulat pajak p[0], ..., p[N-1].

OUTPUT FORMAT:
Satu baris berisi biaya minimum mencapai batu N.

CONSTRAINTS:
1 <= N <= 200.000
-1.000.000 <= h[i] <= 1.000.000
0 <= p[i] <= 1.000.000.000

SAMPLE INPUT 1:
3
0 10 1
0 0 2

SAMPLE OUTPUT 1:
3
(Lompat 1 -> 3: (1 - 0)^2 + 2 = 3)

SAMPLE INPUT 2:
1
7
8

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

    // TODO: Selesaikan dengan Li Chao Tree

    return 0;
}
