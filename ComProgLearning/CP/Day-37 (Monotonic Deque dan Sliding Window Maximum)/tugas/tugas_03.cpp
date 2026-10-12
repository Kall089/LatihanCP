/*
============================================================
📋 TUGAS 03: Sliding Window Average
============================================================
Source: Original
Difficulty: Easy
Topics: queue, sliding window

PROBLEM:
Diberikan stream angka desimal dan window size k.
Hitung rata-rata setiap window berukuran k.
Output dengan presisi 5 angka desimal.

INPUT FORMAT:
- Baris 1: dua integer n dan k
- n baris berikutnya: satu bilangan real per baris

OUTPUT FORMAT:
- (n-k+1) baris: rata-rata tiap window

CONSTRAINTS:
- 1 ≤ k ≤ n ≤ 10^4
- -10^6 ≤ val ≤ 10^6

SAMPLE INPUT 1:
5 3
1.0
2.0
3.0
4.0
5.0

SAMPLE OUTPUT 1:
2.00000
3.00000
4.00000

SAMPLE INPUT 2:
4 2
10.0
20.0
30.0
40.0

SAMPLE OUTPUT 2:
15.00000
25.00000
35.00000

NOTE: Gunakan queue<double> ukuran k. Jaga running sum.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO
    return 0;
}
