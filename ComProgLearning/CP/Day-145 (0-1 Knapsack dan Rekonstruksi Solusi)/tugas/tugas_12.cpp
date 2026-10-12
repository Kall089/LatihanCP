/*
============================================================
📋 TUGAS 12: Knapsack dengan Batas Jumlah Barang
============================================================
Source: Original
Difficulty: Hard
Topics: DP dua dimensi

PROBLEM:
N barang, kapasitas W, dan syarat tambahan: kamu harus memilih TEPAT K
barang. Maksimalkan nilai, atau cetak -1 kalau mustahil.

INPUT FORMAT:
- Baris pertama: N, W, K
- N baris: w dan v

OUTPUT FORMAT:
- Satu bilangan atau -1

CONSTRAINTS:
- 1 <= K <= N <= 100
- 1 <= W <= 10^4

SAMPLE INPUT 1:
3 5 2
3 3
2 4
4 2

SAMPLE OUTPUT 1:
7
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Tambahkan satu dimensi: dp[c][j] = nilai maksimum dengan kapasitas c dan tepat j barang. Perhatikan bahwa kedua loop dalam harus disapu MUNDUR.

    return 0;
}
