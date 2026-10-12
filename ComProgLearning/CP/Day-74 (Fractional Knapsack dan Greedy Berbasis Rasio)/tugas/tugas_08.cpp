/*
============================================================
📋 TUGAS 08: Meet in the Middle Knapsack
============================================================
Source: Latihan mandiri (lanjutan Day 54)
Difficulty: Hard
Topics: MITM

PROBLEM:
Ada n barang dengan berat w[i] dan nilai v[i], kapasitas W.
Batasan n kecil tetapi W dan nilai keduanya besar.

INPUT FORMAT:
Baris 1: n dan W
n baris berikutnya: w[i] dan v[i]

OUTPUT FORMAT:
Satu bilangan: nilai maksimum

CONSTRAINTS:
1 <= n <= 40, 1 <= W <= 10^18, 1 <= w[i] <= 10^18, 1 <= v[i] <= 10^9

SAMPLE INPUT 1:
4 11
6 7
5 5
5 5
1 1

SAMPLE OUTPUT 1:
12
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // n <= 40 dengan kedua dimensi besar adalah tanda meet in the middle (Day 54). Bagi barang jadi dua bagian, enumerasi 2^20 tiap bagian, lalu gabungkan dengan pengurutan plus prefix maximum.

    return 0;
}
