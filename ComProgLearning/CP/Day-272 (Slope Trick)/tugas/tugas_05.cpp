/*
============================================================
📋 TUGAS 05: Perataan Suhu Ruangan Server Berkelanjutan
============================================================
Source: Continuous Thermal Smoothing
Difficulty: Hard
Topics: Slope Trick, 2-Heap, Lazy Tags

PROBLEM:
Terdapat N rak server berderet dengan suhu aktual T[0], ..., T[N-1].
Untuk efisiensi AC pendingin, gradien suhu antar rak bersebelahan dibatasi:
|T'[i] - T'[i-1]| <= K derajat Celsius.
Biaya pengaturan suhu adalah |T[i] - T'[i]|.

Tentukan TOTAL BIAYA PENYESUAIAN SUHU MINIMUM!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan K.
Baris kedua berisi N bilangan bulat T[0], ..., T[N-1].

OUTPUT FORMAT:
Satu baris berisi total biaya minimum.

CONSTRAINTS:
1 <= N <= 100.000
0 <= K <= 1.000.000.000
-1.000.000.000 <= T[i] <= 1.000.000.000

SAMPLE INPUT 1:
3 3
15 25 35

SAMPLE OUTPUT 1:
14
(T' = [22, 25, 28]: |15-22| + |25-25| + |35-28| = 7 + 0 + 7 = 14. Jarak antar rak: |25-22|=3<=3, |28-25|=3<=3)

SAMPLE INPUT 2:
1 5
25

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
    ll k;
    if (!(cin >> n >> k)) return 0;

    // TODO: Selesaikan dengan Slope Trick 2-Heap O(N log N)

    return 0;
}
