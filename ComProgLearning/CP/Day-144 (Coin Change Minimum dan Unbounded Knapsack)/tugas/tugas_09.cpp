/*
============================================================
📋 TUGAS 09: Integer Break (Maksimal Hasil Kali Penjumlah)
============================================================
Source: LeetCode 343 / Math & DP Classic
Difficulty: Medium
Topics: Unbounded Knapsack (Multiplicative Maximization)

PROBLEM:
Diberikan bilangan bulat positif N (N >= 2).
Pecah N menjadi penjumlahan dari SETIDAKNYA DUA bilangan bulat positif:
N = k_1 + k_2 + ... + k_m (m >= 2, k_i >= 1).
Tentukan nilai maksimum dari hasil kali suku-suku penjumlahnya:
k_1 * k_2 * ... * k_m.

INPUT FORMAT:
Satu bilangan bulat N.

OUTPUT FORMAT:
Satu bilangan bulat: hasil kali maksimum yang bisa diperoleh.

CONSTRAINTS:
2 <= N <= 60

SAMPLE INPUT 1:
2

SAMPLE OUTPUT 1:
1
(Penjelasan: 2 = 1 + 1 -> 1 * 1 = 1)

SAMPLE INPUT 2:
10

SAMPLE OUTPUT 2:
36
(Penjelasan: 10 = 3 + 3 + 4 -> 3 * 3 * 4 = 36)

SAMPLE INPUT 3:
8

SAMPLE OUTPUT 3:
18
(Penjelasan: 8 = 3 + 3 + 2 -> 3 * 3 * 2 = 18)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // TODO: Selesaikan dengan Dynamic Programming
    // dp[i] = hasil kali maksimum untuk memecah i menjadi minimal dua bagian.
    // Untuk setiap i dari 2 sampai n:
    //   Untuk setiap j dari 1 sampai i - 1:
    //     dp[i] = max(dp[i], max((ll)j * (i - j), (ll)j * dp[i - j]))

    return 0;
}
