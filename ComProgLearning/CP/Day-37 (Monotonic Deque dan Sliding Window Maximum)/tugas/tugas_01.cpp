/*
============================================================
📋 TUGAS 01: Hot Queue — Prioritas Dinamis
============================================================
Source: Original
Difficulty: Easy
Topics: queue, simulation

PROBLEM:
Simulasikan antrian dengan dua kelas: VIP dan regular.
VIP selalu dilayani sebelum regular. Tiap siklus layani 1 VIP (jika ada)
lalu 2 regular. Cetak urutan pelayanan.

INPUT FORMAT:
- Baris 1: integer q
- q baris: "VIP nama" atau "REG nama"
- Setelah semua masuk, layani semua (cetak urutan)

OUTPUT FORMAT:
- Nama per baris (urutan dilayani)

CONSTRAINTS:
- 1 ≤ q ≤ 100
- Nama panjang ≤ 20

SAMPLE INPUT 1:
5
REG A
VIP B
REG C
VIP D
REG E

SAMPLE OUTPUT 1:
B D A C E

SAMPLE INPUT 2:
3
REG X
REG Y
REG Z

SAMPLE OUTPUT 2:
X Y Z

NOTE: Dua queue terpisah: queue<string> vip, reg.
      Siklus: pop 1 VIP (jika ada), lalu pop 2 REG (jika ada).
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
