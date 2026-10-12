/*
============================================================
📋 TUGAS 06: Road Reparation
============================================================
Source: CSES 1675
Difficulty: Medium
Topics: Kruskal

PROBLEM:
N kota dan M jalan berbiaya. Cari total biaya minimum agar seluruh kota
terhubung, atau IMPOSSIBLE.

INPUT FORMAT:
- Baris pertama: N dan M
- M baris: a, b, c

OUTPUT FORMAT:
- Satu bilangan atau IMPOSSIBLE

CONSTRAINTS:
- 1 <= N, M <= 2*10^5
- 1 <= c <= 10^9

SAMPLE INPUT 1:
5 6
1 2 3
2 3 5
2 4 2
3 4 8
5 1 7
5 4 4

SAMPLE OUTPUT 1:
14
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Sort + unite. Deteksi IMPOSSIBLE lewat jumlah sisi terpakai != n-1. long long untuk totalnya.

    return 0;
}
