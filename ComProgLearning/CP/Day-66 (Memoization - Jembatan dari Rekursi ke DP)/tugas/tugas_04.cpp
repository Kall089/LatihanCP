/*
============================================================
📋 TUGAS 04: Pemotong Kayu Palindromik (Palindrome Partitioning Min Cuts)
============================================================
Source: LeetCode 132 / Classic String DP Top-Down
Difficulty: Medium
Topics: Top-Down Memoization, Palindrome Checking

PROBLEM:
Diberikan sebuah string S. Potong string S menjadi sekumpulan bagian sedemikian rupa sehingga
setiap bagian merupakan string palindrom.
Hitung JUMLAH PEMOTONGAN MINIMUM yang diperlukan!
(Jika string S sudah merupakan palindrom dari awal, dibutuhkan 0 pemotongan).

INPUT FORMAT:
Satu baris berisi string S.

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: jumlah pemotongan minimum.

CONSTRAINTS:
1 <= |S| <= 1.000
S hanya terdiri dari huruf kecil 'a'..'z'

SAMPLE INPUT 1:
aab

SAMPLE OUTPUT 1:
1
(Potong menjadi "aa" | "b", total 1 pemotongan)

SAMPLE INPUT 2:
a

SAMPLE OUTPUT 2:
0
("a" sudah palindrom)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;

    // TODO: Selesaikan dengan top-down memoization

    return 0;
}
