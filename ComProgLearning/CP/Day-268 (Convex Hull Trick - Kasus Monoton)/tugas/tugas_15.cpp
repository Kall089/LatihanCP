/*
============================================================
📋 TUGAS 15: Penumpukan Kontainer Pelabuhan dengan Biaya Crane
============================================================
Source: Classic CHT DP
Difficulty: Menantang
Topics: Convex Hull Trick, Monotone Deque

PROBLEM:
Terdapat N kontainer dengan berat w[0], ..., w[N-1] dan tinggi h[0] <= h[1] <= ... <= h[N-1] (terurut menaik).
Kontainer dapat ditumpuk menjadi beberapa tumpukan.
Setiap tumpukan yang mencakup kontainer j+1 sampai i memerlukan biaya crane sebesar:
`Cost(j+1, i) = C_crane + (h[i] - h[j+1])^2 + (sum_{k=j+1}^i w[k])`.

Tentukan TOTAL BIAYA MINIMUM untuk menumpuk seluruh N kontainer!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan C_crane.
Baris kedua berisi N bilangan bulat berat w[0], ..., w[N-1].
Baris ketiga berisi N bilangan bulat tinggi h[0], ..., h[N-1] (terurut menaik).

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: total biaya minimum.

CONSTRAINTS:
1 <= N <= 200.000
1 <= C_crane <= 1.000.000.000
1 <= w[i] <= 10.000
0 <= h[i] <= 1.000.000

SAMPLE INPUT 1:
3 20
2 3 4
1 3 6

SAMPLE OUTPUT 1:
37

SAMPLE INPUT 2:
1 10
5
2

SAMPLE OUTPUT 2:
15
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll c_crane;
    if (!(cin >> n >> c_crane)) return 0;

    // TODO: Selesaikan dengan CHT Deque

    return 0;
}
