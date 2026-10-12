/*
============================================================
📋 TUGAS 8: Priority Queue — Merge K Sorted Arrays
============================================================
Source: Classic
Difficulty: Medium
Topics: priority_queue (min heap), merge

PROBLEM:
Diberikan K array yang SUDAH TERURUT. Gabungkan semuanya menjadi
satu array terurut.

INPUT:
- Baris pertama: integer K (jumlah array)
- Untuk setiap array:
  - Satu integer N_i (ukuran array ke-i)
  - N_i integer (elemen array, sorted ascending)

OUTPUT:
- Satu baris: semua elemen merged dalam urutan ascending

CONSTRAINTS:
- 1 ≤ K ≤ 1000
- 1 ≤ N_i ≤ 1000
- Total elemen ≤ 200,000
- 1 ≤ elemen ≤ 1,000,000,000

SAMPLE INPUT:
3
3
1 4 7
3
2 5 8
3
3 6 9

SAMPLE OUTPUT:
1 2 3 4 5 6 7 8 9
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Hint: Min heap of (value, array_idx, element_idx).
    //       Push first element of each array.
    //       Pop min, push next element from same array.

    return 0;
}
