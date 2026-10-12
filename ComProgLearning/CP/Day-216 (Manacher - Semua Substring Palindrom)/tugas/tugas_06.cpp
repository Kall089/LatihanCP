/*
============================================================
📋 TUGAS 06: Potongan Palindrom Minimal
============================================================
Source: LeetCode 132 (varian)
Difficulty: Medium
Topics: manacher + DP

PROBLEM:
Bagi S menjadi potongan-potongan berurutan yang semuanya palindrom.
Cari jumlah potongan minimal.

INPUT FORMAT:
- Satu baris: string S

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= |S| <= 5000

SAMPLE INPUT 1:
abacaba

SAMPLE OUTPUT 1:
1
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // dp[i] = min(dp[j] + 1) untuk semua j dengan S[j..i-1] palindrom.

    return 0;
}
