/*
============================================================
📋 TUGAS 15: Optimasi Rasio dengan Batasan
============================================================
Source: Original
Difficulty: Hard
Topics: fractional + DP

PROBLEM:
Diberikan N benda, benda ke-i punya nilai v[i], bobot w[i], dan biaya c[i].
Pilih himpunan bagian dengan total biaya tidak melebihi C, yang
memaksimalkan (jumlah v) / (jumlah w). Cetak 6 desimal.

INPUT FORMAT:
- Baris pertama: N dan C
- N baris: v, w, c

OUTPUT FORMAT:
- Satu bilangan, 6 desimal

CONSTRAINTS:
- 1 <= N <= 100
- 1 <= C <= 1000

SAMPLE INPUT 1:
2 5
10 2 3
5 1 2

SAMPLE OUTPUT 1:
5.000000
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Gabungkan transformasi v - x*w dengan knapsack (Day 145): untuk x tertentu, maksimalkan sum(v[i] - x*w[i]) dengan batas biaya C. Binary search di luar, DP di dalam.

    return 0;
}
