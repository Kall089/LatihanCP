/*
============================================================
📋 TUGAS 03: Longest Flight Route
============================================================
Source: CSES 1680
Difficulty: Medium
Topics: terpanjang + rekonstruksi

PROBLEM:
DAG N kota, M penerbangan. Cari rute 1 -> N yang melewati kota SEBANYAK
mungkin. Cetak banyak kota lalu rutenya, atau IMPOSSIBLE.

INPUT FORMAT:
- Baris 1: N M
- M baris: a b

OUTPUT FORMAT:
- Baris 1: banyak kota
- Baris 2: urutan kota

CONSTRAINTS:
- 2 <= N <= 10^5, 1 <= M <= 2*10^5

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
5 5                    4
1 2                    1 3 4 5
2 5
1 3
3 4
4 5

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
2 1                    2
1 2                    1 2

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
4 2                    IMPOSSIBLE
1 2
3 4
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
}
