/*
============================================================
📋 TUGAS 01: Minimum Bilangan Kuadrat (Perfect Squares)
============================================================
Source: LeetCode 279 / Classic DP
Difficulty: Easy
Topics: Coin Change Minimum

PROBLEM:
Diberikan sebuah bilangan bulat positif N.
Tentukan jumlah minimum bilangan kuadrat sempurna (1, 4, 9, 16, 25, ...)
yang jika dijumlahkan menghasilkan tepat N.
Setiap bilangan kuadrat boleh digunakan berkali-kali tanpa batas.

INPUT FORMAT:
Satu bilangan bulat N.

OUTPUT FORMAT:
Satu bilangan bulat: jumlah minimum bilangan kuadrat pembentuk N.

CONSTRAINTS:
1 <= N <= 100.000

SAMPLE INPUT 1:
12

SAMPLE OUTPUT 1:
3
(Penjelasan: 12 = 4 + 4 + 4)

SAMPLE INPUT 2:
13

SAMPLE OUTPUT 2:
2
(Penjelasan: 13 = 4 + 9)

SAMPLE INPUT 3:
1

SAMPLE OUTPUT 3:
1
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // TODO: Selesaikan dengan Coin Change Minimum
    // "Koin" yang tersedia adalah k^2 <= n.
    // Inisialisasi vector dp(n + 1, INF), dp[0] = 0.
    // Transisi: dp[i] = min(dp[i], dp[i - k*k] + 1).

    return 0;
}
