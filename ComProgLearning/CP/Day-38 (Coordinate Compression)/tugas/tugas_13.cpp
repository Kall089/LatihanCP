/*
============================================================
📋 TUGAS 13: Luas Gabungan Persegi Panjang
============================================================
Source: Original
Difficulty: Hard
Topics: kompresi 2D + sweep

PROBLEM:
Diberikan N persegi panjang sejajar sumbu dengan koordinat bilangan bulat.
Hitung LUAS gabungan seluruhnya (bagian yang tumpang tindih dihitung sekali).

INPUT FORMAT:
- Baris pertama: N
- N baris: x1, y1, x2, y2

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 1000
- -10^9 <= koordinat <= 10^9

SAMPLE INPUT 1:
2
0 0 2 2
1 1 3 3

SAMPLE OUTPUT 1:
7
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Kompres sumbu x dan y. Untuk tiap sel grid terkompresi, cek apakah tertutup, lalu kalikan lebar asli x tinggi asli. O(n^3) cukup untuk n=1000? Hitung dulu.

    return 0;
}
