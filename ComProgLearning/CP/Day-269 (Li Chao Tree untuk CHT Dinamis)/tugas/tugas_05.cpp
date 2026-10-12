/*
============================================================
📋 TUGAS 05: Jaringan Transmisi Energi Nirkabel Acak
============================================================
Source: Wireless Power CHT
Difficulty: Hard
Topics: Li Chao Tree, Dynamic DP

PROBLEM:
Terdapat N pemancar nirkabel bernomor 1 sampai N dengan koordinat acak x[0], ..., x[N-1].
Energi dipancarkan dari pemancar 1 dengan biaya awal 0.
Untuk menghubungkan pemancar j ke pemancar i (j < i), rugi daya yang terjadi adalah:
`Cost(j, i) = (x[i] - x[j])^2 + R * abs(i - j)`.
Sederhanakan ekspansi kuadratik untuk menerapkan Li Chao Tree.

Tentukan TOTAL RUGI DAYA MINIMUM mencapai pemancar N!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan R.
Baris kedua berisi N bilangan bulat x[0], ..., x[N-1].

OUTPUT FORMAT:
Satu baris berisi rugi daya minimum mencapai pemancar N.

CONSTRAINTS:
1 <= N <= 100.000
0 <= R <= 10.000
-1.000.000 <= x[i] <= 1.000.000

SAMPLE INPUT 1:
3 5
0 10 2

SAMPLE OUTPUT 1:
14
(1 -> 3: (2 - 0)^2 + 5 * 2 = 4 + 10 = 14)

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
    ll r;
    if (!(cin >> n >> r)) return 0;

    // TODO: Selesaikan dengan Li Chao Tree

    return 0;
}
