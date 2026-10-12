/*
============================================================
📋 TUGAS 09: Berapa Titik dalam Persegi
============================================================
Source: Original
Difficulty: Medium
Topics: BIT 2D

PROBLEM:
Diberikan grid R x C yang mula-mula kosong, dan Q operasi: '1 r c' menaruh
satu titik di sel (r,c), '2 r1 c1 r2 c2' menghitung berapa titik di dalam
submatriks itu.

INPUT FORMAT:
- Baris pertama: R, C, Q
- Q baris berisi operasi

OUTPUT FORMAT:
- Satu baris per operasi jenis 2

CONSTRAINTS:
- 1 <= R, C <= 1000
- 1 <= Q <= 2*10^5

SAMPLE INPUT 1:
3 3 3
1 2 2
1 3 3
2 1 1 3 3

SAMPLE OUTPUT 1:
2
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // BIT 2D: dua loop bersarang, O(log R log C). Submatriks lewat inklusi-eksklusi empat sudut (Day 30).

    return 0;
}
