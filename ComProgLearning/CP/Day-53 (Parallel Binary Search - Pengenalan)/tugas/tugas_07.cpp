/*
============================================================
📋 TUGAS 07: Pulau Muncul
============================================================
Source: Original
Difficulty: Hard
Topics: PBS + DSU grid

PROBLEM:
Grid R x C mula-mula terendam. Setiap hari satu sel jadi daratan. Untuk
tiap query dua sel, cari hari keberapa keduanya terhubung lewat daratan
(gerak 4 arah).

INPUT FORMAT:
- Baris pertama: R, C, T, Q
- T baris: r c
- Q baris: r1 c1 r2 c2

OUTPUT FORMAT:
- Q baris

CONSTRAINTS:
- R*C <= 2*10^5

SAMPLE INPUT 1:
2 2 4 2
1 1
1 2
2 2
2 1
1 1 1 2
1 1 2 1

SAMPLE OUTPUT 1:
2
4
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Gabungkan HANYA dengan tetangga yang SUDAH jadi daratan. Batas bawah lo = max(hari kemunculan kedua sel).

    return 0;
}
