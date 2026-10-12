/*
============================================================
📋 TUGAS 10: Pemotongan Kabel Fiber Optik Menjadi K Segmen
============================================================
Source: Fiber Optic K-Partition
Difficulty: Hard
Topics: Aliens Trick, CHT

PROBLEM:
Kabel fiber optik sepanjang total L meter telah memiliki N titik terminasi internal:
0 = d[0] < d[1] < ... < d[N-1] = L.
Kabel harus dipartisi menjadi TEPAT K segmen dengan memilih K-1 titik potong di antara terminasi.
Rugi redaman cahaya pada segmen dari d[j] ke d[i] adalah (d[i] - d[j])^2.

Tentukan TOTAL REDAMAN MINIMUM untuk seluruh K segmen!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan K.
Baris kedua berisi N bilangan bulat d[0], ..., d[N-1] (terurut menaik, d[0] = 0).

OUTPUT FORMAT:
Satu baris berisi total redaman minimum.

CONSTRAINTS:
2 <= N <= 100.000
1 <= K <= N - 1
0 = d[0] < ... < d[N-1] <= 1.000.000.000

SAMPLE INPUT 1:
3 2
0 4 8

SAMPLE OUTPUT 1:
32
(Dua segmen: [0, 4] dan [4, 8] -> 16 + 16 = 32)

SAMPLE INPUT 2:
2 1
0 50

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

    // TODO: Selesaikan dengan Aliens Trick + CHT O(N log(L^2))

    return 0;
}
