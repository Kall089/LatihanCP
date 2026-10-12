/*
============================================================
📋 TUGAS 15: Segmentasi Kata Kamus Terbanyak
============================================================
Source: LeetCode 139 / Word Break DP Variation
Difficulty: Medium
Topics: String DP, Dictionary Matching, Prefix DP

PROBLEM:
Diberikan sebuah string S dan kamus berisi D kata berbeda.
Tentukan apakah string S dapat disegmentasikan menjadi barisan kata-kata yang valid dari kamus.
Jika BISA, cetak JUMLAH KATA MAKSIMUM yang dapat diperoleh dari segmentasi yang valid.
Jika TIDAK BISA, cetak -1.

INPUT FORMAT:
Baris pertama berisi string S.
Baris kedua berisi satu bilangan bulat D (banyak kata di kamus).
D baris berikutnya masing-masing berisi satu kata di kamus.

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: jumlah kata maksimum, atau -1 jika mustahil.

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
2
("leet" + "code" = 2 kata)

SAMPLE INPUT 2:
applepenapple
2
apple
pen

SAMPLE OUTPUT 2:
3
("apple" + "pen" + "apple" = 3 kata)

SAMPLE INPUT 3:
catsandog
5
cats
dog
sand
and
cat

SAMPLE OUTPUT 3:
-1
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

    // TODO: Selesaikan Word Break DP dengan mencari kata terbanyak

    return 0;
}
