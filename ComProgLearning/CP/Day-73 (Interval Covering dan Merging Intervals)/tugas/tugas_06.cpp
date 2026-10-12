/*
============================================================
📋 TUGAS 06: Interval List Intersections
============================================================
Source: LeetCode 986
Difficulty: Medium
Topics: Irisan dua daftar

PROBLEM:
Diberikan DUA daftar interval yang masing-masing sudah terurut dan saling terpisah.
Cetak irisan kedua daftar itu, yaitu semua rentang yang termuat di kedua daftar.

INPUT FORMAT:
Baris 1: n dan m
n baris berikutnya: interval daftar pertama
m baris berikutnya: interval daftar kedua

OUTPUT FORMAT:
Baris 1: banyaknya interval hasil
Baris berikutnya: masing-masing satu interval

CONSTRAINTS:
0 <= n, m <= 1000, 0 <= koordinat <= 10^9

SAMPLE INPUT 1:
4 3
0 2
5 10
13 23
24 25
1 5
8 12
15 24

SAMPLE OUTPUT 1:
5
1 2
5 5
8 10
15 23
24 24
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Dua penunjuk. Irisan A[i] dan B[j] adalah [max(l), min(r)], valid bila l <= r. Majukan penunjuk yang r-nya lebih kecil — pikirkan kenapa itu aman.

    return 0;
}
