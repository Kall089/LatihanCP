/*
============================================================
📋 TUGAS 08: Jumlah Langkah Tangga K-Langkah O(K) Space
============================================================
Source: LeetCode 70 Variation / Sliding Window DP
Difficulty: Medium
Topics: Sliding Window DP, Queue / Circular Buffer, Modulo 10^9+7

PROBLEM:
Kamu ingin menaiki tangga dengan N anak tangga (dari 0 menuju N).
Dari anak tangga saat ini, kamu dapat melangkah 1, 2, ..., hingga paling banyak K anak tangga sekaligus.
Hitung total banyak cara berbeda untuk mencapai puncak tangga ke-N, modulo 1.000.000.007!
Nilai N dapat mencapai 1.000.000, sehingga array DP ukuran N akan menghabiskan memori.
Gunakan memori tambahan O(K) dengan teknik sliding window sum.

INPUT FORMAT:
Satu baris berisi dua bilangan bulat N dan K.

OUTPUT FORMAT:
Satu baris berisi banyak cara modulo 1.000.000.007.

CONSTRAINTS:
1 <= N <= 1.000.000
1 <= K <= 100
Memori tambahan O(K)

SAMPLE INPUT 1:
3 2
SAMPLE OUTPUT 1:
3
(Cara: 1+1+1, 1+2, 2+1)

SAMPLE INPUT 2:
4 3
SAMPLE OUTPUT 2:
7
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    // TODO: Selesaikan Climbing Stairs K-langkah dengan memori O(K) dan sliding sum

    return 0;
}
