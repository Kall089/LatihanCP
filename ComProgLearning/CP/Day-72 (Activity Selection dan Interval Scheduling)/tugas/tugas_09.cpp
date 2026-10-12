/*
============================================================
📋 TUGAS 09: Menembak Balon
============================================================
Source: LeetCode 452 - Minimum Arrows to Burst Balloons
Difficulty: Medium
Topics: Titik penusuk minimum

PROBLEM:
Ada n balon; balon ke-i menempati rentang horizontal [l, r]. Sebuah panah yang
ditembakkan pada posisi x akan memecahkan SEMUA balon dengan l <= x <= r.
Cari jumlah panah MINIMUM untuk memecahkan seluruh balon.

INPUT FORMAT:
Baris 1: n
n baris berikutnya: l dan r

OUTPUT FORMAT:
Satu bilangan: jumlah panah minimum

CONSTRAINTS:
1 <= n <= 10^5, -2^31 <= l <= r <= 2^31 - 1

SAMPLE INPUT 1:
4
10 16
2 8
1 6
7 12

SAMPLE OUTPUT 1:
2
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Ini DUAL dari activity selection: jumlah panah minimum sama dengan jumlah interval saling lepas maksimum. Buktikan kesamaan itu, lalu kode-nya hampir identik dengan Exercise 1.

    return 0;
}
