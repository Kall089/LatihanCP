/*
============================================================
📋 TUGAS 15: Subarray Maksimum dengan Panjang Minimum L
============================================================
Source: Varian kontes
Difficulty: Hard
Topics: prefix sum + minimum prefiks bergeser

PROBLEM:
Cari subarray dengan PANJANG MINIMAL L yang jumlahnya maksimum.

INPUT FORMAT:
- Baris 1: N L
- Baris 2: N bilangan
OUTPUT FORMAT: satu bilangan
CONSTRAINTS: 1 <= L <= N <= 2*10^5, |a[i]| <= 10^9

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
5 2                    9
1 -2 5 4 -3

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
4 4                    -2
1 -2 -3 2

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
3 1                    5
-1 5 -1
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // Kadane biasa TIDAK bisa memaksakan panjang minimum.
    // Pakai prefix sum P: jawaban = max over i>=L of (P[i] - min P[j] untuk
    // j <= i-L). Pelihara minimum prefiks yang TERTUNDA L langkah.
    // Ini juga memperlihatkan kenapa versi prefix-sum dari Kadane lebih mudah
    // diperluas daripada versi "cur" yang klasik.
    return 0;
}
