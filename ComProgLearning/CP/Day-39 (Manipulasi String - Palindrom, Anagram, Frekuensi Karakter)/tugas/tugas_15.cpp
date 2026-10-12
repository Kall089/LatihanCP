/*
============================================================
📋 TUGAS 15: Cek Rotasi
============================================================
Source: Original
Difficulty: Hard
Topics: Trik penggandaan string

PROBLEM:
Dua kata A dan B disebut rotasi satu sama lain jika B bisa diperoleh dengan
memotong A di suatu titik lalu menukar kedua bagiannya.
Contoh: "cdeab" adalah rotasi dari "abcde".
Tentukan apakah B merupakan rotasi dari A.

INPUT FORMAT:
- Baris pertama: string A
- Baris kedua: string B

OUTPUT FORMAT:
- Satu baris: "YA" atau "TIDAK".

CONSTRAINTS:
- 1 <= |A|, |B| <= 10^5
- Petunjuk: B adalah rotasi A jika panjangnya sama DAN B muncul di dalam A+A

SAMPLE INPUT 1:
abcde
cdeab

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

    if (a.length() != b.length())
    {
        cout << "TIDAK";
        return 0;
    }
    else
    {
        string digabung = a + a;

        if (digabung.find(b) != string::npos)
        {
            cout << "YA";
            return 0;
        }
    }

    cout << "TIDAK";
}