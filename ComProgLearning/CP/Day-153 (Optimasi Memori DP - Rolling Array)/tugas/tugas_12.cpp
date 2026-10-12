/*
============================================================
📋 TUGAS 12: Jalur Terbesar Matriks Kotak dengan 2 Baris
============================================================
Source: Classic Grid DP / Max Path Sum
Difficulty: Medium
Topics: 2-Row Rolling Array, Grid DP

PROBLEM:
Diberikan matriks berukuran R x C.
Kamu mulai dari sembarang kolom pada baris pertama (0, c_start) dan ingin mencapai sembarang kolom
pada baris terakhir (R-1, c_end).
Dari sel (r, c), kamu dapat melangkah ke (r + 1, c - 1), (r + 1, c), atau (r + 1, c + 1) (jika koordinat valid).
Tentukan JUMLAH MAKSIMUM yang dapat dikumpulkan.
Gunakan teknik 2 Baris Bergantian O(C) memori.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat R dan C.
R baris berikutnya masing-masing berisi C bilangan bulat.

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: jumlah maksimum.

CONSTRAINTS:
1 <= R <= 1.000
1 <= C <= 1.000
-10^6 <= nilai <= 10^6

SAMPLE INPUT 1:
3 3
1 2 3
4 5 6
7 8 9

SAMPLE OUTPUT 1:
18
(3 -> 6 -> 9 = 18)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int r, c;
    if (!(cin >> r >> c)) return 0;

    // TODO: Selesaikan Grid Max Path dengan 2 baris prev dan cur

    return 0;
}
