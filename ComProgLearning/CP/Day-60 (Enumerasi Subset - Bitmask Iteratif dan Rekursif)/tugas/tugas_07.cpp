/*
============================================================
📋 TUGAS 07: Maximum XOR Subset
============================================================
Source: Original
Difficulty: Medium
Topics: bitmask enumeration, XOR, subset

PROBLEM:
Diberikan array a[] dengan n elemen bilangan bulat non-negatif.
Cari subset TIDAK KOSONG yang XOR semua elemennya adalah MAKSIMUM.
Cetak nilai XOR maksimum tersebut.

INPUT FORMAT:
- Baris 1: integer n
- Baris 2: n buah integer a[0..n-1]

OUTPUT FORMAT:
- Satu integer: nilai XOR maksimum dari suatu subset tidak kosong

CONSTRAINTS:
- 1 ≤ n ≤ 18
- 0 ≤ a[i] ≤ 10^6

SAMPLE INPUT 1:
3
1 5 7

SAMPLE OUTPUT 1:
7

SAMPLE INPUT 2:
4
3 5 6 9

SAMPLE OUTPUT 2:
15

NOTE: Untuk a=[1,5,7]: XOR dari semua subset tidak kosong:
      {1}=1, {5}=5, {7}=7, {1,5}=4, {1,7}=6, {5,7}=2, {1,5,7}=3 → max=7.
      Untuk a=[3,5,6,9]: {6,9}=15 → max=15.
      Iterasi semua mask dari 1 sampai (1<<n)-1.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    int maxXor = 0;
    // Enumerate all non-empty subsets (mask from 1 to 2^n - 1)
    for (int mask = 1; mask < (1 << n); mask++) {
        int xorVal = 0;
        for (int i = 0; i < n; i++)
            if ((mask >> i) & 1) xorVal ^= a[i];
        maxXor = max(maxXor, xorVal);
    }

    cout << maxXor << '\n';
    return 0;
}
