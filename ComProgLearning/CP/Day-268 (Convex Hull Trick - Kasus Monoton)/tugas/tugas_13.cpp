/*
============================================================
📋 TUGAS 13: Relai Sinyal Satelit dengan Kehilangan Transmisi
============================================================
Source: Classic CHT DP
Difficulty: Hard
Topics: Convex Hull Trick, Deque

PROBLEM:
Terdapat N stasiun pemancar satelit bernomor 1 sampai N dengan faktor redaman a[0] <= a[1] <= ... <= a[N-1]
dan faktor penguatan antena b[0] >= b[1] >= ... >= b[N-1].
Stasiun 1 telah menyala dengan biaya transmisi 0.
Untuk mengirimkan sinyal ke stasiun i (i > 1), sinyal diteruskan dari stasiun j yang sudah aktif (j < i)
dengan biaya:
`dp[i] = min_{j < i} (dp[j] + b[j] * a[i] + C * (i - j))`.

Tentukan TOTAL BIAYA MINIMUM untuk mencapai stasiun N!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan C.
Baris kedua berisi N bilangan bulat a[0], ..., a[N-1].
Baris ketiga berisi N bilangan bulat b[0], ..., b[N-1].

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: biaya minimum mencapai stasiun N.

CONSTRAINTS:
1 <= N <= 200.000
0 <= C <= 1.000.000
0 <= a[i], b[i] <= 1.000.000

SAMPLE INPUT 1:
3 2
1 3 5
6 4 1

SAMPLE OUTPUT 1:
18

SAMPLE INPUT 2:
1 10
2
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
    ll c;
    if (!(cin >> n >> c)) return 0;

    // TODO: Selesaikan dengan CHT Deque

    return 0;
}
