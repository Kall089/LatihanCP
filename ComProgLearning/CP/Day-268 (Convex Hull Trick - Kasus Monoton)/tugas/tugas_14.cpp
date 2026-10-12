/*
============================================================
📋 TUGAS 14: Penataan Rak Buku dengan Biaya Ruang Kosong
============================================================
Source: Classic CHT Optimization
Difficulty: Hard
Topics: Convex Hull Trick, Monotone Deque

PROBLEM:
Terdapat N buku dengan tebal t[0], ..., t[N-1].
Buku harus ditata ke dalam rak-rak berurutan. Setiap rak memiliki lebar standar W.
Jika rak memuat buku dari j+1 sampai i, total tebal buku adalah S = sum_{k=j+1}^i t[k].
Biaya ruang kosong rak adalah:
`Cost(j+1, i) = Base + (W - S)^2`.

Tentukan TOTAL BIAYA MINIMUM untuk menata seluruh N buku ke dalam rak!

INPUT FORMAT:
Baris pertama berisi tiga bilangan bulat N, W, dan Base.
Baris kedua berisi N bilangan bulat positif t[0], ..., t[N-1].

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: biaya minimum.

CONSTRAINTS:
1 <= N <= 100.000
1 <= W <= 1.000.000
0 <= Base <= 1.000.000.000
1 <= t[i] <= 10.000

SAMPLE INPUT 1:
3 10 5
3 4 5

SAMPLE OUTPUT 1:
23

SAMPLE INPUT 2:
1 5 10
5

SAMPLE OUTPUT 2:
10
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll w, base_cost;
    if (!(cin >> n >> w >> base_cost)) return 0;

    // TODO: Selesaikan dengan CHT Deque

    return 0;
}
