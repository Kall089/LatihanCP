/*
============================================================
📋 TUGAS 08: Rantai Konveyor Tambang Batubara
============================================================
Source: Coal Conveyor Merging
Difficulty: Hard
Topics: Knuth Optimization, Range DP

PROBLEM:
Terdapat N seksi sabuk konveyor tambang berurutan dengan laju aliran batubara f[0], ..., f[N-1].
Untuk mengonsolidasikan kendali, seksi-seksi bersebelahan digabungkan bertahap.
Biaya penggabungan adalah total laju aliran ditambah biaya kalibrasi motor M:
`Cost(l, r) = sum_{k=l}^r f[k] + M`.

Tentukan TOTAL BIAYA KONSOLIDASI MINIMUM untuk seluruh N seksi konveyor!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan M.
Baris kedua berisi N bilangan bulat non-negatif f[0], ..., f[N-1].

OUTPUT FORMAT:
Satu baris berisi biaya konsolidasi minimum.

CONSTRAINTS:
1 <= N <= 2000
0 <= M <= 1.000.000.000
0 <= f[i] <= 1.000.000.000

SAMPLE INPUT 1:
3 0
10 20 30

SAMPLE OUTPUT 1:
90
(10+20 = 30, lalu 30+30 = 60 -> total = 90)

SAMPLE INPUT 2:
1 100
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
    ll m;
    if (!(cin >> n >> m)) return 0;

    // TODO: Selesaikan dengan Knuth Optimization O(N^2)

    return 0;
}
