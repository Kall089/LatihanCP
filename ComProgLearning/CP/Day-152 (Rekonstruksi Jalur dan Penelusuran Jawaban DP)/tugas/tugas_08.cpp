/*
============================================================
📋 TUGAS 08: Rekonstruksi Barisan Koin Kasir Bounded
============================================================
Source: Classic DP / Bounded Coin Change Reconstruction
Difficulty: Medium-Hard
Topics: Bounded Knapsack DP, Coin Frequency Output

PROBLEM:
Kasir memiliki N jenis koin. Koin ke-i bernilai c[i] dan memiliki stok sebanyak k[i] keping.
Pelanggan ingin menukarkan uang sejumlah X dengan jumlah keping koin seminimal mungkin.
Jika memungkinkan, cetak jumlah keping minimum pada baris pertama,
dan pada N baris berikutnya cetak banyak keping koin yang dipakai untuk setiap jenis koin ke-i:
"c[i]: count".
Jika mustahil, cetak -1.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan X.
N baris berikutnya masing-masing berisi dua bilangan bulat c[i] dan k[i].

OUTPUT FORMAT:
Jika mustahil: -1.
Jika mungkin: jumlah koin minimum pada baris pertama, diikuti N baris format "c[i]: count".

CONSTRAINTS:
1 <= N <= 100
1 <= X <= 5.000
1 <= c[i] <= 5.000
1 <= k[i] <= 100

SAMPLE INPUT 1:
3 11
5 2
2 5
1 10

SAMPLE OUTPUT 1:
3
5: 2
2: 0
1: 1
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    if (!(cin >> n >> x)) return 0;

    vector<int> c(n), k(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i] >> k[i];
    }

    // TODO: Selesaikan Bounded Coin Change dan rekonstruksi jumlah per koin

    return 0;
}
