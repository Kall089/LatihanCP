/*
============================================================
📋 TUGAS 15: Rekonstruksi Kurung MCM Lengkap
============================================================
Source: CLRS / Classic Matrix Chain Parenthesization
Difficulty: Hard
Topics: Range DP, Split Table Backtracking, Expression Tree

PROBLEM:
Diberikan N buah matriks dengan rantai dimensi p[0], p[1], ..., p[N].
Matriks ke-i berukuran p[i-1] x p[i].
Cari:
1. Di baris pertama: biaya perkalian skalar minimum.
2. Di baris kedua: ekspresi tanda kurung lengkap dalam format `(A1 x (A2 x A3))`.
   Jika N = 1, cukup cetak `A1`.
   Jika ada seri, pilih titik pecah k terkecil.

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N + 1 bilangan bulat p[0], ..., p[N].

OUTPUT FORMAT:
Baris pertama: biaya minimum.
Baris kedua: string ekspresi tanda kurung.

CONSTRAINTS:
1 <= N <= 100
1 <= p[i] <= 10.000

SAMPLE INPUT 1:
3
10 30 5 60

SAMPLE OUTPUT 1:
4500
((A1 x A2) x A3)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<ll> p(n + 1);
    for (int i = 0; i <= n; i++) {
        cin >> p[i];
    }

    // TODO: Selesaikan MCM dan rekonstruksi kurung

    return 0;
}
