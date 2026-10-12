/*
============================================================
📋 TUGAS 07: Koin dengan Batas Maksimum Banyak Keping
============================================================
Source: Competitive Programming Variation
Difficulty: Medium
Topics: Coin Change Minimum + Predicate Check

PROBLEM:
Diberikan N jenis koin c[0], ..., c[N-1], sebuah nominal target X,
dan sebuah bilangan bulat K.
Setiap jenis koin tersedia dalam jumlah tak terbatas.
Tentukan apakah nominal X dapat dibentuk menggunakan PALING BANYAK K keping koin.
Cetak "YES" jika mungkin, atau "NO" jika mustahil.

INPUT FORMAT:
Baris pertama berisi tiga bilangan bulat N, X, dan K.
Baris kedua berisi N bilangan bulat c[0], ..., c[N-1].

OUTPUT FORMAT:
Satu baris: "YES" atau "NO".

CONSTRAINTS:
1 <= N <= 100
0 <= X <= 10.000
0 <= K <= 10.000
1 <= c[i] <= 10.000

SAMPLE INPUT 1:
2 6 2
1 3

SAMPLE OUTPUT 1:
YES
(Penjelasan: 6 = 3 + 3, butuh 2 keping. 2 <= 2, maka YES)

SAMPLE INPUT 2:
2 6 1
1 3

SAMPLE OUTPUT 2:
NO
(Penjelasan: Butuh minimal 2 keping koin untuk membentuk 6. Karena K = 1, jawabannya NO)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x, k;
    if (!(cin >> n >> x >> k)) return 0;

    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    // TODO: Hitung koin minimum untuk membentuk nominal x
    // Jika min_coins <= k, cetak "YES", selain itu cetak "NO"

    return 0;
}
