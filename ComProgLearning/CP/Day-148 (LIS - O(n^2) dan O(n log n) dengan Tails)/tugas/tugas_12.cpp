/*
============================================================
📋 TUGAS 12: Menghitung Banyak LIS dalam O(n log n)
============================================================
Source: Varian LC 673
Difficulty: Hard
Topics: Fenwick menyimpan pasangan (panjang, jumlah)

PROBLEM:
Sama seperti Tugas 06, tetapi N sampai 2*10^5 sehingga O(n^2) TLE.

INPUT: Baris 1 N; Baris 2 N bilangan
OUTPUT: dua bilangan: panjang LIS, dan banyaknya (mod 10^9+7)
CONSTRAINTS: 1 <= N <= 2*10^5, |a[i]| <= 10^9

SAMPLE INPUT 1:            SAMPLE OUTPUT 1:
5                          4 2
1 3 5 4 7

SAMPLE INPUT 2:            SAMPLE OUTPUT 2:
4                          1 4
2 2 2 2

SAMPLE INPUT 3:            SAMPLE OUTPUT 3:
6                          4 3
1 2 4 3 5 4
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL);
    // TODO: Kerjakan di sini
    // Kompresi koordinat dulu (Day 38). Fenwick menyimpan node berisi
    // (maxLen, count); operasi gabungnya: len lebih besar -> ganti,
    // len sama -> jumlahkan count. Perhatikan bahwa gabungan ini ASOSIATIF
    // dan punya elemen netral (0, 0) -- itulah syarat agar BIT sah dipakai.
    return 0;}
