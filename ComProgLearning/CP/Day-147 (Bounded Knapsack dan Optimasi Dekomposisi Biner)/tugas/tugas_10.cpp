/*
============================================================
📋 TUGAS 10: Membeli Bahan Bangunan dengan Diskon Batas
============================================================
Source: Competitive Programming Variation
Difficulty: Medium-Hard
Topics: Bounded Knapsack with Tiered Pricing

PROBLEM:
Sebuah proyek konstruksi membutuhkan sejumlah bahan bangunan.
Toko material menjual N jenis produk semen instan.
Satu sak semen jenis ke-i berbobot w[i] kg dan memberikan kualitas perekat v[i] poin.
Namun, ada aturan pembelian:
- Setiap kontraktor hanya diperbolehkan membeli paling banyak c[i] sak semen jenis ke-i.
Truk pengangkut hanya mampu mengangkut bobot total maksimum W kg.
Tentukan total kualitas perekat maksimum yang dapat diangkut oleh truk tanpa melebihi batas bobot W.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan W.
N baris berikutnya, masing-masing berisi tiga bilangan bulat w[i], v[i], dan c[i].

OUTPUT FORMAT:
Satu bilangan bulat: total poin kualitas perekat maksimum.

CONSTRAINTS:
1 <= N <= 150
1 <= W <= 30.000
1 <= w[i] <= W
1 <= v[i] <= 10^9
1 <= c[i] <= 5.000

SAMPLE INPUT 1:
3 20
5 12 3
4 9 4
6 15 2

SAMPLE OUTPUT 1:
48
(Penjelasan: Ambil 2 sak jenis 2 (bobot 12, val 30) + 2 sak jenis 1 (bobot 8, val 18) = bobot 20, kualitas 48)

SAMPLE INPUT 2:
1 10
7 20 1

SAMPLE OUTPUT 2:
20
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

    vector<int> w(n);
    vector<ll> v(n);
    vector<ll> c(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> v[i] >> c[i];
    }

    // TODO: Selesaikan Bounded Knapsack dengan Optimasi Biner
    // vector<ll> dp(W + 1, 0)
    // Pecah c[i] secara biner dan loop mundur

    return 0;
}
