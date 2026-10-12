/*
============================================================
📋 TUGAS 14: Bucket Sort Bilangan Real
============================================================
Source: Original
Difficulty: Hard
Topics: bucket sort

PROBLEM:
Diberikan N bilangan real di rentang [0, 1) yang terdistribusi SERAGAM,
urutkan menaik dan cetak dengan enam angka desimal. Selesaikan dengan
bucket sort dan jelaskan (dalam komentar) apa yang terjadi kalau
distribusinya ternyata tidak seragam.

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan real

OUTPUT FORMAT:
- N bilangan real, enam desimal

CONSTRAINTS:
- 1 <= N <= 10^6

SAMPLE INPUT 1:
4
0.9 0.1 0.5 0.3

SAMPLE OUTPUT 1:
0.100000
0.300000
0.500000
0.900000
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // N ember, indeks = (int)(x * N). Kalau semua jatuh ke satu ember, kompleksitasnya menjadi kompleksitas sort yang kamu pakai di dalam ember.

    return 0;
}
