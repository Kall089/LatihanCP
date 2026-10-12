/*
============================================================
📋 TUGAS 11: Bounded Knapsack
============================================================
Source: Original
Difficulty: Hard
Topics: dekomposisi biner

PROBLEM:
N jenis barang; jenis ke-i punya berat w, nilai v, dan tersedia k buah.
Kapasitas W. Maksimalkan nilai.

INPUT FORMAT:
- Baris pertama: N dan W
- N baris: w, v, k

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 100
- 1 <= W <= 10^5
- 1 <= k <= 10^6

SAMPLE INPUT 1:
2 10
2 3 3
3 4 2

SAMPLE OUTPUT 1:
14
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Memperlakukan k barang terpisah memberi O(W * sum k) - terlalu lambat untuk k = 10^6. Pecah k menjadi 1, 2, 4, ..., sisa sehingga menjadi O(W log k). Materi lengkapnya Day 147.

    return 0;
}
