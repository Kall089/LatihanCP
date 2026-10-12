/*
============================================================
📋 TUGAS 07: Maximum Area Rectangle in Binary Matrix
============================================================
Source: Original
Difficulty: Medium
Topics: stack, histogram, 2D

PROBLEM:
Diberikan matriks binary R×C yang berisi 0 dan 1. Temukan luas persegi panjang
terbesar yang hanya berisi angka 1.

INPUT FORMAT:
- Baris 1: dua integer R dan C
- R baris berikutnya: C integer (0 atau 1)

OUTPUT FORMAT:
- Satu baris: integer (luas maksimum)

CONSTRAINTS:
- 1 ≤ R, C ≤ 200
- Elemen hanya 0 atau 1

SAMPLE INPUT 1:
4 5
1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

SAMPLE OUTPUT 1:
6

SAMPLE INPUT 2:
2 2
1 1
1 1

SAMPLE OUTPUT 2:
4

NOTE: Bangun histogram tinggi per kolom, lalu gunakan algoritma Largest Rectangle in Histogram.
      h[j] = jumlah '1' berturut-turut di atas baris i pada kolom j.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO
    return 0;
}
