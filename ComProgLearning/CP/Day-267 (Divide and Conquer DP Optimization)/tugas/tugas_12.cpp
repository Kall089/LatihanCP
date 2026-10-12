/*
============================================================
📋 TUGAS 12: Pengelompokan Pasukan dengan Biaya Konflik Submatriks
============================================================
Source: Classic D&C DP Optimization / 2D Prefix Sums
Difficulty: Hard
Topics: Divide and Conquer DP Optimization, 2D Prefix Sums

PROBLEM:
Terdapat N prajurit yang berbaris dari 1 sampai N. Mereka harus dibagi menjadi TEPAT K pleton berurutan.
Antara prajurit i dan j terdapat potensi konflik c[i][j] (c[i][j] = c[j][i], c[i][i] = 0).
Biaya konflik satu pleton yang memuat prajurit dari l sampai r adalah:
`Cost(l, r) = sum_{l <= i < j <= r} c[i][j]`.

Tentukan TOTAL BIAYA KONFLIK MINIMUM untuk membagi seluruh prajurit ke dalam tepat K pleton!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan K.
N baris berikutnya masing-masing berisi N bilangan bulat (matriks konflik c[i][j]).

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: total konflik minimum.

CONSTRAINTS:
1 <= N <= 2.000
1 <= K <= min(N, 200)
0 <= c[i][j] <= 100
c[i][j] = c[j][i], c[i][i] = 0

SAMPLE INPUT 1:
4 2
0 5 1 1
5 0 1 1
1 1 0 5
1 1 5 0

SAMPLE OUTPUT 1:
10
(Bagi [1, 2] (konflik 5) dan [3, 4] (konflik 5), total = 5 + 5 = 10)

SAMPLE INPUT 2:
3 3
0 1 2
1 0 3
2 3 0

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

    int n, k;
    if (!(cin >> n >> k)) return 0;

    // TODO: Selesaikan dengan 2D Prefix Sum + D&C DP

    return 0;
}
