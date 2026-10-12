/*
============================================================
📋 TUGAS 07: Subsekuens Palindrom Terpanjang (LPS)
============================================================
Source: LeetCode 516 / Classic DP
Difficulty: Medium
Topics: Range DP on Subsequences

PROBLEM:
Diberikan sebuah string S. Tentukan panjang SUBSEKUENS palindrom TERPANJANG yang ada di dalam S.
Subsekuens adalah barisan karakter yang dapat diperoleh dengan menghapus nol atau lebih
karakter dari string tanpa mengubah urutan relatif karakter yang tersisa.

INPUT FORMAT:
Satu baris berisi satu string S tanpa spasi.

OUTPUT FORMAT:
Satu bilangan bulat: panjang subsekuens palindrom terpanjang.

CONSTRAINTS:
1 <= |S| <= 1.000
S hanya berisi huruf kecil 'a'..'z'.

SAMPLE INPUT 1:
bbbab

SAMPLE OUTPUT 1:
4
(Penjelasan: Salah satu subsekuens palindrom terpanjang adalah "bbbb" dengan panjang 4)

SAMPLE INPUT 2:
cbbd

SAMPLE OUTPUT 2:
2
(Penjelasan: Subsekuens palindrom terpanjang adalah "bb" dengan panjang 2)
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

    // TODO: Selesaikan LPS dengan Range DP
    // dp[l][r] = panjang LPS dalam S[l..r]
    // Basis: dp[i][i] = 1
    // Jika S[l] == S[r]: dp[l][r] = dp[l+1][r-1] + 2
    // Jika S[l] != S[r]: dp[l][r] = max(dp[l+1][r], dp[l][r-1])

    return 0;
}
