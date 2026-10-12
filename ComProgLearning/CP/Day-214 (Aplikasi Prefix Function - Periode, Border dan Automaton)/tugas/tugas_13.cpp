/*
============================================================
📋 TUGAS 13: Om Nom dan Kalung
============================================================
Source: CF 526D
Difficulty: Hard
Topics: periodisitas lanjut

PROBLEM:
Diberikan string S dan bilangan K. Untuk setiap prefiks S sepanjang i,
tentukan apakah prefiks tersebut dapat ditulis sebagai A^K + A' di mana
A' adalah awalan dari A (boleh kosong) dan A tidak kosong. Cetak string
berisi '1' atau '0' sepanjang |S| sebagai jawabannya.

INPUT FORMAT:
- Baris pertama: n dan K
- Baris kedua: string S

OUTPUT FORMAT:
- Satu baris berisi n karakter '0'/'1'

CONSTRAINTS:
- 1 <= n <= 10^6
- 1 <= K <= 10^6

SAMPLE INPUT 1:
7 2
bcabcab

SAMPLE OUTPUT 1:
0000011
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Untuk tiap prefiks, periode terkecil p = i - pi[i-1]. Cek apakah i / p >= K setelah menangani sisa bagi.

    return 0;
}
