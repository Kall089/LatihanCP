/*
============================================================
📋 TUGAS 02: Katak dengan Pajak Pendaratan
============================================================
Source: Frog 3 Variant
Difficulty: Medium
Topics: Convex Hull Trick, Quadratic Transitions

PROBLEM:
Seekor katak berada di batu 1 dengan ketinggian h[0]. Ketinggian batu tidak pernah menurun:
h[0] <= h[1] <= ... <= h[N-1].
Katak ingin mencapai batu N.
Dari batu j, katak dapat melompat ke batu i (j < i) dengan biaya:
`Biaya(j, i) = (h[i] - h[j])^2 + C + p[i]`.
Di mana C adalah biaya lompatan dasar dan p[i] adalah pajak pendaratan di batu i.
Batu awal (batu 1) tidak memiliki pajak (biaya awal = 0).

Tentukan BIAYA MINIMUM katak untuk mencapai batu N!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan C.
Baris kedua berisi N bilangan bulat h[0], ..., h[N-1].
Baris ketiga berisi N bilangan bulat p[0], ..., p[N-1].

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: biaya minimum mencapai batu N.

CONSTRAINTS:
1 <= N <= 200.000
-1.000.000 <= h[i] <= 1.000.000
0 <= C, p[i] <= 1.000.000.000

SAMPLE INPUT 1:
3 0
0 1 2
9 10 0

SAMPLE OUTPUT 1:
4
(Lompat langsung 1 -> 3: (2 - 0)^2 + 0 + 0 = 4)

SAMPLE INPUT 2:
1 8
5
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
    ll c;
    if (!(cin >> n >> c)) return 0;

    // TODO: Selesaikan dengan CHT Deque

    return 0;
}
