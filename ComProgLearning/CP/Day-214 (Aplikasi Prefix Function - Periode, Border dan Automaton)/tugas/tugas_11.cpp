/*
============================================================
📋 TUGAS 11: Sensor Dua Pola
============================================================
Source: Original
Difficulty: Hard
Topics: automaton, state gabungan

PROBLEM:
Diberikan dua pola P1 dan P2 dan panjang L. Hitung banyaknya string
sepanjang L atas alfabet A huruf pertama yang tidak memuat P1 maupun P2.
Cetak hasilnya modulo 1_000_000_007.

INPUT FORMAT:
- Baris pertama: L dan A
- Baris kedua: P1
- Baris ketiga: P2

OUTPUT FORMAT:
- Satu bilangan mod 1e9+7

CONSTRAINTS:
- 1 <= L <= 1000
- 1 <= A <= 26
- 1 <= |P1|, |P2| <= 50

SAMPLE INPUT 1:
3 2
aa
bb

SAMPLE OUTPUT 1:
4
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // State DP = pasangan (state automaton P1, state automaton P2). Atau pelajari Aho-Corasick (Day 219).

    return 0;
}
