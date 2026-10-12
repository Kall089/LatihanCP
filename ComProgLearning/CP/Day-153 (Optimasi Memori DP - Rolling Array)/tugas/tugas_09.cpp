/*
============================================================
📋 TUGAS 09: Beli Jual Saham dengan Cooldown O(1) Memori
============================================================
Source: LeetCode 309 (Best Time to Buy and Sell Stock with Cooldown)
Difficulty: Hard
Topics: State Machine DP, O(1) Space Optimization

PROBLEM:
Diberikan array harga saham selama N hari: prices[0], ..., prices[N-1].
Kamu boleh melakukan transaksi sebanyak mungkin (beli lalu jual), dengan aturan:
1. Kamu tidak boleh memiliki lebih dari satu saham secara bersamaan (harus jual dulu sebelum beli lagi).
2. Setelah kamu menjual saham pada hari ke-i, kamu harus beristirahat (cooldown) pada hari ke-i+1
   (tidak boleh membeli saham pada hari ke-i+1).
Tentukan keuntungan maksimum yang dapat dicapai!
Gunakan O(1) memori tambahan (hanya variabel state hold, sold, rest).

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat prices[0], ..., prices[N-1].

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: keuntungan maksimum.

CONSTRAINTS:
1 <= N <= 200.000
0 <= prices[i] <= 10.000

SAMPLE INPUT 1:
5
1 2 3 0 2

SAMPLE OUTPUT 1:
3
(Beli di hari 0 [1], jual di hari 1 [2], profit 1. Cooldown di hari 2.
Beli di hari 3 [0], jual di hari 4 [2], profit 2. Total = 3)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<ll> prices(n);
    for (int i = 0; i < n; i++) {
        cin >> prices[i];
    }

    // TODO: Selesaikan Stock with Cooldown dengan 3 variabel O(1) memori

    return 0;
}
