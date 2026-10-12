/*
============================================================
📋 TUGAS 14: Partisi Rantai Produksi Pabrik Menjadi K Tahapan
============================================================
Source: Assembly Line Stage Balancing
Difficulty: Hard
Topics: Aliens Trick, CHT

PROBLEM:
Pabrik manufaktur memiliki N stasiun kerja berurutan dengan durasi kerja w[0], ..., w[N-1].
Seluruh stasiun harus dikelompokkan menjadi TEPAT K tahapan perakitan berseri.
Biaya inefisiensi setiap tahapan adalah kuadrat dari total durasi stasiun di dalamnya:
`Inefisiensi = (sum_{x in Tahap} w[x])^2`.

Tentukan TOTAL BIAYA INEFISIENSI MINIMUM dari seluruh K tahapan perakitan!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan K.
Baris kedua berisi N bilangan bulat non-negatif w[0], ..., w[N-1].

OUTPUT FORMAT:
Satu baris berisi total inefisiensi minimum.

CONSTRAINTS:
1 <= K <= N <= 100.000
0 <= w[i] <= 10.000

SAMPLE INPUT 1:
3 2
5 5 10

SAMPLE OUTPUT 1:
200
(Tahap 1: [5, 5] -> 10^2 = 100. Tahap 2: [10] -> 10^2 = 100. Total = 200)

SAMPLE INPUT 2:
1 1
20

SAMPLE OUTPUT 2:
400
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

    // TODO: Selesaikan dengan Aliens Trick + CHT O(N log(MaxCost))

    return 0;
}
