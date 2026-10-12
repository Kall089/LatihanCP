/*
============================================================
📋 TUGAS 13: LCS Dua Permutasi dalam O(n log n)
============================================================
Source: Klasik (jembatan Day 148 <-> Day 149)
Difficulty: Hard
Topics: reduksi LCS -> LIS

PROBLEM:
Diberi DUA permutasi dari 1..N. Cari panjang LCS-nya. N besar, jadi O(N^2)
tidak cukup.

INPUT: Baris 1 N; Baris 2 permutasi A; Baris 3 permutasi B
OUTPUT: satu bilangan
CONSTRAINTS: 1 <= N <= 2*10^5

SAMPLE INPUT 1:            SAMPLE OUTPUT 1:
5                          3
1 2 3 4 5
1 3 5 2 4

SAMPLE INPUT 2:            SAMPLE OUTPUT 2:
4                          1
1 2 3 4
4 3 2 1

SAMPLE INPUT 3:            SAMPLE OUTPUT 3:
3                          3
1 2 3
1 2 3
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL);
    // TODO: Kerjakan di sini
    // REDUKSI: beri setiap nilai posisinya di B, yaitu pos[v].
    // Ganti A menjadi barisan pos[A[i]]. LCS(A,B) = LIS dari barisan itu.
    // Kenapa? Subsekuens bersama = himpunan nilai yang urutannya naik di
    // KEDUA permutasi -- dan setelah pemetaan, "naik di B" menjadi
    // "nilainya naik". Reduksi ini HANYA berlaku untuk permutasi
    // (setiap nilai muncul tepat sekali).
    return 0;}
