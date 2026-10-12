/*
============================================================
📋 TUGAS 13: Pohon Pencarian Optimal dengan Biaya Akses Gagal
============================================================
Source: Extended Optimal BST (Donald Knuth Classic)
Difficulty: Menantang
Topics: Knuth Optimization, OBST with Dummy Keys

PROBLEM:
Diberikan N kunci k[1] < k[2] < ... < k[N] dengan frekuensi sukses p[1..N],
serta N+1 frekuensi kueri gagal (dummy leaves) q[0..N], di mana:
- q[0] adalah frekuensi kueri x < k[1]
- q[i] adalah frekuensi kueri k[i] < x < k[i+1] untuk 1 <= i < N
- q[N] adalah frekuensi kueri x > k[N].

Kedalaman simpul akar adalah 1. Simpul daun dummy (kueri gagal) memiliki kedalaman = kedalaman orang tua + 1.
Total biaya pohon yang ingin diminimalkan adalah:
`sum_{i=1}^N depth(k[i]) * p[i] + sum_{i=0}^N depth(dummy[i]) * q[i]`.

Tentukan TOTAL BIAYA PENCARIAN MINIMUM!

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat positif p[1], ..., p[N].
Baris ketiga berisi N+1 bilangan bulat non-negatif q[0], ..., q[N].

OUTPUT FORMAT:
Satu baris berisi total biaya minimum.

CONSTRAINTS:
1 <= N <= 1000
1 <= p[i] <= 1.000.000
0 <= q[i] <= 1.000.000

SAMPLE INPUT 1:
2
10 20
2 3 5

SAMPLE OUTPUT 1:
67
(Dengan struktur pohon biner optimal yang memuat simpul internal dan daun dummy)

SAMPLE INPUT 2:
1
10
5 5

SAMPLE OUTPUT 2:
30
(Akar k1 kedalaman 1 (10), dua daun dummy di kedalaman 2: 2*5 + 2*5 = 20. Total = 30)
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

    // TODO: Selesaikan Extended OBST dengan Knuth Optimization O(N^2)

    return 0;
}
