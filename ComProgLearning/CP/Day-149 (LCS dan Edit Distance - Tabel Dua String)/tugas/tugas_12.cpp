/*
============================================================
📋 TUGAS 12: Regular Expression Matching
============================================================
Source: LC 10
Difficulty: Hard
Topics: tabel dua string, '*' merujuk karakter SEBELUMNYA

PROBLEM:
Pola p boleh memuat '.' (satu karakter apa pun) dan 'x*' (nol atau lebih
kemunculan karakter x sebelumnya). Tentukan apakah s cocok seluruhnya.

INPUT: Baris 1 s; Baris 2 p
OUTPUT: "YA" atau "TIDAK"
CONSTRAINTS: 1 <= |s| <= 20, 1 <= |p| <= 30

SAMPLE INPUT 1:      SAMPLE OUTPUT 1:
aa                   YA
a*

SAMPLE INPUT 2:      SAMPLE OUTPUT 2:
ab                   YA
.*

SAMPLE INPUT 3:      SAMPLE OUTPUT 3:
mississippi          TIDAK
mis*is*p*.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL);
    // TODO: Kerjakan di sini
    // BEDANYA DARI WILDCARD: di sini '*' TIDAK berdiri sendiri -- ia mengubah
    // arti karakter di depannya. Jadi transisinya melompat DUA:
    //   p[j-1] == '*': dp[i][j] = dp[i][j-2]                    (nol kemunculan)
    //                  || (cocok(s[i-1], p[j-2]) && dp[i-1][j]) (satu lagi)
    // Kesalahan umum: memperlakukan '*' seperti pada wildcard matching.
    return 0;}
