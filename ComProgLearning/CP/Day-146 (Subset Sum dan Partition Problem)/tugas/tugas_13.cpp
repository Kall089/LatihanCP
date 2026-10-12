/*
============================================================
📋 TUGAS 13: Small Negative Numbers
============================================================
Source: Practice
Difficulty: Hard
Topics: subset sum with offset

PROBLEM:
Diberikan N bilangan yang boleh negatif, nol, atau positif, dan target S.
Tentukan apakah ada subset yang jumlahnya tepat S. Setiap elemen boleh dipakai
paling banyak sekali.

INPUT FORMAT:
- Baris pertama: N dan S
- Baris kedua: N bilangan A[i]

OUTPUT FORMAT:
- YES atau NO

CONSTRAINTS:
- 1 <= N <= 60
- -1000 <= A[i] <= 1000
- -30000 <= S <= 30000

SAMPLE INPUT 1:
5 1
-7 -3 -2 5 8

SAMPLE OUTPUT 1:
YES

HINT:
Sum bisa negatif, jadi index array perlu offset. Rentang sum minimum adalah
jumlah semua elemen negatif, dan maksimum adalah jumlah semua elemen positif.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Hitung min_sum dan max_sum, gunakan offset agar sum negatif bisa jadi index.

    return 0;
}
