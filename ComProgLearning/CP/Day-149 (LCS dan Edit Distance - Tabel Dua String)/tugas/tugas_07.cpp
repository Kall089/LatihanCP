/*
============================================================
📋 TUGAS 07: Edit Distance dengan Biaya Berbeda
============================================================
Source: Varian klasik
Difficulty: Medium
Topics: DP berbobot

PROBLEM:
Biaya sisip = ci, hapus = cd, ganti = cr. Cari total biaya minimum mengubah
A menjadi B.

INPUT:
- Baris 1: A
- Baris 2: B
- Baris 3: ci cd cr
OUTPUT: satu bilangan (long long)
CONSTRAINTS: 1 <= |A|, |B| <= 2000; 1 <= biaya <= 10^9

SAMPLE INPUT 1:      SAMPLE OUTPUT 1:
abc                  2
abd
1 1 3
Penjelasan: ganti berbiaya 3, sedangkan hapus+sisip hanya 1+1=2.
min() memilih yang lebih murah tanpa perlu if tambahan.

SAMPLE INPUT 2:      SAMPLE OUTPUT 2:
abc                  1
abd
5 5 1

SAMPLE INPUT 3:      SAMPLE OUTPUT 3:
abc                  0
abc
7 7 7
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL);
    // TODO: Kerjakan di sini
    // dp[i][0] = i*cd ; dp[0][j] = j*ci
    // min() otomatis memilih hapus+sisip kalau cr > ci + cd -- tidak perlu if.
    return 0;}
