/*
============================================================
📋 TUGAS 07: Subset Sum Reachability dengan Bitset
============================================================
Source: Classic DP / Bitset Acceleration
Difficulty: Medium
Topics: Bitset DP, Subset Sum Reachability

PROBLEM:
Diberikan N buah bilangan bulat positif dan target bilangan T.
Tentukan apakah target T dapat dibentuk dari jumlahan subset bilangan-bilangan tersebut.
Jika bisa, cetak "YA", jika tidak bisa cetak "TIDAK".
Target T bisa mencapai 200.000, gunakan std::bitset untuk efisiensi waktu dan memori.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan T.
Baris kedua berisi N bilangan bulat a[0], ..., a[N-1].

OUTPUT FORMAT:
"YA" atau "TIDAK".

CONSTRAINTS:
1 <= N <= 1.000
1 <= T <= 200.000
1 <= a[i] <= 200.000

SAMPLE INPUT 1:
3 10
2 5 3

SAMPLE OUTPUT 1:
YA
(Subset {2, 5, 3} berjumlah 10)

SAMPLE INPUT 2:
3 4
2 5 3

SAMPLE OUTPUT 2:
TIDAK
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int MAX_T = 200005;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, t;
    if (!(cin >> n >> t)) return 0;

    // TODO: Selesaikan Subset Sum dengan bitset<MAX_T>

    return 0;
}
