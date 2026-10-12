/*
============================================================
📋 TUGAS 02: Panjang Kemiripan Dua Arsip (LCS 2-Row O(min(N, M)))
============================================================
Source: Classic DP / LCS Space Optimization
Difficulty: Medium
Topics: LCS DP, 2-Row Rolling Array

PROBLEM:
Diberikan dua string A dan B.
Tentukan panjang Subsekuens Bersama Terpanjang (LCS) antara A dan B.
Tanda `-` mewakili string kosong.
Gunakan teknik Rolling Array 2 Baris agar pemakaian memori hanya O(min(|A|, |B|)).

INPUT FORMAT:
Satu baris berisi dua token string A dan B dipisahkan oleh spasi.

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: panjang LCS.

CONSTRAINTS:
0 <= |A|, |B| <= 3.000
A dan B berupa string huruf kecil atau tanda `-`

SAMPLE INPUT 1:
abc ac

SAMPLE OUTPUT 1:
2
(LCS adalah "ac" dengan panjang 2)

SAMPLE INPUT 2:
- abc

SAMPLE OUTPUT 2:
0
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string a, b;
    if (!(cin >> a >> b)) return 0;

    // TODO: Selesaikan LCS dengan 2 baris bergantian O(min(|A|, |B|))

    return 0;
}
