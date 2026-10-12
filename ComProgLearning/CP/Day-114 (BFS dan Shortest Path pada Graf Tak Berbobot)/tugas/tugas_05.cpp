/*
============================================================
📋 TUGAS 05: Rekonstruksi Path Terpendek
============================================================
Source: Original
Difficulty: Easy-Medium
Topics: BFS, shortest path, path reconstruction, prev array

PROBLEM:
Diberikan graph tidak berarah tidak berbobot dengan n node
dan m edge. Diberikan sumber S dan tujuan T.
Cetak:
1. Panjang path terpendek dari S ke T
2. Salah satu path terpendek (node-node dari S ke T)

Jika tidak ada path, cetak "TIDAK ADA PATH".

INPUT FORMAT:
- Baris 1: dua integer n, m
- m baris berikutnya: dua integer u v
- Baris terakhir: dua integer S, T

OUTPUT FORMAT:
- Baris 1: "Panjang: X" (X = jumlah edge)
- Baris 2: node-node path dari S ke T, dipisah " -> "
  Atau "TIDAK ADA PATH" jika tidak ada jalur

CONSTRAINTS:
- 2 ≤ n ≤ 10^5
- 1 ≤ m ≤ 2×10^5

SAMPLE INPUT 1:
6 6
1 2
1 3
2 4
3 4
4 5
5 6
1 6

SAMPLE OUTPUT 1:
Panjang: 4
1 -> 2 -> 4 -> 5 -> 6

SAMPLE INPUT 2:
4 2
1 2
3 4
1 4

SAMPLE OUTPUT 2:
TIDAK ADA PATH

NOTE: Simpan prev[v] = u saat BFS (parent v).
      Rekonstruksi: trace dari T ke S via prev[], balik hasilnya.
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
