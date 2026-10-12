/*
============================================================
📋 TUGAS 06: Pohon Pencarian Biner Berbobot Khusus (OBST)
============================================================
Source: Classic OBST
Difficulty: Hard
Topics: Knuth Optimization, Binary Trees

PROBLEM:
Diberikan N kunci k[1] < k[2] < ... < k[N] dengan frekuensi akses f[0], ..., f[N-1].
Kita ingin menyusun sebuah Binary Search Tree (BST) sehingga biaya pencarian total:
`sum_{i=1}^N depth(k[i]) * f[i]`
bernilai seminimum mungkin (dengan akar berada pada kedalaman 1).

Tentukan TOTAL BIAYA PENCARIAN MINIMUM!

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat positif f[0], ..., f[N-1].

OUTPUT FORMAT:
Satu baris berisi total biaya minimum.

CONSTRAINTS:
1 <= N <= 2000
1 <= f[i] <= 1.000.000.000

SAMPLE INPUT 1:
3
5 10 20

SAMPLE OUTPUT 1:
55
(Akar kunci 1: 10 + 2 * 5 + 2 * 20 = 10 + 10 + 40 = 60.
 Akar kunci 2: 20 + 2 * 10 + 3 * 5 = 20 + 20 + 15 = 55. Minimum = 55.)

SAMPLE INPUT 2:
1
100

SAMPLE OUTPUT 2:
100
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

    // TODO: Selesaikan dengan Knuth OBST O(N^2)

    return 0;
}
