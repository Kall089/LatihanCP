/*
============================================================
📋 TUGAS 01: Antrean Buku Perpustakaan
============================================================
Source: Classic Recursion / Counting Partition
Difficulty: Easy-Medium
Topics: Top-Down Memoization, Counting

PROBLEM:
Terdapat N buah buku di perpustakaan yang harus dikelompokkan secara berurutan menjadi paket-paket.
Setiap paket hanya boleh berisi tepat 2 buku atau tepat 3 buku.
Hitung berapa banyak susunan urutan ukuran paket yang berbeda untuk mengelompokkan seluruh N buku,
modulo 1.000.000.007!
Catatan: Untuk N = 0, terdapat tepat 1 susunan (paket kosong).

INPUT FORMAT:
Satu baris berisi satu bilangan bulat N.

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: banyak susunan modulo 1.000.000.007.

CONSTRAINTS:
0 <= N <= 400

SAMPLE INPUT 1:
5

SAMPLE OUTPUT 1:
2
(Susunan: 2+3 atau 3+2)

SAMPLE INPUT 2:
1

SAMPLE OUTPUT 2:
0
(Tidak bisa dibagi menjadi paket berukuran 2 atau 3)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // TODO: Selesaikan dengan top-down memoization: f(rem) = f(rem - 2) + f(rem - 3)

    return 0;
}
