/*
============================================================
📋 TUGAS 11: Penyelarasan Volume Suara Rangkaian Audio Track
============================================================
Source: Audio Master Volume Smoothing
Difficulty: Medium
Topics: Slope Trick, Max-Heap

PROBLEM:
Terdapat N segmen lagu dengan tingkat kekerasan suara awal v[0], ..., v[N-1] (desibel).
Untuk transisi bertahap (fade-in), tingkat suara baru v'[i] harus tidak menurun:
v'[0] <= v'[1] <= ... <= v'[N-1].
Biaya distorsi adalah |v[i] - v'[i]|.

Tentukan TOTAL BIAYA DISTORSI MINIMUM!

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat v[0], ..., v[N-1].

OUTPUT FORMAT:
Satu baris berisi total biaya minimum.

CONSTRAINTS:
1 <= N <= 200.000
-1.000.000.000 <= v[i] <= 1.000.000.000

SAMPLE INPUT 1:
3
80 60 40

SAMPLE OUTPUT 1:
40
(v' = [60, 60, 60] -> |80-60| + 0 + |40-60| = 20 + 20 = 40)

SAMPLE INPUT 2:
3
30 40 50

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
    if (!(cin >> n)) return 0;

    // TODO: Selesaikan dengan Slope Trick O(N log N)

    return 0;
}
