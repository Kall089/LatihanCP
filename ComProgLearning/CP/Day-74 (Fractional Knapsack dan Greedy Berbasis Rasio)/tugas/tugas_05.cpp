/*
============================================================
📋 TUGAS 05: Maximum Average Subarray II
============================================================
Source: LeetCode 644
Difficulty: Hard
Topics: Binary search on answer

PROBLEM:
Diberikan array n bilangan dan sebuah k. Cari RATA-RATA MAKSIMUM di antara semua
subarray kontigu yang panjangnya minimal k. Cetak dengan enam angka di belakang koma.

INPUT FORMAT:
Baris 1: n dan k
Baris 2: n bilangan

OUTPUT FORMAT:
Satu bilangan real dengan enam desimal

CONSTRAINTS:
1 <= k <= n <= 10^5, -10^4 <= a[i] <= 10^4

SAMPLE INPUT 1:
5 4
1 12 -5 -6 50

SAMPLE OUTPUT 1:
12.750000
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Trik a[i] - x dari Day 51. Setelah dikurangi x, pertanyaannya menjadi 'adakah subarray panjang >= k dengan jumlah >= 0' — dan itu bisa dijawab dengan prefix sum plus minimum berjalan.

    return 0;
}
