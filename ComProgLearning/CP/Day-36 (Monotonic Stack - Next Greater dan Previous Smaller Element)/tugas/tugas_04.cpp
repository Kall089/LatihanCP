/*
============================================================
📋 TUGAS 04: Score of Brackets
============================================================
Source: Original
Difficulty: Easy
Topics: stack, balanced brackets

PROBLEM:
Hitung skor dari string balanced brackets:
- "()" mendapat skor 1
- "AB" (dua string valid bersebelahan) mendapat skor A + B
- "(A)" mendapat skor 2 × A

INPUT FORMAT:
- Satu baris: string s (balanced brackets)

OUTPUT FORMAT:
- Satu baris: integer (skor)

CONSTRAINTS:
- 2 ≤ |s| ≤ 50
- s adalah balanced bracket yang valid

SAMPLE INPUT 1:
(()(()))

SAMPLE OUTPUT 1:
6

SAMPLE INPUT 2:
()()

SAMPLE OUTPUT 2:
2

NOTE: Gunakan stack<int>.
      Push 0 saat '('. Saat ')', pop x: jika x==0 push 1, else push 2*x.
      Gabungkan sisa stack dengan penjumlahan.
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
