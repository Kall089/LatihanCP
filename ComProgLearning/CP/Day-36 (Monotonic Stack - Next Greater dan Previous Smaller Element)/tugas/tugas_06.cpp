/*
============================================================
📋 TUGAS 06: Daily Temperatures
============================================================
Source: Original
Difficulty: Medium
Topics: stack, next greater element

PROBLEM:
Diberikan array suhu selama n hari. Untuk setiap hari, hitung berapa hari
yang harus menunggu hingga ada suhu yang lebih tinggi. Jika tidak ada, output 0.

INPUT FORMAT:
- Baris 1: integer n
- Baris 2: n integer (suhu)

OUTPUT FORMAT:
- n integer (hari tunggu)

CONSTRAINTS:
- 1 ≤ n ≤ 10^5
- 30 ≤ temp[i] ≤ 100

SAMPLE INPUT 1:
8
73 74 75 71 69 72 76 73

SAMPLE OUTPUT 1:
1 1 4 2 1 1 0 0

SAMPLE INPUT 2:
3
30 40 50

SAMPLE OUTPUT 2:
1 1 0

NOTE: Ini adalah variasi NGE di mana outputnya adalah selisih index.
      wait[i] = index(NGE[i]) - i. Gunakan monotonic stack.
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
