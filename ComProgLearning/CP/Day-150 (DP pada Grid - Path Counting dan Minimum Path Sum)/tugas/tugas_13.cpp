/*
============================================================
📋 TUGAS 13: Grid 4 Arah — Kapan DP Menyerah
============================================================
Source: Latihan sintesis (pembatas Day 150)
Difficulty: Hard
Topics: mengenali batas DP

PROBLEM:
Grid R x C berisi biaya non-negatif. Kali ini gerakan diizinkan ke EMPAT arah
(atas, bawah, kiri, kanan). Cari total biaya minimum dari (0,0) ke (R-1,C-1),
di mana biaya sebuah jalur adalah jumlah biaya sel yang diinjak (termasuk
kedua ujung).

INPUT: Baris 1 R C; R baris berisi C bilangan
OUTPUT: satu bilangan
CONSTRAINTS: 1 <= R, C <= 500, 0 <= a[i][j] <= 10^9

SAMPLE INPUT 1:      SAMPLE OUTPUT 1:
3 3                  7
1 3 1
1 5 1
4 2 1

SAMPLE INPUT 2:      SAMPLE OUTPUT 2:
1 1                  5
5

SAMPLE INPUT 3:      SAMPLE OUTPUT 3:
2 3                  6
1 9 1
1 1 1
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL);
    // TODO: Kerjakan di sini
    // JANGAN memakai DP. Dengan 4 arah, argumen "i+j selalu naik" runtuh dan
    // grafnya BERSIKLUS -- tidak ada urutan topologis, jadi DP tidak
    // terdefinisi.
    // Pakai DIJKSTRA (Day 127): simpul = sel, id = i*C + j, bobot masuk = a[i][j].
    // Kerjakan juga versi DP kanan-bawahnya, lalu bandingkan pada Sampel 3 --
    // di situ jawabannya berbeda, dan itulah buktinya.
    return 0;}
