/*
============================================================
📋 TUGAS 06: Subarray Sums II
============================================================
Source: CSES 1661
Difficulty: Medium
Topics: prefix + map

PROBLEM:
Diberikan array N bilangan (boleh negatif) dan target X. Hitung berapa banyak
subarray tidak kosong yang jumlahnya tepat X.

INPUT FORMAT:
- Baris pertama: N dan X
- Baris kedua: N bilangan

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 2*10^5
- -10^9 <= a[i] <= 10^9

SAMPLE INPUT 1:
5 7
2 -1 3 5 -2

SAMPLE OUTPUT 1:
2
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // freq[0] = 1, lalu hasil += freq[cur - X] sebelum freq[cur]++.

    return 0;
}
