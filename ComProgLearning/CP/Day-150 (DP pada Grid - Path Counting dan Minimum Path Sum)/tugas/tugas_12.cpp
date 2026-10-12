/*
============================================================
📋 TUGAS 12: Grid Berlapis — K Tembok Boleh Dihancurkan
============================================================
Source: Varian kontes
Difficulty: Hard
Topics: dimensi tambahan dp[i][j][k]

PROBLEM:
Grid R x C dengan '.' dan '#'. Kamu boleh MENGHANCURKAN sampai K tembok.
Cari banyak jalur kiri-atas ke kanan-bawah (kanan/bawah) modulo 10^9+7,
dengan paling banyak K tembok dihancurkan sepanjang jalur.

INPUT: Baris 1 R C K; R baris grid
OUTPUT: satu bilangan
CONSTRAINTS: 1 <= R, C <= 500, 0 <= K <= 10

SAMPLE INPUT 1:      SAMPLE OUTPUT 1:
2 2 1                2
.#
..

SAMPLE INPUT 2:      SAMPLE OUTPUT 2:
2 2 0                1
.#
..

SAMPLE INPUT 3:      SAMPLE OUTPUT 3:
2 2 2                0
##
##
Penjelasan: sel awal dan tujuan juga tembok, dan KEDUANYA ikut memakai jatah K.
Setiap jalur menyentuh 3 sel, jadi butuh 3 penghancuran -- lebih dari K=2,
sehingga jawabannya 0.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL);
    // TODO: Kerjakan di sini
    // dp[i][j][k] = banyak jalur ke (i,j) dengan k tembok sudah dihancurkan.
    // Transisi: sel '.' -> k tetap ; sel '#' -> datang dari k-1.
    // Dimensi grid tetap dikendalikan urutan baris; dimensi k di dalamnya.
    // O(R*C*K).
    return 0;}
