/*
============================================================
📋 TUGAS 10: Longest Palindromic Subsequence
============================================================
Source: LC 516
Difficulty: Medium
Topics: LCS dengan dirinya sendiri yang dibalik

PROBLEM: Cari subsekuens palindrom terpanjang dari satu string.
INPUT: satu string
OUTPUT: satu bilangan
CONSTRAINTS: 1 <= |S| <= 1000

SAMPLE INPUT 1:      SAMPLE OUTPUT 1:
bbbab                4

SAMPLE INPUT 2:      SAMPLE OUTPUT 2:
cbbd                 2

SAMPLE INPUT 3:      SAMPLE OUTPUT 3:
abcde                1
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL);
    // TODO: Kerjakan di sini
    // TRIK: LPS(S) = LCS(S, reverse(S)).
    // Buktikan sendiri kenapa ini benar sebelum memakainya -- ini salah satu
    // reduksi tercantik di seluruh materi DP string.
    // (Alternatif: range DP dp[l][r], yang akan dibahas Day 151.)
    return 0;}
