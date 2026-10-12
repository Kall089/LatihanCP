/*
============================================================
📋 TUGAS 09: Menutupi Segmen Jalan Tol dengan K Kamera Pengawas
============================================================
Source: Toll Road Surveillance Optimization
Difficulty: Hard
Topics: Aliens Trick, CHT

PROBLEM:
Terdapat N titik rawan kecelakaan pada kilometer tol: p[0] < p[1] < ... < p[N-1].
Pengelola jalan tol ingin memasang PALING BANYAK K unit kamera pemantau panorama.
Kamera yang menutupi bentang dari p[j] sampai p[i] memiliki biaya perangkat sebanding dengan
kuadrat jarak jangkauan:
`Biaya = (p[i] - p[j])^2`.

Tentukan TOTAL BIAYA PEMASANGAN MINIMUM untuk memantau seluruh N titik rawan!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan K.
Baris kedua berisi N bilangan bulat non-negatif p[0], ..., p[N-1] (terurut menaik).

OUTPUT FORMAT:
Satu baris berisi total biaya minimum.

CONSTRAINTS:
1 <= K <= N <= 100.000
0 <= p[0] < ... < p[N-1] <= 1.000.000.000

SAMPLE INPUT 1:
4 2
0 3 6 10

SAMPLE OUTPUT 1:
25
(Kamera 1: [0, 3] -> (3-0)^2 = 9. Kamera 2: [6, 10] -> (10-6)^2 = 16. Total = 25.
 Titik yang dicover: [0..1] dan [2..3], mencakup semua 4 titik.)

SAMPLE INPUT 2:
3 3
1 5 10

SAMPLE OUTPUT 2:
0
(Tiga kamera jangkauan 0 di masing-masing titik: 0 + 0 + 0 = 0)
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

    // TODO: Selesaikan dengan Aliens Trick + CHT

    return 0;
}
