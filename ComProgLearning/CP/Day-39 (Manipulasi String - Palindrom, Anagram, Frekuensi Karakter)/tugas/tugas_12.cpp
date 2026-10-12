/*
============================================================
📋 TUGAS 12: Berapa Huruf Perlu Diubah
============================================================
Source: Original
Difficulty: Hard
Topics: Dua pointer + penghitungan

PROBLEM:
Diberikan sebuah kata. Kamu boleh mengganti huruf apa pun menjadi huruf lain.
Tentukan berapa penggantian MINIMAL agar kata tersebut menjadi palindrom.
Contoh: "abcda" cukup satu penggantian (ubah 'b' menjadi 'd' atau sebaliknya).

INPUT FORMAT:
- Satu baris berisi string S

OUTPUT FORMAT:
- Satu bilangan: jumlah penggantian minimal.

CONSTRAINTS:
- 1 <= |S| <= 10^6

SAMPLE INPUT 1:
abcda

SAMPLE OUTPUT 1:
1
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    cin >> s;

    int left = 0, right = s.length() - 1;

    int count = 0;

    while (right > left)
    {
        if (s[left] != s[right])
        {
            count++;
            left++;
            right--;
        }
        else
        {
            left++;
            right--;
        }
    }

    cout << count;
}