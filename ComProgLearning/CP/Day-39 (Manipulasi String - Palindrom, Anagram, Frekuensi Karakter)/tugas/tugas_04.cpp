/*
============================================================
📋 TUGAS 04: Cek Substring
============================================================
Source: Original
Difficulty: Easy
Topics: Pencarian substring

PROBLEM:
Diberikan dua kata A dan B. Tentukan apakah B muncul sebagai substring di dalam A.
Substring berarti potongan huruf yang berurutan.

INPUT FORMAT:
- Baris pertama: string A
- Baris kedua: string B

OUTPUT FORMAT:
- Satu baris: "YA" jika B ada di dalam A, "TIDAK" jika tidak.

CONSTRAINTS:
- 1 <= |B| <= |A| <= 10^5

SAMPLE INPUT 1:
kompetisi
peti

SAMPLE OUTPUT 1:
YA
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main()
{
    string a, b;
    cin >> a >> b;

    if (a.find(b) != string::npos)
    {
        cout << "YA";
    }
    else
    {
        cout << "TIDAK";
    }
}