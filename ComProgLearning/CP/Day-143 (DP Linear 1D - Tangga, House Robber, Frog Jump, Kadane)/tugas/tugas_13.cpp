/*
============================================================
📋 TUGAS 13: House Robber dengan Rekonstruksi
============================================================
Source: Varian latihan
Difficulty: Medium
Topics: telusuri balik array dp

PROBLEM:
Selain total maksimum, cetak juga indeks rumah mana saja yang dirampok
(0-indexed, menaik). Jika ada beberapa jawaban optimal, cetak yang indeks
pertamanya paling kecil.

INPUT FORMAT:
- Baris 1: N
- Baris 2: N bilangan
OUTPUT FORMAT:
- Baris 1: total
- Baris 2: indeks yang dipilih
CONSTRAINTS: 1 <= N <= 2*10^5

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
4                      4
2 1 1 2                0 3

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
5                      12
2 7 9 3 1              0 2 4
Penjelasan: 2 + 9 + 1 = 12.

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
1                      5
5                      0
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // Butuh array dp PENUH (rolling variable tidak bisa direkonstruksi).
    // Telusuri dari belakang: kalau dp[i] == dp[i-1] berarti rumah i-1 tidak
    // dirampok; kalau tidak, ia dirampok dan lompat dua langkah.
    return 0;
}
