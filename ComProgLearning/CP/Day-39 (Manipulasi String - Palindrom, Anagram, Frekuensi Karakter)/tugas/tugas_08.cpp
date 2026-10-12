/*
============================================================
📋 TUGAS 08: Bisa Jadi Palindrom
============================================================
Source: Original
Difficulty: Medium
Topics: Tabel frekuensi + huruf ganjil

PROBLEM:
Diberikan sebuah kata. Tentukan apakah huruf-hurufnya bisa disusun ulang
menjadi sebuah palindrom. Cukup cetak jawabannya, tidak perlu susunannya.

INPUT FORMAT:
- Satu baris berisi string S

OUTPUT FORMAT:
- Satu baris: "BISA" atau "TIDAK".

CONSTRAINTS:
- 1 <= |S| <= 10^6

SAMPLE INPUT 1:
aabbc

SAMPLE OUTPUT 1:
BISA
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

    int ganjil = 0;

    for (int i = 0; i < 26; i++)
    {
        if (hitung[i] % 2 == 1)
        {
            ganjil++;
        }
    }

    if (ganjil > 1)
    {
        cout << "TIDAK";
        return 0;
    }

    cout << "BISA";
}