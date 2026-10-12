/*
============================================================
📋 TUGAS 13: Kelompokkan Anagram
============================================================
Source: Original
Difficulty: Hard
Topics: Map of vector + kunci terurut

PROBLEM:
Diberikan N kata. Kelompokkan kata-kata yang saling anagram.
Cetak ada berapa kelompok yang terbentuk.

INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: satu kata per baris

OUTPUT FORMAT:
- Satu bilangan: banyaknya kelompok anagram.

CONSTRAINTS:
- 1 <= N <= 10^5
- Total panjang seluruh kata <= 10^6

SAMPLE INPUT 1:
5
gerak
kerag
tali
lati
batu

SAMPLE OUTPUT 1:
3
============================================================
*/

#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;

    set<string> kelompok_terurut;

    while (n--)
    {
        string s;
        cin >> s;

        sort(s.begin(), s.end());

        kelompok_terurut.insert(s);
    }

    cout << kelompok_terurut.size();
}
