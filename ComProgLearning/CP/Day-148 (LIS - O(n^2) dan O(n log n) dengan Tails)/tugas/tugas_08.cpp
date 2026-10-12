/*
============================================================
📋 TUGAS 08: Rekonstruksi LIS Leksikografis Terkecil
============================================================
Source: Varian latihan
Difficulty: Medium
Topics: rekonstruksi + tie-break

PROBLEM:
Cetak panjang LIS lalu barisan LIS yang LEKSIKOGRAFIS TERKECIL di antara
semua LIS yang sah.

INPUT: Baris 1 N; Baris 2 N bilangan
OUTPUT: dua baris
CONSTRAINTS: 1 <= N <= 5000

SAMPLE INPUT 1:            SAMPLE OUTPUT 1:
8                          4
3 1 4 1 5 9 2 6            1 4 5 6

SAMPLE INPUT 2:            SAMPLE OUTPUT 2:
5                          4
1 3 5 4 7                  1 3 4 7

SAMPLE INPUT 3:            SAMPLE OUTPUT 3:
3                          1
5 5 5                      5
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL);
    // TODO: Kerjakan di sini
    // Dengan N <= 5000, versi O(n^2) lebih mudah dikendalikan untuk tie-break.
    // Hitung dp mundur (panjang LIS yang MULAI di i), lalu bangun barisan dari
    // kiri dengan selalu memilih NILAI TERKECIL yang masih memungkinkan
    // panjang penuh.
    return 0;}
