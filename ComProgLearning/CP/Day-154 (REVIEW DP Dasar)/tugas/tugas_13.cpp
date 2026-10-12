/*
============================================================
📋 TUGAS 13: Subsekuens Bersama Terpanjang dari Tiga String (LCS 3D)
============================================================
Source: Classic DP / LCS of Three Strings
Difficulty: Medium
Topics: 3D DP, String Subsequences

PROBLEM:
Diberikan tiga buah string S1, S2, dan S3.
Tentukan PANJANG dari Subsekuens Bersama Terpanjang (LCS) yang ada pada KETIGA STRING tersebut!

INPUT FORMAT:
Baris pertama berisi string S1.
Baris kedua berisi string S2.
Baris ketiga berisi string S3.

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: panjang LCS dari 3 string.

CONSTRAINTS:
1 <= |S1|, |S2|, |S3| <= 100
Karakter hanya huruf kecil 'a'..'z'

SAMPLE INPUT 1:
geeks
geeksfor
geeksforgeeks

SAMPLE OUTPUT 1:
5
(LCS adalah "geeks", panjang 5)

SAMPLE INPUT 2:
abcd1e2
bc12ea
bd1ea

SAMPLE OUTPUT 2:
3
(LCS adalah "b1e" atau "b1a", panjang 3)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s1, s2, s3;
    if (!(cin >> s1 >> s2 >> s3)) return 0;

    // TODO: Selesaikan LCS 3 String dengan tabel 3D dp[i][j][k]

    return 0;
}
