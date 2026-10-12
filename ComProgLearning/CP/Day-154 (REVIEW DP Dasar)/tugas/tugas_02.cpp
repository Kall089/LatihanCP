/*
============================================================
📋 TUGAS 02: Cara Partisi Palindrom Paling Sedikit
============================================================
Source: Classic DP / Palindrome Partitioning II + Counting
Difficulty: Medium-Hard
Topics: Palindrome DP, Optimization + Counting

PROBLEM:
Diberikan sebuah string S. Potong string S menjadi sekumpulan bagian di mana setiap bagian
merupakan string palindrom.
Kamu diminta menghitung DUA HAL:
1. Jumlah bagian minimum yang mungkin terbentuk.
2. Banyak cara berbeda untuk memotong S menjadi jumlah bagian minimum tersebut, modulo 1.000.000.007.

INPUT FORMAT:
Satu baris berisi string S.

OUTPUT FORMAT:
Satu baris berisi dua bilangan bulat dipisahkan spasi:
[jumlah bagian minimum] [banyak cara modulo 1.000.000.007].

CONSTRAINTS:
1 <= |S| <= 800
S hanya terdiri dari huruf kecil 'a'..'z'

SAMPLE INPUT 1:
abab

SAMPLE OUTPUT 1:
2 2
(Bagian minimum = 2 bagian: "a" + "bab" atau "aba" + "b")

SAMPLE INPUT 2:
aaa

SAMPLE OUTPUT 2:
1 1
(Seluruh string "aaa" sudah palindrom, 1 bagian)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;

    // TODO: Selesaikan Palindrome Partitioning Min Cuts + Way Counting

    return 0;
}
