/*
============================================================
📋 TUGAS 09: Antrian Paling Sedikit Operasi
============================================================
Source: Original
Difficulty: Hard
Topics: BFS, queue, state space

PROBLEM:
Diberikan bilangan bulat start dan target (0 ≤ keduanya ≤ 10^5).
Setiap langkah kamu bisa: ×2 atau -1.
Hitung jumlah operasi minimum untuk mencapai target dari start.

INPUT FORMAT:
- Satu baris: dua integer start dan target

OUTPUT FORMAT:
- Satu baris: integer (minimum operasi)

CONSTRAINTS:
- 0 ≤ start, target ≤ 10^5

SAMPLE INPUT 1:
3 12

SAMPLE OUTPUT 1:
3

SAMPLE INPUT 2:
4 1

SAMPLE OUTPUT 2:
3

NOTE: BFS dengan state = nilai saat ini.
      Dari state x: bisa ke 2x atau x-1 (jika >= 0).
      Hindari nilai di luar batas [0, 2×target] untuk mencegah infinite loop.
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
