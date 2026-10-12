/*
============================================================
📋 TUGAS 12: Pengelompokan Data Sensor Suhu
============================================================
Source: Sensor Reading Clustered Partition
Difficulty: Hard
Topics: Aliens Trick, CHT

PROBLEM:
Terdapat N pembacaan data sensor suhu berurutan s[0], ..., s[N-1].
Data harus dikelompokkan ke dalam TEPAT K kluster berurutan.
Biaya kompresi setiap kluster adalah kuadrat dari total deviasi pembacaan di dalamnya:
`Biaya(Kluster) = (sum_{x in Kluster} s[x])^2`.

Tentukan TOTAL BIAYA KOMPRESI MINIMUM untuk seluruh K kluster!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan K.
Baris kedua berisi N bilangan bulat non-negatif s[0], ..., s[N-1].

OUTPUT FORMAT:
Satu baris berisi total biaya minimum.

CONSTRAINTS:
1 <= K <= N <= 100.000
0 <= s[i] <= 10.000

SAMPLE INPUT 1:
4 2
2 2 3 3

SAMPLE OUTPUT 1:
52
(Kluster 1: [2, 2] -> 4^2 = 16. Kluster 2: [3, 3] -> 6^2 = 36. Total = 52)

SAMPLE INPUT 2:
1 1
100

SAMPLE OUTPUT 2:
10000
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

    // TODO: Selesaikan dengan Aliens Trick + CHT O(N log(MaxCost))

    return 0;
}
