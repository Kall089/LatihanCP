/*
============================================================
📋 TUGAS 14: Minimum Absolute Difference Pair (Multiset)
============================================================
Source: Classic
Difficulty: Hard
Topics: multiset, adjacent elements, dynamic insert

PROBLEM:
Diberikan N bilangan satu per satu. Setelah SETIAP bilangan
dimasukkan (mulai dari bilangan ke-2), cetak MINIMUM ABSOLUTE
DIFFERENCE antara dua elemen manapun dari semua yang sudah masuk.

INPUT:
- Baris pertama: integer N
- Baris kedua: N buah integer

OUTPUT:
- (N-1) integer: min abs diff setelah insert ke-2, ke-3, ..., ke-N

CONSTRAINTS:
- 2 ≤ N ≤ 200,000
- 1 ≤ a[i] ≤ 1,000,000,000

SAMPLE INPUT:
5
5 1 3 2 4

SAMPLE OUTPUT:
4 2 1 1

NOTE:
- After [1,5]: min diff = |5-1| = 4
- After [1,3,5]: min diff = |3-1| = 2
- After [1,2,3,5]: min diff = |2-1| = 1
- After [1,2,3,4,5]: min diff = 1 (multiple pairs)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Hint: Maintain multiset + track current minimum.
    //       Saat insert x, cek diff dengan predecessor & successor.
    //       Update min jika lebih kecil.

    return 0;
}
