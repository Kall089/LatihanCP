/*
============================================================
📋 TUGAS 01: Batas Grup Bobot Biner
============================================================
Source: Classic D&C DP Variation
Difficulty: Medium
Topics: Divide and Conquer DP Optimization, Binary Weights

PROBLEM:
Diberikan array N bilangan bulat a[0], ..., a[N-1] di mana setiap elemen hanya bernilai 0 atau 1.
Kamu harus membagi seluruh array menjadi TEPAT K grup berurutan tak kosong.
Biaya satu grup adalah kuadrat dari total bobotnya:
`Cost(l, r) = (sum_{p=l}^r a[p])^2`.

Hitung TOTAL BIAYA MINIMUM untuk membagi seluruh array menjadi tepat K grup!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan K.
Baris kedua berisi N bilangan bulat a[0], ..., a[N-1] (setiap elemen bernilai 0 atau 1).

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: biaya minimum.

CONSTRAINTS:
1 <= K <= min(N, 30)
1 <= N <= 20.000
a[i] in {0, 1}

SAMPLE INPUT 1:
4 2
1 0 1 1

SAMPLE OUTPUT 1:
5
(Bagi menjadi [1, 0] [sum=1, cost=1] dan [1, 1] [sum=2, cost=4], total = 1 + 4 = 5)

SAMPLE INPUT 2:
3 3
0 0 0

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
