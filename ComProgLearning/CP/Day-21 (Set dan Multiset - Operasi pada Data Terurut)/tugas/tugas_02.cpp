/*
============================================================
📋 TUGAS 2: First Unique Character
============================================================
Source: Original
Difficulty: Easy
Topics: map/unordered_map, frequency

PROBLEM:
Diberikan string s (huruf kecil). Cari INDEX (0-indexed) dari
karakter pertama yang hanya muncul SEKALI. Jika tidak ada, output -1.

INPUT:
- Satu baris: string s

OUTPUT:
- Satu integer: index karakter unik pertama, atau -1

CONSTRAINTS:
- 1 ≤ |s| ≤ 200,000

SAMPLE INPUT:
leetcode

SAMPLE OUTPUT:
0

SAMPLE INPUT 2:
aabb

SAMPLE OUTPUT 2:
-1

NOTE: Di "leetcode", 'l' muncul sekali dan ada di index 0.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    string s;
    cin >> s;

    unordered_map<char, int> freq;

    for (char c : s)
    {
        freq[c]++;
    }

    for (int i = 0; i < s.size(); i++)
    {
        if (freq[s[i]] == 1)
        {
            cout << i << endl;
            return 0;
        }
    }

    cout << -1 << endl;

    return 0;
}
