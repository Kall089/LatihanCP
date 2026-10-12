/*
============================================================
📋 TUGAS 10: Sum of All Subset Sums
============================================================
Source: Original
Difficulty: Medium
Topics: bitmask enumeration, math, contribution technique

PROBLEM:
Diberikan array a[] dengan n elemen. Untuk setiap mask dari 0 sampai
(1<<n)-1, definisikan f(mask) = jumlah a[i] di mana bit ke-i aktif di mask.
Hitung total dari semua f(mask), yaitu: Σ f(mask) untuk mask = 0..2^n-1.

INPUT FORMAT:
- Baris 1: integer n
- Baris 2: n buah integer a[0..n-1]

OUTPUT FORMAT:
- Satu integer: total dari semua f(mask)

CONSTRAINTS:
- 1 ≤ n ≤ 20
- 1 ≤ a[i] ≤ 100

SAMPLE INPUT 1:
3
1 2 4

SAMPLE OUTPUT 1:
28

SAMPLE INPUT 2:
2
3 5

SAMPLE OUTPUT 2:
16

NOTE: Untuk n=3, a=[1,2,4]:
      f(000)=0, f(001)=1, f(010)=2, f(011)=3,
      f(100)=4, f(101)=5, f(110)=6, f(111)=7 → total=28.
      Untuk n=2, a=[3,5]: f(00)=0, f(01)=3, f(10)=5, f(11)=8 → total=16.
      
      Cara naif O(n×2^n): iterasi semua mask dan bit.
      Cara cerdas O(n): tiap elemen a[i] muncul di 2^(n-1) mask.
      Total = (Σ a[i]) × 2^(n-1). Coba implementasikan keduanya!
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (long long& x : a) cin >> x;

    // Smart solution: each a[i] appears in exactly 2^(n-1) subsets
    // Total = (sum of all a[i]) * 2^(n-1)
    long long total = 0;
    for (long long x : a) total += x;
    cout << total * (1LL << (n - 1)) << '\n';

    /* Naive verification O(n * 2^n):
    long long naive = 0;
    for (int mask = 0; mask < (1 << n); mask++)
        for (int i = 0; i < n; i++)
            if ((mask >> i) & 1) naive += a[i];
    assert(naive == total * (1LL << (n-1)));
    */
    return 0;
}
