/*
============================================================
📋 TUGAS 14: Pembelian Buku Perpustakaan (CSES Book Shop 1D)
============================================================
Source: CSES Dynamic Programming - Book Shop
Difficulty: Medium
Topics: 0/1 Knapsack, 1D Array Optimization

PROBLEM:
Kamu memiliki uang sebesar X dan ingin membeli beberapa buku dari N buku yang tersedia.
Buku ke-i memiliki harga h[i] dan memiliki banyak halaman s[i].
Setiap buku boleh dibeli paling banyak satu kali.
Tentukan JUMLAH HALAMAN MAKSIMUM yang dapat kamu peroleh dengan uang paling banyak X!
Gunakan 1D array DP berukuran O(X) agar lolos batas memori CSES yang ketat.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan X.
Baris kedua berisi N bilangan bulat h[0], ..., h[N-1] (harga setiap buku).
Baris ketiga berisi N bilangan bulat s[0], ..., s[N-1] (halaman setiap buku).

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: total halaman maksimum.

CONSTRAINTS:
1 <= N <= 1.000
1 <= X <= 100.000
1 <= h[i], s[i] <= 1.000

SAMPLE INPUT 1:
4 10
4 8 5 3
5 12 8 1

SAMPLE OUTPUT 1:
13
(Beli buku 1 [harga 4, hal 5] dan buku 3 [harga 5, hal 8] -> total harga 9 <= 10, total halaman 13)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    if (!(cin >> n >> x)) return 0;

    vector<int> h(n), s(n);
    for (int i = 0; i < n; i++) cin >> h[i];
    for (int i = 0; i < n; i++) cin >> s[i];

    // TODO: Selesaikan CSES Book Shop dengan 1 baris DP loop mundur

    return 0;
}
