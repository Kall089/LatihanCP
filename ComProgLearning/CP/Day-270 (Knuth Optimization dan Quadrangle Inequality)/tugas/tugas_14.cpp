/*
============================================================
📋 TUGAS 14: Rantai Penggabungan DNA Sintetis
============================================================
Source: Synthetic DNA Oligomer Merging
Difficulty: Hard
Topics: Knuth Optimization, Range DP

PROBLEM:
Terdapat N fragmen rantai oligonukleotida DNA berurutan dari 1 sampai N dengan panjang pasangan basa b[0], ..., b[N-1].
Dua segmen DNA bersebelahan dapat diligasi dengan enzim ligase.
Biaya ligasi untuk menggabungkan segmen [l..k] dan [k+1..r] adalah:
`Cost(l, r) = sum_{t=l}^r b[t] + E_ligase`.

Tentukan TOTAL BIAYA ENZIM MINIMUM untuk menggabungkan seluruh fragmen DNA menjadi satu heliks panjang!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan E_ligase.
Baris kedua berisi N bilangan bulat non-negatif b[0], ..., b[N-1].

OUTPUT FORMAT:
Satu baris berisi total biaya minimum ligasi.

CONSTRAINTS:
1 <= N <= 2000
0 <= E_ligase <= 1.000.000.000
0 <= b[i] <= 1.000.000.000

SAMPLE INPUT 1:
3 7
15 25 10

SAMPLE OUTPUT 1:
99
(15+10? Tidak, berurutan: (15+25) = 40 + 7 = 47. Lalu (40)+10 = 50 + 7 = 57. Total = 47 + 57 = 104.
Atau (25+10) = 35 + 7 = 42. Lalu 15+(35) = 50 + 7 = 57. Total = 42 + 57 = 99.
Minimum adalah 99.)

SAMPLE INPUT 2:
1 100
50

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
    ll e_ligase;
    if (!(cin >> n >> e_ligase)) return 0;

    // TODO: Selesaikan dengan Knuth Optimization O(N^2)

    return 0;
}
