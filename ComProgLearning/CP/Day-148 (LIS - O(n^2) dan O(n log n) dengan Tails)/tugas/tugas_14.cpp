/*
============================================================
📋 TUGAS 14: LIS pada Dua Dimensi (Rantai Titik)
============================================================
Source: Varian kontes
Difficulty: Hard
Topics: sort + BIT prefix-max

PROBLEM:
N titik (x, y). Titik P boleh menyusul Q jika xP < xQ DAN yP < yQ.
Cari rantai terpanjang. N besar, jadi O(n^2) tidak cukup.

INPUT: Baris 1 N; N baris "x y"
OUTPUT: satu bilangan
CONSTRAINTS: 1 <= N <= 2*10^5, 1 <= x, y <= 10^9

SAMPLE INPUT 1:            SAMPLE OUTPUT 1:
4                          3
1 1
2 2
3 3
2 1

SAMPLE INPUT 2:            SAMPLE OUTPUT 2:
3                          1
1 5
2 4
3 3

SAMPLE INPUT 3:            SAMPLE OUTPUT 3:
3                          1
1 1
1 2
1 3
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL);
    // TODO: Kerjakan di sini
    // Ini persis Russian Doll dengan nama lain: sort x naik, y MENURUN saat
    // x sama, lalu LIS ketat pada y. Sampel 3 menguji tie-break.
    // Kenali polanya -- soal 2D "rantai" hampir selalu berbentuk begini.
    return 0;}
