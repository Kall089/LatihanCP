/*
============================================================
📋 TUGAS 11: Partisi Sinyal Digital dengan Reduksi Noise
============================================================
Source: Signal Smoothing DP
Difficulty: Hard
Topics: Li Chao Tree, Quadratic DP

PROBLEM:
Diberikan sinyal digital dengan N sampel s[0], ..., s[N-1] (acak).
Sinyal diproses dari sampel 1 hingga N. Sampel 1 memiliki biaya awal 0.
Biaya transisi filter dari sampel j ke sampel i (j < i) adalah:
`Cost(j, i) = (s[i] - s[j])^2 + Lam`.

Tentukan TOTAL BIAYA FILTER MINIMUM untuk mencapai sampel N!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan Lam.
Baris kedua berisi N bilangan bulat sinyal s[0], ..., s[N-1].

OUTPUT FORMAT:
Satu baris berisi biaya filter minimum mencapai sampel N.

CONSTRAINTS:
1 <= N <= 200.000
0 <= Lam <= 1.000.000.000
-1.000.000 <= s[i] <= 1.000.000

SAMPLE INPUT 1:
3 10
5 1 4

SAMPLE OUTPUT 1:
11
(1 -> 3: (4 - 5)^2 + 10 = 11)

SAMPLE INPUT 2:
1 10
5

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
    ll lam;
    if (!(cin >> n >> lam)) return 0;

    // TODO: Selesaikan dengan Li Chao Tree

    return 0;
}
