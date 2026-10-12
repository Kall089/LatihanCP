/*
============================================================
📋 TUGAS 12: Prefix Money Sums
============================================================
Source: Practice
Difficulty: Medium-Hard
Topics: prefix DP, reachable count

PROBLEM:
Diberikan N koin. Setelah membaca koin ke-i, cetak berapa banyak jumlah
positif berbeda yang bisa dibentuk hanya memakai koin 1..i.

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N nilai koin

OUTPUT FORMAT:
- Satu baris berisi N bilangan. Bilangan ke-i adalah banyak reachable sum
  positif setelah prefix i.

CONSTRAINTS:
- 1 <= N <= 200
- 1 <= A[i] <= 1000

SAMPLE INPUT 1:
4
4 2 5 2

SAMPLE OUTPUT 1:
1 3 7 9

HINT:
Setelah setiap update elemen, kamu perlu tahu berapa banyak bit/sum positif
yang menyala. Bisa dihitung dengan scan atau bitset count.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Update reachable per prefix dan cetak jumlah state positif yang true.

    return 0;
}
