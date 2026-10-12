/*
============================================================
📋 TUGAS 10: Anagram Check
============================================================
Source: Original
Difficulty: Medium
Topics: string, sort/frequency

PROBLEM:
Diberikan dua string s dan t. Tentukan apakah t adalah ANAGRAM dari s.
Anagram = string yang bisa dibentuk dengan mengatur ulang huruf-huruf.

Contoh: "listen" dan "silent" adalah anagram.

INPUT:
- Baris pertama: string s
- Baris kedua: string t

OUTPUT:
- "YES" jika anagram, "NO" jika bukan

CONSTRAINTS:
- 1 ≤ |s|, |t| ≤ 100,000
- s dan t hanya berisi huruf kecil a-z

SAMPLE INPUT:
listen
silent

SAMPLE OUTPUT:
YES

SAMPLE INPUT 2:
hello
world

SAMPLE OUTPUT 2:
NO
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Hint: Sort kedua string, bandingkan. Atau gunakan frequency array.

    string s, t;
    cin >> s >> t;

    if (s.size() != t.size())
    {
        cout << "NO" << endl;
        return 0;
    }

    vector<int> freq(26, 0);

    for (char &c : s)
    {
        freq[c - 'a']++;
    }

    for (char &c : t)
    {
        freq[c - 'a']--;
    }

    for (int x : freq)
    {
        if (x != 0)
        {
            cout << "NO" << endl;
            return 0;
        }
    }

    cout << "YES" << endl;

    return 0;
}
