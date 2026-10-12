/*
============================================================
📋 TUGAS 10: Freefall
============================================================
Source: AtCoder ABC279 D
Difficulty: Medium
Topics: ternary integer

PROBLEM:
Sebuah benda jatuh dari ketinggian A pada gravitasi 1, membutuhkan waktu
A / sqrt(g) detik dengan g awalnya 1. Kamu boleh menaikkan g sebanyak k kali,
setiap kenaikan menambah 1 pada g dan memakan waktu B detik. Cari total
waktu minimum. Cetak 9 desimal.

INPUT FORMAT:
- Satu baris: A dan B

OUTPUT FORMAT:
- Satu bilangan, 9 desimal

CONSTRAINTS:
- 1 <= A, B <= 10^18

SAMPLE INPUT 1:
10 1

SAMPLE OUTPUT 1:
6.000000000
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // waktu(k) = k*B + A/sqrt(1+k), cembung terhadap k. Ternary search INTEGER, atau periksa beberapa kandidat di sekitar titik optimal analitisnya.

    return 0;
}
