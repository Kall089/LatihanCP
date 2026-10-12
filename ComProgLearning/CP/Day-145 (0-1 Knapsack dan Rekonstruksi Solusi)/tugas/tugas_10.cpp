/*
============================================================
📋 TUGAS 10: SuperSale
============================================================
Source: UVa 10130
Difficulty: Medium
Topics: knapsack per orang

PROBLEM:
Ada N barang dengan berat dan harga. Ada G orang, orang ke-j mampu
membawa paling banyak MW[j] berat. Setiap orang memilih barang secara
INDEPENDEN (barang boleh dipilih orang berbeda). Cari total harga maksimum.

INPUT FORMAT:
- Baris pertama: T (kasus uji)
- Setiap kasus: N, lalu N baris harga dan berat, lalu G, lalu G kapasitas

OUTPUT FORMAT:
- T baris

CONSTRAINTS:
- 1 <= N <= 1000
- 1 <= G <= 100

SAMPLE INPUT 1:
1
2
3 3
2 1
2
2
3

SAMPLE OUTPUT 1:
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
    // Hitung knapsack SEKALI untuk seluruh kapasitas, lalu jumlahkan dp[MW[j]] untuk setiap orang. Jangan menghitung ulang per orang.

    return 0;
}
