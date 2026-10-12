/*
============================================================
📋 TUGAS 01: Tangga Tiga Langkah (Climbing Stairs 1, 2, atau 3)
============================================================
Source: Classic DP / CSES
Difficulty: Easy
Topics: Top-Down vs Bottom-Up 1D

PROBLEM:
Kamu berdiri di lantai dasar (anak tangga 0) dan ingin mencapai anak tangga ke-N.
Dalam satu langkah, kamu boleh melangkah naik 1, 2, atau 3 anak tangga.
Hitung banyaknya cara berbeda untuk mencapai anak tangga ke-N.
Karena hasilnya bisa sangat besar, keluarkan jawaban modulo 1.000.000.007.

INPUT FORMAT:
Satu bilangan bulat N.

OUTPUT FORMAT:
Satu bilangan bulat: banyaknya cara modulo 1.000.000.007.

CONSTRAINTS:
1 <= N <= 100.000

SAMPLE INPUT 1:
3

SAMPLE OUTPUT 1:
4
(Penjelasan: 1+1+1, 1+2, 2+1, 3)

SAMPLE INPUT 2:
4

SAMPLE OUTPUT 2:
7
(Penjelasan: 1+1+1+1, 1+1+2, 1+2+1, 2+1+1, 2+2, 1+3, 3+1)

SAMPLE INPUT 3:
10

SAMPLE OUTPUT 3:
274
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // TODO: Selesaikan dengan Bottom-Up (atau Top-Down).
    // Basis: dp[0] = 1, dp[1] = 1, dp[2] = 2.
    // Transisi: dp[i] = (dp[i-1] + dp[i-2] + dp[i-3]) % MOD.

    return 0;
}
