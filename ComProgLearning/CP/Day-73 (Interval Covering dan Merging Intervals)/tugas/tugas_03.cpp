/*
============================================================
📋 TUGAS 03: Minimum Arrows to Burst Balloons
============================================================
Source: LeetCode 452
Difficulty: Medium
Topics: Titik penusuk minimum

PROBLEM:
Ada n balon; balon ke-i menempati rentang [l, r]. Panah yang ditembakkan pada posisi
x memecahkan semua balon dengan l <= x <= r.
Cari jumlah panah minimum untuk memecahkan seluruh balon.

INPUT FORMAT:
Baris 1: n
n baris berikutnya: l dan r

OUTPUT FORMAT:
Satu bilangan: jumlah panah minimum

CONSTRAINTS:
1 <= n <= 10^5, -10^9 <= l <= r <= 10^9

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
    // Ini DUAL dari activity selection. Urut menurut r dan tembak tepat di r. Buktikan dulu kenapa angkanya sama dengan jumlah interval saling lepas maksimum.

    return 0;
}
