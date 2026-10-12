/*
============================================================
📋 TUGAS 12: Assignment Problem (Bitmask DP)
============================================================
Source: Original
Difficulty: Hard
Topics: bitmask DP, assignment problem, dp[mask]

PROBLEM:
Terdapat n pekerja dan n tugas. cost[i][j] adalah biaya pekerja i
mengerjakan tugas j. Assign setiap pekerja tepat satu tugas
(dan setiap tugas tepat untuk satu pekerja) untuk meminimalkan
total biaya. Cetak biaya minimumnya.

INPUT FORMAT:
- Baris 1: integer n
- n baris berikutnya: n integer per baris (matriks cost[0..n-1][0..n-1])

OUTPUT FORMAT:
- Satu integer: total biaya minimum

CONSTRAINTS:
- 1 ≤ n ≤ 20
- 0 ≤ cost[i][j] ≤ 10^6

SAMPLE INPUT 1:
3
9 2 7
6 4 3
5 8 1

SAMPLE OUTPUT 1:
9

SAMPLE INPUT 2:
2
3 5
4 1

SAMPLE OUTPUT 2:
4

NOTE: Untuk sample 1: pekerja 0→tugas 1 (biaya 2), pekerja 1→tugas 0 (biaya 6),
      pekerja 2→tugas 2 (biaya 1) → total = 9.
      Untuk sample 2: pekerja 0→tugas 0 (3), pekerja 1→tugas 1 (1) → total=4.
      
      Hint DP:
        dp[mask] = biaya minimum untuk mengassign tugas kepada
                   pekerja ke-0 s/d popcount(mask)-1,
                   di mana bit j pada mask = tugas j sudah diassign.
        worker = __builtin_popcount(mask) (pekerja yang sedang giliran)
        Transisi: dp[mask|(1<<j)] = min(..., dp[mask] + cost[worker][j])
                  untuk setiap j yang belum di mask.
        Jawaban: dp[(1<<n)-1]
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO
    return 0;
}
