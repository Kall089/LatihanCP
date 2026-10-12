/*
============================================================
📋 TUGAS 13: Minimum Stack
============================================================
Source: Original
Difficulty: Hard
Topics: stack, design

PROBLEM:
Implementasikan struktur data MinStack yang mendukung operasi berikut
semua dalam O(1):
- PUSH x   → push x ke stack
- POP      → hapus elemen teratas
- TOP      → tampilkan elemen teratas
- GETMIN   → tampilkan elemen minimum dalam stack

INPUT FORMAT:
- Baris 1: integer q (jumlah operasi)
- q baris: "PUSH x", "POP", "TOP", atau "GETMIN"

OUTPUT FORMAT:
- Untuk setiap TOP atau GETMIN: satu baris output

CONSTRAINTS:
- 1 ≤ q ≤ 10^5
- -10^9 ≤ x ≤ 10^9
- POP/TOP/GETMIN hanya dipanggil saat stack tidak kosong

SAMPLE INPUT 1:
7
PUSH 5
PUSH 3
PUSH 7
GETMIN
POP
GETMIN
TOP

SAMPLE OUTPUT 1:
3
3
5

SAMPLE INPUT 2:
5
PUSH -2
PUSH 0
PUSH -3
GETMIN
POP

SAMPLE OUTPUT 2:
-3

NOTE: Gunakan dua stack: satu untuk elemen, satu untuk minimum saat ini.
      min_stack.top() selalu merupakan minimum dari stack utama.
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
