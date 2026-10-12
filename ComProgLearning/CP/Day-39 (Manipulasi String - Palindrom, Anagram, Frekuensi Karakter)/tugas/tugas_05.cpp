/*
============================================================
📋 TUGAS 05: Hapus Huruf Kembar Berurutan
============================================================
Source: Original
Difficulty: Easy
Topics: Iterasi + perbandingan tetangga

PROBLEM:
Diberikan sebuah kata. Hapus setiap huruf yang sama dengan huruf tepat sebelumnya,
sehingga tidak ada lagi dua huruf sama yang berdampingan.
Contoh: "aabbccd" menjadi "abcd".

INPUT FORMAT:
- Satu baris berisi string S

OUTPUT FORMAT:
- Satu baris: string hasil setelah penghapusan.

CONSTRAINTS:
- 1 <= |S| <= 10^6

SAMPLE INPUT 1:
aabbccd

SAMPLE OUTPUT 1:
abcd
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    cin >> s;

    string hasil = "";

    for (char c : s)
    {
        if (hasil.empty() || hasil.back() != c)
        {
            hasil += c;
        }
    }

    cout << hasil;
}