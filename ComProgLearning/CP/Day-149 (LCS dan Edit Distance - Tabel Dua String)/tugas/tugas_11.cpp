/*
============================================================
📋 TUGAS 11: Wildcard Matching
============================================================
Source: LC 44
Difficulty: Hard
Topics: tabel dua string dengan karakter khusus

PROBLEM:
Pola p boleh memuat '?' (cocok tepat satu karakter apa pun) dan '*' (cocok
dengan barisan karakter apa pun, termasuk kosong). Tentukan apakah s cocok
SELURUHNYA dengan p.

INPUT: Baris 1 s; Baris 2 p
OUTPUT: "YA" atau "TIDAK"
CONSTRAINTS: 0 <= |s|, |p| <= 2000

SAMPLE INPUT 1:      SAMPLE OUTPUT 1:
aa                   TIDAK
a

SAMPLE INPUT 2:      SAMPLE OUTPUT 2:
adceb                YA
*a*b

SAMPLE INPUT 3:      SAMPLE OUTPUT 3:
acdcb                TIDAK
a*c?b
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL);
    // TODO: Kerjakan di sini
    // dp[i][j] = apakah s[0..i-1] cocok dengan p[0..j-1] (bool).
    // p[j-1] == '*'  -> dp[i][j] = dp[i][j-1] (pakai kosong) || dp[i-1][j] (telan satu)
    // p[j-1] == '?' atau cocok -> dp[i][j] = dp[i-1][j-1]
    // BASE PENTING: dp[0][j] benar hanya kalau p[0..j-1] SELURUHNYA '*'.
    return 0;}
