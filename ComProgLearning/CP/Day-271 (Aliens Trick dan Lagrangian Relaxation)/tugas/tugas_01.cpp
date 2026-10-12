/*
============================================================
📋 TUGAS 01: Transaksi Saham dengan Biaya Komisi Broker
============================================================
Source: Stock Trading with Fixed Fee
Difficulty: Medium
Topics: Aliens Trick, State Machine DP

PROBLEM:
Diberikan riwayat harga saham P[0], ..., P[N-1] selama N hari.
Kamu boleh melakukan paling banyak K transaksi.
Setiap transaksi (pembelian dan penjualan) juga dikenakan biaya komisi broker tetap sebesar F.
Artinya, jika membeli pada harga P[i] dan menjual pada harga P[j] (j > i), keuntungan bersihnya adalah:
`Keuntungan = (P[j] - P[i]) - F`.
Kamu tidak boleh memegang lebih dari 1 saham secara bersamaan.
Transaksi tidak wajib dilakukan jika menghasilkan kerugian.

Tentukan TOTAL KEUNTUNGAN BERSIH MAKSIMUM yang dapat diperoleh!

INPUT FORMAT:
Baris pertama berisi tiga bilangan bulat N, K, dan F.
Baris kedua berisi N bilangan bulat non-negatif P[0], ..., P[N-1].

OUTPUT FORMAT:
Satu baris berisi total keuntungan maksimum.

CONSTRAINTS:
1 <= N <= 200.000
1 <= K <= N
0 <= F <= 1.000.000.000
0 <= P[i] <= 1.000.000.000

SAMPLE INPUT 1:
4 2 1
1 3 2 8

SAMPLE OUTPUT 1:
6
(Beli di hari 0 (harga 1) dan jual di hari 3 (harga 8): keuntungan = (8 - 1) - 1 = 6)

SAMPLE INPUT 2:
3 1 10
2 4 1

SAMPLE OUTPUT 2:
0
(Keuntungan kotor = 2, biaya komisi F = 10 -> rugi, lebih baik 0 transaksi).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    ll f;
    if (!(cin >> n >> k >> f)) return 0;

    // TODO: Selesaikan dengan Aliens Trick O(N log(MaxPrice))

    return 0;
}
