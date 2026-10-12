/*
============================================================
📋 TUGAS 5: String Reversal per Word
============================================================
Source: Original
Difficulty: Easy
Topics: string, vector, reverse

PROBLEM:
Diberikan sebuah kalimat (beberapa kata dipisahkan satu spasi).
Balik URUTAN KATA-nya (bukan hurufnya).

Contoh: "hello world foo" → "foo world hello"

INPUT:
- Satu baris: kalimat (kata-kata dipisah spasi tunggal)

OUTPUT:
- Satu baris: kalimat dengan urutan kata dibalik

CONSTRAINTS:
- 1 ≤ jumlah kata ≤ 100
- 1 ≤ panjang setiap kata ≤ 100
- Total panjang kalimat ≤ 10,000

SAMPLE INPUT:
hello world foo

SAMPLE OUTPUT:
foo world hello

SAMPLE INPUT 2:
competitive programming is fun

SAMPLE OUTPUT 2:
fun is programming competitive
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    getline(cin, s);

    stringstream ss(s);

    vector<string> words;
    string word;

    while (ss >> word)
    {
        words.push_back(word);
    }

    reverse(words.begin(), words.end());

    for (string x : words)
    {
        cout << x << " ";
    }

    return 0;
}
