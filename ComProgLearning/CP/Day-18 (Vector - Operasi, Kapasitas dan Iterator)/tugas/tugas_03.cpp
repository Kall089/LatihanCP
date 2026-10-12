/*
============================================================
📋 TUGAS 3: Count Character Frequency
============================================================
Source: Original
Difficulty: Easy
Topics: string, frequency array

PROBLEM:
Diberikan sebuah string s (huruf kecil saja). Cetak frekuensi setiap
huruf yang MUNCUL (> 0), diurutkan berdasarkan huruf (a-z).

INPUT:
- Satu baris: string s

OUTPUT:
- Untuk setiap huruf yang muncul: "X Y" (X=huruf, Y=frekuensi)
  satu per baris, urut dari 'a' ke 'z'

CONSTRAINTS:
- 1 ≤ |s| ≤ 100,000
- s hanya berisi huruf kecil a-z

SAMPLE INPUT:
abracadabra

SAMPLE OUTPUT:
a 5
b 2
c 1
d 1
r 2
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string s;
  cin >> s;

  map<char, int> freq;

  for (char c : s)
  {
    freq[c]++;
  }

  for (auto [ch, count] : freq)
  {
    cout << ch << " " << count << endl;
  }

  return 0;
}
