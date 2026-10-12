/*
============================================================
📋 TUGAS 06: Pengadaan Material dengan Promo Terbatas [L, R]
============================================================
Source: Li Chao Range Segments
Difficulty: Hard
Topics: Li Chao Tree, Segment Trees

PROBLEM:
Terdapat N distributor material. Distributor ke-i menawarkan tarif pengadaan:
`Harga_i(q) = m[i] * q + b[i]`
yang hanya berlaku jika kuantitas pesanan q memenuhi L[i] <= q <= R[i].
Semua penawaran distributor telah terdaftar.

Terdapat Q calon pembeli yang masing-masing membutuhkan kuantitas kueri q.
Tentukan HARGA MINIMUM untuk setiap pembeli, atau `EMPTY` jika tidak ada distributor yang melayani kuantitas tersebut.

INPUT FORMAT:
Baris pertama berisi N dan Q.
N baris berikutnya berisi m[i], b[i], L[i], R[i].
Baris terakhir berisi Q bilangan bulat q[0], ..., q[Q-1].

OUTPUT FORMAT:
Cetak Q baris: harga minimum atau EMPTY.

CONSTRAINTS:
1 <= N, Q <= 100.000
-1.000.000 <= m[i], L[i], R[i], q[k] <= 1.000.000
-1.000.000.000.000 <= b[i] <= 1.000.000.000.000
L[i] <= R[i]

SAMPLE INPUT 1:
2 3
2 10 1 5
-1 20 3 10
2 4 12

SAMPLE OUTPUT 1:
14
16
EMPTY

SAMPLE INPUT 2:
1 1
0 5 2 2
2

SAMPLE OUTPUT 2:
5
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    // TODO: Selesaikan dengan Range Li Chao Tree

    return 0;
}
