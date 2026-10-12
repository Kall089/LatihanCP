/*
============================================================
📋 TUGAS 10: Jalur dengan Tepat K Belokan
============================================================
Source: Varian kontes
Difficulty: Hard
Topics: dimensi arah + hitungan belokan

PROBLEM:
Hitung banyak jalur kiri-atas ke kanan-bawah (kanan/bawah) yang memiliki
TEPAT K belokan. Modulo 10^9+7.
Belokan = perubahan arah antara dua langkah berurutan.

INPUT: R C K
OUTPUT: satu bilangan
CONSTRAINTS: 1 <= R, C <= 500, 0 <= K <= R+C

SAMPLE INPUT 1:   SAMPLE OUTPUT 1:
2 2 1             2

SAMPLE INPUT 2:   SAMPLE OUTPUT 2:
2 2 0             0

SAMPLE INPUT 3:   SAMPLE OUTPUT 3:
3 3 2             2
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL);
    // TODO: Kerjakan di sini
    // dp[i][j][arah][k]: arah = langkah TERAKHIR (0 = kanan, 1 = bawah).
    // Dimensi arah diperlukan karena "belokan" bergantung pada arah datang.
    // Transisi: arah sama -> k tetap ; arah berbeda -> k+1.
    // Perhatikan inisialisasi langkah PERTAMA (belum ada arah sebelumnya).
    return 0;}
