/*
============================================================
📋 TUGAS 07: Pembelian Batch Barang dengan Diskon Linier
============================================================
Source: Classic CHT Optimization
Difficulty: Hard
Topics: Convex Hull Trick, Deque

PROBLEM:
Sebuah grosir menawarkan N jenis produk bernomor 1 sampai N.
Produk harus dibeli dalam urutan 1 sampai N dalam bentuk batch berurutan.
Jika sebuah batch memuat produk dari j+1 sampai i, biaya batch tersebut adalah:
`Cost(j+1, i) = Base_Cost + (P[i] - P[j]) * C[j+1]`.
Di mana P adalah prefix sum kuantitas produk, dan C[j+1] adalah koefisien diskon produk pembuka batch.
Diketahui bahwa C terurut TIDAK MENAIK (C[1] >= C[2] >= ... >= C[N]).

Tentukan TOTAL BIAYA MINIMUM pembelian seluruh N produk!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan Base_Cost.
Baris kedua berisi N bilangan bulat kuantitas q[0], ..., q[N-1].
Baris ketiga berisi N bilangan bulat koefisien C[0], ..., C[N-1] (terurut menurun).

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: biaya minimum.

CONSTRAINTS:
1 <= N <= 200.000
0 <= Base_Cost <= 1.000.000.000
1 <= q[i] <= 10.000
0 <= C[i] <= 1.000.000

SAMPLE INPUT 1:
3 5
1 2 3
10 5 1

SAMPLE OUTPUT 1:
28

SAMPLE INPUT 2:
1 10
5
2

SAMPLE OUTPUT 2:
20
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll base_cost;
    if (!(cin >> n >> base_cost)) return 0;

    // TODO: Selesaikan dengan CHT Deque

    return 0;
}
