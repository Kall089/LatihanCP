/*
============================================================
📋 TUGAS 04: Video Stitching
============================================================
Source: LeetCode 1024
Difficulty: Medium
Topics: Interval covering

PROBLEM:
Ada n potongan video; potongan ke-i mencakup rentang waktu [l, r] dari sebuah video
olahraga berdurasi T.
Cari jumlah potongan MINIMUM agar seluruh [0, T] tercakup, atau -1 kalau tidak mungkin.

INPUT FORMAT:
Baris 1: n dan T
n baris berikutnya: l dan r

OUTPUT FORMAT:
Satu bilangan: jumlah potongan minimum, atau -1

CONSTRAINTS:
1 <= n <= 100, 1 <= T <= 100, 0 <= l < r <= 100

SAMPLE INPUT 1:
6 10
0 2
4 6
8 10
1 9
1 5
5 9

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
    // Greedy jangkauan terjauh, identik dengan Exercise 3. Jangan lupa kasus -1.

    return 0;
}
