/*
============================================================
📋 TUGAS 08: Beli Saham Maksimal Dua Transaksi
============================================================
Source: LeetCode 123
Difficulty: Medium-Hard
Topics: State Design, Multi-Dimensional DP

PROBLEM:
Diberikan array harga saham selama N hari.
Kamu diperbolehkan menyelesaikan MAKSIMAL DUA KALI TRANSAKSI (2 kali beli dan 2 kali jual).
Catatan: Kamu tidak boleh melakukan transaksi ganda secara bersamaan
(kamu harus menjual saham sebelum bisa membeli saham berikutnya).
Hitung keuntungan maksimum yang bisa kamu peroleh.

INPUT FORMAT:
Baris pertama: N
Baris kedua: N bilangan bulat price[0], price[1], ..., price[N-1]

OUTPUT FORMAT:
Satu bilangan bulat: keuntungan maksimum.

CONSTRAINTS:
1 <= N <= 100.000
0 <= price[i] <= 10.000

SAMPLE INPUT 1:
8
3 3 5 0 0 3 1 4

SAMPLE OUTPUT 1:
6
(Penjelasan: Beli di hari ke-4 (harga 0), jual di hari ke-6 (harga 3), untung 3-0=3.
 Kemudian beli di hari ke-7 (harga 1), jual di hari ke-8 (harga 4), untung 4-1=3.
 Total keuntungan = 3 + 3 = 6.)

SAMPLE INPUT 2:
5
1 2 3 4 5

SAMPLE OUTPUT 2:
4
(Penjelasan: Beli di hari 1 (1), jual di hari 5 (5), untung 4.)

SAMPLE INPUT 3:
5
7 6 4 3 1

SAMPLE OUTPUT 3:
0
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> price(n);
    for (int i = 0; i < n; i++) cin >> price[i];

    // TODO: Definisikan 4 variabel transisi:
    // buy1, sell1, buy2, sell2
    // Inisialisasi: buy1 = -INF, sell1 = 0, buy2 = -INF, sell2 = 0

    return 0;
}
