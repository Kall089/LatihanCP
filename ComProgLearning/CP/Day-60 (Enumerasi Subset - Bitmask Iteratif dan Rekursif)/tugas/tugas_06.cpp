/*
============================================================
📋 TUGAS 06: Count Subsets with Even Sum
============================================================
Source: Original
Difficulty: Easy
Topics: bitmask enumeration, subset sum, enumerate 2^n

PROBLEM:
Diberikan array a[] dengan n elemen bilangan bulat positif.
Hitung berapa banyak subset (termasuk empty set) yang total
jumlah elemennya adalah genap.

INPUT FORMAT:
- Baris 1: integer n
- Baris 2: n buah integer a[0..n-1]

OUTPUT FORMAT:
- Satu integer: jumlah subset dengan sum genap

CONSTRAINTS:
- 1 ≤ n ≤ 20
- 1 ≤ a[i] ≤ 10^6

SAMPLE INPUT 1:
3
1 2 3

SAMPLE OUTPUT 1:
4

SAMPLE INPUT 2:
4
2 4 6 8

SAMPLE OUTPUT 2:
16

NOTE: Untuk n=3, a=[1,2,3]: subset dengan sum genap adalah
      {} (sum=0), {2} (sum=2), {1,3} (sum=4), {1,2,3} (sum=6) → 4 subset.
      Untuk n=4 dengan semua elemen genap: semua 2^4=16 subset memiliki sum genap.
      Iterasi semua mask dari 0 sampai (1<<n)-1 dengan O(n * 2^n).
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    int cnt = 0;
    // Enumerate all 2^n subsets including empty set (mask=0, sum=0 is even)
    for (int mask = 0; mask < (1 << n); mask++) {
        int sum = 0;
        for (int i = 0; i < n; i++)
            if ((mask >> i) & 1) sum += a[i];
        if (sum % 2 == 0) cnt++;
    }

    cout << cnt << '\n';
    return 0;
}
