/*
============================================================
📋 TUGAS 11: Distinct Values Queries
============================================================
Source: CSES 1734
Difficulty: Hard
Topics: offline + BIT

PROBLEM:
Untuk setiap query (a, b), hitung berapa NILAI BERBEDA di dalam a[a..b].

INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan
- Q baris: a dan b

OUTPUT FORMAT:
- Q baris

CONSTRAINTS:
- 1 <= N, Q <= 2*10^5

SAMPLE INPUT 1:
5 3
3 2 3 1 2
1 3
2 4
1 5

SAMPLE OUTPUT 1:
2
3
3
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Ini offline tetapi BUKAN parallel binary search: urutkan query berdasarkan ujung kanan, lalu jaga BIT berisi kemunculan TERAKHIR setiap nilai. Pelajarannya: tidak semua soal offline butuh PBS.

    return 0;
}
