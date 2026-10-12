/*
============================================================
📋 TUGAS 14: Jumlah Maksimum Tanpa Tiga Berturut-turut
============================================================
Source: Varian klasik
Difficulty: Hard
Topics: state tambahan "sudah berapa berturut-turut"

PROBLEM:
Diberi array N bilangan. Ambil sebanyak mungkin nilai, TETAPI tidak boleh
mengambil TIGA elemen berturut-turut (dua bersebelahan masih boleh).
Maksimalkan totalnya.

INPUT FORMAT:
- Baris 1: N
- Baris 2: N bilangan
OUTPUT FORMAT: satu bilangan
CONSTRAINTS: 1 <= N <= 2*10^5, 0 <= a[i] <= 10^9

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
4                      8
1 2 3 4
Penjelasan: ambil indeks 0, 2, 3 -> 1 + 3 + 4 = 8. Indeks 1,2,3 dilarang
karena tiga berturut-turut.

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
3                      2
1 1 1
Penjelasan: tidak boleh mengambil ketiganya sekaligus.

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
2                      7
3 4
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // dp[i][j] = maksimum sampai i dengan j elemen terakhir BERTURUT diambil
    // (j = 0, 1, 2). Perhatikan bahwa ini masih "DP linear 1D" -- indeksnya
    // linear; state tambahannya hanya konstanta kecil.
    return 0;
}
