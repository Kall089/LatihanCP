/*
============================================================
📋 TUGAS 11: Largest Rectangle Sum from Histogram
============================================================
Source: Original
Difficulty: Hard
Topics: stack, histogram, prefix sum

PROBLEM:
Diberikan histogram dengan n batang tinggi h[i]. Temukan subrectangle
(bisa berupa satu atau lebih batang bersebelahan) dengan jumlah
area yang diselimuti (sum of heights dalam range) terbesar.

INPUT FORMAT:
- Baris 1: integer n
- Baris 2: n integer (tinggi batang)

OUTPUT FORMAT:
- Satu baris: long long (maksimum sum of heights dalam range)

CONSTRAINTS:
- 1 ≤ n ≤ 10^5
- 0 ≤ h[i] ≤ 10^9

SAMPLE INPUT 1:
5
1 3 2 4 1

SAMPLE OUTPUT 1:
10

SAMPLE INPUT 2:
4
5 2 3 1

SAMPLE OUTPUT 2:
10

NOTE: Ini adalah masalah Maximum Subarray sum (Kadane's algorithm) pada array h[].
      Jawaban = max sum subarray dari h[] (semua nilai non-negatif → seluruh array bisa jadi jawaban).
      Tapi jika ada nilai negatif: Kadane. Untuk n kecil bisa O(n^2).
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
