/*
============================================================
📋 TUGAS 12: Interval dengan Bobot Tutupan
============================================================
Source: Latihan mandiri
Difficulty: Hard
Topics: Covering + DP

PROBLEM:
Diberikan n interval; interval ke-i mencakup [l, r] dan berbiaya c[i].
Cari BIAYA TOTAL MINIMUM untuk menutupi [0, T] seluruhnya, atau -1 kalau tidak
mungkin.

INPUT FORMAT:
Baris 1: n dan T
n baris berikutnya: l, r, dan c

OUTPUT FORMAT:
Satu bilangan: biaya minimum, atau -1

CONSTRAINTS:
1 <= n <= 2000, 1 <= T <= 10^9, 0 <= l <= r <= 10^9, 1 <= c <= 10^9

SAMPLE INPUT 1:
3 10
0 5 1
4 10 5
0 10 10

SAMPLE OUTPUT 1:
6
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Dengan biaya, greedy jangkauan terjauh TIDAK berlaku lagi — sama seperti Day 72 Exercise 5. Buktikan sendiri dengan contoh tandingan, lalu susun DP di atas koordinat terkompresi.

    return 0;
}
