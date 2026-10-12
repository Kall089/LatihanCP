/*
============================================================
📋 TUGAS 8: Caesar Cipher
============================================================
Source: Original
Difficulty: Medium
Topics: string, character manipulation

PROBLEM:
Diberikan string s (huruf kecil) dan integer K. Lakukan Caesar cipher:
geser setiap huruf sebanyak K posisi ke kanan dalam alfabet.
Jika melewati 'z', kembali ke 'a' (wrap around).

Contoh: K=3, 'a' → 'd', 'x' → 'a', 'z' → 'c'

INPUT:
- Baris pertama: string s (huruf kecil saja)
- Baris kedua: integer K

OUTPUT:
- Satu baris: string setelah di-encrypt

CONSTRAINTS:
- 1 ≤ |s| ≤ 100,000
- 0 ≤ K ≤ 1,000,000

SAMPLE INPUT:
abc
3

SAMPLE OUTPUT:
def

SAMPLE INPUT 2:
xyz
2

SAMPLE OUTPUT 2:
zab
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Hint: new_char = 'a' + (old_char - 'a' + K) % 26

    string s;
    cin >> s;

    int k;
    cin >> k;

    k = k % 26;

    for (char &c : s)
    {
        c = 'a' + (c - 'a' + k) % 26;
    }

    cout << s;

    return 0;
}
