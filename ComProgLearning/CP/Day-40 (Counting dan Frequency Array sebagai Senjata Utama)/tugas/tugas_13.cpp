/*
============================================================
📋 TUGAS 13: Selisih Minimum Absolut
============================================================
Source: LeetCode 1200
Difficulty: Hard
Topics: counting sort + sapuan

PROBLEM:
Diberikan array N bilangan berbeda, cari seluruh pasangan yang selisih
absolutnya MINIMUM. Cetak pasangan-pasangan itu terurut menaik.

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

OUTPUT FORMAT:
- Beberapa baris berisi dua bilangan

CONSTRAINTS:
- 2 <= N <= 10^5
- -10^6 <= a[i] <= 10^6

SAMPLE INPUT 1:
4
4 2 1 3

SAMPLE OUTPUT 1:
1 2
2 3
3 4
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Kalau domainnya kecil, counting sort O(n + V) mengalahkan sort. Setelah terurut, minimum selalu di antara tetangga.

    return 0;
}
