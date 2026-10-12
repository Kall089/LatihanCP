/*
============================================================
📋 TUGAS 09: Dungeon Game
============================================================
Source: LC 174
Difficulty: Hard
Topics: DP arah TERBALIK

PROBLEM:
Grid berisi perubahan HP (bisa negatif). Ksatria berjalan dari kiri-atas ke
kanan-bawah (kanan/bawah). HP-nya tidak boleh mencapai 0 KAPAN PUN.
Cari HP AWAL minimum.

INPUT: Baris 1 R C; R baris berisi C bilangan
OUTPUT: satu bilangan
CONSTRAINTS: 1 <= R, C <= 200

SAMPLE INPUT 1:      SAMPLE OUTPUT 1:
3 3                  7
-2 -3 3
-5 -10 1
10 30 -5

SAMPLE INPUT 2:      SAMPLE OUTPUT 2:
1 1                  1
0

SAMPLE INPUT 3:      SAMPLE OUTPUT 3:
1 2                  6
-5 0
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL);
    // TODO: Kerjakan di sini
    // DP MAJU TIDAK BEKERJA: "HP tertinggi sekarang" tidak menjamin kebutuhan
    // masa depan terkecil -- dua besaran itu tidak bisa dioptimalkan bersamaan.
    // Balik arahnya: dp[i][j] = HP MINIMUM yang dibutuhkan SAAT MEMASUKI (i,j)
    // agar bisa selamat sampai tujuan. Isi dari kanan-bawah ke kiri-atas.
    //     dp[i][j] = max(1, min(dp[i+1][j], dp[i][j+1]) - a[i][j])
    // Kalau DP majumu terasa buntu, membalik arah adalah hal pertama yang
    // patut dicoba.
    return 0;}
