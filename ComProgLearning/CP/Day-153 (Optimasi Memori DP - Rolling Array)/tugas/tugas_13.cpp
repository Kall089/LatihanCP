/*
============================================================
📋 TUGAS 13: Menghitung Subsekuens Berulang Khusus 1D
============================================================
Source: LeetCode 115 (Distinct Subsequences)
Difficulty: Hard
Topics: String DP, 1D Backward Loop

PROBLEM:
Diberikan dua string S dan T.
Hitung berapa banyak subsekuens dari S yang sama persis dengan T!
Hasil dihitung modulo 1.000.000.007.
Karena |S| <= 5.000 dan |T| <= 1.000, tabel 2D akan memakan ~20 MB.
Gunakan array 1D berukuran O(|T|) dengan loop kapasitas MUNDUR.

INPUT FORMAT:
Baris pertama berisi string S.
Baris kedua berisi string T.

OUTPUT FORMAT:
Satu baris berisi banyak subsekuens modulo 1.000.000.007.

CONSTRAINTS:
1 <= |S| <= 5.000
1 <= |T| <= 1.000
Karakter hanya huruf kecil 'a'..'z'

SAMPLE INPUT 1:
rabbbit
rabbit

SAMPLE OUTPUT 1:
3
(Ada 3 cara memilih 'b' untuk membentuk "rabbit")
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s, t;
    if (!(cin >> s >> t)) return 0;

    // TODO: Selesaikan Distinct Subsequences dengan 1D DP loop mundur

    return 0;
}
