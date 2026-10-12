/*
============================================================
📋 TUGAS 02: Palindrom Longgar
============================================================
Source: Original
Difficulty: Easy
Topics: Dua pointer + pembersihan karakter

PROBLEM:
Diberikan satu baris kalimat yang boleh mengandung spasi dan huruf besar.
Tentukan apakah kalimat itu palindrom bila spasi diabaikan dan
huruf besar dianggap sama dengan huruf kecil.
Contoh: "Kasur ini rusak" adalah palindrom.

INPUT FORMAT:
- Satu baris berisi kalimat S (boleh mengandung spasi)

OUTPUT FORMAT:
- Satu baris: "YA" atau "TIDAK".

CONSTRAINTS:
- 1 <= |S| <= 10^5
- S berisi huruf dan spasi
- Petunjuk: pakai getline, dan cin.ignore() bila sebelumnya ada cin >>

SAMPLE INPUT 1:
Kasur ini rusak

SAMPLE OUTPUT 1:
YA
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    getline(cin, s);

    int left = 0, right = s.length() - 1;

    while (right > left)
    {
        if (isspace(s[left]))
        {
            left++;
        }
        else if (isspace(s[right]))
        {
            right--;
        }
        else
        {
            if (s[left] != s[right])
            {
                cout << "NO";
                return 0;
            }
            else
            {
                left++;
                right--;
            }
        }
    }

    cout << "YES";
}