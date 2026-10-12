/*
============================================================
📋 TUGAS 06: Pengadaan Kontainer Penyimpanan
============================================================
Source: CEOI (Batch Scheduling Variant)
Difficulty: Hard
Topics: Convex Hull Trick, Monotone Deque

PROBLEM:
Diberikan N barang dengan bobot w[0], ..., w[N-1].
Barang harus dikelompokkan ke dalam beberapa kontainer berurutan.
Jika kontainer memuat barang dari j+1 sampai i, biaya kontainer adalah:
`Cost(j+1, i) = (sum_{k=j+1}^i w[k] + (i - j - 1) - L)^2`.
Biaya ini merupakan deviasi dari kapasitas ideal kontainer L.

Tentukan TOTAL BIAYA MINIMUM untuk memasukkan seluruh N barang ke dalam kontainer!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan L.
Baris kedua berisi N bilangan bulat positif w[0], ..., w[N-1].

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: total biaya minimum.

CONSTRAINTS:
1 <= N <= 100.000
1 <= L <= 1.000.000
1 <= w[i] <= 10.000

SAMPLE INPUT 1:
3 5
2 3 4

SAMPLE OUTPUT 1:
2
(Kontainer 1: [2, 3] -> sum 5 + 1 - 5 = 1, cost 1^2 = 1.
 Kontainer 2: [4] -> sum 4 + 0 - 5 = -1, cost (-1)^2 = 1.
 Total = 1 + 1 = 2)

SAMPLE INPUT 2:
1 10
10

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
    ll l;
    if (!(cin >> n >> l)) return 0;

    // TODO: Definisikan prefix sum dan ekspansi kuadratik CHT

    return 0;
}
