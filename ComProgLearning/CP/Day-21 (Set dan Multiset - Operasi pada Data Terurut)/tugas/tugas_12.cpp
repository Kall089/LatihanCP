/*
============================================================
📋 TUGAS 12: Subarray with Given Sum (Map + Prefix Sum)
============================================================
Source: Classic
Difficulty: Hard
Topics: unordered_map, prefix sum

PROBLEM:
Diberikan array N bilangan bulat (BISA NEGATIF) dan target S.
Hitung berapa banyak SUBARRAY (contiguous) yang jumlahnya = S.

INPUT:
- Baris pertama: dua integer N dan S
- Baris kedua: N buah integer

OUTPUT:
- Satu integer: jumlah subarray dengan sum = S

CONSTRAINTS:
- 1 ≤ N ≤ 200,000
- -1,000,000,000 ≤ a[i] ≤ 1,000,000,000
- -10^15 ≤ S ≤ 10^15

SAMPLE INPUT:
5 5
1 2 3 -1 6

SAMPLE OUTPUT:
3

SAMPLE INPUT 2:
4 0
1 -1 1 -1

SAMPLE OUTPUT 2:
4

NOTE: Sample 1: subarray [2,3], [1,2,3,-1], [3,-1,6-3=no...]
      Sebenarnya: [1,2,3,-1]=(5), [2,3]=(5), [-1,6]=(5) → 3
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Hint: prefix_sum[j] - prefix_sum[i] = S
    //       → cari berapa prefix_sum[i] = prefix_sum[j] - S yang sudah muncul
    //       Gunakan map<long long, int> untuk track prefix sum frequency

    return 0;
}
