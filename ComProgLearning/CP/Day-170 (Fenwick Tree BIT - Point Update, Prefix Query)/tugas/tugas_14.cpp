/*
============================================================
📋 TUGAS 14: Inversi pada Rentang
============================================================
Source: Original
Difficulty: Hard
Topics: BIT + offline

PROBLEM:
Diberikan permutasi 1..N dan Q query berupa rentang [l,r]. Untuk setiap
query, hitung banyaknya inversi yang KEDUA indeksnya berada di dalam
rentang itu.

INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: permutasi
- Q baris: l dan r

OUTPUT FORMAT:
- Q baris

CONSTRAINTS:
- 1 <= N <= 2*10^4
- 1 <= Q <= 2*10^4

SAMPLE INPUT 1:
4 2
3 1 4 2
1 4
2 3

SAMPLE OUTPUT 1:
3
0
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Mo's algorithm (Day 184) dengan BIT untuk memperbarui hitungan saat rentang bergeser. Perhatikan biaya total: O((n+q) sqrt(n) log n).

    return 0;
}
