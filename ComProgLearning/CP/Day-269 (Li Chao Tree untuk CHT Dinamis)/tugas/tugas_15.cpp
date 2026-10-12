/*
============================================================
📋 TUGAS 15: Penilaian Hak Tambang Dinamis
============================================================
Source: Mining Lease Evaluation
Difficulty: Menantang
Topics: Li Chao Tree, Maximization

PROBLEM:
Terdapat N blok konsesi tambang bernomor 1 sampai N.
Blok ke-i memiliki estimasi cadangan mineral c[i] dan potensi yield y[i] (acak).
Blok 1 telah dikembangkan dengan valuasi keuntungan awal 0.
Pengembangan blok i dari blok j sebelumnya (j < i) menghasilkan keuntungan:
`Gain(j, i) = dp[j] + y[j] * c[i] - Cost_base`.

Tentukan VALUASI KEUNTUNGAN MAKSIMUM untuk mengembangkan hingga blok N!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan Cost_base.
Baris kedua berisi N bilangan bulat c[0], ..., c[N-1].
Baris ketiga berisi N bilangan bulat y[0], ..., y[N-1].

OUTPUT FORMAT:
Satu baris berisi keuntungan maksimum mencapai blok N.

CONSTRAINTS:
1 <= N <= 200.000
0 <= Cost_base <= 1.000.000.000
-1.000.000 <= c[i], y[i] <= 1.000.000

SAMPLE INPUT 1:
3 10
2 5 3
4 1 2

SAMPLE OUTPUT 1:
2
(1 -> 3: 0 + 4 * 3 - 10 = 12 - 10 = 2)

SAMPLE INPUT 2:
1 100
5
2

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

    int n;
    ll cost_base;
    if (!(cin >> n >> cost_base)) return 0;

    // TODO: Selesaikan dengan Max Li Chao Tree

    return 0;
}
