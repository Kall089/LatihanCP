/*
============================================================
📋 TUGAS 01: Bit Toggle Game
============================================================
Source: Original
Difficulty: Easy
Topics: bitmask, XOR, toggle, __builtin_popcount

PROBLEM:
Terdapat sebuah bilangan N. Diberikan q operasi, masing-masing
berupa "TOGGLE i" yang men-toggle bit ke-i dari N (flip 0→1 atau 1→0).
Setelah semua operasi, cetak nilai N akhir dan jumlah bit aktifnya.

INPUT FORMAT:
- Baris 1: dua integer N dan q
- q baris berikutnya: "TOGGLE i"

OUTPUT FORMAT:
- Satu baris: nilai N akhir diikuti spasi dan jumlah bit aktif

CONSTRAINTS:
- 0 ≤ N < 2^30
- 1 ≤ q ≤ 1000
- 0 ≤ i ≤ 29

SAMPLE INPUT 1:
0 3
TOGGLE 2
TOGGLE 5
TOGGLE 2

SAMPLE OUTPUT 1:
32 1

SAMPLE INPUT 2:
15 2
TOGGLE 0
TOGGLE 3

SAMPLE OUTPUT 2:
6 2

NOTE: TOGGLE i sama dengan N ^= (1 << i).
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long N;
    int q;
    cin >> N >> q;

    string op;
    int bit;
    while (q--) {
        cin >> op >> bit;          // op always "TOGGLE"
        N ^= (1LL << bit);        // flip bit ke-bit
    }

    cout << N << ' ' << __builtin_popcountll(N) << '\n';
    return 0;
}
