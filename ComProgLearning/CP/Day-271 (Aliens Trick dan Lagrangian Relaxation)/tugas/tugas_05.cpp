/*
============================================================
📋 TUGAS 05: Penempatan K Relai Transmisi Energi Nirkabel
============================================================
Source: Wireless Energy Relay Placement
Difficulty: Hard
Topics: Aliens Trick, CHT

PROBLEM:
Jalur transmisi sepanjang L meter memiliki N titik pemancar: 0 = d[0] < d[1] < ... < d[N-1] = L.
Kita ingin memilih TEPAT K lompatan dari d[0] ke d[N-1].
Setiap kali energi ditransmisikan dari d[j] ke d[i], terbuang energi sebanding dengan
`Loss = (d[i] - d[j])^2 + E_hop`.

Tentukan TOTAL ENERGI TERBUANG MINIMUM dengan tepat K lompatan!

INPUT FORMAT:
Baris pertama berisi tiga bilangan bulat N, K, dan E_hop.
Baris kedua berisi N bilangan bulat d[0], ..., d[N-1] (terurut menaik, d[0] = 0).

OUTPUT FORMAT:
Satu baris berisi total rugi energi minimum.

CONSTRAINTS:
2 <= N <= 100.000
1 <= K <= N - 1
0 <= E_hop <= 1.000.000.000
0 = d[0] < ... < d[N-1] <= 1.000.000.000

SAMPLE INPUT 1:
4 2 10
0 2 5 10

SAMPLE OUTPUT 1:
70
(Distorsi jarak = 50, ditambah 2 * 10 = 20 -> total = 70)

SAMPLE INPUT 2:
4 1 50
0 2 5 10

SAMPLE OUTPUT 2:
150
(100 + 50 = 150)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    ll e_hop;
    if (!(cin >> n >> k >> e_hop)) return 0;

    // TODO: Selesaikan dengan Aliens Trick + CHT O(N log(MaxLoss))

    return 0;
}
