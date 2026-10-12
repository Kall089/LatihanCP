/*
============================================================
📋 TUGAS 03: Jalur Grid dengan Rintangan 1D DP
============================================================
Source: Classic Grid DP / Unique Paths II
Difficulty: Medium
Topics: Grid DP, 1D Array In-Place Update, Modulo Arithmetic

PROBLEM:
Diberikan sebuah grid berukuran N x M yang terdiri dari karakter:
- `.` : sel kosong yang dapat dilalui.
- `#` : sel rintangan / dinding yang tidak dapat dilalui.
Perjalanan dimulai dari sel (0, 0) menuju ke sel (N-1, M-1).
Dari setiap sel, kamu hanya boleh bergerak ke Kanan atau ke Bawah.
Hitung BANYAK JALUR BERBEDA yang dapat ditempuh, modulo 1.000.000.007!
Gunakan satu baris array DP berukuran O(M).
Jika sel saat ini berisi `#`, nilai pada array harus di-reset menjadi 0.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan M.
N baris berikutnya masing-masing berisi string sepanjang M karakter.

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: banyak jalur modulo 1.000.000.007.

CONSTRAINTS:
1 <= N, M <= 1.000
Karakter hanya `.` dan `#`
Memori tambahan O(M)

SAMPLE INPUT 1:
2 3
...
.#.

SAMPLE OUTPUT 1:
1

SAMPLE INPUT 2:
1 1
#

SAMPLE OUTPUT 2:
0
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // TODO: Selesaikan Grid Unique Paths dengan 1 baris DP modulo 10^9+7

    return 0;
}
