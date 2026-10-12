/*
============================================================
📋 TUGAS 07: Penyesuaian Jadwal Kedatangan Kereta Api Cepat
============================================================
Source: Train Dispatch Schedule Alignment
Difficulty: Hard
Topics: Slope Trick, Index Transformation

PROBLEM:
Terdapat N stasiun perhentian kereta api cepat dengan waktu jadwal tentatif t[0], ..., t[N-1] (menit).
Untuk keselamatan jalur rel, selisih waktu tiba di dua stasiun berurutan harus minimal H menit:
t'[i] - t'[i-1] >= H.
Biaya kompensasi ketidaknyamanan adalah |t[i] - t'[i]|.

Tentukan TOTAL BIAYA KOMPENSASI MINIMUM!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan H.
Baris kedua berisi N bilangan bulat t[0], ..., t[N-1].

OUTPUT FORMAT:
Satu baris berisi total biaya minimum.

CONSTRAINTS:
1 <= N <= 200.000
1 <= H <= 10.000
0 <= t[i] <= 1.000.000.000

SAMPLE INPUT 1:
3 10
0 5 15

SAMPLE OUTPUT 1:
5
(t' = [0, 10, 20]: |0-0| + |5-10| + |15-20| = 0 + 5 + 5 = 10?
Tunggu: t' = [-2.5, 7.5, 17.5]? Untuk integer:
Reduksi: t''[i] = t[i] - 10*i -> [0, 5-10=-5, 15-20=-5].
Median dari [0, -5, -5] adalah -5:
|0 - (-5)| + |-5 - (-5)| + |-5 - (-5)| = 5 + 0 + 0 = 5!
Jadwal t' = [-5, 5, 15]: |0 - (-5)| = 5, |5 - 5| = 0, |15 - 15| = 0. Total = 5!)

SAMPLE INPUT 2:
2 5
0 10

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
    ll h;
    if (!(cin >> n >> h)) return 0;

    // TODO: Selesaikan dengan Slope Trick O(N log N)

    return 0;
}
