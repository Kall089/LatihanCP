/*
============================================================
📋 TUGAS 06: Partisi Muatan Kontainer Kargo ke K Kapal
============================================================
Source: Container Cargo Allocation
Difficulty: Hard
Topics: Aliens Trick, CHT

PROBLEM:
Terdapat N kontainer kargo berurutan dengan berat w[0], ..., w[N-1].
Seluruh kontainer harus dimuat ke dalam TEPAT K kapal kargo secara berurutan.
Beban bahan bakar kapal berbanding lurus dengan kuadrat dari total berat kontainer yang diangkutnya:
`Biaya(Kapal) = (sum_{x in Kapal} w[x])^2`.

Tentukan TOTAL BIAYA BAHAN BAKAR MINIMUM untuk seluruh K kapal!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan K.
Baris kedua berisi N bilangan bulat non-negatif w[0], ..., w[N-1].

OUTPUT FORMAT:
Satu baris berisi total biaya minimum.

CONSTRAINTS:
1 <= K <= N <= 100.000
0 <= w[i] <= 10.000

SAMPLE INPUT 1:
3 2
2 4 6

SAMPLE OUTPUT 1:
72
(Muat [2, 4] dan [6] -> 6^2 + 6^2 = 36 + 36 = 72.
 Jika [2] dan [4, 6] -> 2^2 + 10^2 = 4 + 100 = 104 > 72.)

SAMPLE INPUT 2:
1 1
50

SAMPLE OUTPUT 2:
2500
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
