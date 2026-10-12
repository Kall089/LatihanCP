/*
============================================================
📋 TUGAS 11: Interval Maksimum dengan Batas Total
============================================================
Source: Latihan mandiri
Difficulty: Hard
Topics: Interval + DP dua dimensi

PROBLEM:
Diberikan n interval [l, r] dan sebuah bilangan T. Pilih sebanyak mungkin interval
yang saling lepas dengan syarat TOTAL PANJANG interval terpilih tidak melebihi T.
Panjang interval [l, r] didefinisikan sebagai r - l.

INPUT FORMAT:
Baris 1: n dan T
n baris berikutnya: l dan r

OUTPUT FORMAT:
Satu bilangan: jumlah interval maksimum

CONSTRAINTS:
1 <= n <= 2000, 1 <= T <= 5000, 1 <= l < r <= 10^9

SAMPLE INPUT 1:
3 10
1 5
6 9
2 12

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
    // Batasan T <= 5000 adalah petunjuk keras. Greedy tidak cukup karena ada dua besaran yang harus diseimbangkan. Gabungkan pola weighted interval scheduling dengan dimensi kapasitas seperti pada knapsack (Day 145).

    return 0;
}
