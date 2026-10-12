/*
============================================================
📋 TUGAS 01: Paket Bantuan Gempa
============================================================
Source: Classic Bounded Knapsack
Difficulty: Easy
Topics: Bounded Knapsack Dasar, Dekomposisi Biner

PROBLEM:
Sebuah helikopter penyelamat memiliki kapasitas angkut maksimum W kg.
Terdapat N jenis paket bantuan logistik. Paket jenis ke-i memiliki berat w[i] kg,
tingkat urgensi manfaat v[i], dan tersedia sebanyak c[i] paket.
Tentukan total manfaat maksimum yang dapat diangkut oleh helikopter tanpa
melebihi kapasitas W kg.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan W.
N baris berikutnya, masing-masing berisi tiga bilangan bulat w[i], v[i], dan c[i].

OUTPUT FORMAT:
Satu bilangan bulat: total manfaat maksimum.

CONSTRAINTS:
1 <= N <= 100
1 <= W <= 10.000
1 <= w[i] <= W
1 <= v[i] <= 10^6
1 <= c[i] <= 1.000

SAMPLE INPUT 1:
3 15
4 10 3
3 7 4
5 12 2

SAMPLE OUTPUT 1:
36
(Penjelasan: Ambil 2 paket jenis 0 (bobot 8, manfaat 20), 1 paket jenis 1 (bobot 3, manfaat 7),
dan 0 paket jenis 2 -> total bobot 11.
Atau ambil 2 paket jenis 2 (bobot 10, manfaat 24) + 1 paket jenis 0 (bobot 4, manfaat 10) = bobot 14, manfaat 34.
Pilihan terbaik: ambil 1 paket 0 (bobot 4, val 10) + 1 paket 1 (bobot 3, val 7) + 2 paket 2 (bobot 10, val 24) = 17 > 15.
Pilihan valid: 1 paket 0 (4, 10) + 2 paket 1 (6, 14) + 1 paket 2 (5, 12) = bobot 15, manfaat 10 + 14 + 12 = 36!)

SAMPLE INPUT 2:
1 5
6 10 5

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

    int n, W;
    if (!(cin >> n >> W)) return 0;

    vector<int> w(n);
    vector<ll> v(n);
    vector<ll> c(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> v[i] >> c[i];
    }

    // TODO: Selesaikan dengan Bounded Knapsack Dekomposisi Biner
    // 1. Inisialisasi vector<ll> dp(W + 1, 0)
    // 2. Pecah c[i] secara biner
    // 3. Loop mundur dari W ke bobot_paket

    return 0;
}
