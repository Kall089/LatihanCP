/*
============================================================
📋 TUGAS 08: Penukaran Koin Keping Minimum Top-Down
============================================================
Source: Classic Coin Change / Top-Down Paradigm
Difficulty: Medium
Topics: 1D Top-Down Memoization, Unbounded Transitions

PROBLEM:
Terdapat N jenis pecahan koin berbeda: c[0], c[1], ..., c[N-1].
Persediaan setiap pecahan koin tidak terbatas.
Tentukan JUMLAH KEPING KOIN PALING SEDIKIT yang dibutuhkan untuk membentuk total nilai nominal persis X!
Jika nominal X mustahil dibentuk, cetak -1.

Wajib diimplementasikan menggunakan REKURSIF DENGAN MEMOISASI (Top-Down)!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan X.
Baris kedua berisi N bilangan bulat c[0], ..., c[N-1].

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: keping koin minimum, atau -1 jika mustahil.

CONSTRAINTS:
1 <= N <= 100
0 <= X <= 10.000
1 <= c[i] <= 10.000

SAMPLE INPUT 1:
3 11
1 2 5

SAMPLE OUTPUT 1:
3
(11 = 5 + 5 + 1, total 3 keping)

SAMPLE INPUT 2:
2 3
2 4

SAMPLE OUTPUT 2:
-1
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

    vector<int> c(n);
    for (int i = 0; i < n; i++) cin >> c[i];

    // TODO: Selesaikan dengan top-down memoization

    return 0;
}
