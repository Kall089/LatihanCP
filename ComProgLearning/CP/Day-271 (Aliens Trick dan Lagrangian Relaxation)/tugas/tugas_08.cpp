/*
============================================================
📋 TUGAS 08: Penjadwalan K Batch Server Cloud dengan Latensi Kuadratik
============================================================
Source: Cloud Server Batch Scheduling
Difficulty: Hard
Topics: Aliens Trick, CHT

PROBLEM:
Terdapat N tugas komputasi berurutan dengan durasi siklus CPU t[0], ..., t[N-1].
Tugas harus dibagi ke dalam TEPAT K batch pemrosesan berurutan.
Latensi setiap batch berbanding kuadratik terhadap total waktu siklusnya:
`Latensi(Batch) = (sum_{x in Batch} t[x])^2`.

Tentukan TOTAL LATENSI MINIMUM dari seluruh K batch!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan K.
Baris kedua berisi N bilangan bulat non-negatif t[0], ..., t[N-1].

OUTPUT FORMAT:
Satu baris berisi total latensi minimum.

CONSTRAINTS:
1 <= K <= N <= 100.000
0 <= t[i] <= 10.000

SAMPLE INPUT 1:
3 2
3 3 6

SAMPLE OUTPUT 1:
72
(Batch 1: [3, 3] -> 6^2 = 36. Batch 2: [6] -> 6^2 = 36. Total = 72)

SAMPLE INPUT 2:
2 1
10 20

SAMPLE OUTPUT 2:
900
(30^2 = 900)
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

    // TODO: Selesaikan dengan Aliens Trick + CHT O(N log(MaxLatency))

    return 0;
}
