/*
============================================================
📋 TUGAS 10: Decode String
============================================================
Source: Original
Difficulty: Medium
Topics: stack, string, parsing

PROBLEM:
Diberikan encoded string dengan format k[string] yang artinya string
diulang k kali. k selalu positif integer. Decode string tersebut.
(k tidak memiliki leading zero)

INPUT FORMAT:
- Satu baris: encoded string s

OUTPUT FORMAT:
- Satu baris: decoded string

CONSTRAINTS:
- 1 ≤ |s| ≤ 30
- Output tidak melebihi 10^5 karakter
- Hanya berisi digit 0-9, huruf kecil a-z, '[', ']'

SAMPLE INPUT 1:
3[a]2[bc]

SAMPLE OUTPUT 1:
aaabcbc

SAMPLE INPUT 2:
3[a2[c]]

SAMPLE OUTPUT 2:
accaccacc

NOTE: Gunakan dua stack: stack<int> untuk angka, stack<string> untuk string.
      Saat '[': push k dan push current string, reset keduanya.
      Saat ']': pop k dan prev_str. current = prev_str + k * current.
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
