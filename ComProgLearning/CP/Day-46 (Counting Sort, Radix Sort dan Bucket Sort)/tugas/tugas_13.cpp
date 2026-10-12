/*
============================================================
📋 TUGAS 13: Urutkan String Berpanjang Berbeda
============================================================
Source: Original
Difficulty: Hard
Topics: MSD atau padding

PROBLEM:
Urutkan N string secara leksikografis. Panjang string berbeda-beda dan
total panjang seluruhnya sampai 10^6.

INPUT FORMAT:
- Baris pertama: N
- N baris berisi string

OUTPUT FORMAT:
- N baris terurut

CONSTRAINTS:
- 1 <= N <= 10^5

SAMPLE INPUT 1:
3
ab
a
abc

SAMPLE OUTPUT 1:
a
ab
abc
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // LSD radix tidak langsung bekerja untuk panjang berbeda. Pilihanmu: kelompokkan berdasarkan panjang, tambahkan padding, atau tulis MSD radix sort.

    return 0;
}
