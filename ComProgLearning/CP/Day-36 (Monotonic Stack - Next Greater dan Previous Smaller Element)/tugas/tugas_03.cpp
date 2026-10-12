/*
============================================================
📋 TUGAS 03: Remove Outer Brackets
============================================================
Source: Original
Difficulty: Easy
Topics: stack, balanced brackets, string

PROBLEM:
String s merupakan primitive string jika s valid (balanced) dan tidak bisa
dibagi menjadi dua non-empty string valid. Dekomposisi s = P1 + P2 + ... + Pk
di mana semua Pi adalah primitive.

Hapus outer bracket dari setiap primitive string dan gabungkan hasilnya.

INPUT FORMAT:
- Satu baris: string s

OUTPUT FORMAT:
- Satu baris: string hasil

CONSTRAINTS:
- 1 ≤ |s| ≤ 10^5
- s valid balanced, hanya berisi '(' dan ')'

SAMPLE INPUT 1:
(()())(())

SAMPLE OUTPUT 1:
()()()

SAMPLE INPUT 2:
(())(())

SAMPLE OUTPUT 2:
()()
NOTE: Gunakan counter depth. Jika depth > 0 sebelum push '(' → tambah ke output.
      Jika depth > 1 sebelum pop ')' → tambah ke output.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO
    return 0;
}
