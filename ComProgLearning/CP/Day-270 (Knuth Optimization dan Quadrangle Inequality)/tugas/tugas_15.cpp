/*
============================================================
📋 TUGAS 15: Penyatuan Jaringan Pipa Air Melingkar
============================================================
Source: Circular Water Pipeline Integration
Difficulty: Hard
Topics: Knuth Optimization, Circular Array Doubling

PROBLEM:
Terdapat N distrik saluran air yang membentuk cincin distribusi melingkar di kota metropolitan.
Distrik ke-i memiliki debit aliran harian w[i].
Pengelola air ingin mengonsolidasikan seluruh cincin menjadi satu sistem terpadu.
Penggabungan dua segmen pipa melingkar yang bersebelahan memerlukan biaya:
`Cost(l, r) = sum_{k=l}^r w[k] + C_valve`.

Tentukan TOTAL BIAYA VALVE MINIMUM untuk mengonsolidasikan seluruh cincin saluran air!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan C_valve.
Baris kedua berisi N bilangan bulat non-negatif w[0], ..., w[N-1] (mengikuti urutan lingkaran).

OUTPUT FORMAT:
Satu baris berisi total biaya minimum.

CONSTRAINTS:
1 <= N <= 1000
0 <= C_valve <= 1.000.000.000
0 <= w[i] <= 1.000.000.000

SAMPLE INPUT 1:
3 10
4 2 5

SAMPLE OUTPUT 1:
37
(4+2: 6+10 = 16. Lalu (6)+5: 11+10 = 21. Total = 16 + 21 = 37)

SAMPLE INPUT 2:
1 50
10

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
    ll c_valve;
    if (!(cin >> n >> c_valve)) return 0;

    // TODO: Selesaikan dengan Circular Knuth Optimization O(N^2)

    return 0;
}
