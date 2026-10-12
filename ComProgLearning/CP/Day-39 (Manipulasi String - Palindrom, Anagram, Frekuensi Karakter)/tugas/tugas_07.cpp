/*
============================================================
📋 TUGAS 07: Kapitalkan Setiap Kata
============================================================
Source: Original
Difficulty: Medium
Topics: Pemrosesan kata per kata

PROBLEM:
Diberikan satu baris kalimat berisi beberapa kata yang dipisah satu spasi.
Ubah huruf pertama setiap kata menjadi huruf besar, sisanya huruf kecil.

INPUT FORMAT:
- Satu baris berisi kalimat S

OUTPUT FORMAT:
- Satu baris: kalimat yang sudah dikapitalkan.

CONSTRAINTS:
- 1 <= |S| <= 10^5
- Kata dipisah tepat satu spasi

SAMPLE INPUT 1:
halo dunia

SAMPLE OUTPUT 1:
Halo Dunia
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    getline(cin, s);

    bool is_space = true;

    for (char &c : s)
    {
        if (c == ' ')
        {
            is_space = true;
        }
        else
        {
            if (is_space)
            {
                c = toupper(c);
                is_space = false;
            }
            else
            {
                c = tolower(c);
            }
        }
    }

    cout << s;
}