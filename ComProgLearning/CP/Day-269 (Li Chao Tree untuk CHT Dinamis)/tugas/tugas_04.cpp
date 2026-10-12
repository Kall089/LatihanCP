/*
============================================================
📋 TUGAS 04: Pemilihan Mesin Produksi Berkecepatan Bebas
============================================================
Source: Dynamic CHT Linear DP
Difficulty: Hard
Topics: Li Chao Tree, Non-Monotone Lines

PROBLEM:
Sebuah pabrik memproses N tahap manufaktur dari 1 sampai N.
Tahap ke-i memiliki waktu dasar w[i] dan koefisien efisiensi k[i] yang acak.
Tahap 1 dimulai dengan biaya 0.
Untuk beralih dari tahap j ke tahap i (j < i), biaya transisinya adalah:
`dp[i] = min_{j < i} (dp[j] + k[j] * w[i] + C)`.

Tentukan TOTAL BIAYA MINIMUM untuk menyelesaikan tahap N!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan C.
Baris kedua berisi N bilangan bulat w[0], ..., w[N-1].
Baris ketiga berisi N bilangan bulat k[0], ..., k[N-1].

OUTPUT FORMAT:
Satu baris berisi total biaya minimum mencapai tahap N.

CONSTRAINTS:
1 <= N <= 200.000
0 <= C <= 1.000.000.000
-1.000.000 <= w[i], k[i] <= 1.000.000

SAMPLE INPUT 1:
3 5
2 4 1
3 1 2

SAMPLE OUTPUT 1:
8
(Tahap 0: dp=0, garis 3x.
 Tahap 2: min(3*1 + 5) = 8.)

SAMPLE INPUT 2:
1 10
5
2

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

    // TODO: Selesaikan dengan Li Chao Tree

    return 0;
}
