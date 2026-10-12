/*
============================================================
📋 TUGAS 10: Pemotongan Pipa Minyak Lepas Pantai
============================================================
Source: Offshore Pipeline Cutting
Difficulty: Hard
Topics: Knuth Optimization, Cutting Sticks

PROBLEM:
Pipa bawah laut sepanjang L meter harus dipotong pada M titik sambungan:
`0 < p[1] < p[2] < ... < p[M] < L`.
Biaya pemotongan suatu bagian pipa adalah panjang pipa tersebut saat dipotong.
Setiap titik harus dipotong tepat satu kali dengan urutan bebas.

Tentukan TOTAL BIAYA MINIMUM pemotongan seluruh titik!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat L dan M.
Baris kedua berisi M bilangan bulat titik potong p[1], ..., p[M] terurut menaik (boleh kosong jika M = 0).

OUTPUT FORMAT:
Satu baris berisi total biaya minimum.

CONSTRAINTS:
1 <= L <= 1.000.000.000
0 <= M <= 1999
0 < p[1] < ... < p[M] < L

SAMPLE INPUT 1:
100 3
25 50 75

SAMPLE OUTPUT 1:
200
(Potong 50 (biaya 100), lalu potong 25 (biaya 50) dan 75 (biaya 50) -> 100 + 50 + 50 = 200)

SAMPLE INPUT 2:
100 0

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

    ll l;
    int m;
    if (!(cin >> l >> m)) return 0;

    // TODO: Selesaikan dengan Knuth Optimization O(M^2)

    return 0;
}
