/*
============================================================
📋 TUGAS 07: Penukaran Koin dengan Batas Frekuensi Koin
============================================================
Source: Classic DP / Bounded Knapsack Coin Change
Difficulty: Medium-Hard
Topics: Bounded Knapsack, Binary Splitting

PROBLEM:
Kamu memiliki N jenis koin. Koin ke-i memiliki nilai pecahan c[i] dan persediaan sebanyak count[i] keping.
Tentukan apakah kamu bisa membentuk nominal TEPAT X menggunakan koin-koin tersebut!
Cetak "BISA" jika bisa, atau "TIDAK BISA" jika tidak bisa.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan X.
N baris berikutnya masing-masing berisi dua bilangan bulat c[i] dan count[i].

OUTPUT FORMAT:
"BISA" atau "TIDAK BISA".

CONSTRAINTS:
1 <= N <= 100
0 <= X <= 50.000
1 <= c[i] <= 50.000
1 <= count[i] <= 50.000

SAMPLE INPUT 1:
2 10
3 2
4 1

SAMPLE OUTPUT 1:
BISA
(2 keping 3 + 1 keping 4 = 6 + 4 = 10)

SAMPLE INPUT 2:
1 5
2 2

SAMPLE OUTPUT 2:
TIDAK BISA
(2 keping 2 hanya mencapai 4, tidak bisa 5)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    if (!(cin >> n >> x)) return 0;

    // TODO: Selesaikan Bounded Coin Change dengan binary splitting atau count array

    return 0;
}
