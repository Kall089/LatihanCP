/*
============================================================
📋 TUGAS 08: LCS Tiga String
============================================================
Source: Klasik
Difficulty: Medium
Topics: dp tiga dimensi

PROBLEM: Panjang subsekuens bersama terpanjang dari TIGA string.
INPUT: tiga baris
OUTPUT: satu bilangan
CONSTRAINTS: 1 <= panjang <= 100

SAMPLE INPUT 1:      SAMPLE OUTPUT 1:
abcd                 3
acbd
abed
Penjelasan: "abd" muncul sebagai subsekuens di ketiganya.

SAMPLE INPUT 2:      SAMPLE OUTPUT 2:
aaa                  3
aaa
aaa

SAMPLE INPUT 3:      SAMPLE OUTPUT 3:
abc                  0
def
ghi
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL);
    // TODO: Kerjakan di sini
    // dp[i][j][k]: cocok BERTIGA -> diagonal+1 ; selain itu -> max tiga tetangga.
    // O(n^3) memori: 101^3 = ~10^6, aman. Untuk panjang 1000 tidak aman.
    return 0;}
