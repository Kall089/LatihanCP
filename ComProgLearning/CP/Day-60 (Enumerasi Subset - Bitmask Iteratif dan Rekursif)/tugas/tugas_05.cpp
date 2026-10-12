/*
============================================================
📋 TUGAS 05: Power of Two Checker
============================================================
Source: Original
Difficulty: Easy
Topics: bitmask, power of two, bit trick

PROBLEM:
Diberikan T buah bilangan bulat tidak negatif N.
Untuk setiap N, tentukan apakah N adalah pangkat dua tepat
(yaitu N = 2^k untuk suatu k ≥ 0).
Bilangan 0 bukan pangkat dua.

INPUT FORMAT:
- Baris 1: integer T
- T baris berikutnya: satu integer N per baris

OUTPUT FORMAT:
- T baris: "YES" jika N adalah pangkat dua, "NO" jika bukan

CONSTRAINTS:
- 1 ≤ T ≤ 100000
- 0 ≤ N ≤ 10^18

SAMPLE INPUT 1:
5
0
1
7
8
1024

SAMPLE OUTPUT 1:
NO
YES
NO
YES
YES

SAMPLE INPUT 2:
4
3
4
16
1000000007

SAMPLE OUTPUT 2:
NO
YES
YES
NO

NOTE: N adalah pangkat dua jika N > 0 dan (N & (N-1)) == 0.
      Properti ini bekerja karena pangkat dua hanya punya tepat 1 bit aktif.
      Gunakan long long / unsigned long long untuk N ≤ 10^18.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        // Power of 2: n > 0 AND exactly one bit set
        if (n > 0 && (n & (n - 1)) == 0)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}
