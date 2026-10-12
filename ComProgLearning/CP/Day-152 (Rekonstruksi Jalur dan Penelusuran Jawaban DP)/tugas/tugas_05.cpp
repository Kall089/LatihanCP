/*
============================================================
📋 TUGAS 05: Rekonstruksi LCS Leksikografis Terkecil
============================================================
Source: Classic DP / Lexicographically Smallest LCS
Difficulty: Hard
Topics: LCS 2D DP, Lexicographical String Backtracking

PROBLEM:
Diberikan dua string S dan T.
Di antara SELURUH subsekuens bersama terpanjang (LCS) dari S dan T,
tentukan satu string LCS yang bernilai TERKECIL SECARA LEKSIKOGRAFIS.

INPUT FORMAT:
Baris pertama berisi string S.
Baris kedua berisi string T.

OUTPUT FORMAT:
Satu baris berisi string LCS leksikografis terkecil.

CONSTRAINTS:
1 <= |S|, |T| <= 1.000
String S dan T hanya berisi huruf kecil 'a'..'z'.

SAMPLE INPUT 1:
acba
abac

SAMPLE OUTPUT 1:
ab
(Penjelasan: Dua kemungkinan LCS berpanjang 2 adalah "ac", "ab", "ba".
Yang terkecil secara leksikografis adalah "ab")

SAMPLE INPUT 2:
bba
abb

SAMPLE OUTPUT 2:
bb
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s, t;
    if (!(cin >> s >> t)) return 0;

    // TODO: Selesaikan LCS Leksikografis Terkecil
    // Gunakan Suffix LCS dp[i][j]: panjang LCS dari S[i..] dan T[j..]
    // Rekonstruksi maju dari karakter 'a' s.d. 'z' yang valid

    return 0;
}
