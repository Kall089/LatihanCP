/*
============================================================
📋 TUGAS 01: Periode Terkecil
============================================================
Source: CSES 1733 (varian)
Difficulty: Easy
Topics: periode, pi

PROBLEM:
Diberikan string S. Cetak semua panjang periode dari S, terurut menaik.
Panjang p disebut periode jika S[i] == S[i+p] untuk setiap i yang valid.
Perhatikan bahwa n sendiri selalu merupakan periode.

INPUT FORMAT:
- Satu baris: string S

OUTPUT FORMAT:
- Satu baris: semua panjang periode, urut menaik

CONSTRAINTS:
- 1 <= |S| <= 10^6

SAMPLE INPUT 1:
abcabca

SAMPLE OUTPUT 1:
3 6 7
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Periode p <=> border n-p. Telusuri rantai pi, konversi tiap border jadi periode.

    return 0;
}
