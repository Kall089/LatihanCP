/*
============================================================
📋 TUGAS 11: Inversion Count
============================================================
Source: SPOJ INVCNT
Difficulty: Hard
Topics: kompresi + BIT

PROBLEM:
Hitung banyaknya pasangan (i, j) dengan i < j dan a[i] > a[j].

INPUT FORMAT:
- Baris pertama: T
- Setiap kasus: N lalu N bilangan

OUTPUT FORMAT:
- T baris berisi bilangan

CONSTRAINTS:
- 1 <= N <= 2*10^5
- nilai sampai 10^9

SAMPLE INPUT 1:
1
5
2 4 1 3 5

SAMPLE OUTPUT 1:
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
    // Kompres dulu supaya BIT muat, lalu sapu dari kanan sambil menghitung yang lebih kecil. Atau pakai merge sort (Day 44).

    return 0;
}
