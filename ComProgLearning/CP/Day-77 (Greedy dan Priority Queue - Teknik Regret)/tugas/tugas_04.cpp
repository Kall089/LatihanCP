/*
============================================================
📋 TUGAS 04: IPO
============================================================
Source: LeetCode 502
Difficulty: Hard
Topics: Dua struktur

PROBLEM:
Modal awal C, boleh menjalankan paling banyak K proyek. Proyek ke-i butuh modal
minimal m[i] dan menambah modalmu sebesar p[i].
Cari modal akhir maksimum.

INPUT FORMAT:
Baris 1: n, K, dan C
n baris berikutnya: m[i] dan p[i]

OUTPUT FORMAT:
Satu bilangan: modal akhir maksimum

CONSTRAINTS:
1 <= n <= 10^5, 1 <= K <= 10^5, 0 <= C, m[i], p[i] <= 10^9

SAMPLE INPUT 1:
3 2 0
0 1
1 2
1 3

SAMPLE OUTPUT 1:
4
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Array terurut untuk yang belum terjangkau, max-heap untuk yang sudah. Penunjuk tidak pernah mundur karena modal hanya membesar.

    return 0;
}
