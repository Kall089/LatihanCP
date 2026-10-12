/*
============================================================
📋 TUGAS 04: Toko Roti dengan Bahan Baku Terbatas
============================================================
Source: Classic DP / Exact Target
Difficulty: Medium
Topics: Exact Target Bounded Knapsack

PROBLEM:
Sebuah toko roti memiliki sisa tepung tepat seberat W gram. Pemilik toko
ingin menghabiskan seluruh tepung tersebut sampai tidak tersisa sedikit pun
(total berat bahan tepung yang digunakan harus TEPAT SAMA DENGAN W).
Toko dapat memanggang N jenis kue. Satu buah kue jenis ke-i membutuhkan tepung
seberat w[i] gram, menghasilkan laba v[i] rupiah, dan cetakan kue tersebut hanya
dapat digunakan paling banyak c[i] kali hari ini.

Tentukan laba total maksimum yang bisa diperoleh.
Jika tidak ada kombinasi kue yang dapat menghabiskan tepung tepat W gram, cetak -1.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan W.
N baris berikutnya, masing-masing berisi tiga bilangan bulat w[i], v[i], dan c[i].

OUTPUT FORMAT:
Satu bilangan bulat: laba maksimum pada kapasitas tepat W, atau -1 jika mustahil.

CONSTRAINTS:
1 <= N <= 100
1 <= W <= 20.000
1 <= w[i] <= W
1 <= v[i] <= 10^9
1 <= c[i] <= 1.000

SAMPLE INPUT 1:
2 10
3 8 2
2 5 3

SAMPLE OUTPUT 1:
26
(Penjelasan: Panggang 2 kue jenis 0 (tepung 6, laba 16) + 2 kue jenis 1 (tepung 4, laba 10) = tepung 10, laba 26)

SAMPLE INPUT 2:
1 7
2 10 5

SAMPLE OUTPUT 2:
-1
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
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> v[i] >> c[i];
    }

    // TODO: Selesaikan Exact Target Bounded Knapsack
    // vector<ll> dp(W + 1, -1); dp[0] = 0;
    // Loop paket biner mundur, hanya update jika dp[s - wt] != -1

    return 0;
}
