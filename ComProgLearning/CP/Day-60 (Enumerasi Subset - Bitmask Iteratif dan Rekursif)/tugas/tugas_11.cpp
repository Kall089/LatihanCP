/*
============================================================
📋 TUGAS 11: Minimum Items to Hit Exact Budget
============================================================
Source: Original
Difficulty: Medium
Topics: bitmask enumeration, subset sum, optimization

PROBLEM:
Diberikan n item dengan harga price[i] dan sebuah target T.
Cari jumlah item MINIMUM dalam suatu subset yang total harganya
tepat sama dengan T.
Jika tidak ada subset dengan total tepat T, cetak -1.

INPUT FORMAT:
- Baris 1: dua integer n dan T
- Baris 2: n buah integer price[0..n-1]

OUTPUT FORMAT:
- Satu integer: jumlah item minimum, atau -1 jika tidak ada

CONSTRAINTS:
- 1 ≤ n ≤ 20
- 1 ≤ price[i] ≤ 10^6
- 1 ≤ T ≤ 10^7

SAMPLE INPUT 1:
4 6
1 5 3 2

SAMPLE OUTPUT 1:
2

SAMPLE INPUT 2:
3 10
1 2 3

SAMPLE OUTPUT 2:
-1

NOTE: Untuk a=[1,5,3,2], T=6: {1,5}=6 (2 item), {1,2,3}=6 (3 item) → min=2.
      Iterasi semua mask, filter yang sum==T, ambil minimum __builtin_popcount.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO
    return 0;
}
