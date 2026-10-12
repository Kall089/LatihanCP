/*
============================================================
📋 TUGAS 11: Range Update dan Single Point Query 2D
============================================================
Source: Original
Difficulty: Hard
Topics: Difference Array 2D

PROBLEM:
Diberikan matriks N × M yang awalnya berisi 0.
Kamu harus memproses Q buah operasi yang terdiri dari 2 jenis:
- Tipe 1: `1 r1 c1 r2 c2 val` -> Tambahkan `val` ke semua sel di submatriks (r1, c1) ke (r2, c2).
- Tipe 2: `2 r c` -> Cetak nilai terkini pada sel (r, c).

Catatan: Operasi tipe 2 bisa dipanggil di antara operasi tipe 1!
Jika jumlah query Tipe 2 sedikit (misal setelah semua update), kita bisa rekonstruksi.
Namun untuk masalah ini: Semua update Tipe 1 diberikan TERLEBIH DAHULU, lalu diikuti oleh semua query Tipe 2.

INPUT FORMAT:
- Baris 1: N M U Q (1 ≤ N, M ≤ 1000, 1 ≤ U, Q ≤ 10^5)
  (U = jumlah update Tipe 1, Q = jumlah query Tipe 2)
- U baris berikutnya: r1 c1 r2 c2 val
- Q baris berikutnya: r c

OUTPUT FORMAT:
- Q baris: nilai sel (r, c) setelah U update.

CONSTRAINTS:
- 1 ≤ N, M ≤ 1000
- 1 ≤ U, Q ≤ 10^5

SAMPLE INPUT 1:
3 3 2 2
1 1 2 2 10
2 2 3 3 5
2 2
3 1

SAMPLE OUTPUT 1:
15
0
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Hint: Gunakan Difference Array 2D, rekonstruksi 1x di akhir update, lalu jawab Q query O(1)

    return 0;
}
