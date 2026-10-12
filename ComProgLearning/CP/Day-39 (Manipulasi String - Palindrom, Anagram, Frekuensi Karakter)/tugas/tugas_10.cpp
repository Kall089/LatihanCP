/*
============================================================
📋 TUGAS 10: Hitung Pasangan Anagram
============================================================
Source: Original
Difficulty: Medium-Hard
Topics: Map + kunci frekuensi

PROBLEM:
Diberikan N kata. Hitung ada berapa PASANGAN kata (i, j) dengan i < j
yang merupakan anagram satu sama lain.

INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: satu kata per baris

OUTPUT FORMAT:
- Satu bilangan: banyaknya pasangan anagram.

CONSTRAINTS:
- 1 <= N <= 10^5
- Total panjang seluruh kata <= 10^6
- Petunjuk: kata yang hurufnya diurutkan bisa jadi kunci map

SAMPLE INPUT 1:
4
gerak
kerag
tali
lati

SAMPLE OUTPUT 1:
2
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    map<string, long long> hitung;

    while (n--)
    {
        string s;
        cin >> s;

        sort(s.begin(), s.end());
        hitung[s]++;
    }

    long long total_pasangan = 0;

    for (auto pasangan : hitung)
    {
        int x = pasangan.second;

        if (x > 0)
        {
            total_pasangan += (x * (x - 1)) / 2;
        }
    }

    cout << total_pasangan;
}