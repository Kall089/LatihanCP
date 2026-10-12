/*
============================================================
📋 TUGAS 04: Triangle
============================================================
Source: LC 120
Difficulty: Medium
Topics: tetangga bukan atas/kiri

PROBLEM:
Segitiga dengan baris ke-i berisi i+1 bilangan. Mulai dari puncak; dari
posisi j di baris i boleh turun ke j atau j+1 di baris i+1. Cari total
minimum sampai baris terakhir.

INPUT: Baris 1 N; lalu N baris segitiga
OUTPUT: satu bilangan
CONSTRAINTS: 1 <= N <= 200, |a| <= 10^4

SAMPLE INPUT 1:      SAMPLE OUTPUT 1:
4                    11
2
3 4
6 5 7
4 1 8 3

SAMPLE INPUT 2:      SAMPLE OUTPUT 2:
1                    -10
-10

SAMPLE INPUT 3:      SAMPLE OUTPUT 3:
2                    3
1
2 5
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL);
    // TODO: Kerjakan di sini
    // Tetangganya (i-1,j-1) dan (i-1,j). Bentuk tabelnya berubah, tapi
    // STRUKTUR DAG-nya sama. Coba juga versi bottom-up (dari bawah ke atas):
    // di situ tidak perlu penjagaan tepi sama sekali.
    return 0;}
