/*
============================================================
📋 TUGAS 05: Rekonstruksi Barang
============================================================
Source: Original
Difficulty: Easy
Topics: telusuri mundur

PROBLEM:
Selain nilai maksimum, cetak indeks barang mana saja yang dipilih.

INPUT FORMAT:
- Baris pertama: N dan W
- N baris: w dan v

OUTPUT FORMAT:
- Baris pertama: nilai maksimum
- Baris kedua: indeks (1-based, menaik)

CONSTRAINTS:
- 1 <= N <= 500
- 1 <= W <= 2000

SAMPLE INPUT 1:
3 5
3 3
2 4
4 2

SAMPLE OUTPUT 1:
7
1 2
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Versi 1D menimpa riwayatnya - butuh tabel 2D. dp[i][c] != dp[i-1][c] berarti barang i diambil.

    return 0;
}
