/*
============================================================
📋 TUGAS 12: Nilai ke-K pada Rentang
============================================================
Source: SPOJ MKTHNUM
Difficulty: Hard
Topics: persistent segtree

PROBLEM:
Diberikan array dan Q pertanyaan (l, r, k). Untuk setiap pertanyaan, cari
elemen terkecil ke-k di dalam subarray a[l..r].

INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan
- Q baris: l, r, k

OUTPUT FORMAT:
- Q baris

CONSTRAINTS:
- 1 <= N <= 10^5
- 1 <= Q <= 5*10^3

SAMPLE INPUT 1:
5 2
1 5 2 6 3
1 3 2
2 5 3

SAMPLE OUTPUT 1:
2
5
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Quickselect per query terlalu lambat. Butuh persistent segment tree (Day 186-187) atau Mo's algorithm (Day 184).

    return 0;
}
