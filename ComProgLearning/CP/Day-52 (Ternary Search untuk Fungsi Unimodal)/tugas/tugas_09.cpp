/*
============================================================
📋 TUGAS 09: Biaya Perjalanan Optimal
============================================================
Source: Original
Difficulty: Medium
Topics: linear per bagian

PROBLEM:
Dari lantai 0 ke lantai N. Tangga A detik per lantai; lift menunggu B detik
lalu C detik per lantai. Naik tangga sampai lantai k lalu lift sampai N.
Cari waktu minimum.

INPUT FORMAT:
- Satu baris: N A B C

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 10^12
- 1 <= A, B, C <= 10^9

SAMPLE INPUT 1:
100 10 100 1

SAMPLE OUTPUT 1:
200
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Fungsinya LINEAR PER BAGIAN, jadi minimumnya di titik ekstrem. Kalau A == C ada DATARAN yang membuat ternary search tidak aman.

    return 0;
}
