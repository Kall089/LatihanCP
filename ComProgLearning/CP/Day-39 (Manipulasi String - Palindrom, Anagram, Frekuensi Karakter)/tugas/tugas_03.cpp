/*
============================================================
📋 TUGAS 03: Hitung Vokal
============================================================
Source: Original
Difficulty: Easy
Topics: Iterasi karakter

PROBLEM:
Diberikan sebuah kata. Hitung ada berapa huruf vokal (a, i, u, e, o) di dalamnya.

INPUT FORMAT:
- Satu baris berisi string S

OUTPUT FORMAT:
- Satu bilangan: banyaknya huruf vokal.

CONSTRAINTS:
- 1 <= |S| <= 10^6
- S berisi huruf kecil 'a'-'z'

SAMPLE INPUT 1:
pemrograman

SAMPLE OUTPUT 1:
4
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

bool isVokal(char c)
{
    c = tolower(c);
    return (c == 'a' || c == 'i' || c == 'u' || c == 'e' || c == 'o');
}

int main()
{
    string s;
    cin >> s;

    int vokal_size = 0;

    for (int i = 0; i < s.length(); i++)
    {
        if (isVokal(s[i]))
        {
            vokal_size++;
        }
    }

    cout << vokal_size;
}