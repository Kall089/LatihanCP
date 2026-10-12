/*
============================================================
📋 TUGAS 03: Biaya Seluruh Subrentang (Precomputed Range DP)
============================================================
Source: Subrange Knuth DP Queries
Difficulty: Medium
Topics: Knuth Optimization, Offline Precomputation

PROBLEM:
Terdapat N peti barang berjejer dari 1 sampai N dengan bobot a[0], ..., a[N-1].
Terdapat Q kueri. Setiap kueri terdiri dari sepasang indeks (L, R) (1-indexed, L <= R).
Untuk setiap kueri, tentukan BIAYA MINIMUM untuk menggabungkan subrentang peti dari L sampai R
(mengabaikan peti di luar interval [L, R]).

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan Q.
Baris kedua berisi N bilangan bulat non-negatif a[0], ..., a[N-1].
Q baris berikutnya masing-masing berisi dua bilangan bulat L dan R (1-indexed).

OUTPUT FORMAT:
Cetak Q baris, masing-masing berisi biaya minimum untuk rentang tersebut.

CONSTRAINTS:
1 <= N <= 2000
1 <= Q <= 100.000
0 <= a[i] <= 1.000.000.000
1 <= L <= R <= N

SAMPLE INPUT 1:
3 3
1 2 3
1 3
1 2
2 2

SAMPLE OUTPUT 1:
9
3
0

SAMPLE INPUT 2:
1 1
7
1 1

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

    int n, q;
    if (!(cin >> n >> q)) return 0;

    // TODO: Precomputasi seluruh dp[l][r] dengan Knuth Optimization O(N^2),
    // lalu jawab setiap kueri dalam O(1).

    return 0;
}
