/*
============================================================
📋 TUGAS 9: Stack — Longest Valid Parentheses
============================================================
Source: LeetCode 32 / Classic
Difficulty: Medium
Topics: stack, dynamic programming concept

PROBLEM:
Diberikan string hanya berisi '(' dan ')'.
Cari panjang SUBSTRING terpanjang yang merupakan valid parentheses.

INPUT:
- Satu baris: string s

OUTPUT:
- Satu integer: panjang substring valid parentheses terpanjang

CONSTRAINTS:
- 0 ≤ |s| ≤ 200,000

SAMPLE INPUT:
(()

SAMPLE OUTPUT:
2

SAMPLE INPUT 2:
)()())

SAMPLE OUTPUT 2:
4

SAMPLE INPUT 3:
()(()

SAMPLE OUTPUT 3:
2

NOTE: "()" valid length 2. "(())" valid length 4.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Hint: Stack simpan INDEX. Push -1 sebagai base.
    //       Saat ')': pop. Jika stack kosong push index sebagai base baru.
    //       Jika tidak kosong: length = i - stack.top(). Update max.

    return 0;
}
