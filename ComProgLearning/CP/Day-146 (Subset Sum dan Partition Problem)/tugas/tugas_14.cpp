/*
============================================================
📋 TUGAS 14: Three Equal Groups
============================================================
Source: Practice
Difficulty: Hard
Topics: multi-dimensional subset sum

PROBLEM:
Diberikan N bilangan positif. Tentukan apakah semua bilangan bisa dibagi
menjadi tiga kelompok dengan jumlah yang sama. Setiap bilangan harus masuk
tepat ke salah satu kelompok.

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan A[i]

OUTPUT FORMAT:
- YES jika bisa, NO jika tidak

CONSTRAINTS:
- 1 <= N <= 60
- 1 <= A[i] <= 100
- Total seluruh A[i] <= 1500

SAMPLE INPUT 1:
6
2 1 4 5 6 3

SAMPLE OUTPUT 1:
YES

HINT:
Jika total tidak habis dibagi 3, langsung NO. Jika target tiap kelompok adalah
T, kamu bisa memakai DP dua dimensi: dp[x][y] berarti kelompok pertama bisa
berjumlah x dan kelompok kedua bisa berjumlah y. Sisanya otomatis masuk
kelompok ketiga.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Gunakan DP 2D untuk dua kelompok pertama dengan target total/3.

    return 0;
}
