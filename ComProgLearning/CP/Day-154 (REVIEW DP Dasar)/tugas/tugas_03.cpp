/*
============================================================
📋 TUGAS 03: Benda Terbaik dengan Jumlah Seri
============================================================
Source: Classic DP / Knapsack Value Optimization + Way Counting
Difficulty: Medium
Topics: 0/1 Knapsack, Optimization + Counting DP

PROBLEM:
Terdapat N barang dengan berat w[i] dan nilai v[i].
Kamu memiliki ransel dengan kapasitas berat maksimum W.
Setiap barang boleh diambil paling banyak satu kali.
Hitung:
1. Total nilai MAKSIMUM yang dapat diperoleh dengan berat <= W.
2. Banyak SUBSET BARANG BERBEDA yang menghasilkan total nilai maksimum tersebut, modulo 1.000.000.007!
(Subset kosong sah jika semua pilihan bernilai 0).

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan W.
N baris berikutnya masing-masing berisi dua bilangan bulat w[i] dan v[i].

OUTPUT FORMAT:
Satu baris berisi dua bilangan bulat:
[nilai maksimum] [banyak subset optimum modulo 1.000.000.007].

CONSTRAINTS:
1 <= N <= 100
0 <= W <= 2.000
1 <= w[i] <= 2.000
0 <= v[i] <= 10^9

SAMPLE INPUT 1:
2 1
1 5
1 5

SAMPLE OUTPUT 1:
5 2
(Nilai maksimum 5 didapat dari {barang 1} atau {barang 2}, total 2 subset)

SAMPLE INPUT 2:
1 1
1 0

SAMPLE OUTPUT 2:
0 2
(Nilai maksimum 0 didapat dari subset kosong {} atau {barang 1})
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, W;
    if (!(cin >> n >> W)) return 0;

    // TODO: Selesaikan Knapsack Value + Count Optimum Subsets

    return 0;
}
