/*
============================================================
📋 TUGAS 15: Disjoint Sparse Table
============================================================
Source: Original
Difficulty: Hard
Topics: varian non-idempoten

PROBLEM:
Implementasikan disjoint sparse table: varian yang membagi rentang di
TITIK TENGAH alih-alih memakai dua blok tumpang tindih, sehingga bekerja
untuk operasi ASOSIATIF apa pun termasuk penjumlahan.
Gunakan untuk menjawab Q query 'jumlah pada rentang' dengan build
O(n log n) dan query O(1), lalu bandingkan dengan prefix sum biasa.

INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan
- Q baris: a dan b

OUTPUT FORMAT:
- Q baris

CONSTRAINTS:
- 1 <= N, Q <= 2*10^5

SAMPLE INPUT 1:
5 2
1 2 3 4 5
1 5
2 4

SAMPLE OUTPUT 1:
15
9
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Untuk tiap level k, bagi array jadi blok sepanjang 2^k dan hitung prefix/suffix di dalam tiap blok. Query mencari level di mana l dan r berada di dua paruh berbeda. Berguna untuk operasi asosiatif yang tidak idempoten dan tidak punya invers.

    return 0;
}
