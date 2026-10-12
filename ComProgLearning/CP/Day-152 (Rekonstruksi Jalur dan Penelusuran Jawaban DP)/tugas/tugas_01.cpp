/*
============================================================
📋 TUGAS 01: Rute Grid dengan D Lebih Dahulu
============================================================
Source: Classic Grid DP / Lexicographical Path
Difficulty: Medium
Topics: Grid DP, Suffix DP, Lexicographical Tie-Breaker

PROBLEM:
Diberikan grid berukuran N x M dengan biaya sel non-negatif.
Perjalanan dimulai dari sel (0, 0) dan berakhir di (N-1, M-1).
Dari setiap sel hanya boleh melangkah 'D' (Bawah) atau 'R' (Kanan).
Biaya perjalanan adalah jumlah bobot seluruh sel yang dilewati termasuk awal dan akhir.
Tentukan biaya minimum dan string langkah terpendek yang leksikografis terkecil dengan aturan 'D' < 'R'.
Khusus jika N = 1 dan M = 1, cetak teks `EMPTY` pada baris kedua.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan M.
N baris berikutnya masing-masing berisi M bilangan bulat non-negatif.

OUTPUT FORMAT:
Baris pertama: biaya minimum.
Baris kedua: string gerakan ('D' dan 'R') atau `EMPTY`.

CONSTRAINTS:
1 <= N, M <= 100
0 <= biaya <= 10^9

SAMPLE INPUT 1:
2 2
1 1
1 1

SAMPLE OUTPUT 1:
3
DR

SAMPLE INPUT 2:
1 1
7

SAMPLE OUTPUT 2:
7
EMPTY
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<ll>> grid(n, vector<ll>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    // TODO: Selesaikan dengan Suffix DP pada grid dan rekonstruksi maju ('D' < 'R')

    return 0;
}
