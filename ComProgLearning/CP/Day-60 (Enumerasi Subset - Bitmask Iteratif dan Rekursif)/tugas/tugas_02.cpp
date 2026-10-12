/*
============================================================
📋 TUGAS 02: Parity Check
============================================================
Source: Original
Difficulty: Easy
Topics: bitmask, __builtin_parity, __builtin_popcount

PROBLEM:
Diberikan T buah bilangan bulat tidak negatif N.
Untuk setiap N, tentukan apakah jumlah bit aktifnya
ganjil ("ODD") atau genap ("EVEN").

INPUT FORMAT:
- Baris 1: integer T
- T baris berikutnya: satu integer N per baris

OUTPUT FORMAT:
- T baris: "ODD" atau "EVEN" untuk setiap N

CONSTRAINTS:
- 1 ≤ T ≤ 100000
- 0 ≤ N ≤ 10^9

SAMPLE INPUT 1:
4
0
7
5
15

SAMPLE OUTPUT 1:
EVEN
ODD
EVEN
EVEN

SAMPLE INPUT 2:
3
1
2
3

SAMPLE OUTPUT 2:
ODD
ODD
EVEN

NOTE: 0 memiliki 0 bit aktif (genap). 7 = 0b111 memiliki 3 bit aktif (ganjil).
      Gunakan __builtin_parity(N) yang mengembalikan 1 jika jumlah bit ganjil.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        // __builtin_parity returns 1 if popcount is odd
        cout << (__builtin_parity(n) ? "ODD" : "EVEN") << '\n';
    }
    return 0;
}
