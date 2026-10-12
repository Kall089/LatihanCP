/*
============================================================
📋 TUGAS 15: Queue Reconstruction dengan Waktu
============================================================
Source: Original
Difficulty: Medium
Topics: queue, simulation, greedy

PROBLEM:
Diberikan n customer dengan arrival time dan patience time.
Customer datang tepat pada arrival time dan pergi jika sudah menunggu
lebih dari patience time tanpa dilayani.
Server melayani 1 customer per unit waktu. Hitung customer yang dilayani.

INPUT FORMAT:
- Baris 1: integer n
- n baris: dua integer arrival dan patience (1-indexed)

OUTPUT FORMAT:
- Satu baris: integer (jumlah customer dilayani)

CONSTRAINTS:
- 1 ≤ n ≤ 10^5
- 0 ≤ arrival[i] ≤ 10^9 (tidak harus terurut)
- 1 ≤ patience[i] ≤ 10^5

SAMPLE INPUT 1:
3
1 3
2 1
3 2

SAMPLE OUTPUT 1:
2

SAMPLE INPUT 2:
2
0 5
0 1

SAMPLE OUTPUT 2:
2

NOTE: Sort berdasarkan arrival. Simulasikan waktu.
      Layani customer yang belum habis patience (arrival + patience > waktu_mulai).
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
