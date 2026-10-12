/*
============================================================
📋 TUGAS 07: Alien Dictionary
============================================================
Source: LC 269
Difficulty: Medium
Topics: model graf dari data, Kahn leksikografis

PROBLEM:
Diberi N kata yang sudah terurut menurut alfabet suatu bahasa asing. Cetak
urutan huruf yang konsisten dan memuat semua huruf yang muncul. Jika ada
beberapa jawaban, cetak yang terkecil menurut alfabet Latin. Jika datanya
mustahil, cetak baris kosong.

INPUT FORMAT:
- Baris 1: N
- N baris: kata (huruf kecil 'a'..'z')

OUTPUT FORMAT:
- satu string

CONSTRAINTS:
- 1 <= N <= 1000, panjang kata <= 20

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
3                      abcd
abc
abd
b
Penjelasan: "abc" vs "abd" -> c sebelum d. "abd" vs "b" -> a sebelum b.

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
2                      ba
ba
ab
Penjelasan: beda pertama di posisi 0 -> b sebelum a.

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
1                      abz
zab
Penjelasan: tidak ada batasan sama sekali -> alfabetis Latin biasa.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // Ingat kasus prefiks: kata panjang muncul sebelum prefiksnya -> mustahil.
    // Saring edge ganda agar indeg tidak dihitung berlebih.
    return 0;
}
