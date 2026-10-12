/*
============================================================
📋 TUGAS 14: Priority Queue — Huffman Encoding Cost
============================================================
Source: Classic Greedy
Difficulty: Hard
Topics: priority_queue (min heap), greedy

PROBLEM:
Diberikan N buah frekuensi karakter. Hitung minimum total cost
untuk membangun Huffman tree.

Cost = setiap kali merge dua node, cost bertambah sebesar jumlah
kedua frekuensi. Total cost = sum of all merge costs.

Greedy: selalu merge dua node dengan frekuensi TERKECIL.

INPUT:
- Baris pertama: integer N
- Baris kedua: N integer (frekuensi)

OUTPUT:
- Satu integer: minimum total cost

CONSTRAINTS:
- 2 ≤ N ≤ 200,000
- 1 ≤ freq[i] ≤ 1,000,000,000

SAMPLE INPUT:
4
5 10 20 15

SAMPLE OUTPUT:
95

NOTE: Merge 5+10=15 (cost=15). Merge 15+15=30 (cost=30). Merge 20+30=50 (cost=50).
      Total = 15+30+50 = 95.

SAMPLE INPUT 2:
2
10 20

SAMPLE OUTPUT 2:
30
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Hint: Min heap. While size > 1: pop two smallest, merge, push sum, add to cost.

    return 0;
}
