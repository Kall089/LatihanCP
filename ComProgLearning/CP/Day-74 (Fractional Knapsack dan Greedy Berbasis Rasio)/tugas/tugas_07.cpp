/*
============================================================
📋 TUGAS 07: Knapsack Nilai Kecil
============================================================
Source: Latihan mandiri
Difficulty: Hard
Topics: Membalik dimensi DP

PROBLEM:
Ada n barang dengan berat w[i] dan nilai v[i], kapasitas W. Barang tidak boleh
dipotong dan hanya sekali. Cari nilai maksimum.
Perhatikan: W sangat besar tetapi total nilai kecil.

INPUT FORMAT:
Baris 1: n dan W
n baris berikutnya: w[i] dan v[i]

OUTPUT FORMAT:
Satu bilangan: nilai maksimum

CONSTRAINTS:
1 <= n <= 100, 1 <= W <= 10^9, 1 <= w[i] <= 10^9, 1 <= v[i] <= 1000, sum(v) <= 10^5

SAMPLE INPUT 1:
3 10
6 7
5 5
5 5

SAMPLE OUTPUT 1:
10
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Tukar peran berat dan nilai di dalam tabel. Hati-hati dengan nilai sentinel INF agar tidak meluap saat ditambah berat.

    return 0;
}
