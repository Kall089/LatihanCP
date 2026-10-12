/*
============================================================
📋 TUGAS 7: Group Anagrams
============================================================
Source: Classic / LeetCode-style
Difficulty: Medium
Topics: map, string sort, grouping

PROBLEM:
Diberikan N kata. Kelompokkan kata-kata yang merupakan ANAGRAM
satu sama lain. Untuk setiap kelompok, cetak kata-kata dalam
urutan lexicographic, dipisah spasi. Cetak kelompok-kelompok
dalam urutan kata pertama masing-masing kelompok (lexicographic).

Dua kata adalah anagram jika huruf-hurufnya sama tapi beda urutan.

INPUT:
- Baris pertama: integer N
- N baris berikutnya: satu kata per baris

OUTPUT:
- Setiap kelompok anagram dalam satu baris (sorted per kata, sorted per group)

CONSTRAINTS:
- 1 ≤ N ≤ 100,000
- 1 ≤ |kata| ≤ 20

SAMPLE INPUT:
6
eat
tea
tan
ate
nat
bat

SAMPLE OUTPUT:
ate eat tea
bat
nat tan

NOTE: {eat,tea,ate} adalah satu kelompok anagram (sorted: ate eat tea)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    int n;
    cin >> n;

    map<string, vector<string>> groups;

    for (int i = 0; i < n; i++)
    {
        string x;
        cin >> x;

        string key = x;
        sort(key.begin(), key.end());
        groups[key].push_back(x);
    }
    cout << endl;

    for (auto &[c, y] : groups)
    {
        sort(y.begin(), y.end());
        for (string &word : y)
        {
            cout << word << " ";
        }
        cout << endl;
    }
    // Hint: Sort setiap kata → gunakan sebagai key di map
    //       map<string, vector<string>> groups;

    return 0;
}
