/*
============================================================
📋 TUGAS 01: Balik Kata
============================================================
Source: Original
Difficulty: Easy
Topics: Operasi string dasar

PROBLEM:
Diberikan sebuah kata. Cetak kata tersebut dalam urutan huruf terbalik.

INPUT FORMAT:
- Satu baris berisi string S

OUTPUT FORMAT:
- Satu baris: S yang sudah dibalik.

CONSTRAINTS:
- 1 <= |S| <= 10^6
- S berisi huruf kecil 'a'-'z'

SAMPLE INPUT 1:
kompetisi

SAMPLE OUTPUT 1:
isitepmok
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    cin >> s;

    reverse(s.begin(), s.end());

    cout << s;
}
