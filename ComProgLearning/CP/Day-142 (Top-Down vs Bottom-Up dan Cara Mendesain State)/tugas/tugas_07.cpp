/*
============================================================
📋 TUGAS 07: Jalur Robot dengan Tiket Tembus Rintangan
============================================================
Source: Codeforces / Original
Difficulty: Medium
Topics: Grid DP, Multi-Dimensional State

PROBLEM:
Sebuah grid berukuran R x C memiliki sel kosong ('.') dan rintangan ('#').
Robot mulai dari pojok kiri atas (0, 0) dan ingin menuju ke pojok kanan bawah (R-1, C-1).
Setiap langkah, robot hanya boleh bergerak 1 petak ke Kanan atau ke Bawah.
Robot tidak boleh menginjak rintangan ('#'), KECUALI jika robot menggunakan "Tiket Tembus Rintangan".
Robot memiliki tepat 1 tiket yang mengizinkannya menembus maksimal 1 petak rintangan '#'
sepanjang rute perjalanannya.
Hitung banyaknya jalur berbeda dari (0, 0) ke (R-1, C-1) modulo 1.000.000.007.
Asumsikan sel (0, 0) dan (R-1, C-1) selalu berupa sel kosong ('.').

INPUT FORMAT:
Baris pertama: R C
R baris berikutnya: string sepanjang C berisi '.' atau '#'

OUTPUT FORMAT:
Satu bilangan bulat: banyak jalur modulo 1.000.000.007.

CONSTRAINTS:
1 <= R, C <= 500

SAMPLE INPUT 1:
3 3
...
.#.
...

SAMPLE OUTPUT 1:
6
(Penjelasan: Seluruh 6 jalur legal dari (0,0) ke (2,2) bisa dilewati karena tiket mengizinkan menembus 1 sel '#' di tengah.)

SAMPLE INPUT 2:
3 3
.##
#..
...

SAMPLE OUTPUT 2:
2
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int r, c;
    if (!(cin >> r >> c)) return 0;

    vector<string> grid(r);
    for (int i = 0; i < r; i++) cin >> grid[i];

    // TODO: Definisikan dp[i][j][used]
    // used = 0 (belum menembus rintangan), used = 1 (sudah menembus 1 rintangan)
    // Basis: dp[0][0][0] = 1

    return 0;
}
