/*
============================================================
📋 TUGAS 06: Pengecatan Barisan Rumah (Paint House)
============================================================
Source: LeetCode 256 / Classic
Difficulty: Easy-Medium
Topics: State Design, Minimization DP

PROBLEM:
Terdapat barisan N rumah yang harus dicat. Tersedia 3 pilihan warna: Merah (0), Biru (1), atau Hijau (2).
Mengecat rumah ke-i dengan warna j membutuhkan biaya cost[i][j].
Aturan: Tidak boleh ada dua rumah yang berdampingan dicat dengan warna yang sama!
Hitung biaya total minimum untuk mengecat seluruh N rumah.

INPUT FORMAT:
Baris pertama: N
N baris berikutnya: 3 bilangan bulat cost[i][0], cost[i][1], cost[i][2]

OUTPUT FORMAT:
Satu bilangan bulat: biaya minimum mengecat seluruh rumah.

CONSTRAINTS:
1 <= N <= 100.000
1 <= cost[i][j] <= 10.000

SAMPLE INPUT 1:
3
17 2 17
16 16 5
14 3 19

SAMPLE OUTPUT 1:
10
(Penjelasan: Rumah 0 cat Biru (2), Rumah 1 cat Hijau (5), Rumah 2 cat Biru (3). Total = 2 + 5 + 3 = 10.)

SAMPLE INPUT 2:
1
7 6 2

SAMPLE OUTPUT 2:
2
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<vector<int>> cost(n, vector<int>(3));
    for (int i = 0; i < n; i++) {
        cin >> cost[i][0] >> cost[i][1] >> cost[i][2];
    }

    // TODO: Implementasikan DP tabulasi dengan rolling variable (O(1) space)
    // dp[j] = biaya minimum sampai rumah saat ini dengan warna j

    return 0;
}
