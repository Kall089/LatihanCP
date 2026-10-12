/*
============================================================
📋 TUGAS 10: Rekonstruksi Substring Palindrom Terpanjang
============================================================
Source: LeetCode 5 (Longest Palindromic Substring)
Difficulty: Medium
Topics: Range DP, Substring Output

PROBLEM:
Diberikan sebuah string S. Tentukan dan cetak SUBSTRING palindrom TERPANJANG
yang terdapat di dalam S.
Jika ada beberapa substring palindrom dengan panjang maksimum yang sama,
cetak yang kemunculannya PALING AWAL di dalam string S.

INPUT FORMAT:
Satu baris berisi string S tanpa spasi.

OUTPUT FORMAT:
Satu baris berisi substring palindrom terpanjang.

CONSTRAINTS:
1 <= |S| <= 1.000
S hanya berisi huruf kecil 'a'..'z'.

SAMPLE INPUT 1:
babad

SAMPLE OUTPUT 1:
bab
(Catatan: "bab" muncul lebih awal daripada "aba")

SAMPLE INPUT 2:
cbbd

SAMPLE OUTPUT 2:
bb
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

    // TODO: Selesaikan Substring Palindrom Terpanjang dan cetak substringnya

    return 0;
}
