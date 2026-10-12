/*
============================================================
📋 TUGAS 03: Promo Titik Akhir (Static Line Segments Li Chao)
============================================================
Source: Li Chao Tree on Range Segments
Difficulty: Hard
Topics: Li Chao Tree, Segment Trees

PROBLEM:
Terdapat N kupon promo yang masing-masing memiliki fungsi harga:
`Tarif_i(x) = m[i] * x + b[i]`
yang HANYA VALID untuk jarak x di mana L[i] <= x <= R[i].
Seluruh kupon promo diberikan di awal.

Terdapat Q kueri titik jarak x[0], ..., x[Q-1].
Untuk setiap titik jarak x, tentukan TARIF PROMO TERMURAH yang berlaku di titik x.
Jika tidak ada promo yang mencakup x, cetak `EMPTY`.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan Q.
N baris berikutnya berisi empat bilangan bulat m[i], b[i], L[i], R[i].
Baris terakhir berisi Q bilangan bulat x[0], ..., x[Q-1].

OUTPUT FORMAT:
Cetak Q baris, masing-masing berisi tarif termurah atau `EMPTY`.

CONSTRAINTS:
1 <= N, Q <= 100.000
-1.000.000 <= m[i], L[i], R[i], x[q] <= 1.000.000
-1.000.000.000.000 <= b[i] <= 1.000.000.000.000
L[i] <= R[i]

SAMPLE INPUT 1:
1 3
1 2 0 1
0 1 2

SAMPLE OUTPUT 1:
2
3
EMPTY

SAMPLE INPUT 2:
1 2
0 -5 -2 -2
-2 0

SAMPLE OUTPUT 2:
-5
EMPTY
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    // TODO: Selesaikan dengan Li Chao Tree Range Segments

    return 0;
}
