/*
============================================================
📋 TUGAS 11: Stack — Largest Rectangle in Histogram
============================================================
Source: LeetCode 84 / Classic
Difficulty: Hard
Topics: monotonic stack

PROBLEM:
Diberikan histogram dengan N bar, masing-masing tinggi h[i] dan
lebar 1. Cari luas PERSEGI PANJANG terbesar yang bisa dibentuk
di dalam histogram.

INPUT:
- Baris pertama: integer N
- Baris kedua: N integer (tinggi bar)

OUTPUT:
- Satu integer: luas rectangle terbesar

CONSTRAINTS:
- 1 ≤ N ≤ 200,000
- 1 ≤ h[i] ≤ 1,000,000,000

SAMPLE INPUT:
6
2 1 5 6 2 3

SAMPLE OUTPUT:
10

NOTE: Rectangle dengan tinggi 5, lebar 2 (bar index 2 dan 3) → 5*2 = 10

SAMPLE INPUT 2:
3
3 3 3

SAMPLE OUTPUT 2:
9
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Hint: Monotonic stack (increasing heights). Saat pop:
    //       width = i - stack.top() - 1 (atau i jika stack kosong)
    //       area = h[popped] * width

    return 0;
}
