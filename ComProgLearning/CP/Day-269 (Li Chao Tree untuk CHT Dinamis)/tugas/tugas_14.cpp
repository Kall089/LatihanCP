/*
============================================================
📋 TUGAS 14: Penentuan Rute Drone Lintas Ketinggian
============================================================
Source: Drone Pathfinding CHT
Difficulty: Hard
Topics: Li Chao Tree, Non-Monotone Coordinates

PROBLEM:
Drone pengirim paket terbang melintasi N waypoint dari 1 sampai N dengan ketinggian alt[0], ..., alt[N-1] (acak).
Waypoint 1 sudah dicapai dengan energi awal 0.
Untuk beralih dari waypoint j ke i (j < i), konsumsi baterai memenuhi:
`Cost(j, i) = (alt[i] - alt[j])^2 + E_hop`.

Tentukan TOTAL ENERGI MINIMUM untuk mencapai waypoint N!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan E_hop.
Baris kedua berisi N bilangan bulat alt[0], ..., alt[N-1].

OUTPUT FORMAT:
Satu baris berisi konsumsi energi minimum mencapai waypoint N.

CONSTRAINTS:
1 <= N <= 200.000
0 <= E_hop <= 1.000.000.000
-1.000.000 <= alt[i] <= 1.000.000

SAMPLE INPUT 1:
3 50
500 100 520

SAMPLE OUTPUT 1:
450
(1 -> 3: (520 - 500)^2 + 50 = 400 + 50 = 450)

SAMPLE INPUT 2:
1 10
100

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
    ll e_hop;
    if (!(cin >> n >> e_hop)) return 0;

    // TODO: Selesaikan dengan Li Chao Tree

    return 0;
}
