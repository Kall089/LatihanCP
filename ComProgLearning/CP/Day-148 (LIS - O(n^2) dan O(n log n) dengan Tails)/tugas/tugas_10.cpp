/*
============================================================
📋 TUGAS 10: Minimum Jumlah Barisan Tidak Naik (Dilworth)
============================================================
Source: Klasik (sistem antirudal / patience sorting)
Difficulty: Medium
Topics: teorema Dilworth

PROBLEM:
Sebuah sistem hanya bisa menembak rudal dengan ketinggian TIDAK NAIK.
Diberi urutan ketinggian rudal, berapa MINIMUM sistem yang dibutuhkan untuk
menembak semuanya?

INPUT: Baris 1 N; Baris 2 N bilangan
OUTPUT: satu bilangan
CONSTRAINTS: 1 <= N <= 2*10^5

SAMPLE INPUT 1:            SAMPLE OUTPUT 1:
8                          2
389 207 155 300 299 170 158 65

SAMPLE INPUT 2:            SAMPLE OUTPUT 2:
5                          5
1 2 3 4 5

SAMPLE INPUT 3:            SAMPLE OUTPUT 3:
4                          1
9 7 7 2
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL);
    // TODO: Kerjakan di sini
    // TEOREMA DILWORTH: minimum banyaknya barisan TIDAK NAIK yang menutupi
    // seluruh array = panjang barisan NAIK KETAT terpanjang.
    // Jadi jawabannya adalah LIS ketat. Sampel 2 dan 3 menguji dua ekstremnya.
    return 0;}
