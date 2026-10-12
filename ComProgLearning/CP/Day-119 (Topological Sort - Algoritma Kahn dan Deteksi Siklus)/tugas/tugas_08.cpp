/*
============================================================
📋 TUGAS 08: Fox And Names
============================================================
Source: CF 510C
Difficulty: Medium
Topics: model graf, Kahn atas 26 huruf

PROBLEM:
Diberi N nama. Tentukan suatu urutan 26 huruf sehingga daftar nama tersebut
terurut menaik menurut urutan itu. Cetak permutasi 26 huruf mana pun yang
valid, atau "Impossible".

INPUT FORMAT:
- Baris 1: N
- N baris: nama (huruf kecil)

OUTPUT FORMAT:
- string 26 huruf, atau Impossible

CONSTRAINTS:
- 1 <= N <= 100, panjang nama <= 100

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
3                      bcdefghijklmnopqrstuvwxyza
rivest
shamir
adleman
Penjelasan: syaratnya r sebelum s, dan s sebelum a. Output mana pun yang
memenuhi diterima.

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
2                      Impossible
cart
car
Penjelasan: "car" adalah prefiks "cart" tetapi muncul BELAKANGAN -> mustahil.

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
1                      abcdefghijklmnopqrstuvwxyz
solo
Penjelasan: tidak ada batasan; permutasi apa pun boleh.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // SEMUA 26 huruf harus muncul di output, termasuk yang tak pernah dipakai.
    return 0;
}
