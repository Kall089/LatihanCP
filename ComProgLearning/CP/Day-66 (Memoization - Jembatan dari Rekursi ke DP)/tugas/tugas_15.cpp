/*
============================================================
📋 TUGAS 15: Segmentasi String Kamus Kata Top-Down (Word Break)
============================================================
Source: LeetCode 139 / Classic String DP Top-Down
Difficulty: Medium
Topics: Top-Down Memoization, String Matching

PROBLEM:
Diberikan sebuah string S dan daftar kata kamus yang berisi D buah kata unik.
Tentukan apakah string S dapat dipecah menjadi barisan satu atau lebih kata-kata yang semuanya ada di dalam kamus!
(Setiap kata di dalam kamus boleh digunakan berulang kali).

Cetak "BISA" jika string S dapat disegmentasikan, atau "TIDAK BISA" jika tidak.

Wajib diimplementasikan menggunakan REKURSIF DENGAN MEMOISASI (Top-Down)!

INPUT FORMAT:
Baris pertama berisi string S.
Baris kedua berisi satu bilangan bulat D.
D baris berikutnya masing-masing berisi satu kata di dalam kamus.

OUTPUT FORMAT:
"BISA" atau "TIDAK BISA".

CONSTRAINTS:
1 <= |S| <= 1.000
1 <= D <= 500
1 <= panjang kata kamus <= 50
Karakter hanya huruf kecil 'a'..'z'

SAMPLE INPUT 1:
leetcode
2
leet
code

SAMPLE OUTPUT 1:
BISA

SAMPLE INPUT 2:
applepenapple
2
apple
pen

SAMPLE OUTPUT 2:
BISA

SAMPLE INPUT 3:
catsandog
5
cats
dog
sand
and
cat

SAMPLE OUTPUT 3:
TIDAK BISA
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;

    int d;
    if (!(cin >> d)) return 0;

    // TODO: Selesaikan dengan top-down memoization: solve(idx)

    return 0;
}
