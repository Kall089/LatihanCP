/*
============================================================
📋 TUGAS 08: Optimasi Biaya Pipeline Gas dengan Elevasi
============================================================
Source: Pipeline Routing CHT
Difficulty: Hard
Topics: Li Chao Tree, Non-Monotone Queries

PROBLEM:
Pipa gas dipasang melalui N stasiun pompa dari 1 sampai N dengan elevasi kontur h[0], ..., h[N-1] (acak).
Stasiun 1 telah siap dengan biaya awal 0.
Biaya menyambung stasiun j ke stasiun i (j < i) adalah:
`Cost(j, i) = (h[i] - h[j])^2 + C + P * abs(h[i] - h[j])`.
Jika P = 0, rumus tereduksi menjadi CHT kuadratik standar.

Selesaikan kasus dengan P = 0 untuk N stasiun elevasi acak!
`Cost(j, i) = (h[i] - h[j])^2 + C`.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan C.
Baris kedua berisi N bilangan bulat h[0], ..., h[N-1].

OUTPUT FORMAT:
Satu baris berisi biaya minimum mencapai stasiun N.

CONSTRAINTS:
1 <= N <= 200.000
0 <= C <= 1.000.000.000
-1.000.000 <= h[i] <= 1.000.000

SAMPLE INPUT 1:
3 25
10 30 15

SAMPLE OUTPUT 1:
50
(1 -> 3 langsung: (15 - 10)^2 + 25 = 25 + 25 = 50)

SAMPLE INPUT 2:
1 10
5

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
    ll c;
    if (!(cin >> n >> c)) return 0;

    // TODO: Selesaikan dengan Li Chao Tree

    return 0;
}
