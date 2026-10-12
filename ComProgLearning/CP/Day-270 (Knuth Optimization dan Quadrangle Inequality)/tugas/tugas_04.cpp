/*
============================================================
📋 TUGAS 04: Penggabungan Logistik Gudang Multi-Regional
============================================================
Source: Regional Warehouse Integration
Difficulty: Hard
Topics: Knuth Optimization, Range DP

PROBLEM:
Terdapat N gudang logistik berurutan dari barat ke timur dengan kapasitas barang c[0], ..., c[N-1].
Penggabungan dua kelompok gudang bersebelahan memerlukan biaya sebanding dengan
jumlah kapasitas kedua kelompok dikalikan biaya transfer regional T:
`Cost(l, r) = T * sum_{k=l}^r c[k]`.

Tentukan TOTAL BIAYA MINIMUM untuk menggabungkan seluruh gudang menjadi satu gudang terpusat!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan T.
Baris kedua berisi N bilangan bulat c[0], ..., c[N-1].

OUTPUT FORMAT:
Satu baris berisi total biaya minimum.

CONSTRAINTS:
1 <= N <= 2000
1 <= T <= 10.000
0 <= c[i] <= 1.000.000.000

SAMPLE INPUT 1:
4 2
4 1 2 3

SAMPLE OUTPUT 1:
38
(Biaya dasar = 19, dikalikan T=2 -> 38)

SAMPLE INPUT 2:
1 5
100

SAMPLE OUTPUT 2:
0
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll t;
    if (!(cin >> n >> t)) return 0;

    // TODO: Selesaikan dengan Knuth Optimization O(N^2)

    return 0;
}
