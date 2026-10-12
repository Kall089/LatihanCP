/*
============================================================
📋 TUGAS 11: Banyak Subarray dengan Jumlah dalam Rentang
============================================================
Source: Original
Difficulty: Hard
Topics: prefix + BIT/ordered set

PROBLEM:
Diberikan array N bilangan (boleh negatif) dan dua bilangan A dan B.
Hitung berapa banyak subarray yang jumlahnya berada di antara A dan B
(inklusif).

INPUT FORMAT:
- Baris pertama: N, A, dan B
- Baris kedua: N bilangan

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 2*10^5
- -10^14 <= A <= B <= 10^14

SAMPLE INPUT 1:
3 1 5
1 2 3

SAMPLE OUTPUT 1:
5
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Untuk tiap r, hitung berapa pre[l] yang berada di [pre[r+1]-B, pre[r+1]-A]. Butuh struktur terurut; pikirkan merge sort (Day 44) atau BIT + kompresi (Day 38 + 170).

    return 0;
}
