/*
============================================================
📋 TUGAS 02: Range Update Queries
============================================================
Source: CSES 1651
Difficulty: Easy
Topics: BIT + difference array

PROBLEM:
Array N bilangan, Q operasi: '1 a b u' menambah u ke a[a..b], '2 k'
mencetak a[k].

INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan
- Q baris berisi operasi

OUTPUT FORMAT:
- Satu baris per operasi jenis 2

CONSTRAINTS:
- 1 <= N, Q <= 2*10^5

SAMPLE INPUT 1:
8 3
3 2 4 5 1 1 5 3
2 4
1 2 5 1
2 4

SAMPLE OUTPUT 1:
5
6
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Simpan SELISIH di dalam BIT. rangeAdd menyentuh dua posisi; pointQuery adalah query prefiks.

    return 0;
}
