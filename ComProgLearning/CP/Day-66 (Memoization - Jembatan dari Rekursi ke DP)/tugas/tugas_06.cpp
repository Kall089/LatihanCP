/*
============================================================
📋 TUGAS 06: Subarray Selang-Seling Maksimum (House Robber Top-Down)
============================================================
Source: LeetCode 198 / Classic Top-Down DP
Difficulty: Easy-Medium
Topics: 1D Top-Down Memoization

PROBLEM:
Terdapat N rumah berjajar di sepanjang jalan raya. Rumah ke-i menyimpan harta bernilai val[i].
Sistem alarm keamanan akan menyala otomatis jika dua rumah yang bersebelahan dirampok pada malam yang sama.
Tentukan TOTAL NILAI MAKSIMUM yang dapat dikumpulkan tanpa memicu alarm keamanan!

Wajib diimplementasikan menggunakan REKURSIF DENGAN MEMOISASI (Top-Down)!

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat non-negatif val[0], ..., val[N-1].

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: total nilai maksimum.

CONSTRAINTS:
1 <= N <= 100.000
0 <= val[i] <= 10^9

SAMPLE INPUT 1:
4
1 2 3 1

SAMPLE OUTPUT 1:
4
(Pilih rumah 0 [nilai 1] dan rumah 2 [nilai 3], total 4)

SAMPLE INPUT 2:
5
2 7 9 3 1

SAMPLE OUTPUT 2:
12
(Pilih rumah 0 [2], rumah 2 [9], dan rumah 4 [1], total 12)
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

    vector<ll> val(n);
    for (int i = 0; i < n; i++) cin >> val[i];

    // TODO: Selesaikan dengan top-down memoization: f(i) = max(f(i+1), val[i] + f(i+2))

    return 0;
}
