/*
============================================================
📋 TUGAS 09: Penjadwalan Server dengan Bobot Fleksibel
============================================================
Source: Classic Dynamic CHT
Difficulty: Hard
Topics: Li Chao Tree, Linear DP

PROBLEM:
Terdapat N tugas pemrosesan server bernomor 1 sampai N.
Tugas ke-i memiliki beban komputasi b[i] dan waktu latensi w[i] yang tidak terurut.
Tugas 1 telah selesai dengan biaya 0.
Untuk mengeksekusi tugas i (i > 1), tugas dihubungkan dengan salah satu tugas j sebelumnya (j < i)
dengan penalti:
`dp[i] = min_{j < i} (dp[j] + b[j] * w[i])`.

Tentukan TOTAL PENALTI MINIMUM untuk menyelesaikan tugas ke-N!

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat w[0], ..., w[N-1].
Baris ketiga berisi N bilangan bulat b[0], ..., b[N-1].

OUTPUT FORMAT:
Satu baris berisi penalti minimum menyelesaikan tugas N.

CONSTRAINTS:
1 <= N <= 200.000
-1.000.000 <= w[i], b[i] <= 1.000.000

SAMPLE INPUT 1:
3
4 1 2
3 5 1

SAMPLE OUTPUT 1:
6
(Tugas 0: dp=0, garis 3x.
 Tugas 2: dp[2] = 3 * 2 = 6.)

SAMPLE INPUT 2:
1
10
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
    if (!(cin >> n)) return 0;

    // TODO: Selesaikan dengan Li Chao Tree

    return 0;
}
