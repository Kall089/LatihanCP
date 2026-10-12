/*
============================================================
📋 TUGAS 15: Trapping Rain Water II (Histogram Variant)
============================================================
Source: Original
Difficulty: Hard
Topics: stack, histogram, water trapping

PROBLEM:
Diberikan histogram n batang. Setelah hujan, air mengisi ruang di antara batang.
Namun kali ini air juga bisa meluap dari sisi kiri atau kanan.
Hitung total volume air yang tertampung jika kedua sisi terbuka.

Ini berbeda dari klasik: sisi paling kiri dan kanan tidak memiliki "dinding",
sehingga air hanya tertampung di antara batang yang lebih tinggi dari kedua sisinya.

INPUT FORMAT:
- Baris 1: integer n
- Baris 2: n integer (tinggi)

OUTPUT FORMAT:
- Satu baris: long long (volume air)

CONSTRAINTS:
- 1 ≤ n ≤ 10^5
- 0 ≤ h[i] ≤ 10^9

SAMPLE INPUT 1:
12
0 1 0 2 1 0 1 3 2 1 2 1

SAMPLE OUTPUT 1:
6

SAMPLE INPUT 2:
6
3 0 2 0 4 0

SAMPLE OUTPUT 2:
7

NOTE: Ini sama dengan masalah Trapping Rain Water klasik.
      Air di posisi i = max(0, min(max_kiri[i], max_kanan[i]) - h[i]).
      Gunakan dua pass: hitung left_max dan right_max terlebih dahulu.
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
