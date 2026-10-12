/*
============================================================
📋 TUGAS 06: Anagram dari Kalimat
============================================================
Source: Original
Difficulty: Medium
Topics: Tabel frekuensi + pembersihan

PROBLEM:
Diberikan dua kalimat yang boleh mengandung spasi. Tentukan apakah keduanya
anagram bila spasi diabaikan.

INPUT FORMAT:
- Baris pertama: kalimat A
- Baris kedua: kalimat B

OUTPUT FORMAT:
- Satu baris: "YA" atau "TIDAK".

CONSTRAINTS:
- 1 <= |A|, |B| <= 10^5
- Hanya berisi huruf kecil dan spasi

SAMPLE INPUT 1:
tali rapi
pia ratli

SAMPLE OUTPUT 1:
YA
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    string a, b;
    getline(cin, a);
    getline(cin, b);

    int hitung[26] = {};

    for (char c : a)
    {
        if (isalpha(c))
        {
            hitung[c - 'a']++;
        }
    }

    for (char c : b)
    {
        if (isalpha(c))
        {
            hitung[c - 'a']--;
        }
    }

    for (int i = 0; i < 26; i++)
    {
        if (hitung[i] != 0)
        {
            cout << "TIDAK";
            return 0;
        }
    }

    cout << "YA";
}