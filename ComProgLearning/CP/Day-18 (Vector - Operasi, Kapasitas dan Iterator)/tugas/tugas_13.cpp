/*
============================================================
📋 TUGAS 13: Interval Scheduling (Sort Pairs)
============================================================
Source: Classic Greedy / Codeforces-style
Difficulty: Hard
Topics: vector, pair, sort, greedy

PROBLEM:
Ada N kegiatan, masing-masing punya waktu mulai (start) dan waktu
selesai (end). Cari jumlah MAKSIMUM kegiatan yang bisa diikuti
tanpa ada yang overlap (satu kegiatan harus selesai sebelum yang
lain dimulai, boleh end_i == start_j).

INPUT:
- Baris pertama: integer N
- N baris berikutnya: dua integer start_i dan end_i

OUTPUT:
- Satu integer: jumlah maksimum kegiatan non-overlap

CONSTRAINTS:
- 1 ≤ N ≤ 200,000
- 0 ≤ start_i < end_i ≤ 1,000,000,000

SAMPLE INPUT:
5
1 3
2 5
4 7
6 8
5 9

SAMPLE OUTPUT:
3

NOTE: Pilih kegiatan [1,3], [4,7], [6,8] → total 3 kegiatan

SAMPLE INPUT 2:
3
1 10
2 3
4 5

SAMPLE OUTPUT 2:
2
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Hint: Sort by END time, lalu greedy pilih yang end-nya paling awal

    return 0;
}
