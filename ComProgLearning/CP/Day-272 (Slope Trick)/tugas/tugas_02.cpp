/*
============================================================
📋 TUGAS 02: Alokasi Spektrum Frekuensi Radio dengan Pita Pengaman
============================================================
Source: Radio Frequency Allocation with Guard Bands
Difficulty: Hard
Topics: Slope Trick, Index Transformation

PROBLEM:
Terdapat N pemancar radio yang memiliki frekuensi dasar f[0], ..., f[N-1].
Untuk menghindari interferensi gelombang, frekuensi baru f'[i] harus terurut tegas menaik dengan
pita pengaman (guard band) minimal sebesar G MHz:
f'[i] - f'[i-1] >= G untuk setiap i = 1, ..., N-1.
Biaya tuning adalah |f[i] - f'[i]|.

Tentukan TOTAL BIAYA TUNING MINIMUM!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan G.
Baris kedua berisi N bilangan bulat f[0], ..., f[N-1].

OUTPUT FORMAT:
Satu baris berisi total biaya minimum.

CONSTRAINTS:
1 <= N <= 200.000
1 <= G <= 10.000
1 <= f[i] <= 1.000.000.000

SAMPLE INPUT 1:
3 2
5 4 3

SAMPLE OUTPUT 1:
6
(Syarat: f'[1] - f'[0] >= 2 dan f'[2] - f'[1] >= 2.
 Reduksi f''[i] = f[i] - 2*i: f'' = [5, 4-2=2, 3-4=-1].
 Median dari [5, 2, -1] adalah 2: |5-2| + |2-2| + |-1-2| = 3 + 0 + 3 = 6.)

SAMPLE INPUT 2:
3 5
10 20 30

SAMPLE OUTPUT 2:
0
(20 - 10 = 10 >= 5, 30 - 20 = 10 >= 5. Biaya = 0)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll g;
    if (!(cin >> n >> g)) return 0;

    // TODO: Selesaikan dengan Slope Trick O(N log N)

    return 0;
}
