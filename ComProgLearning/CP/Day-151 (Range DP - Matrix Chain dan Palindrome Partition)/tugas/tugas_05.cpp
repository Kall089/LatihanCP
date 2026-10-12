/*
============================================================
📋 TUGAS 05: Perkalian Rantai Matriks dengan Batas Anggaran
============================================================
Source: Competitive Programming Variation
Difficulty: Medium
Topics: Range DP, Matrix Chain Multiplication, Threshold Check

PROBLEM:
Sebuah superkomputer diberi tugas mengalikan N buah matriks berantai A[1] * ... * A[N].
Matriks ke-i berukuran p[i-1] x p[i].
Komputer memiliki kuota anggaran komputasi maksimum sebesar B operasi perkalian skalar.
Tentukan apakah perkalian seluruh rantai matriks tersebut dapat diselesaikan
dengan biaya komputasi tidak melebihi anggaran B (biaya <= B).
Cetak "BISA" jika memungkinkan, atau "TIDAK BISA" jika melebihi anggaran.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan B.
Baris kedua berisi N + 1 bilangan bulat p[0], p[1], ..., p[N].

OUTPUT FORMAT:
Cetak "BISA" (tanpa tanda kutip) atau "TIDAK BISA".

CONSTRAINTS:
1 <= N <= 150
1 <= B <= 10^18
1 <= p[i] <= 50.000

SAMPLE INPUT 1:
3 5000
10 30 5 60

SAMPLE OUTPUT 1:
BISA
(Penjelasan: Biaya minimum adalah 4500 <= 5000)

SAMPLE INPUT 2:
3 4000
10 30 5 60

SAMPLE OUTPUT 2:
TIDAK BISA
(Penjelasan: Biaya minimum 4500 > 4000)
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
    ll b;
    if (!(cin >> n >> b)) return 0;

    vector<ll> p(n + 1);
    for (int i = 0; i <= n; i++) {
        cin >> p[i];
    }

    // TODO: Selesaikan dengan MCM Range DP
    // Hitung dp[0][n-1], bandingkan dengan b

    return 0;
}
