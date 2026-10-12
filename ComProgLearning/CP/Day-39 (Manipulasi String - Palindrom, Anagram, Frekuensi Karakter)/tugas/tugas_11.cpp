/*
============================================================
📋 TUGAS 11: Palindrom Terpanjang (Teks Panjang)
============================================================
Source: Original
Difficulty: Hard
Topics: Expand around center

PROBLEM:
Diberikan sebuah kata. Cetak substring palindrom terpanjang di dalamnya.
Jika ada beberapa yang panjangnya sama, cetak yang paling kiri.

INPUT FORMAT:
- Satu baris berisi string S

OUTPUT FORMAT:
- Satu baris: substring palindrom terpanjang.

CONSTRAINTS:
- 1 <= |S| <= 5000

SAMPLE INPUT 1:
forgeeksskeegfor

SAMPLE OUTPUT 1:
geeksskeeg
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

void lebarkan(string s, char L, char R, int &panjangBest, int &mulai)
{
    int n = s.length();

    while (L >= 0 && R < n && s[L] == s[R])
    {
        int pjg = R - L + 1;

        if (pjg > panjangBest)
        {
            panjangBest = pjg;
            mulai = L;
        }
        L--;
        R++;
    }
}

int main()
{
    string s;
    cin >> s;
    int panjangBest = 1, mulai = 0;

    for (int i = 0; i < s.length(); i++)
    {
        lebarkan(s, i, i, panjangBest, mulai);
        lebarkan(s, i, i + 1, panjangBest, mulai);
    }

    cout << s.substr(mulai, panjangBest) << "\n";
}