/*
============================================================
📋 TUGAS 15: Interval Query Offline
============================================================
Source: Latihan mandiri
Difficulty: Hard
Topics: Interval + BIT + offline

PROBLEM:
Diberikan n interval [l, r] dan q pertanyaan. Pertanyaan ke-j berupa sepasang
bilangan (x, y): berapa banyak interval yang SELURUHNYA berada di dalam [x, y],
yaitu memenuhi x <= l dan r <= y?

INPUT FORMAT:
Baris 1: n dan q
n baris berikutnya: l dan r
q baris berikutnya: x dan y

OUTPUT FORMAT:
q baris, masing-masing satu bilangan

CONSTRAINTS:
1 <= n, q <= 2*10^5, 1 <= l <= r <= 10^9, 1 <= x <= y <= 10^9

SAMPLE INPUT 1:
3 2
1 4
2 3
5 8
1 4
1 8

SAMPLE OUTPUT 1:
2
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
    // Butuh Fenwick Tree (Day 170) dan kompresi koordinat (Day 38/40). Urutkan interval dan pertanyaan menurut satu koordinat, lalu proses offline sambil memasukkan interval ke BIT. Pikirkan koordinat mana yang menjadi 'waktu' dan mana yang masuk ke BIT.

    return 0;
}
