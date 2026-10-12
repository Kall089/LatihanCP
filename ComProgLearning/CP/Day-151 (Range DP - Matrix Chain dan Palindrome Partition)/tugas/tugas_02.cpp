/*
============================================================
📋 TUGAS 02: Sisipan Cermin (Minimum Insertions to Palindrome)
============================================================
Source: LeetCode 1312 / Classic DP
Difficulty: Medium
Topics: Range DP on Strings, Palindrome Transformation

PROBLEM:
Diberikan sebuah string S yang hanya terdiri dari karakter huruf kecil.
Dalam satu operasi, kamu boleh menyisipkan satu karakter huruf apa pun di posisi mana pun
(di awal, di tengah, atau di akhir string).
Tentukan jumlah operasi penyisipan MINIMUM yang diperlukan agar seluruh string S
berubah menjadi sebuah palindrom.

INPUT FORMAT:
Satu baris berisi string S tanpa spasi.

OUTPUT FORMAT:
Satu bilangan bulat: jumlah penyisipan minimum.

CONSTRAINTS:
1 <= |S| <= 1.000
S hanya berisi huruf kecil 'a'..'z'.

SAMPLE INPUT 1:
ab

SAMPLE OUTPUT 1:
1
(Penjelasan: Sisipkan 'a' di akhir menjadi "aba", atau 'b' di awal menjadi "bab". Butuh 1 sisipan)

SAMPLE INPUT 2:
aba

SAMPLE OUTPUT 2:
0
(Penjelasan: String sudah palindrom, butuh 0 sisipan)

SAMPLE INPUT 3:
leetcode

SAMPLE OUTPUT 3:
5
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

    // TODO: Selesaikan Minimum Insertions to Palindrome dengan Range DP
    // dp[l][r] = jumlah sisipan minimum untuk membuat S[l..r] menjadi palindrom
    // Jika s[l] == s[r] -> dp[l][r] = dp[l+1][r-1]
    // Jika tidak -> dp[l][r] = 1 + min(dp[l+1][r], dp[l][r-1])

    return 0;
}
