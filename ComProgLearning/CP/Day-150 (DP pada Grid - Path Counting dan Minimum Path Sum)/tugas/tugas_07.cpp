/*
============================================================
📋 TUGAS 07: Hitung Jalur dengan Kombinatorika
============================================================
Source: Latihan sintesis
Difficulty: Medium
Topics: C(R+C-2, R-1), invers modular

PROBLEM:
Grid TANPA halangan, tetapi R dan C bisa sampai 10^6 sehingga tabel O(R*C)
mustahil. Cetak banyak jalur modulo 10^9+7.

INPUT: R C
OUTPUT: satu bilangan
CONSTRAINTS: 1 <= R, C <= 10^6

SAMPLE INPUT 1:   SAMPLE OUTPUT 1:
3 7               28

SAMPLE INPUT 2:   SAMPLE OUTPUT 2:
1 1000000         1

SAMPLE INPUT 3:   SAMPLE OUTPUT 3:
1000 1000         965601742
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL);
    // TODO: Kerjakan di sini
    // Setiap jalur = barisan (R-1) langkah bawah dan (C-1) langkah kanan.
    // Jalurnya ditentukan sepenuhnya oleh POSISI MANA yang dipilih untuk
    // langkah bawah -> C(R+C-2, R-1).
    // Faktorial sampai R+C, invers modular lewat Fermat (Day 90-an). O(R+C).
    return 0;}
