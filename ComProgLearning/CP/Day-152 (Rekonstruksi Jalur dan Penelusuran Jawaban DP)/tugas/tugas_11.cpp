/*
============================================================
📋 TUGAS 11: Rekonstruksi Subsekuens Berulang Terpanjang (LRS)
============================================================
Source: GeeksforGeeks / Classic DP
Difficulty: Medium-Hard
Topics: LCS Variation, Self-Matching with i != j

PROBLEM:
Diberikan sebuah string S. Tentukan Subsekuens Berulang Terpanjang (Longest Repeating Subsequence).
LRS adalah subsekuens dari S yang muncul setidaknya dua kali di dalam string S
pada posisi indeks karakter yang BERBEDA.
Cetak panjang LRS di baris pertama, dan string LRS itu sendiri di baris kedua.
Jika tidak ada, cetak 0 dan baris kedua kosong.

INPUT FORMAT:
Satu baris berisi string S tanpa spasi.

OUTPUT FORMAT:
Baris pertama: panjang LRS.
Baris kedua: string LRS.

CONSTRAINTS:
1 <= |S| <= 1.000

SAMPLE INPUT 1:
aabebcdd

SAMPLE OUTPUT 1:
3
abd
(Penjelasan: "abd" muncul di indeks [0, 2, 6] dan [1, 4, 7])
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;

    // TODO: Selesaikan LRS dengan mencocokkan S dengan dirinya sendiri dengan syarat i != j

    return 0;
}
