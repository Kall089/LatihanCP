/*
============================================================
📋 TUGAS 07: Rekonstruksi Jalur Piramida Angka (Triangle Path)
============================================================
Source: LeetCode 120 / Project Euler 18
Difficulty: Medium
Topics: Triangle Grid DP, Path Reconstruction

PROBLEM:
Terdapat sebuah piramida angka setinggi N tingkat.
Tingkat ke-i (0-indexed) memiliki i + 1 bilangan bulat.
Dari posisi (r, c), kamu hanya boleh melangkah ke (r + 1, c) atau (r + 1, c + 1).
Cari jalur dari puncak (0, 0) ke dasar tingkat N-1 yang menghasilkan JUMLAH ANGKA MAKSIMUM.
Cetak jumlah maksimum di baris pertama, dan deretan N angka yang dilewati di baris kedua.
Jika ada seri, utamakan langkah kiri (c) dibanding kanan (c + 1).

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
N baris berikutnya berisi barisan angka piramida (baris ke-i berisi i + 1 angka).

OUTPUT FORMAT:
Baris pertama: jumlah maksimum.
Baris kedua: N bilangan bulat jalur terpilih dipisahkan spasi.

CONSTRAINTS:
1 <= N <= 200
-10^6 <= angka <= 10^6

SAMPLE INPUT 1:
4
2
3 4
6 5 7
4 1 8 3

SAMPLE OUTPUT 1:
21
2 4 7 8
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

    vector<vector<ll>> tri(n);
    for (int i = 0; i < n; i++) {
        tri[i].resize(i + 1);
        for (int j = 0; j <= i; j++) {
            cin >> tri[i][j];
        }
    }

    // TODO: Selesaikan Triangle Max Path dengan rekonstruksi

    return 0;
}
