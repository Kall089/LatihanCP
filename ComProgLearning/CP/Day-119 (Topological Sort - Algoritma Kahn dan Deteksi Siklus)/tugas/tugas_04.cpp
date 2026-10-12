/*
============================================================
📋 TUGAS 04: Urutan Kompilasi Modul
============================================================
Source: Klasik (build system)
Difficulty: Easy
Topics: Kahn, model dependency

PROBLEM:
N modul. Baris ke-i berisi k_i nomor modul yang HARUS dikompilasi sebelum
modul i. Cetak urutan kompilasi yang valid, atau -1 jika ada dependensi
melingkar.

INPUT FORMAT:
- Baris 1: N
- N baris: k_i lalu k_i nomor modul

OUTPUT FORMAT:
- N bilangan, atau -1

CONSTRAINTS:
- 1 <= N <= 10^5, total dependensi <= 2*10^5

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
3                      1 2 3
0
1 1
1 2

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
2                      -1
1 2
1 1

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
4                      1 2 3 4
0
0
2 1 2
1 3
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // HATI-HATI ARAH: "j prasyarat i" -> edge j -> i.
    return 0;
}
