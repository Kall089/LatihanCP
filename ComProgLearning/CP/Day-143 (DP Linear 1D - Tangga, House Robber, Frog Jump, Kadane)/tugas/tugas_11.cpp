/*
============================================================
📋 TUGAS 11: Kadane 2D (Submatriks dengan Jumlah Maksimum)
============================================================
Source: Klasik (SPOJ KGSS varian / maximum sum rectangle)
Difficulty: Hard
Topics: Kadane + kompresi kolom

PROBLEM:
Matriks R x C berisi bilangan (boleh negatif). Cari submatriks tidak kosong
dengan jumlah maksimum.

INPUT FORMAT:
- Baris 1: R C
- R baris berisi C bilangan
OUTPUT FORMAT: satu bilangan
CONSTRAINTS: 1 <= R, C <= 300, |a[i][j]| <= 10^9

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
3 3                    12
1 2 -1
-3 4 5
2 -1 3

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
2 2                    -1
-1 -2
-3 -4

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
1 4                    6
1 -2 3 -1
Penjelasan: submatriks 1x1 sampai 1x4; jawabannya subarray biasa.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // Untuk setiap pasangan baris (atas, bawah): jumlahkan kolom menjadi satu
    // array 1D, lalu jalankan KADANE di atasnya. O(R^2 * C).
    // Ini contoh terbaik bahwa menguasai DP 1D langsung membuka soal 2D.
    return 0;
}
