/*
============================================================
📋 TUGAS 05: Pemotongan Balok Kayu dengan Biaya Pisau
============================================================
Source: Timber Cutting with Tool Wear
Difficulty: Hard
Topics: Knuth Optimization, Cutting Sticks Variant

PROBLEM:
Sebuah balok kayu panjang L harus dipotong pada M titik potong terurut:
`0 < p[1] < p[2] < ... < p[M] < L`.
Setiap pemotongan sebuah balok berbiaya sama dengan panjang balok tersebut DITAMBAH biaya aus mata pisau sebesar W.
Setiap titik potong harus dieksekusi tepat satu kali.

Tentukan TOTAL BIAYA PEMOTONGAN MINIMUM untuk memotong seluruh M titik!

INPUT FORMAT:
Baris pertama berisi tiga bilangan bulat L, M, dan W.
Baris kedua berisi M bilangan bulat titik potong p[1], ..., p[M] (terurut menaik).
(Baris kedua boleh kosong jika M = 0).

OUTPUT FORMAT:
Satu baris berisi total biaya minimum pemotongan.

CONSTRAINTS:
1 <= L <= 1.000.000.000
0 <= M <= 1999
0 <= W <= 1.000.000.000
0 < p[1] < ... < p[M] < L

SAMPLE INPUT 1:
10 3 5
2 4 7

SAMPLE OUTPUT 1:
35
(Biaya dasar pemotongan = 20, ada 3 kali pemotongan: 20 + 3 * 5 = 35)

SAMPLE INPUT 2:
100 0 10

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

    ll l, w;
    int m;
    if (!(cin >> l >> m >> w)) return 0;

    // TODO: Selesaikan dengan Knuth Optimization

    return 0;
}
