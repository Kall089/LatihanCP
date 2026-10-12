/*
============================================================
📋 TUGAS 09: Submatrix dengan Karakter Mayoritas
============================================================
Source: Original
Difficulty: Medium
Topics: Multi-layer Prefix Sum 2D

PROBLEM:
Diberikan grid N × M berisi huruf kecil 'a'-'z'.
Untuk Q buah query, kamu diberikan koordinat subgrid (r1, c1) ke (r2, c2).
Tentukan karakter apa yang PALING SERING MUNCUL di dalam subgrid tersebut!
Jika ada lebih dari satu karakter dengan frekuensi maksimum yang sama,
pilih karakter yang secara alfabetis paling kecil!

INPUT FORMAT:
- Baris 1: N M Q (1 ≤ N, M ≤ 300, 1 ≤ Q ≤ 10^4)
- N baris berikutnya: string M karakter huruf kecil ('a'-'z')
- Q baris berikutnya: r1 c1 r2 c2

OUTPUT FORMAT:
- Q baris: karakter terbanyak di subgrid tersebut.

CONSTRAINTS:
- 1 ≤ N, M ≤ 300
- 1 ≤ Q ≤ 10^4

SAMPLE INPUT 1:
3 3 2
aab
bba
ccc
1 1 2 2
1 1 3 3

SAMPLE OUTPUT 1:
a
c

NOTE:
- Query 1: (1,1)->(2,2) berisi 'a','a','b','b'. Karakter 'a' dan 'b' sama-sama 2. Pilih 'a'.
- Query 2: (1,1)->(3,3) berisi 'a':3, 'b':3, 'c':3. Pilih 'a'. (Jika 'c' 3, 'a' 3, 'b' 3 -> 'a').
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Hint: Buat 26 tabel Prefix Sum 2D (satu untuk setiap karakter 'a'..'z')

    return 0;
}
