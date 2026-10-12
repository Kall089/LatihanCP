/*
============================================================
📋 TUGAS 08: Rekonstruksi Barisan Sensor Topografi Terurut Tegas
============================================================
Source: Topographic Sensor Monotonic Reconstruction
Difficulty: Hard
Topics: Slope Trick, Index Transformation

PROBLEM:
N sensor kontur ketinggian menghasilkan pembacaan y[0], ..., y[N-1].
Untuk merekonstruksi model lereng terjal, ketinggian baru y'[i] harus terurut tegas menaik:
y'[0] < y'[1] < ... < y'[N-1].
Biaya kalibrasi sensor adalah |y[i] - y'[i]|.

Tentukan TOTAL BIAYA KALIBRASI MINIMUM!

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat y[0], ..., y[N-1].

OUTPUT FORMAT:
Satu baris berisi total biaya minimum.

CONSTRAINTS:
1 <= N <= 200.000
-1.000.000.000 <= y[i] <= 1.000.000.000

SAMPLE INPUT 1:
3
3 2 1

SAMPLE OUTPUT 1:
4
(y' = [0, 1, 2]: |3-0| + |2-1| + |1-2| = 3 + 1 + 1 = 5?
Tunggu: y''[i] = y[i] - i -> [3-0=3, 2-1=1, 1-2=-1].
Median dari [3, 1, -1] adalah 1:
|3-1| + |1-1| + |-1-1| = 2 + 0 + 2 = 4!
y' = [1, 2, 3]: |3-1| + |2-2| + |1-3| = 2 + 0 + 2 = 4!)

SAMPLE INPUT 2:
3
1 2 3

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

    // TODO: Selesaikan dengan Slope Trick O(N log N)

    return 0;
}
