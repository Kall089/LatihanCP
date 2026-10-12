/*
============================================================
📋 TUGAS 07: Pembagian Menara Selular di Garis Pantai
============================================================
Source: Classic D&C DP Optimization
Difficulty: Hard
Topics: Divide and Conquer DP Optimization, Prefix Sums

PROBLEM:
Terdapat N rumah di garis pantai pada koordinat x[0] <= x[1] <= ... <= x[N-1].
Kita akan memasang K menara pemancar di posisi salah satu rumah di setiap kelompok.
Biaya menara di posisi x_m untuk melayani rumah-rumah di rentang [l..r] adalah
JUMLAH KUADRAT JARAK ke menara:
`Cost(l, r) = min_{m \in [l, r]} sum_{i=l}^r (x[i] - x[m])^2`.

Tentukan TOTAL BIAYA MINIMUM untuk melayani seluruh rumah dengan tepat K pemancar!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan K.
Baris kedua berisi N bilangan bulat non-negatif x[0], ..., x[N-1] (terurut menaik).

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: total biaya minimum.

CONSTRAINTS:
1 <= K <= min(N, 30)
1 <= N <= 10.000
0 <= x[i] <= 100.000

SAMPLE INPUT 1:
3 1
1 2 4

SAMPLE OUTPUT 1:
5
(Jika pasang di 2: (1-2)^2 + (2-2)^2 + (4-2)^2 = 1 + 0 + 4 = 5)

SAMPLE INPUT 2:
4 2
1 2 5 6

SAMPLE OUTPUT 2:
2
(Kelompok 1 [1, 2] pasang di 1 atau 2 -> biaya 1; Kelompok 2 [5, 6] pasang di 5 atau 6 -> biaya 1. Total = 2)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    // TODO: Selesaikan dengan D&C DP

    return 0;
}
