/*
============================================================
📋 TUGAS 15: Query Tutupan Offline
============================================================
Source: Latihan mandiri
Difficulty: Hard
Topics: Sapuan + BIT

PROBLEM:
Diberikan n interval [l, r] dan q pertanyaan. Pertanyaan ke-j berupa satu bilangan x:
berapa banyak interval yang memuat titik x?

INPUT FORMAT:
Baris 1: n dan q
n baris berikutnya: l dan r
q baris berikutnya: x

OUTPUT FORMAT:
q baris, masing-masing satu bilangan

CONSTRAINTS:
1 <= n, q <= 2*10^5, 1 <= l <= r <= 10^9, 1 <= x <= 10^9

SAMPLE INPUT 1:
3 3
1 5
3 7
10 12
4
8
11

SAMPLE OUTPUT 1:
2
0
1
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Dua pendekatan sama-sama benar: (a) difference array di atas koordinat terkompresi lalu prefix sum, (b) offline dengan BIT (Day 170). Kerjakan keduanya dan bandingkan kesederhanaan kodenya — kadang solusi yang lebih 'canggih' justru lebih rawan bug.

    return 0;
}
