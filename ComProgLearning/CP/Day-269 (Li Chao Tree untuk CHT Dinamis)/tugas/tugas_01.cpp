/*
============================================================
📋 TUGAS 01: Harga Maksimum Dinamis (Max Li Chao Tree)
============================================================
Source: Dynamic CHT Maximization
Difficulty: Medium
Topics: Max Li Chao Tree, Online Queries

PROBLEM:
Terdapat Q operasi yang datang secara dinamis:
- Operasi 1: `1 m b` -> menambahkan fungsi penawaran harga y = m * x + b.
- Operasi 2: `2 x`   -> menanyakan HARGA MAKSIMUM dari seluruh fungsi yang aktif saat ini.
  Jika belum ada penawaran yang terdaftar, cetak `EMPTY`.

INPUT FORMAT:
Baris pertama berisi Q.
Q baris berikutnya berisi salah satu dari dua operasi.

OUTPUT FORMAT:
Untuk setiap operasi tipe 2, cetak harga maksimum atau EMPTY.

CONSTRAINTS:
1 <= Q <= 200.000
-1.000.000 <= m, x <= 1.000.000
-1.000.000.000.000 <= b <= 1.000.000.000.000

SAMPLE INPUT 1:
3
1 2 1
1 -1 5
2 3

SAMPLE OUTPUT 1:
7

SAMPLE INPUT 2:
1
2 0

SAMPLE OUTPUT 2:
EMPTY
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    if (!(cin >> q)) return 0;

    // TODO: Selesaikan dengan Max Li Chao Tree

    return 0;
}
