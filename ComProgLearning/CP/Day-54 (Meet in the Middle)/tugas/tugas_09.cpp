/*
============================================================
📋 TUGAS 09: Maximum Subsequence
============================================================
Source: CF 888E
Difficulty: Medium
Topics: MITM + modulo

PROBLEM:
Diberikan N bilangan dan modulus m, pilih subhimpunan tidak kosong yang
memaksimalkan (jumlah subhimpunan) mod m.

INPUT FORMAT:
- Baris pertama: N dan m
- Baris kedua: N bilangan

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 35
- 1 <= m <= 10^9

SAMPLE INPUT 1:
4 4
5 2 4 1

SAMPLE OUTPUT 1:
3
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Setelah membagi dua, jumlah masing-masing paruh diambil mod m. Untuk tiap s dari kanan, cari nilai kiri terbesar yang < m - s, DAN pertimbangkan juga nilai kiri terbesar secara keseluruhan (kasus totalnya melewati m).

    return 0;
}
