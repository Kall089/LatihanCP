/*
============================================================
📋 TUGAS 10: Jalur Segitiga Penjumlahan Maksimum 1D
============================================================
Source: Classic Triangle DP / Project Euler 18
Difficulty: Medium
Topics: Bottom-Up DP, 1D Array In-Place

PROBLEM:
Terdapat sebuah segitiga angka dengan N baris.
Baris ke-i (0 <= i < N) memiliki i + 1 bilangan.
Dari posisi (r, c), kamu hanya boleh melangkah ke (r + 1, c) atau (r + 1, c + 1).
Tentukan JUMLAH MAKSIMUM dari puncak (0, 0) ke dasar segitiga.
Gunakan satu array 1D berukuran O(N) dengan menghitung dari dasar (bottom-up) ke atas!

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
N baris berikutnya berisi barisan angka segitiga.

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: jumlah maksimum.

CONSTRAINTS:
1 <= N <= 1.000
-10^6 <= angka <= 10^6

SAMPLE INPUT 1:
4
2
3 4
6 5 7
4 1 8 3

SAMPLE OUTPUT 1:
21
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

    // TODO: Simpan baris segitiga dan lakukan bottom-up 1D DP

    return 0;
}
