/*
============================================================
  Exercise 1: Bit Operations Dasar
============================================================
Implementasikan 7 fungsi operasi bitmask standar, kemudian
gunakan untuk memecahkan soal berikut:

Diberikan sebuah bilangan N dan q buah query. Tiap query adalah
salah satu dari:
  CHECK i   -> cetak 1 jika bit ke-i aktif, 0 jika tidak
  SET i     -> set bit ke-i menjadi 1
  CLEAR i   -> set bit ke-i menjadi 0
  TOGGLE i  -> balik nilai bit ke-i
  COUNT     -> cetak jumlah bit yang aktif
  LOWBIT    -> cetak nilai lowest set bit (0 jika N=0)
  REMOVE    -> hapus lowest set bit dari N

Setelah semua query, cetak nilai N akhir.

📏 CONSTRAINTS:
  - 0 ≤ N ≤ 10^9
  - 1 ≤ q ≤ 100
  - 0 ≤ i ≤ 29  (sehingga 1<<i tidak overflow int)

📎 SAMPLE INPUT:
  10 7
  CHECK 1
  SET 2
  TOGGLE 3
  CLEAR 1
  COUNT
  LOWBIT
  REMOVE

📎 SAMPLE OUTPUT:
  1
  6
  4
  2
  (N akhir = 4)

💡 HINT:
  - Bit ke-i diperiksa dengan (N >> i) & 1
  - Set: N |= (1 << i)
  - Clear: N &= ~(1 << i)
  - Toggle: N ^= (1 << i)
  - Count: __builtin_popcount(N)
  - Lowbit: N & -N
  - Remove lowest: N &= (N-1)

🎯 Learning Goals:
  Hafal dan bisa implementasi semua 7 operasi bitmask dasar.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, q;
    cin >> N >> q;

    while (q--) {
        string op;
        cin >> op;

        if (op == "CHECK") {
            // TODO: baca i, cetak 1 jika bit ke-i aktif, 0 jika tidak
        } else if (op == "SET") {
            // TODO: baca i, set bit ke-i
        } else if (op == "CLEAR") {
            // TODO: baca i, clear bit ke-i
        } else if (op == "TOGGLE") {
            // TODO: baca i, toggle bit ke-i
        } else if (op == "COUNT") {
            // TODO: cetak jumlah bit aktif
        } else if (op == "LOWBIT") {
            // TODO: cetak nilai lowest set bit (0 jika N=0)
        } else if (op == "REMOVE") {
            // TODO: hapus lowest set bit dari N
        }
    }

    cout << "(N akhir = " << N << ")\n";
    return 0;
}
