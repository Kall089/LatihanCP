/*
============================================================
📋 TUGAS 04: 0/1 Knapsack Maksimum Nilai 1D (O(W) Space)
============================================================
Source: Classic 0/1 Knapsack
Difficulty: Medium
Topics: 0/1 Knapsack, Backward Loop Optimization

PROBLEM:
Diberikan N barang dengan berat w[i] dan nilai v[i], serta kapasitas ransel W.
Setiap barang boleh diambil paling banyak satu kali.
Tentukan nilai maksimum yang dapat ditampung ke dalam ransel.
Program harus berjalan dengan memori DP O(W) menggunakan 1 baris array loop mundur.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan W.
N baris berikutnya masing-masing berisi dua bilangan bulat w[i] dan v[i].

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: total nilai maksimum.

CONSTRAINTS:
1 <= N <= 1.000
1 <= W <= 100.000
1 <= w[i] <= W
0 <= v[i] <= 10^9
Memori tambahan O(W)

SAMPLE INPUT 1:
3 8
3 30
4 50
5 60

SAMPLE OUTPUT 1:
90
(Ambil barang 2 [berat 4, nilai 50] dan barang 3 [berat 5... total 9 > 8? Tidak bisa.
Ambil barang 1 [berat 3, nilai 30] dan barang 3 [berat 5, nilai 60] -> berat 8, nilai 90)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, W;
    if (!(cin >> n >> W)) return 0;

    // TODO: Selesaikan 0/1 Knapsack dengan 1 baris DP loop mundur

    return 0;
}
