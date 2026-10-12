/*
============================================================
📋 TUGAS 15: Optimasi K Rantai Pasok Multi-Gudang
============================================================
Source: Multi-Warehouse Supply Chain K-Partition
Difficulty: Menantang
Topics: Aliens Trick, CHT

PROBLEM:
Terdapat N simpul distribusi rantai pasok dengan volume permintaan v[0], ..., v[N-1].
Manajemen membagi rantai pasok menjadi TEPAT K zona distribusi berurutan.
Biaya pengoperasian sebuah zona dari v[l] sampai v[r] adalah:
`Cost(l, r) = (sum_{t=l}^r v[t])^2 + C_hub`.
di mana C_hub adalah biaya fasilitas hub regional tetap.

Tentukan TOTAL BIAYA PENGOPERASIAN MINIMUM untuk seluruh K zona distribusi!

INPUT FORMAT:
Baris pertama berisi tiga bilangan bulat N, K, dan C_hub.
Baris kedua berisi N bilangan bulat non-negatif v[0], ..., v[N-1].

OUTPUT FORMAT:
Satu baris berisi total biaya minimum.

CONSTRAINTS:
1 <= K <= N <= 100.000
0 <= C_hub <= 1.000.000.000
0 <= v[i] <= 10.000

SAMPLE INPUT 1:
3 2 15
2 3 5

SAMPLE OUTPUT 1:
80
(Zona 1: [2, 3] -> 5^2 + 15 = 40. Zona 2: [5] -> 5^2 + 15 = 40. Total = 40 + 40 = 80)

SAMPLE INPUT 2:
1 1 50
10

SAMPLE OUTPUT 2:
150
(10^2 + 50 = 150)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    ll c_hub;
    if (!(cin >> n >> k >> c_hub)) return 0;

    // TODO: Selesaikan dengan Aliens Trick + CHT O(N log(MaxCost))

    return 0;
}
