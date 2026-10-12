/*
============================================================
📋 TUGAS 03: Playlist Tanpa Genre Berurutan
============================================================
Source: Original
Difficulty: Medium
Topics: State Design, Counting DP

PROBLEM:
Kamu diminta menyusun sebuah playlist yang terdiri dari N slot lagu berurutan.
Tersedia G pilihan genre musik berbeda (berlabel 0 sampai G-1).
Setiap slot wajib diisi tepat satu genre musik.
Aturan: Tidak boleh ada dua slot bersebelahan yang memiliki genre musik yang sama.
Hitung banyaknya kemungkinan susunan playlist berbeda modulo 1.000.000.007.
Untuk N = 0, didefinisikan terdapat tepat 1 playlist kosong.

INPUT FORMAT:
Satu baris berisi dua bilangan bulat N dan G.

OUTPUT FORMAT:
Satu bilangan bulat: banyak kemungkinan playlist modulo 1.000.000.007.

CONSTRAINTS:
0 <= N <= 100.000
1 <= G <= 100

SAMPLE INPUT 1:
3 2

SAMPLE OUTPUT 1:
2
(Penjelasan: Genre {A, B}. Playlist valid: ABA dan BAB.)

SAMPLE INPUT 2:
1 4

SAMPLE OUTPUT 2:
4
(Penjelasan: Slot tunggal bisa diisi genre apa pun dari 4 genre.)

SAMPLE INPUT 3:
4 3

SAMPLE OUTPUT 3:
24
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, g;
    if (!(cin >> n >> g)) return 0;

    // TODO: Selesaikan dengan DP atau analisis kombinatorik transisi
    // Slot 1: G pilihan
    // Slot 2 s.d. N: masing-masing memiliki (G - 1) pilihan

    return 0;
}
