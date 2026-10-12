/*
============================================================
📋 TUGAS 09: Pemasangan Tiang Kabel Fiber dengan Batas Regangan
============================================================
Source: Fiber Pole Spacing with Tension Limits
Difficulty: Hard
Topics: Slope Trick, 2-Heap, Lazy Tags

PROBLEM:
Terdapat N tiang kabel fiber dengan posisi garis lurus p[0], ..., p[N-1].
Untuk mencegah kabel putus karena tarikan berlebih atau terlalu kendur, jarak antar tiang dibatasi:
|p'[i] - p'[i-1]| <= S meter.
Biaya pemindahan tiang adalah |p[i] - p'[i]|.

Tentukan TOTAL BIAYA PEMINDAHAN MINIMUM!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan S.
Baris kedua berisi N bilangan bulat p[0], ..., p[N-1].

OUTPUT FORMAT:
Satu baris berisi total biaya minimum.

CONSTRAINTS:
1 <= N <= 100.000
0 <= S <= 1.000.000.000
-1.000.000.000 <= p[i] <= 1.000.000.000

SAMPLE INPUT 1:
3 5
0 20 40

SAMPLE OUTPUT 1:
30
(p' = [10, 15, 20]: |0-10| + |20-15| + |40-20| = 10 + 5 + 20 = 35?
Atau p' = [10, 20, 25]?
Evaluasi dengan solve_bounded_distance(3, 5, {0, 20, 40}):
tag_L: 0, -5, -10.
tag_R: 0, +5, +10.
L: [0], R: [0]
i=1 (20): L.top()=0-5=-5, R.top()=0+5=5. cur=20 > 5 -> min_val += 20 - 5 = 15.
R.pop(), R.push(20-5=15), R.push(15), L.push(5 - (-5) = 10).
i=2 (40): tag_L = -10, tag_R = 10.
r_top = 15 + 10 = 25. cur = 40 > 25 -> min_val += 40 - 25 = 15.
Total min_val = 15 + 15 = 30!
Hasil optimal adalah 30!)

SAMPLE INPUT 2:
2 10
5 12

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
    ll s;
    if (!(cin >> n >> s)) return 0;

    // TODO: Selesaikan dengan Slope Trick 2-Heap O(N log N)

    return 0;
}
