/*
============================================================
📋 TUGAS 14: Kompresi Berulang
============================================================
Source: Original
Difficulty: Hard
Topics: Run-length encoding

PROBLEM:
Diberikan sebuah kata. Kompres dengan cara menuliskan tiap huruf diikuti
jumlah kemunculan berurutannya. Huruf yang muncul sekali tetap ditulis
beserta angka 1.
Contoh: "aaabbc" menjadi "a3b2c1".

INPUT FORMAT:
- Satu baris berisi string S

OUTPUT FORMAT:
- Satu baris: hasil kompresi.

CONSTRAINTS:
- 1 <= |S| <= 10^6

SAMPLE INPUT 1:
aaabbc

SAMPLE OUTPUT 1:
a3b2c1
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    cin >> s;

    int hitung[26] = {};

    for (char c : s)
    {
        hitung[c - 'a']++;
    }

    string hasil = "";

    for (int i = 0; i < 26; i++)
    {
        int count = 0;
        if (hitung[i] != 0)
        {
            count = hitung[i];
            hasil += char(i + 'a');
            hasil += to_string(count);
        }
    }

    cout << hasil;
}
