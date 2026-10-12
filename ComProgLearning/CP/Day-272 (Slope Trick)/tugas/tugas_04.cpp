/*
============================================================
📋 TUGAS 04: Penyelarasan Posisi Konvoi Drone dengan Batas Deviasi
============================================================
Source: Drone Fleet Position Alignment
Difficulty: Hard
Topics: Slope Trick, 2-Heap, Lazy Tags

PROBLEM:
Formasi N drone memiliki koordinat awal x[0], ..., x[N-1] pada garis lintasan.
Untuk menjaga keamanan formasi, jarak antar dua drone berurutan tidak boleh melebihi D meter:
|x'[i] - x'[i-1]| <= D untuk setiap i = 1, ..., N-1.
Biaya reposisi adalah |x[i] - x'[i]|.

Tentukan TOTAL BIAYA REPOSISI MINIMUM!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan D.
Baris kedua berisi N bilangan bulat x[0], ..., x[N-1].

OUTPUT FORMAT:
Satu baris berisi total biaya minimum.

CONSTRAINTS:
1 <= N <= 100.000
0 <= D <= 1.000.000.000
-1.000.000.000 <= x[i] <= 1.000.000.000

SAMPLE INPUT 1:
3 4
0 10 20

SAMPLE OUTPUT 1:
12
(x' = [6, 10, 14]: |0-6| + |10-10| + |20-14| = 6 + 0 + 6 = 12.
 Jarak: |10-6| = 4 <= 4, |14-10| = 4 <= 4)

SAMPLE INPUT 2:
2 10
0 5

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
    ll d;
    if (!(cin >> n >> d)) return 0;

    // TODO: Selesaikan dengan Slope Trick 2-Heap O(N log N)

    return 0;
}
