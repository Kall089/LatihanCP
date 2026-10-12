/*
============================================================
📋 TUGAS 12: Pengelompokan Data Sensor Cuaca
============================================================
Source: Sensor Clustering CHT
Difficulty: Hard
Topics: Li Chao Tree, Non-Monotone CHT

PROBLEM:
Terdapat N stasiun sensor cuaca dengan pembacaan suhu t[0], ..., t[N-1] (acak).
Sensor 1 memiliki biaya awal 0.
Biaya relai transmisi data dari sensor j ke sensor i (j < i) adalah:
`Cost(j, i) = (t[i] - t[j])^2 + C_trans`.

Tentukan TOTAL BIAYA TRANSMISI MINIMUM untuk mencapai sensor N!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan C_trans.
Baris kedua berisi N bilangan bulat t[0], ..., t[N-1].

OUTPUT FORMAT:
Satu baris berisi biaya transmisi minimum mencapai sensor N.

CONSTRAINTS:
1 <= N <= 200.000
0 <= C_trans <= 1.000.000.000
-1.000.000 <= t[i] <= 1.000.000

SAMPLE INPUT 1:
3 20
15 25 10

SAMPLE OUTPUT 1:
45
(1 -> 3: (10 - 15)^2 + 20 = 25 + 20 = 45)

SAMPLE INPUT 2:
1 50
12

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
    ll c_trans;
    if (!(cin >> n >> c_trans)) return 0;

    // TODO: Selesaikan dengan Li Chao Tree

    return 0;
}
