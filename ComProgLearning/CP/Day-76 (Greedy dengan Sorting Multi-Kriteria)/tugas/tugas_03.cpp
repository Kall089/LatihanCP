/*
============================================================
📋 TUGAS 03: Russian Doll Envelopes
============================================================
Source: LeetCode 354
Difficulty: Hard
Topics: Tie-break + LIS

PROBLEM:
Ada n amplop berukuran (w, h). Amplop bisa dimasukkan ke amplop lain kalau lebar DAN
tingginya benar-benar lebih kecil. Cari panjang rantai bersarang terpanjang.

INPUT FORMAT:
Baris 1: n
n baris berikutnya: w dan h

OUTPUT FORMAT:
Satu bilangan: panjang rantai terpanjang

CONSTRAINTS:
1 <= n <= 10^5, 1 <= w, h <= 10^5

SAMPLE INPUT 1:
4
5 4
6 4
6 7
2 3

SAMPLE OUTPUT 1:
3
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Tie-break tinggi MENURUN membuat amplop berlebar sama otomatis ditolak oleh algoritma barisan naik. Pakai lower_bound (tegas), bukan upper_bound.

    return 0;
}
