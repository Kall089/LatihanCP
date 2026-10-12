/*
============================================================
📋 TUGAS 03: Bit Reversal
============================================================
Source: Original
Difficulty: Easy
Topics: bitmask, bit manipulation, reverse

PROBLEM:
Diberikan bilangan N dan panjang representasi biner k.
Balik k bit pertama (bit ke-0 sampai bit ke-(k-1)) dari N,
lalu cetak hasilnya. Dijamin 0 ≤ N < 2^k.

INPUT FORMAT:
- Satu baris: dua integer N dan k

OUTPUT FORMAT:
- Satu integer: hasil setelah k bit pertama dibalik

CONSTRAINTS:
- 0 ≤ N < 2^k
- 1 ≤ k ≤ 30

SAMPLE INPUT 1:
13 4

SAMPLE OUTPUT 1:
11

SAMPLE INPUT 2:
6 3

SAMPLE OUTPUT 2:
3

NOTE: 13 dalam biner 4-bit = 1101. Dibalik = 1011 = 11.
      6 dalam biner 3-bit = 110. Dibalik = 011 = 3.
      Cara mudah: iterasi i dari 0 sampai k/2-1, tukar bit i dengan bit (k-1-i).
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;

    // Swap bit i with bit (k-1-i) for i = 0..k/2-1
    for (int i = 0; i < k / 2; i++) {
        int j = k - 1 - i;
        int bi = (n >> i) & 1;
        int bj = (n >> j) & 1;
        if (bi != bj) {
            n ^= (1 << i);    // flip bit i
            n ^= (1 << j);    // flip bit j
        }
    }

    cout << n << '\n';
    return 0;
}
