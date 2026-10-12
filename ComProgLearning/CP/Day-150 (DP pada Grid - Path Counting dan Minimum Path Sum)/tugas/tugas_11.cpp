/*
============================================================
📋 TUGAS 11: Dua Jalur Mengumpulkan Permen
============================================================
Source: Klasik (Cherry Pickup / IOI varian)
Difficulty: Hard
Topics: state gabungan, langkah bersamaan

PROBLEM:
Grid R x C berisi permen (non-negatif). Dua orang berjalan dari (0,0) ke
(R-1,C-1), keduanya kanan/bawah. Sel yang dilewati keduanya dihitung sekali.
Maksimalkan total.

INPUT: Baris 1 R C; R baris berisi C bilangan
OUTPUT: satu bilangan
CONSTRAINTS: 1 <= R, C <= 100

SAMPLE INPUT 1:      SAMPLE OUTPUT 1:
2 2                  10
1 2
3 4

SAMPLE INPUT 2:      SAMPLE OUTPUT 2:
1 4                  10
1 2 3 4

SAMPLE INPUT 3:      SAMPLE OUTPUT 3:
3 3                  38
1 2 3
4 5 6
7 8 9
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL);
    // TODO: Kerjakan di sini
    // dp[k][i1][i2], j = k - i. Sel bersama dihitung SEKALI.
    // O(R*C*R), bukan O((R*C)^2) -- itulah gunanya langkah bersamaan.
    return 0;}
