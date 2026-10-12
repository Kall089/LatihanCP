/*
============================================================
📋 TUGAS 13: Penjadwalan Waktu Pemrosesan Pabrik dengan Batas Latensi
============================================================
Source: Factory Processing Time Scheduling
Difficulty: Hard
Topics: Slope Trick, Index Transformation

PROBLEM:
N batch produk dijadwalkan diproses pada waktu awal s[0], ..., s[N-1] (menit).
Untuk mencegah kemacetan mesin, interval waktu mulai antara dua batch berurutan harus
setidaknya M menit:
s'[i] - s'[i-1] >= M.
Biaya rescheduling adalah |s[i] - s'[i]|.

Tentukan TOTAL BIAYA RESCHEDULING MINIMUM!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan M.
Baris kedua berisi N bilangan bulat s[0], ..., s[N-1].

OUTPUT FORMAT:
Satu baris berisi total biaya minimum.

CONSTRAINTS:
1 <= N <= 200.000
1 <= M <= 10.000
0 <= s[i] <= 1.000.000.000

SAMPLE INPUT 1:
3 5
0 2 4

SAMPLE OUTPUT 1:
6
(s''[i] = s[i] - 5*i -> [0, 2-5=-3, 4-10=-6].
 Median dari [0, -3, -6] adalah -3.
 Biaya: |0 - (-3)| + |-3 - (-3)| + |-6 - (-3)| = 3 + 0 + 3 = 6.
 Jadwal baru: s' = [-3, 2, 7] -> biaya = 3 + 0 + 3 = 6.)

SAMPLE INPUT 2:
2 10
0 20

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

    // TODO: Selesaikan dengan Slope Trick O(N log N)

    return 0;
}
