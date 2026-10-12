/*
============================================================
📋 TUGAS 01: Taksi Paling Mahal (Upper Convex Hull CHT)
============================================================
Source: Classic CHT Maximization
Difficulty: Medium
Topics: Upper Convex Hull Trick, Monotone Deque

PROBLEM:
Tersedia N jenis armada taksi mewah. Tarif perjalanan armada ke-i dinyatakan dengan rumus:
`Tarif_i(x) = m[i] * x + b[i]`.
Seluruh armada diberikan terurut dengan faktor kemiringan m yang TIDAK MENURUN (m[0] <= m[1] <= ... <= m[N-1]).

Terdapat Q calon pelanggan yang masing-masing akan menempuh jarak x.
Seluruh jarak x terurut TIDAK MENURUN (x[0] <= x[1] <= ... <= x[Q-1]).

Untuk setiap pelanggan, tentukan TARIF MAKSIMUM di antara seluruh armada!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan Q.
N baris berikutnya masing-masing berisi dua bilangan bulat m[i] dan b[i].
Baris terakhir berisi Q bilangan bulat x[0], ..., x[Q-1].

OUTPUT FORMAT:
Cetak Q baris, masing-masing berisi tarif maksimum.

CONSTRAINTS:
1 <= N, Q <= 200.000
-1.000.000 <= m[i], x[q] <= 1.000.000
-1.000.000.000.000 <= b[i] <= 1.000.000.000.000
m tidak menurun, x tidak menurun

SAMPLE INPUT 1:
2 2
1 0
2 -1
0 3

SAMPLE OUTPUT 1:
0
5

SAMPLE INPUT 2:
1 2
0 -4
-5 5

SAMPLE OUTPUT 2:
-4
-4
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

    // TODO: Selesaikan dengan Upper Convex Hull Trick

    return 0;
}
