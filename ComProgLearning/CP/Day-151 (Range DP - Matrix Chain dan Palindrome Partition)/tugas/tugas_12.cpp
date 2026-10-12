/*
============================================================
📋 TUGAS 12: Cetak Palindrom Terpendek (Shortest Palindromic Supersequence)
============================================================
Source: Classic DP / LeetCode 1092 Variation
Difficulty: Hard
Topics: Range DP Reconstruction, Palindromic Supersequence

PROBLEM:
Diberikan sebuah string S. Buatlah sebuah string palindrom terpendek yang memuat
string S sebagai salah satu subsekuensnya.
Jika ada beberapa kemungkinan string palindrom terpendek, cetak salah satu yang valid.

INPUT FORMAT:
Satu baris berisi string S tanpa spasi.

OUTPUT FORMAT:
Satu baris string: string palindrom terpendek yang memuat S.

CONSTRAINTS:
1 <= |S| <= 500
S hanya berisi huruf kecil 'a'..'z'.

SAMPLE INPUT 1:
ab

SAMPLE OUTPUT 1:
aba
(Catatan: "bab" juga jawaban yang valid)

SAMPLE INPUT 2:
racecar

SAMPLE OUTPUT 2:
racecar
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;

    int n = s.size();

    // TODO: Selesaikan Shortest Palindromic Supersequence
    // 1. dp[l][r] = panjang minimum palindrom supersequence untuk S[l..r]
    // 2. Backtracking dari (0, n-1) untuk merekonstruksi string

    return 0;
}
