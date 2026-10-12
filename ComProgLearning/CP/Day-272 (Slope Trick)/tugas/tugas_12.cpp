/*
============================================================
📋 TUGAS 12: Perataan Sudut Kemiringan Robot Lengan Manufaktur
============================================================
Source: Robotic Arm Joint Angle Trajectory
Difficulty: Hard
Topics: Slope Trick, 2-Heap, Lazy Tags

PROBLEM:
Robot industri memiliki lintasan sudut sendi theta[0], ..., theta[N-1].
Untuk mencegah getaran mekanis, perbedaan sudut antara dua titik waktu berurutan dibatasi:
|theta'[i] - theta'[i-1]| <= W derajat.
Biaya deviasi adalah |theta[i] - theta'[i]|.

Tentukan TOTAL BIAYA DEVIASI MINIMUM!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan W.
Baris kedua berisi N bilangan bulat theta[0], ..., theta[N-1].

OUTPUT FORMAT:
Satu baris berisi total biaya minimum.

CONSTRAINTS:
1 <= N <= 100.000
0 <= W <= 1.000.000.000
-1.000.000.000 <= theta[i] <= 1.000.000.000

SAMPLE INPUT 1:
3 2
0 10 20

SAMPLE OUTPUT 1:
16
(Posisi optimal theta' = [8, 10, 12]. Selisih: |10-8| = 2 <= 2, |12-10| = 2 <= 2.
 Total biaya = |0 - 8| + |10 - 10| + |20 - 12| = 8 + 0 + 8 = 16.)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll w;
    if (!(cin >> n >> w)) return 0;

    // TODO: Selesaikan dengan Slope Trick 2-Heap O(N log N)

    return 0;
}
